#include "StringWork.h"

bool StringWork::isString(const std::string &value)
{
	if(value == "")
		return true;

	if (value[0] == '"' && value.back() == '"' && value.size() > 1) {

		bool first = true;
		bool isString = true;
		for (unsigned i = 1; i < value.size() - 1; i++) {
			if (value[i] == '\\') {
				if (first) {
					if ((i + 1 == value.size() - 1) || (value[i + 1] != '\\' && value[i + 1] != '\'' && value[i + 1] != '\"')) {
						isString = false;
						break;
					}
					first = false;
					continue;
				}
			}

			first = true;
			if ((value[i] == '\'' || value[i] == '\"') && slashesCount(value, i-1) % 2 == 0) {
				isString = false;
				break;
			}
		}

		if (isString) {
			return true;
		}	
	}

	return false;
}

bool StringWork::isInt(const std::string &value)
{
	unsigned i = (value[0] == '+' || value[0] == '-');
	return onlyDigits(value, i);
}

bool StringWork::isDouble(const std::string &value)
{
    unsigned i = (value[0] == '+' || value[0] == '-');
	onlyDigits(value, i);
	if(value[i] != '.')
		return false;

	return onlyDigits(value, ++i);
}

bool StringWork::isEquation(const std::string &value)
{
	if(value[0] != '=')
		return false;

	std::vector<std::string> parts;
    StringWork::separateEquation(value, parts);

	if(parts[0] != "=" || parts.size() != 4 || isEqSigh(parts.back())){
		return false;

	}

	return isEquationInOrder(parts, 1, false);
    
}

bool StringWork::isInvalid(const std::string &value)
{
    return !isString(value) && !isInt(value) && !isDouble(value) && !isEquation(value);
}

bool StringWork::onlyDigits(const std::string &value, unsigned& i){

	bool hasDigits = false;

	for (; i < value.size(); i++) {

		if (value[i] < '0' || value[i] > '9')
			return false;
		
		hasDigits = true;
	}

	return hasDigits;
}

bool StringWork::isEquationInOrder(const std::vector<std::string>& parts, int partIndex, bool expectEqSign){

	if(partIndex == parts.size())
		return true;

	if(expectEqSign){
		if(!isEqSigh(parts[partIndex])){
			return false;

		}
	}
	else{

		if(!isInt(parts[partIndex]) && !isDouble(parts[partIndex]) && !isReferingCell(parts[partIndex])){
			return false;

		}
	}

	return isEquationInOrder(parts, partIndex + 1, !expectEqSign);	
}

bool StringWork::isEqSigh(const std::string eqSign){

	return !(eqSign != "+" && eqSign != "-" && eqSign != "*" 
			&& eqSign != "/" && eqSign != ">" && eqSign != ">="
			&& eqSign != "<" && eqSign != "<=" && eqSign != "==" && eqSign != "!=");
}

bool StringWork::isReferingCell(const std::string& value)
{	
	if(value.size() < 4)
		return false;

    if(value[0] != 'R')
		return false;

	if(value[1] < '1' || value[1] > '9')
		return false;

	unsigned i = 1;
	onlyDigits(value, i);
	if(value[i] != 'C')
		return false;

	if(value[++i] < '1' || value[i] > '9')
		return false;

	return onlyDigits(value, i);
}

int StringWork::slashesCount(const std::string& value, int i) {

	int count = 0;

	for (; i >= 0 && value[i] == '\\'; i--) {
		count++;
	}
	return count;
}

Pair StringWork::positionOfReferingCell(const std::string &value)
{
    if(!isReferingCell(value))
		return Pair{-1, -1};

	size_t i = 1;
	size_t* idx = &i;
	int col = stoi(value.substr(1, value.size() - 1), idx);
	// std::cout << *idx;
	int row = stoi(value.substr(*idx + 2, value.size() - 1));

	return Pair{col, row};
}

void StringWork::separateEquation(const std::string &value, std::vector<std::string> &parts, int valIndex, bool spaces, int partIndex)
{
    if(valIndex == value.size()){
		return;
	}

	if(valIndex == 0)
		parts.push_back("");

	if(value[valIndex] == ' '){

		if(!spaces){
			partIndex++;
			parts.push_back("");
			spaces = true;
		}

		separateEquation(value, parts, valIndex + 1, spaces, partIndex);
	}
	else{
		spaces = false;
		parts[partIndex].push_back(value[valIndex]);
		separateEquation(value, parts, valIndex + 1, spaces, partIndex);
	}
}

