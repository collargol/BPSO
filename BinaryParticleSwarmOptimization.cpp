#include <iostream>
#include <ctime>

#include "particle.h"
#include "algorithm.h"
#include "csvfilereaderwriter.h"

int main(int argc, char * argv[])
{
	std::string inputFilePath;
	std::string outputFilePath;
	switch (argc)
	{
	default:
	case 1:
		inputFilePath = "gender_data.csv";
		outputFilePath = "solution.csv";
		break;
	case 2:
		inputFilePath = std::string(argv[0]);
		outputFilePath = "solution.csv";
		break;
	case 3:
		inputFilePath = std::string(argv[0]);
		outputFilePath = std::string(argv[1]);
		break;
	}
	std::cout << "inputFilePath: " << inputFilePath << std::endl;
	std::cout << "outputFilePath: " << outputFilePath << std::endl;

	srand(static_cast<unsigned int>(time(0)));

	CSVFileReaderWriter csvRW(inputFilePath, outputFilePath);
	DataSet * ds = csvRW.readCSV();
	std::unique_ptr<DataSet> dataset(ds);
	size_t particlesNumber = 100;
	size_t iterations = 200;
	float maxVelocity = 6.f;

	Algorithm algorithm(particlesNumber, dataset->featuresNumber, iterations, dataset, maxVelocity, 1.0f, 1.0f);
	algorithm.performOptimization();

	csvRW.writeSolutionCSV(algorithm.getSolution());
}

