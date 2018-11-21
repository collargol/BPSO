#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "dataset.h"
#include "particle.h"

class CSVFileReaderWriter
{
private:
	std::string inputFilePath;
	std::string outputFilePath;
	std::string csvFileHeader;
	size_t rowsNumber;
	size_t colsNumber;

public:
	CSVFileReaderWriter(std::string inputFilePath, std::string outputFilePath);
	~CSVFileReaderWriter();

	std::vector<std::string> readCSVRow(const std::string &row);
	DataSet * readCSV();
	void writeSolutionCSV(Particle * solution);
};

