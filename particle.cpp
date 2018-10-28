#include "particle.h"

#include <iostream>
#include <cstdlib>

Particle::Particle()
	: dataSize(64)
	, currentState(0)
	, bestLocalState(0)
{}

Particle::Particle(size_p size)
	: dataSize((size > 64) ? 64 : size)
{
	setRandomState();
}

Particle::Particle(size_p size, data_p data)
	: dataSize((size > 64) ? 64 : size)
	, currentState(data)
	, bestLocalState(currentState)
{}

Particle::~Particle()
{}

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
