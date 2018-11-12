#pragma once

typedef unsigned char pbit;

class Particle
{
public:
	Particle(size_t size);
	~Particle();

	Particle(const Particle & particle) = delete;
	Particle(Particle && particle) = delete;
	Particle & operator=(const Particle & particle) = delete;
	Particle & operator=(Particle && particle);

	void updateParticle();

	//size_p getDataSize();
	//data_p getCurrentState();
	//data_p getBestLocalState();
		
	//void setRandomState();
	//void setBestGlobalState(data_p * bestGlobal);

	// debug
	void printCurrentState();

private:
	size_t size;
	pbit * currentState;
	pbit * bestLocalState;
	pbit * bestGlobalState;

	float * velocities;

	void setRandomState();
	void updateBestLocalState();
	//size_p dataSize;
	//data_p currentState;
	//data_p bestLocalState;
	//data_p * bestGlobalState;

	//float * velocities = nullptr;

};


