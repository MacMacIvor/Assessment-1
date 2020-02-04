#include "CubeLUT.h"
#include <iostream>
#include <sstream>

void CubeLUT::SaveCubeData(const char* infile)
{
	
	// Open the file in binary mode
	std::ifstream file;
	file.open(infile, std::ios::binary);

	if (!file) {
		throw new std::runtime_error("Failed to open file");
	}
	std::string currentLine;

	int dimension;
	int whereAt_r = 0;
	int whereAt_b = 0;
	int whereAt_g = 0;
	while (std::getline(file, currentLine)) {
		if (currentLine.substr(0, 1) == "#" || currentLine.substr(0, 1) == "") {
			int hello = 0;//pass because it's a commented line
		}
		else if (currentLine.substr(0, 10) == "DOMAIN_MIN") {
			domainMin.push_back(std::stof(currentLine.substr(11, 3)));
			domainMin.push_back(std::stof(currentLine.substr(15, 3)));
			domainMin.push_back(std::stof(currentLine.substr(19, 3)));
		}
		else if (currentLine.substr(0, 10) == "DOMAIN_MAX") {
			domainMax.push_back(std::stof(currentLine.substr(11, 3)));
			domainMax.push_back(std::stof(currentLine.substr(15, 3)));
			domainMax.push_back(std::stof(currentLine.substr(19, 3)));
		}
		else if (currentLine.substr(0, 5) == "TITLE") {
			title = currentLine.substr(7, 10); //NOTE ON THIS IT WON'T WORK IF YOU DON"T HAVE A CORRECTLY SIZE TITLE
												//THAT BEING SAID, I DIDN'T CONSIDER THIS IMPORTANT SO I LEFT IT AS IS
		}
		else if (currentLine.substr(0, 11) == "LUT_3D_SIZE") {
			dimension = std::stof(currentLine.substr(12, 2));
			LUT1D = table1D(dimension, tableRow(3));
			LUT3D = table3D(dimension, table2D(dimension, table1D(dimension, tableRow(3))));
		}
		else if (currentLine.substr(0, 1) == "0" || currentLine.substr(0, 1) == "1") {
			std::vector<float> values = { std::stof(currentLine.substr(0,8)), std::stof(currentLine.substr(9,8)), std::stof(currentLine.substr(18,8)) };

			LUT3D[whereAt_r][whereAt_g][whereAt_b] = tableRow(values);
			whereAt_r++;
			if (whereAt_r > dimension - 1) {
				whereAt_r = 0;
				whereAt_g += 1;
			}
			if (whereAt_g > dimension - 1) {
				whereAt_g = 0;
				whereAt_b += 1;
			}
		}
	}

	return;
}

