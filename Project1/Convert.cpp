#include "Convert.h"
#include <fstream>
#include <string>
void ConvertTxtToBinary() {
	std::fstream TxtFile("Database/Symbols.txt", std::ios::in);

	std::fstream DatFile("Database/Symbols.dat", std::ios::binary | std::ios::out);

	if (!DatFile.is_open() || !TxtFile.is_open()) { return; }
	

	std::string Line = "";

	while (std::getline(TxtFile, Line)) {
		size_t CommaPosition = Line.find(',');

		if (CommaPosition != std::string::npos) {
			std::string UserInput = Line.substr(0, CommaPosition);
			std::string APISymbol = Line.substr(CommaPosition + 1);

			unsigned long long int InputSize = UserInput.size();

			DatFile.write((char*)&InputSize, sizeof(InputSize));
			DatFile.write(UserInput.c_str(), InputSize);

			unsigned long long int APISymbolSize = APISymbol.size();

			DatFile.write((char*)&APISymbolSize, sizeof(APISymbolSize));
			DatFile.write(APISymbol.c_str(), APISymbolSize);
		}
	}
	TxtFile.close();
	DatFile.close();

}