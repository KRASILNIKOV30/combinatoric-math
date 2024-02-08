#include <iostream>
#include <string>
#include <optional>
#include <fstream>
#include <sstream>
#include "GetMinAssignment.h"

struct Args
{
    std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;
}

bool SaveErrorHandling(std::ofstream& output)
{
	if (!output.flush())
	{
		std::cout << "Failed to save data on disk\n";
		return false;
	}
	return true;
}

std::vector<int> ReadMatrixRow(std::string str)
{
	std::istringstream input(str);
	int value;
	std::vector<int> row;
	while (input >> value)
	{
		row.push_back(value);
	}

	return row;
}

Matrix ReadMatrix(std::istream& input)
{
    std::string line;
	Matrix matrix;
    while (std::getline(input, line) && line != "")
    {
		matrix.push_back(ReadMatrixRow(line));
    }

	return matrix;
}

bool ProcessArgError(const std::optional<Args>& args)
{
	if (!args.has_value())
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: qap.exe <input file> <output file>\n";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!ProcessArgError(args))
	{
		return 1;
	}

	std::ifstream input(args->inputFileName);
	std::ofstream output(args->outputFileName);

	Matrix facilities = ReadMatrix(input);
	Matrix locations = ReadMatrix(input);
	
	std::vector<int> minAssignment = GetMinAssigment(facilities, locations);
	std::ranges::copy(minAssignment, std::ostream_iterator<int>(output, " "));

	if (!SaveErrorHandling(output))
	{
		return 1;
	}

	return 0;
}

