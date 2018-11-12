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
			++rowsNumber;
		}
		fb.close();
	}
	table.erase(table.begin());
	--rowsNumber;
	//for (auto i : table)
	//{
	//	for (auto j : i)
	//		std::cout << j << "  ";
	//	std::cout << std::endl;
	//}
	std::cout << "ROWS: " << rowsNumber << std::endl;
	std::cout << "COLS: " << colsNumber << std::endl;

	DataSet * dataset = new DataSet(colsNumber, rowsNumber);

	if (dataset)
	{
		for (size_t r = 0; r < table.size(); ++r)
			for (size_t c = 0; c < table[r].size(); ++c)
				(*dataset)[c][r] = std::stoi(table[r][c]);
	}

	std::cout << "struct : " << (*dataset)[10][5] << std::endl;
	std::cout << "vector : " << table[5][10] << std::endl;

	return dataset;
}

//DataSet * CSVFileReader::readToDataSet()
//{
//	io::CSVReader<50> in(filePath);
//	in.read_header(io::ignore_extra_column
//		, "Eyebrows_1", "Eyebrows_2", "Eyebrows_3", "Eyebrows_4", "Eyebrows_5", "Eyebrows_6", "Eyebrows_7", "Eyebrows_8", "Eyebrows_9", "Eyebrows_10"
//		, "Eyes_1", "Eyes_2", "Eyes_3", "Eyes_4", "Eyes_5", "Eyes_6", "Eyes_7", "Eyes_8", "Eyes_9", "Eyes_10"
//		, "Nose_1", "Nose_2", "Nose_3", "Nose_4", "Nose_5", "Nose_6", "Nose_7", "Nose_8", "Nose_9", "Nose_10"
//		, "Mouth_1", "Mouth_2", "Mouth_3", "Mouth_4", "Mouth_5", "Mouth_6", "Mouth_7", "Mouth_8", "Mouth_9", "Mouth_10"
//		, "Jaw_1", "Jaw_2", "Jaw_3", "Jaw_4", "Jaw_5", "Jaw_6", "Jaw_7", "Jaw_8", "Jaw_9", "Jaw_10");
//
//	//while (in.read_row(vendor, size, speed)) {
//	//	// do stuff with the data
//	//}
//	for (size_t i = 0; i < 4; ++i)
//	{
//		char * currentLine = in.next_line();
//		std::cout << currentLine;
//	}
//
//	return nullptr;
//}
