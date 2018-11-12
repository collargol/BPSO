#include "csvfilereader.h"

enum class CSVState {
	UnquotedField,
	QuotedField,
	QuotedQuote
};

CSVFileReader::CSVFileReader(std::string path)
	: filePath(path)
	, rowsNumber(0)
	, colsNumber(0)
{
}

CSVFileReader::~CSVFileReader()
{
}

std::vector<std::string> CSVFileReader::readCSVRow(const std::string &row) 
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
	fields.erase(fields.begin());

	if (colsNumber < fields.size())
		colsNumber = fields.size();
	return fields;
}

/// Read CSV file, Excel dialect. Accept "quoted fields ""with quotes"""
DataSet * CSVFileReader::readCSV()
{
	std::vector<std::vector<std::string>> table;
	std::filebuf fb;
	if (fb.open(filePath, std::ios::in))
	{
		std::istream in(&fb);
		std::string row;
		while (!in.eof())
		{
			std::getline(in, row);
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
		for (size_t r = 0; r < table.size(); ++r)
			for (size_t c = 0; c < table[r].size(); ++c)
				(*dataset)[c][r] = std::stoi(table[r][c]);
		dataset->computeMeanData();
	}

	return dataset;
}

