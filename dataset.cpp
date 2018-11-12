#include "dataset.h"

DataSet::DataSet(size_t featuresNumber, size_t datasetSize)
	: featuresNumber(featuresNumber)
	, datasetSize(datasetSize)
{
	data = new fint*[featuresNumber];
	for (size_t i = 0; i < featuresNumber; ++i)
		data[i] = new fint[datasetSize];
}

DataSet::~DataSet()
{
	if (data)
	{
		for (size_t i = 0; i < featuresNumber; ++i)
			delete[] data[i];
		delete[] data;
	}
}

fint * DataSet::operator[](size_t i)
{
	return (i < featuresNumber) ? data[i] : nullptr;
}
