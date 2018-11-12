#pragma once

#include "particle.h"
#include "dataset.h"

class Algorithm
{
public:
	Algorithm(size_t particlesNumber, size_t particlesSize, size_t iterations, DataSet * ds, float vMax, float alpha, float beta);
	~Algorithm();

	void bindDataSet(DataSet * ds);
	void performOptimization();
	float objectiveFunction(Particle * particle, bool useBestLocal = false);
	void printSolution();

private:
	size_t particlesNumber;
	size_t particlesSize;
	size_t iterations;

	float alpha;
	float beta;

	float vMax;

	Particle ** particles;
	Particle * bestKnownParticle;

	DataSet * dataset;
};