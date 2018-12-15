#include "algorithm.h"
#include <iostream>

Algorithm::Algorithm(size_t particlesNumber, size_t particlesSize, size_t iterations, std::unique_ptr<DataSet> & ds, size_t objFunctionIdentifier, float vMax, float alpha, float beta, float fNumImportance)
	: particlesNumber(particlesNumber)
	, particlesSize(particlesSize)
	, particles()
	//, particles(particlesNumber, std::make_unique<Particle>(Particle(particlesSize)))		// ERROR !!!
	, bestKnownParticle(particlesSize)
	, iterations(iterations)
	, dataset(ds.get())
	, objFcnIdentifier(objFcnIdentifier)
	, vMax(vMax)
	, alpha(alpha)
	, beta(beta)
	, fNumImportance(fNumImportance)
{
	/*particles = std::vector<std::unique_ptr<Particle>>(particlesNumber, std::make_unique)
	particles = new Particle*[particlesNumber];*/
	//particles.clear();
	//for (size_t i = 0; i < particlesNumber; ++i)
	//{
	//	//particles[i] = new Particle(particlesSize);
	//	/*if (!bestKnownParticle)
	//		std::cout << "BestKnownParticle is nullptr, something went wrong" << std::endl;*/
	//	particles.push_back(std::make_unique<Particle>(Particle(particlesSize)));
	//	if (i == 0 || (objectiveFunction(particles[i].get()->getCurrentState()) < objectiveFunction(bestKnownParticle.getCurrentState())))
	//		bestKnownParticle = *(particles[i].get());
	//}
	refreshParticles();
}


Algorithm::~Algorithm()
{
	/*if (particles)
	{
		for (size_t i = 0; i < particlesNumber; ++i)
			delete particles[i];
		delete[] particles;
	}

	if (bestKnownParticle)
		delete bestKnownParticle;

	if (dataset)
		delete dataset;*/
}

void Algorithm::performOptimization()
{
	float objFcn;
	for (size_t it = 0; it < iterations; ++it)
	{
		std::cout << "iteration: " << (it + 1) << std::endl;
		for (size_t i = 0; i < particlesNumber; ++i)
		{
			particles[i]->updateParticleState(alpha, beta, vMax, bestKnownParticle.getCurrentState());
			objFcn = objectiveFunction(particles[i].get()->getCurrentState());
			if (objectiveFunction(particles[i].get()->getBestLocalState()) > objFcn)
			{
				particles[i].get()->makeCurrentStateBest();
				if (objectiveFunction(bestKnownParticle.getCurrentState()) > objFcn)
					bestKnownParticle = *(particles[i].get());		// !!!!!!!!
				else if (objectiveFunction(bestKnownParticle.getCurrentState()) == objFcn)
				{
					if (!bestParticlesHistory.size() || (bestParticlesHistory.size() && bestParticlesHistory.back() != bestKnownParticle))
					{
						bestParticlesHistory.push_back(bestKnownParticle);
						std::cout << "WRITING BEST SOLUTION TO MEMORY" << std::endl;
					}
					refreshParticles();
				}
			}
		}
		bestKnownParticle.printCurrentState();
		std::cout << "obj fcn: " << objectiveFunction(bestKnownParticle.getCurrentState()) << std::endl;
	}

	for (size_t i = 0; i < bestParticlesHistory.size(); ++i)
	{
		if (objectiveFunction(bestParticlesHistory[i].getCurrentState()) < objectiveFunction(bestKnownParticle.getCurrentState()))
			bestKnownParticle = bestParticlesHistory[i];
	}

	std::cout << "***************SOLUTION***************" << std::endl;
	bestKnownParticle.printCurrentState();
	std::cout << "obj fcn: " << objectiveFunction(bestKnownParticle.getCurrentState()) << std::endl;

	// xi is a vector of m features
	// Vmax should be probably 6
	//
	// initialize S particles with random components from {0, 1}
	//		initialize every particle's best position as it's initial position pi <-- xi
	//		if (f(pi) < f(g))
	//			update global best position g <-- pi
	//		initialize velocity of particle ???
	//
	// MAIN ALGORITHM:
	// while (NOT stop_criteria)
	//		foreach (particle)
	//			foreach (component d in 1,2,...,m)
	//				pick random numbers
	//				update velocity of particle vi,d <-- vi,d + fi*(pi,d - xi,d) + fi*(pg,d - xi,d)   ( fi is randomly generated)
	//			update particle position xi <-- xi + vi
	//			if (f(xi) < f(pi)
	//				update particle's best known position pi <-- xi
	//				if (f(pi) < f(g))
	//					update best known global position g <-- pi
}

float Algorithm::objectiveFunction(std::vector<pbit> state)
{
	// 1st idea
	// objective function value is computed as sum of all
	// covariances (each feature with every other) from set 
	// of "valid" features. Then the sum is divided by the 
	// number of covariances.

	// 2nd idea
	// check which parameters differ genders the most

	float functionValue = 0.0f;
	size_t validFeatures = 0;

	if (objFcnIdentifier == 0)
	{
		float sumValue = 0.0f;
		size_t howManyFeatures = 0;
		for (size_t i = 0; i < particlesSize; ++i)
		{
			if (state[i] == 1)
			{
				sumValue += dataset->meanDiffs[i];
				howManyFeatures++;
			}
		}
		//--validFeatures;
		//functionValue /= ((validFeatures + validFeatures * validFeatures) / 2);
		functionValue = -sumValue / howManyFeatures;
		functionValue += (howManyFeatures * functionValue * fNumImportance);
	}
	else if (objFcnIdentifier == 1)
	{
		float sumValue = 0.0f;
		size_t howManyFeatures = 0;
		for (size_t i = 0; i < particlesSize; ++i)
		{
			if (state[i] == 1)
			{
				sumValue += (dataset->meanDiffs[i] / dataset->stdDevDiffs[i]);
				howManyFeatures++;
			}
		}
		//--validFeatures;
		//functionValue /= ((validFeatures + validFeatures * validFeatures) / 2);
		functionValue = -sumValue / howManyFeatures;
		functionValue += (howManyFeatures * functionValue * fNumImportance);
	}
	return functionValue;
}

void Algorithm::printSolution()
{
	bestKnownParticle.printCurrentState();
	//bestKnownParticle->printCurrentState();
}

Particle Algorithm::getSolution()
{
	return bestKnownParticle;
}

void Algorithm::refreshParticles()
{
	particles.clear();
	for (size_t i = 0; i < particlesNumber; ++i)
	{
		particles.push_back(std::make_unique<Particle>(Particle(particlesSize)));
		if (i == 0 || (objectiveFunction(particles[i].get()->getCurrentState()) < objectiveFunction(bestKnownParticle.getCurrentState())))
			bestKnownParticle = *(particles[i].get());
	}
}


