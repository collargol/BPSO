#include "algorithm.h"
#include <iostream>

Algorithm::Algorithm(size_t pNumber, size_t pSize, size_t iters, DataSet * ds, float vMax, float alpha, float beta)
	: particlesNumber(pNumber)
	, particlesSize(pSize)
	, iterations(iters)
	, dataset(ds)
	, vMax(vMax)
	, alpha(alpha)
	, beta(beta)
{
	bestKnownParticle = new Particle(particlesSize);
	
	particles = new Particle*[particlesNumber];
	for (size_t i = 0; i < particlesNumber; ++i)
	{
		particles[i] = new Particle(particlesSize);
		if (!bestKnownParticle)
			std::cout << "BestKnownParticle is nullptr, something went wrong" << std::endl;
		if (objectiveFunction(particles[i]) < objectiveFunction(bestKnownParticle))
			(*bestKnownParticle) = (*particles[i]);
	}

	for (size_t i = 0; i < particlesNumber; ++i)
		particles[i]->setBestGlobalState(bestKnownParticle);
}

Algorithm::~Algorithm()
{
	if (particles)
	{
		for (size_t i = 0; i < particlesNumber; ++i)
			delete particles[i];
		delete[] particles;
	}

	if (bestKnownParticle)
		delete bestKnownParticle;

	if (dataset)
		delete dataset;
}

void Algorithm::bindDataSet(DataSet * ds)
{
	if (ds)
		dataset = ds;
}

void Algorithm::performOptimization()
{
	for (size_t it = 0; it < iterations; ++it)
	{
		std::cout << "iteration: " << (it + 1) << std::endl;
		for (size_t i = 0; i < particlesNumber; ++i)
		{
			particles[i]->updateParticleState(alpha, beta, vMax);
			if (objectiveFunction(particles[i], true) > objectiveFunction(particles[i]))
				particles[i]->updateBestLocalState();
			if (objectiveFunction(particles[i]) < objectiveFunction(bestKnownParticle))
			{
				(*bestKnownParticle) = (*particles[i]);		// !!!!!!!!
				bestKnownParticle->setBestGlobalState(bestKnownParticle);
				for (size_t p = 0; p < particlesNumber; ++p)
					particles[p]->setBestGlobalState(bestKnownParticle);
			}
		}
		bestKnownParticle->printCurrentState();
		std::cout << "obj fcn: " << objectiveFunction(bestKnownParticle) << std::endl;
	}

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

float Algorithm::objectiveFunction(Particle * particle, bool useBestLocal)
{
	// objective function value is computed as sum of all
	// covariances (each feature with every other) from set 
	// of "valid" features. Then the sum is divided by the 
	// number of covariances.

	// TODO: refactor this method and particle communication to remove this ugly bool parameter !!!

	float functionValue = 0.0f;
	size_t validFeatures = 0;
	float sumValue = 0.0f;
	size_t howManyFeatures = 0;
	for (size_t i = 0; i < particlesSize; ++i)
	{
		if ((*particle)[i] == 1)
		{
			sumValue += dataset->meanDiffs[i];
			howManyFeatures++;
		}

		//if ((!useBestLocal && (*particle)[i] == 1) || (useBestLocal && particle->getBestLocalBit(i) == 1))
		//{
		//	++validFeatures;
		//	for (size_t j = i + 1; j < particlesSize; ++j)
		//	{
		//		if ((!useBestLocal && (*particle)[j] == 1) || (useBestLocal && particle->getBestLocalBit(j) == 1))
		//		{
		//			float covariance = 0.0f;
		//			// this is VERY slow because dataset is big
		//			// for (size_t k = 0; k < dataset->datasetSize; ++k)
		//			// another approach - getting 100 random values within range
		//			for (size_t k = 0; k < 50; ++k)
		//			{
		//				size_t r = rand() % dataset->datasetSize;
		//				covariance += ((*dataset)[i][r] - dataset->meanData[i]) * ((*dataset)[j][r] - dataset->meanData[j]);
		//			}
		//			covariance /= (dataset->datasetSize - 1);
		//			std::cout << "covariance: " << covariance << std::endl;
		//			functionValue += covariance;
		//		}
		//	}
		//}
	}
	--validFeatures;
	//functionValue /= ((validFeatures + validFeatures * validFeatures) / 2);
	functionValue = sumValue / howManyFeatures;
	return functionValue;
}

void Algorithm::printSolution()
{
		bestKnownParticle->printCurrentState();
}

Particle * Algorithm::getSolution()
{
	return bestKnownParticle;
}


