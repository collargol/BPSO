#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "dataset.h"

class CSVFileReader
{
private:
	std::string filePath;
	size_t rowsNumber;
	size_t colsNumber;

public:
	CSVFileReader(std::string path);
	~CSVFileReader();

	std::vector<std::string> readCSVRow(const std::string &row);
	DataSet * readCSV();
};

