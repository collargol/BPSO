#pragma once

typedef unsigned short int fint;

struct DataSet
{
	size_t featuresNumber;	// columns
	size_t datasetSize;		// rows
	size_t datasetSizeClass0;
	size_t datasetSizeClass1;

	fint ** data;
	fint * classifData;
	float * meanData;
	float ** meanClassData;

	DataSet(size_t featuresNumber, size_t datasetSize);
	~DataSet();

	void computeMeanData();
	fint * operator[](size_t i);
};

