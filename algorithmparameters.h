#pragma once

class AlgorithmParameters
{
public:
	static AlgorithmParameters & getAlgorithmParameters()
	{
		static AlgorithmParameters parameters;
		return parameters;
	}

	void setAlpha(float a) { alpha = a; }
	void setBeta(float b) { beta = b; }
	void setParameters(size_t n = 20, size_t s = 100, size_t it = 200, float a = 0.f, float b = 0.f);

	float getAlpha() { return alpha; }
	float getBeta() { return beta; }

private:
	AlgorithmParameters() : alpha(0.f), beta(0.f) {}

	size_t particlesNumber;
	size_t particleSize;
	size_t iterations;

	float alpha;
	float beta;
};

void AlgorithmParameters::setParameters(size_t n, size_t s, size_t it, float a, float b)
{
	particlesNumber = n;
	particleSize = s;
	iterations = it;
	alpha = a;
	beta = b;
}