#include "dataset.h"

#include <iostream>

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
		meanDiffs[i] = abs(meanClassData[0][i] - meanClassData[1][i]) / meanData[i];
		std::cout << meanClassData[0][i] << "   " << meanClassData[1][i] << " diff:  : " << meanDiffs[i] << std::endl;
	}
}

fint * DataSet::operator[](size_t i)
{
	return (i < featuresNumber) ? data[i] : nullptr;
}
