#pragma once

typedef unsigned short int fint;

struct DataSet
{
	size_t featuresNumber;	// columns
	size_t datasetSize;		// rows
	fint ** data;

	DataSet(size_t featuresNumber, size_t datasetSize);
	~DataSet();

	fint * operator[](size_t i);
};

