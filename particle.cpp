#include "particle.h"
#include "systemparameters.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

Particle::Particle(size_p size, data_p data)
	: dataSize((size > 64) ? 64 : size)
	, currentState(data)
	, bestLocalState(currentState)
{
	velocities = new float[dataSize];
	if (velocities)
	{
		for (size_t i = 0; i < dataSize; ++i)
			velocities[i] = 0.f;
	}
}

Particle::~Particle()
{
	if (velocities)
		delete[] velocities;
}

Particle & Particle::operator=(Particle && particle)
{
	if (this != &particle)
	{
		dataSize = particle.dataSize;
		currentState = particle.currentState;
		bestLocalState = particle.bestLocalState;
		bestGlobalState = particle.bestGlobalState;
		// clear up
		particle.dataSize = 0;
		particle.currentState = 0;
		particle.bestLocalState = 0;
		particle.bestGlobalState = nullptr;
	}
	return *this;
}

void Particle::updateParticle()
{
	for (size_t i = 0; i < dataSize; ++i)
	{
		// update velocity
		// need reimplementation!!!
		velocities[i] = velocities[i] +
			SystemParameters.fi1 * (static_cast<float>(rand()) / RAND_MAX) * (BIT_VALUE(bestLocalState, i) - BIT_VALUE(currentState, i)) +
			SystemParameters.fi2 * (static_cast<float>(rand()) / RAND_MAX) * (BIT_VALUE(*bestGlobalState, i) - BIT_VALUE(currentState, i));
		// update particle component - should be HERE or below this scope??
		float sigmoidV = 1 / (1 + exp(-velocities[i]));
		if ((static_cast<float>(rand()) / RAND_MAX) < 1)
			currentState |= (1 << i);
		else
			currentState &= ~(1 << i);
	}

	//			if (f(xi) < f(pi)
	//				update particle's best known position pi <-- xi
	//				if (f(pi) < f(g))
	//					update best known global position g <-- pi
}

size_p Particle::getDataSize()
{
	return dataSize;
}

data_p Particle::getCurrentState()
{
	return currentState;
}

data_p Particle::getBestLocalState()
{
	return bestLocalState;
}

void Particle::setRandomState()
{
	for (int i = 0; i < dataSize; ++i)
		currentState |= ((rand() % 2) << i);
}

void Particle::setBestGlobalState(data_p * bestGlobal)
{
	if (bestGlobal)
		bestGlobalState = bestGlobal;
}

void Particle::printCurrentState()
{
	for (int i = dataSize - 1; i > -1; --i)
		std::cout << ((currentState >> i) & 1);
	std::cout << std::endl;
}
