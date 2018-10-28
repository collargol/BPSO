#pragma once

// data_p is described as unsigned long long int so the limitation
// of solution size is 64 bits in this case.

typedef unsigned long long int data_p;
typedef unsigned short int size_p;

class Particle
{
public:
	Particle();
	Particle(size_p size);
	Particle(size_p size, data_p data);
	Particle(const Particle & particle) = delete;
	Particle(Particle && particle) = delete;
	~Particle();

	Particle & operator=(Particle && particle);

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

};