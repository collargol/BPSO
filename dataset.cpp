#include "dataset.h"

DataSet::DataSet(size_t featuresNumber, size_t datasetSize)
	: featuresNumber(featuresNumber)
	, datasetSize(datasetSize)
{
	data = new fint*[featuresNumber];
	for (size_t i = 0; i < featuresNumber; ++i)
		data[i] = new fint[datasetSize];

	meanData = new float[featuresNumber];
}

DataSet::~DataSet()
{
	if (data)
	{
		for (size_t i = 0; i < featuresNumber; ++i)
			delete[] data[i];
		delete[] data;
	}

	if (meanData)
		delete[] meanData;
}

void DataSet::computeMeanData()
{
	for (size_t i = 0; i < featuresNumber; ++i)
	{
		int sum = 0.f;
		for (size_t j = 0; j < datasetSize; ++j)
			sum += data[i][j];
		meanData[i] = static_cast<float>(sum / datasetSize);
	}
}

fint * DataSet::operator[](size_t i)
{
	return (i < featuresNumber) ? data[i] : nullptr;
}
