#include "dataset.h"

#include <iostream>
#include <cmath>

DataSet::DataSet(size_t featuresNumber, size_t datasetSize)
	: featuresNumber(featuresNumber)
	, datasetSize(datasetSize)
{
	data = new fint*[featuresNumber];
	for (size_t i = 0; i < featuresNumber; ++i)
		data[i] = new fint[datasetSize];

	datasetSizeClass = new size_t[2];

	classifData = new fint[datasetSize];

	meanData = new float[featuresNumber];

	meanClassData = new float*[2];
	meanClassData[0] = new float[featuresNumber];
	meanClassData[1] = new float[featuresNumber];

	meanDiffs = new float[featuresNumber];

	stdDeviationClassData = new float*[2];
	stdDeviationClassData[0] = new float[featuresNumber];
	stdDeviationClassData[1] = new float[featuresNumber];

	stdDevDiffs = new float[featuresNumber];
}

DataSet::~DataSet()
{
	if (data)
	{
		for (size_t i = 0; i < featuresNumber; ++i)
			delete[] data[i];
		delete[] data;
	}

	if (datasetSizeClass)
		delete[] datasetSizeClass;

	if (classifData)
		delete[] classifData;

	if (meanData)
		delete[] meanData;

	if (meanClassData)
	{
		delete[] meanClassData[0];
		delete[] meanClassData[1];
		delete[] meanClassData;
	}

	if (meanDiffs)
		delete[] meanDiffs;

	if (stdDeviationClassData)
	{
		delete[] stdDeviationClassData[0];
		delete[] stdDeviationClassData[1];
		delete[] stdDeviationClassData;
	}

	if (stdDevDiffs)
		delete[] stdDevDiffs;
}

void DataSet::computeMeanData()
{
	for (size_t i = 0; i < featuresNumber; ++i)
	{
		int sum = 0;
		int sumClass0 = 0;
		int sumClass1 = 0;
		for (size_t j = 0; j < datasetSize; ++j)
		{
			//sum += data[i][j];
			if (classifData[j] == 0)
				sumClass0 += data[i][j];
			else if (classifData[j] == 1)
				sumClass1 += data[i][j];
		}
		sum = sumClass0 + sumClass1;

		meanData[i] = static_cast<float>(sum / datasetSize);
		meanClassData[0][i] = static_cast<float>(sumClass0 / datasetSizeClass[0]);
		meanClassData[1][i] = static_cast<float>(sumClass1 / datasetSizeClass[1]);
		meanDiffs[i] = fabsf(meanClassData[0][i] - meanClassData[1][i]) / meanData[i];
		
		// standard deviation
		float nominatorClass0 = 0.0f;
		float nominatorClass1 = 0.0f;
		for (size_t j = 0; j < datasetSize; ++j)
		{
			if (classifData[j] == 0)
				nominatorClass0 += powf(data[i][j] - meanClassData[0][i], 2.0f);
			else if (classifData[j] == 1)
				nominatorClass1 += powf(data[i][j] - meanClassData[1][i], 2.0f);;
		}
		stdDeviationClassData[0][i] = sqrtf(nominatorClass0 / sumClass0);
		stdDeviationClassData[1][i] = sqrtf(nominatorClass1 / sumClass1);
		stdDevDiffs[i] = fabsf((stdDeviationClassData[0][i] - stdDeviationClassData[1][i]) / meanData[i]);

		std::cout << meanClassData[0][i] << "   " << meanClassData[1][i] << " diff:  : " << meanDiffs[i] << std::endl;
		std::cout << stdDeviationClassData[0][i] << "   " << stdDeviationClassData[1][i] << " normalized diff: " << stdDevDiffs[i] << std::endl; //fabsf(stdDeviationClassData[0][i] / meanClassData[0][i] - stdDeviationClassData[1][i] / meanClassData[1][i]) << std::endl;
	}
}

fint * DataSet::operator[](size_t i)
{
	return (i < featuresNumber) ? data[i] : nullptr;
}
