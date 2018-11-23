#pragma once

#include <vector>

typedef unsigned char pbit;

class Particle
{
public:
	Particle(size_t size);
	~Particle();

	Particle(const Particle & particle);
	Particle(Particle && particle);
	Particle & operator=(const Particle & particle);
	Particle & operator=(Particle && particle);

	void updateParticleState(float alpha, float beta, float maxVelocity, std::vector<pbit> bestKnownState);
	void makeCurrentStateBest();

	size_t getSize();
	void printCurrentState();
	pbit getBestLocalBit(size_t i);
	pbit operator[](size_t i);

	std::vector<pbit> getCurrentState();
	std::vector<pbit> getBestLocalState();

private:
	size_t size;
	std::vector<pbit> currentState;
	std::vector<pbit> bestLocalState;
	std::vector<float> velocities;

	/*pbit * currentState;
	pbit * bestLocalState;
	Particle * bestGlobalState;
	float * velocities;*/

	void setRandomState();
};


