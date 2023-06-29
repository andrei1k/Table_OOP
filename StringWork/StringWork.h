#ifndef STRINGWORK_H
#define STRINGWORK_H

#include "../Cells/Pair.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class StringWork{

public:

    static bool isString(const std::string& value);
    static bool isInt(const std::string& value);
    static bool isDouble(const std::string& value);
    static bool isEquation(const std::string& value);
    static bool isInvalid(const std::string& value);
    static int slashesCount(const std::string& value, int i);
	static bool isEquationInOrder(const std::vector<std::string>& parts, int partIndex, bool expectEqSign);

	static bool isEqSigh(const std::string eqSign);

	static bool isReferingCell(const std::string& value);
    static Pair positionOfReferingCell(const std::string& value);
	static void separateEquation(const std::string& value, std::vector<std::string>& parts, int valIndex = 0, bool spaces = false,  int partIndex = 0);

    static bool onlyDigits(const std::string &value, unsigned& i);

    static std::vector<std::string> fileToString(const std::string& path);

    static void numOfColumnsAndRowsInTable(const std::string& path, unsigned& cols, unsigned& rows);

    static std::string removeWhiteSpaces(const std::string& value);
	static std::string removeWhiteSpacesFromBothSides(const std::string& value);

    static int hasInvalidType(const std::vector<std::string>& parts, std::string& invalidPart);
    static std::string needsCommaAfter(const std::string& buffer);
    static bool allValidParts(const std::vector<std::string>& parts, unsigned numOfColsInTable);

    
    static void separateInto(const std::string &value, std::vector<std::string> &parts,int n, int valIndex, bool spaces, int partIndex);
    static void separateCommand(const std::string &value, std::vector<std::string> &parts);
};

#endif // !STRINGWORK_H
