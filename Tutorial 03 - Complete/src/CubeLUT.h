#pragma once

#include <string>
#include <vector>
#include <fstream>

/*

CubeLUT is somewhat made from 
https://wwwimages2.adobe.com/content/dam/acom/en/products/speedgrade/cc/pdfs/cube-lut-specification-1.0.pdf
and more prominently from florp's obj loader 
Thank you Shawn

*/

class CubeLUT {
public:
	typedef std::vector<float>		tableRow;
	typedef std::vector<tableRow>	table1D;
	typedef std::vector<table1D>	table2D;
	typedef std::vector<table2D>	table3D; //    <table2D>
											//	  <<Table1D>>
											//	 <<<tableRow>>>
											//	<<<<  float >>>>

	enum LUTState {
		OK = 0, NotInitialized = 1, ReadError = 10, WriteError, PrematureEndOfFile, LineError, UnknownOrRepeatedKeyword = 20,
		TitleMissingQuote, DomainBoundsReversed, LUTSizeOutOfRange, CouldNotParseTableData
	};

	LUTState status;
	std::string title;
	tableRow domainMin;
	tableRow domainMax;
	table1D LUT1D;
	table3D LUT3D;

	CubeLUT(void) { status = NotInitialized; };

	LUTState LoadCubeFile(std::ifstream& infile);
	LUTState SaveCubeFile(std::ofstream& outfile);

	void SaveCubeData(const char* infile);

private:
	std::string ReadLine(std::ifstream& infile, char lineSeparator);
	tableRow ParseTableRow(const std::string& lineOfText);

};