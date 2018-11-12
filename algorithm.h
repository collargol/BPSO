#pragma once

#include "particle.h"

class Algorithm
{
public:
	Algorithm(size_t particlesNumber, size_t particlesSize, size_t iterations);
	~Algorithm();

private:
	size_t particlesNumber;
	size_t particlesSize;
	size_t iterations;

	Particle ** particles;

	float alpha;
	float beta;
};