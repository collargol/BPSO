#pragma once

// returns 0 or 1 value from data integer. consider making it a inline fcn!!
#define BIT_VALUE(data, p) ((data >> p) & 1)


// data_p is described as unsigned long long int so the limitation
// of solution size is 64 bits in this case.
typedef unsigned long long int data_p;
typedef unsigned short int size_p;

class Particle
{
public:
	Particle(size_p size = 64, data_p data = 0);
	Particle(const Particle & particle) = delete;
	Particle(Particle && particle) = delete;
	~Particle();

	Particle & operator=(Particle && particle);

	inline

	void updateParticle();

	size_p getDataSize();
	data_p getCurrentState();
	data_p getBestLocalState();

	void setRandomState();
	void setBestGlobalState(data_p * bestGlobal);

	// debug
	void printCurrentState();

private:
	size_p dataSize;
	data_p currentState;
	data_p bestLocalState;
	data_p * bestGlobalState;

	float * velocities = nullptr;

};