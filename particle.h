#pragma once

typedef unsigned char pbit;

class Particle
{
public:
	Particle(size_t size);
	~Particle();

	Particle(const Particle & particle);
	Particle(Particle && particle) = delete;
	Particle & operator=(const Particle & particle);
	Particle & operator=(Particle && particle);

	void updateParticleState(float alpha, float beta, float maxVelocity);
	void updateBestLocalState();
	void setBestGlobalState(Particle * bestKnownParticle);

	size_t getSize();
	void printCurrentState();
	pbit getBestLocalBit(size_t i);
	pbit operator[](size_t i);

private:
	size_t size;

	pbit * currentState;
	pbit * bestLocalState;
	Particle * bestGlobalState;
	float * velocities;

	void setRandomState();
};


