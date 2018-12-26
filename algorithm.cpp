#include "algorithm.h"
#include <iostream>

Algorithm::Algorithm(size_t particlesNumber, size_t particlesSize, size_t iterations, std::unique_ptr<DataSet> & ds, size_t objFunctionIdentifier, float vMax, float alpha, float beta, float fNumImportance)
	: particlesNumber(particlesNumber)
	, particlesSize(particlesSize)
	, particles()
	, bestKnownParticle(particlesSize)
	, iterations(iterations)
	, dataset(ds.get())
	, objFcnIdentifier(objFcnIdentifier)
	, vMax(vMax)
	, alpha(alpha)
	, beta(beta)
	, fNumImportance(fNumImportance)
{
	refreshParticles();
}


Algorithm::~Algorithm()
{
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
					}
					refreshParticles();
				}
			}
		}
		std::cout << "Current solution: " << std::endl << objectiveFunction(bestKnownParticle.getCurrentState()) << std::endl;
	}

	for (size_t i = 0; i < bestParticlesHistory.size(); ++i)
	{
		if (objectiveFunction(bestParticlesHistory[i].getCurrentState()) < objectiveFunction(bestKnownParticle.getCurrentState()))
			bestKnownParticle = bestParticlesHistory[i];
	}

	std::cout << "***************SOLUTION***************" << std::endl;
	bestKnownParticle.printCurrentState();
	std::cout << "obj fcn: " << objectiveFunction(bestKnownParticle.getCurrentState()) << std::endl;
}

float Algorithm::objectiveFunction(std::vector<pbit> state)
{
	float functionValue = 0.0f;

	if (objFcnIdentifier == 0)
	{
		float sumValue = 0.0f;
		size_t howManyFeatures = 0;
		for (size_t i = 0; i < particlesSize; ++i)
		{
			if (state[i] == 1)
			{
				sumValue += (dataset->meanDiffs[i] / ((dataset->stdDeviationClassData[0][i] + dataset->stdDeviationClassData[1][i]) / dataset->meanData[i]));
				howManyFeatures++;
			}
		}
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
				sumValue += dataset->meanDiffs[i];
				howManyFeatures++;
			}
		}
		functionValue = -sumValue / howManyFeatures;
		functionValue += (howManyFeatures * functionValue * fNumImportance);
	}
	return functionValue;
}

void Algorithm::printSolution()
{
	bestKnownParticle.printCurrentState();
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


