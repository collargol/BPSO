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

	void updateParticleState();
	void updateBestLocalState();
	void setBestGlobalState(Particle * bestKnownParticle);
	//size_p getDataSize();
	//data_p getCurrentState();
	//data_p getBestLocalState();
		
	//void setRandomState();
	//void setBestGlobalState(data_p * bestGlobal);

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

	//size_p dataSize;
	//data_p currentState;
	//data_p bestLocalState;
	//data_p * bestGlobalState;

	//float * velocities = nullptr;
};


