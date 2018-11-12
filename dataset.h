#pragma once

typedef unsigned short int fint;

struct DataSet
{
	size_t featuresNumber;	// columns
	size_t datasetSize;		// rows
	fint ** data;
	float * meanData;

	DataSet(size_t featuresNumber, size_t datasetSize);
	~DataSet();

	void computeMeanData();
	fint * operator[](size_t i);
};

