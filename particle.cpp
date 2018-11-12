#include "particle.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

Particle::Particle(size_t size)
	: size(size > 0 ? size : 8)
{
	currentState = new pbit[size];
	bestLocalState = new pbit[size];
	velocities = new float[size];

	setRandomState();
}

Particle::~Particle()
{
	if (currentState)
		delete[] currentState;
	if (bestLocalState)
		delete[] bestLocalState;
	if (velocities)
		delete[] velocities;
}

Particle::Particle(const Particle & particle)
{
	size = particle.size;

	currentState = new pbit[size];
	bestLocalState = new pbit[size];
	velocities = new float[size];

	for (size_t i = 0; i < size; ++i)
	{
		currentState[i] = particle.currentState[i];
		bestLocalState[i] = particle.bestLocalState[i];
		velocities[i] = particle.velocities[i];
	}

	bestGlobalState = particle.bestGlobalState;
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
	for (size_t i = 0; i < size; ++i)
	{
		currentState[i] = static_cast<pbit>(rand() % 2);
		bestLocalState[i] = currentState[i];
		velocities[i] = 0.0f;
	}
}

void Particle::updateBestLocalState()
{
	for (size_t i = 0; i < size; ++i)
		bestLocalState[i] = currentState[i];
}

pbit Particle::operator[](size_t i)
{
	return (i < size) ? currentState[i] : -1;	// -1 will gave big value
}


Particle & Particle::operator=(const Particle & particle)
{
	if (this != &particle && size == particle.size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			currentState[i] = particle.currentState[i];
			bestLocalState[i] = particle.bestLocalState[i];
			velocities[i] = particle.velocities[i];
		}

		bestGlobalState = particle.bestGlobalState;
	}
	return *this;
}

Particle & Particle::operator=(Particle && particle)
{
	if (this != &particle && size == particle.size)
	{
		if (currentState)
			delete[] currentState;
		if (bestLocalState)
			delete[] bestLocalState;
		if (velocities)
			delete[] velocities;

		currentState = particle.currentState;
		bestLocalState = particle.bestLocalState;
		velocities = particle.velocities;
		bestGlobalState = particle.bestGlobalState;

		particle.currentState = nullptr;
		particle.bestLocalState = nullptr;
		particle.velocities = nullptr;

	}
	return *this;
}

void Particle::updateParticleState(float alpha, float beta)
{
	float velocitySigmoid = 0.0f;
	float c1 = 0.0f;
	float c2 = 0.0f;
	for (size_t i = 0; i < size; ++i)
	{
		// update velocity
		// need reimplementation!!!
		c1 = (static_cast<float>(rand()) / RAND_MAX) * alpha;
		c2 = (static_cast<float>(rand()) / RAND_MAX) * beta;
		velocities[i] += c1 * (bestLocalState[i] - currentState[i]) + c2 * ((*bestGlobalState)[i] - currentState[i]);
		// update particle component - should be HERE or below this scope??
		velocitySigmoid = 1 / (1 + exp(-velocities[i]));
		currentState[i] = ((static_cast<float>(rand()) / RAND_MAX) < velocitySigmoid) ? 1 : 0;
	}

	//			if (f(xi) < f(pi)
	//				update particle's best known position pi <-- xi
	//				if (f(pi) < f(g))
	//					update best known global position g <-- pi
}

void Particle::setBestGlobalState(Particle * bestKnownParticle)
{
	if (bestKnownParticle)
		bestGlobalState = bestKnownParticle;
}

