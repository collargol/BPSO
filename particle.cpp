#include "particle.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

Particle::Particle(size_t size)
	: size(size > 0 ? size : 8)
{
	setRandomState();

	/*currentState = new pbit[size];
	bestLocalState = new pbit[size];
	velocities = new float[size];

	setRandomState();*/
}

Particle::~Particle()
{
	/*if (currentState)
		delete[] currentState;
	if (bestLocalState)
		delete[] bestLocalState;
	if (velocities)
		delete[] velocities;*/
}

Particle::Particle(const Particle & particle)
{
	size = particle.size;

	currentState = particle.currentState;
	bestLocalState = particle.bestLocalState;
	velocities = particle.velocities;
}

Particle::Particle(Particle && particle)
{
	size = particle.size;

	currentState = particle.currentState;
	bestLocalState = particle.bestLocalState;
	velocities = particle.velocities;

	particle.size = 0;
	particle.currentState.clear();
	particle.bestLocalState.clear();
	particle.velocities.clear();
}

size_t Particle::getSize()
{
	return size;
}

void Particle::printCurrentState()
{
	for (size_t i = 0; i < size; ++i)
		std::cout << static_cast<int>(currentState[i]);
	std::cout << std::endl;
}

pbit Particle::getBestLocalBit(size_t i)
{
	return (i < size) ? bestLocalState[i] : -1;
}

void Particle::setRandomState()
{
	currentState.clear();
	bestLocalState.clear();
	velocities.clear();

	currentState.reserve(size);
	bestLocalState.reserve(size);
	velocities.reserve(size);

	for (size_t i = 0; i < size; ++i)
	{
		currentState.push_back(static_cast<pbit>(rand() % 2));
		bestLocalState.push_back(currentState[i]);
		velocities.push_back(0.0f);
	}
}

void Particle::makeCurrentStateBest()
{
	bestLocalState = currentState;
}

pbit Particle::operator[](size_t i)
{
	return (i < size) ? currentState[i] : -1;	// -1 will gave big value
}

std::vector<pbit> Particle::getCurrentState()
{
	return currentState;
}

std::vector<pbit> Particle::getBestLocalState()
{
	return bestLocalState;
}

Particle & Particle::operator=(const Particle & particle)
{
	if (this != &particle && size == particle.size)
	{
		currentState = particle.currentState;
		bestLocalState = particle.bestLocalState;
		velocities = particle.velocities;
	}
	return *this;
}

Particle & Particle::operator=(Particle && particle)
{
	if (this != &particle && size == particle.size)
	{
		currentState = particle.currentState;
		bestLocalState = particle.bestLocalState;
		velocities = particle.velocities;
	}
	return *this;
}

void Particle::updateParticleState(float alpha, float beta, float maxVelocity, std::vector<pbit> bestGlobalState)
{
	float velocitySigmoid = 0.0f;
	float c1 = 0.0f;
	float c2 = 0.0f;
	for (size_t i = 0; i < size; ++i)
	{
		c1 = alpha * (static_cast<float>(rand()) / RAND_MAX);
		c2 = beta  * (static_cast<float>(rand()) / RAND_MAX);
		velocities[i] += c1 * (bestLocalState[i] - currentState[i]) + c2 * (bestGlobalState[i] - currentState[i]);
		velocities[i] = abs(velocities[i]) > maxVelocity ? (maxVelocity * velocities[i] / abs(velocities[i])) : velocities[i];
		// update particle component
		velocitySigmoid = 1 / (1 + exp(-velocities[i]));
		currentState[i] = ((static_cast<float>(rand()) / RAND_MAX) < velocitySigmoid) ? 1 : 0;
	}
}

bool operator==(const Particle & lp, const Particle & rp)
{
	return lp.size == rp.size
		&& lp.currentState == rp.currentState
		&& lp.bestLocalState == rp.bestLocalState
		&& lp.velocities == rp.velocities;
}

bool operator!=(const Particle & lp, const Particle & rp)
{
	return !(lp == rp);
}
