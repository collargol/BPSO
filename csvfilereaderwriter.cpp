#include "csvfilereaderwriter.h"

enum class CSVState {
	UnquotedField,
	QuotedField,
	QuotedQuote
};

CSVFileReaderWriter::CSVFileReaderWriter(std::string inputFilePath, std::string outputFilePath)
	: inputFilePath(inputFilePath)
	, outputFilePath(outputFilePath)
	, csvFileHeader("null")
	, rowsNumber(0)
	, colsNumber(0)
{
}

CSVFileReaderWriter::~CSVFileReaderWriter()
{
}

std::vector<std::string> CSVFileReaderWriter::readCSVRow(const std::string &row) 
{
	CSVState state = CSVState::UnquotedField;
	std::vector<std::string> fields{ "" };
	size_t i = 0; // index of the current field
	for (char c : row) 
	{
		switch (state) 
		{
			case CSVState::UnquotedField:
				switch (c) 
				{
					case ',': // end of field
						fields.push_back(""); i++;
						break;
					case '"': state = CSVState::QuotedField;
						break;
					default:  fields[i].push_back(c);
						break;
				}
				break;
			case CSVState::QuotedField:
				switch (c) 
				{
					case '"': state = CSVState::QuotedQuote;
						break;
					default:  fields[i].push_back(c);
						break;
				}
				break;
			case CSVState::QuotedQuote:
				switch (c) 
				{
					case ',': // , after closing quote
						fields.push_back(""); i++;
						state = CSVState::UnquotedField;
						break;
					case '"': // "" -> "
						fields[i].push_back('"');
						state = CSVState::QuotedField;
						break;
					default:  // end of quote
						state = CSVState::UnquotedField;
						break;
				}
				break;
		}
	}
	//fields.erase(fields.begin());

	if (colsNumber < fields.size() - 1)
		colsNumber = fields.size() - 1;	//to omit first column with classif data
	return fields;
}

/// Read CSV file, Excel dialect. Accept "quoted fields ""with quotes"""
DataSet * CSVFileReaderWriter::readCSV()
{
	std::vector<std::vector<std::string>> table;
	std::filebuf fb;
	if (fb.open(inputFilePath, std::ios::in))
	{
		std::istream in(&fb);
		std::string row;
		while (!in.eof())
		{
			std::getline(in, row);
			if (!csvFileHeader.compare("null"))
				csvFileHeader = row.substr(row.find(" ") + 1);
			if (in.bad() || in.fail())
				break;
			auto fields = readCSVRow(row);
			table.push_back(fields);
		}
		fb.close();
	}
	table.erase(table.begin());
	rowsNumber = table.size();

	std::cout << "ROWS: " << rowsNumber << std::endl;
	std::cout << "COLS: " << colsNumber << std::endl;

	DataSet * dataset = new DataSet(colsNumber, rowsNumber);

	if (dataset)
	{
		dataset->datasetSizeClass[0] = 0;
		dataset->datasetSizeClass[1] = 0;
		for (size_t r = 0; r < table.size(); ++r)
		{
			dataset->classifData[r] = std::stoi(table[r][0]);
			//std::cout << "classif data : " << dataset->classifData[r] << std::endl;
			if (dataset->classifData[r] == 0)
				(dataset->datasetSizeClass[0])++;
			else //if (dataset->classifData[r] == 1)
				(dataset->datasetSizeClass[1])++;

			table[r].erase(table[r].begin());
		}
		//std::cout << "c0 : " << dataset->datasetSizeClass0 << std::endl;
		//std::cout << "c1 : " << dataset->datasetSizeClass1 << std::endl;

		for (size_t r = 0; r < table.size(); ++r)
			for (size_t c = 0; c < table[r].size(); ++c)
				(*dataset)[c][r] = std::stoi(table[r][c]);

		dataset->computeMeanData();
	}
	return dataset;
}

void CSVFileReaderWriter::writeSolutionCSV(Particle * solution)
{
	std::filebuf fb;
	if (fb.open(outputFilePath, std::ios::out))
	{
		std::ostream out(&fb);
		out << csvFileHeader;
		out << std::endl;
		std::string solutionRow;
		for (size_t i = 0; i < solution->getSize(); ++i)
		{	
			//char bit = static_cast<char>((*solution)[i]);
			//char * c = reinterpret_cast<char *>((*solution)[i]);
			if (i > 0) 
				solutionRow += ", ";
				//solutionRow.append(", ");
			//solutionRow.append(std::string(&bit));
			//std::cout << "bit value: " << char(int((*solution)[i])) << std::endl;
			//solutionRow += static_cast<char>((*solution)[i]);
			solutionRow += ((*solution)[i] == 1) ? "1" : "0";
		}
		std::cout << "solution to write: " << solutionRow << std::endl;
		out << solutionRow;
		fb.close();
	}
}