std::vector<std::string> StringWork::fileToString(const std::string& path){

	std::ifstream in(path);

	if (!in.is_open()) {
		std::cout << "Could not load the file " << path << '\n';
		return std::vector<std::string>{}; 
	}

    std::vector<std::string> tableValues;
	unsigned colNum = 1, rowNum = 1, col = 1, row = 1;
	numOfColumnsAndRowsInTable(path, colNum, rowNum);

	std::string buffer = "";

	bool newLine = true;
	char c;

	while(in.get(c)) {


		if (c == '\n' && newLine) {
			for (unsigned j = 0; j < colNum; j++) {
				tableValues.push_back("");
			}
			row++;
			col = 1;
			continue;
		}

		newLine = false;
		if (c == ',') {
			tableValues.push_back(buffer);
			buffer = "";
			col++;
		}
		else if (c == '\n') {
			tableValues.push_back(buffer);
			buffer = "";
			col++;
			for (; col <= colNum; col++) {
				tableValues.push_back("");
			}
			row++;
			col = 1;
			newLine = true;
		}
		else {	
			buffer.push_back(c);
		}		
	}

	if (!in.eof())
		std::cout << "The end of file has not been reached!\n";

	tableValues.push_back(buffer);	
	col++;
	for (; col <= colNum; col++) {
		tableValues.push_back("");
	}
	
	in.close();

	return tableValues;
}


void StringWork::numOfColumnsAndRowsInTable(const std::string& path, unsigned& cols, unsigned& rows)
{
	std::ifstream in(path);
	if (!in.is_open()) {
		std::cout << "Could not load the file " << path << '\n';
		return;
	}

    int maxColumns = 1;
	char c;

	while(in.get(c)){

		if (c == ',')
			cols++;

		else if (c == '\n')
		{
			if (cols > maxColumns)
				maxColumns = cols;
			cols = 1;
			rows++;
		}
	}

	if (!in.eof())
		std::cout << "The end of file has not been reached!\n";

	cols = maxColumns;

	in.close();
}

std::string StringWork::removeWhiteSpaces(const std::string& value)
{
	std::string newVal;
	bool start = true;
	for (unsigned i = 0; i < value.size(); i++) {

		if ((value[i] == ' ' || value[i] == 9) && start)
			continue;

		start = false;
		newVal.push_back(value[i]);
		
	}

	return newVal;
}

std::string StringWork::removeWhiteSpacesFromBothSides(const std::string& value){

	std::string newVal = removeWhiteSpaces(value);

	for(int i = newVal.size() - 1; newVal[i] == ' ' || newVal[i] == 9; i--){
		newVal.pop_back();
	}

	return newVal;
}


std::string StringWork::needsCommaAfter(const std::string& buffer)
{
	for (unsigned i = 0; i < buffer.size(); i++) {

		if (buffer[i] == ' ') {
			std::string buf1 = "", buf2 = "";
			unsigned j = 0;
			for (; j < i; j++) {
				buf1.push_back(buffer[j]);
			}
			for (; j < buffer.size(); j++) {
				buf2.push_back(buffer[j]);
			}
			buf1 = StringWork::removeWhiteSpaces(buf1);
			buf2 = StringWork::removeWhiteSpaces(buf2);

			if (!StringWork::isInvalid(buf1) && !StringWork::isInvalid(buf2)) {
				return buf1;
			}
		}
	}
	return "no";
}

bool StringWork::allValidParts(const std::vector<std::string>& parts, unsigned numOfColsInTable)
{
	std::string part = "";
	int indexOfInvalid = hasInvalidType(parts, part);
    if(indexOfInvalid == -1)
		return true;

	if(needsCommaAfter(part) == "no")
			std::cout << "Error: row " << (indexOfInvalid / numOfColsInTable) + 1 << ", col " << (indexOfInvalid % numOfColsInTable) + 1 << ", " << part << " is unknown data type.";
		else
			std::cout << "Error: row " << (indexOfInvalid / numOfColsInTable) + 1 << ", col " << (indexOfInvalid % numOfColsInTable) + 1
					  << ": missing comma after " << needsCommaAfter(part) << '.';
	
	return false;
}

int StringWork::hasInvalidType(const std::vector<std::string>& parts, std::string& invalidPart)
{
    for(int i = 0; i < parts.size(); i++){

		if(isInvalid(parts[i])){

			invalidPart = parts[i];
			return i;
		}
	}

	return -1;
}


void StringWork::separateCommand(const std::string &value, std::vector<std::string> &parts){

	separateInto(value, parts, 2, 0, true, 0);

	if(parts[0] == "edit"){
		parts.clear();
		separateInto(value, parts, 4, 0, true, 0);
	}
}

void StringWork::separateInto(const std::string &value, std::vector<std::string> &parts,int n, int valIndex, bool spaces, int partIndex){

	if(value[valIndex] == '\0')
		return;

	if(partIndex == n - 1){
		parts[partIndex] = StringWork::removeWhiteSpacesFromBothSides(value.substr(valIndex, value.size() - valIndex));
		// std::cout << parts[partIndex];
		return;
	}

	if(valIndex == 0)
		parts.push_back("");

	if(value[valIndex] == ' ' && partIndex < 3){

		if(!spaces){
			partIndex++;
			parts.push_back("");
			spaces = true;
		}
	}
	else{
		spaces = false;
		parts[partIndex].push_back(value[valIndex]);
	}

	separateInto(value, parts, n, valIndex + 1, spaces, partIndex);

}