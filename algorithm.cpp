#include "algorithm.h"

Algorithm::Algorithm(size_t pNumber, size_t pSize, size_t iters)
	: particlesNumber(pNumber)
	, particlesSize(pSize)
	, iterations(iters)
{
	particles = new Particle*[particlesNumber];
	for (size_t i = 0; i < particlesNumber; ++i)
		particles[i] = new Particle(particlesSize);
}

Algorithm::~Algorithm()
{
	for (size_t i = 0; i < particlesNumber; ++i)
		delete particles[i];
	delete[] particles;
}
