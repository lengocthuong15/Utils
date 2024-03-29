#include <iostream>
#include <fstream>
#include <string>
#include <regex> 
#include <iterator> 


void cleanEvent(const std::string& inputStr, std::string& outputStr)
{
	std::string result;
	std::string tempStr;
	std::regex regEx("<Event xmln.*/Keywords>");
	std::regex_replace(back_inserter(tempStr), inputStr.begin(), inputStr.end(), regEx, "");

	regEx = "<EventRecordID>.*<Data>";
	std::regex_replace(back_inserter(result), tempStr.begin(), tempStr.end(), regEx, "");

	tempStr = result;
	result = "";
	regEx = "TimeCreated SystemTime=";
	std::regex_replace(back_inserter(result), tempStr.begin(), tempStr.end(), regEx, "");

	outputStr = result;
}

int convertToASCII(const std::string& inputPath, const std::string outPath)
{
	std::ifstream inFile(inputPath);

	if (inFile.is_open()) {
		std::ofstream outFile(outPath);
		if (!outFile.is_open())
		{
			std::cout << "Cannot open output file";
			return 1;
		}
		std::string line;
		std::cout << "Processing......" << std::endl;
		while (getline(inFile, line))
		{
			char* buffer = new char[line.length()];
			char* s = buffer;
			int counter = 0;
			for (int i = 0; i < line.length(); ++i)
			{
				char buff = line[i];
				if (buff > 0)
				{
					counter++;
					*s++ = buff;
				}
			}

			//Clean log
			std::string tempStr = buffer;
			delete[] buffer;
			std::string outputStr;
			cleanEvent(tempStr, outputStr);
			outFile << outputStr << "\n";
		}

		inFile.close();
		outFile.close();
	}
	else
	{
		std::cout << "Cannot open input file";
		return 1;
	}
	return 0;
}

//int cleanEvent(const std::string& inputPath, const std::string outPath)
//{
//	std::ifstream inFile(inputPath);
//
//	if (inFile.is_open()) {
//		std::ofstream outFile(outPath);
//		if (!outFile.is_open())
//		{
//			std::cout << "Cannot open output file";
//			return 1;
//		}
//		std::string line;
//		std::cout << "Processing......" << std::endl;
//		while (getline(inFile, line))
//		{
//			std::string result;
//			cleanEvent(line, result);
//
//			outFile << result << "\n";
//		}
//
//		inFile.close();
//		outFile.close();
//	}
//	else
//	{
//		std::cout << "Cannot open input file";
//		return 1;
//	}
//	return 0;
//}

int main(int argc, char* argv[]) {

	int counter;
	if (argc == 3)
	{
		std::cout << "Input file: " << argv[1] << std::endl;
		std::cout << "Output file: " << argv[2]<< std::endl;
	}
	else
	{
		std::cout << "Please give input and out file";
	}

	//bool isConvertOK = convertToASCII(argv[1], argv[2]);

	bool isCleanOK = convertToASCII(argv[1], argv[2]);
		
}

