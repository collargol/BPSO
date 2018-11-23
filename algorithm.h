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
			float vMax, 
			float alpha, 
			float beta);
	~Algorithm();

	void performOptimization();
	float objectiveFunction(std::vector<pbit> state);
	void printSolution();
	Particle getSolution();

private:
	size_t particlesNumber;
	size_t particlesSize;
	size_t iterations;

	float alpha;
	float beta;
	float vMax;
	
	std::vector<std::unique_ptr<Particle>> particles;
	Particle bestKnownParticle;
	DataSet * dataset;

	//Particle ** particles;
	//DataSet * dataset;
};