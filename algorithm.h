#pragma once

#include "particle.h"
#include "dataset.h"
#include <memory>

class Algorithm
{
public:
	Algorithm(size_t particlesNumber, 
			size_t particlesSize, 
			size_t iterations, 
			std::unique_ptr<DataSet> & ds, 
			size_t objFunctionIdentifier,
			float vMax, 
			float alpha, 
			float beta,
			float fNumImportance);
	~Algorithm();

	void performOptimization();
	float objectiveFunction(std::vector<pbit> state);
	void printSolution();
	Particle getSolution();
	void refreshParticles();

private:
	size_t particlesNumber;
	size_t particlesSize;
	size_t iterations;

	size_t objFcnIdentifier;

	float alpha;
	float beta;
	float vMax;
	float fNumImportance;

	std::vector<std::unique_ptr<Particle>> particles;
	std::vector<Particle> bestParticlesHistory;
	Particle bestKnownParticle;
	DataSet * dataset;

	//Particle ** particles;
	//DataSet * dataset;
};