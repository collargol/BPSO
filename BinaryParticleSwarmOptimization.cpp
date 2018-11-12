#include <iostream>
#include <ctime>

#include "particle.h"
#include "algorithm.h"
#include "csvfilereader.h"

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	CSVFileReader reader("gender_data.csv");
	DataSet * dataset = reader.readCSV();
	size_t particlesNumber = 100;
	size_t iterations = 200;
	float maxVelocity = 6.f;

	Algorithm algorithm(particlesNumber, dataset->featuresNumber, iterations, dataset, maxVelocity, 1.0f, 1.0f);
	algorithm.performOptimization();



	/*Particle P(8);
	P.printCurrentState();

	Particle R(10);
	Particle Q(10);
	Q = Particle(10);*/

	//initialize
	/*for (size_t i = 0; i < particlesNumber; ++i)
	{

	}*/

}

