#include "EquationCell.h"

EquationCell::EquationCell(unsigned row, unsigned column, std::string value) : Cell(row, column, value)
{	
	this->myValue =  value;

	std::vector<std::string> parts;
	StringWork::separateEquation(value, parts);

	arguments[0] = parts[1];
	arguments[1] = parts[3];
	sign = parts[2];
}

std::string EquationCell::getValue() const
{
	return this->myValue;
}

double EquationCell::compareValue() const
{
	return 0.0;
}

bool EquationCell::getIsRefered() const
{
    return isRefered;
}

void EquationCell::setIsRefered(bool isRefered)
{
	this->isRefered = isRefered;
}

const std::string* EquationCell::getArguments() const
{
    return arguments;
}

double EquationCell::calculateWithGivenSigh(double agument1, double argument2) const
{
    if(sign == "+")
		return agument1 + argument2;
	else if(sign == "-")
		return agument1 - argument2;
	else if(sign == "*")
		return agument1 * argument2;
	else if(sign == "/"){
		if(argument2 == 0)
			throw std::invalid_argument("ERROR!");
		return agument1 / argument2;
	}
	else if(sign == "==")
		return (agument1 == argument2);
	else if(sign == "!=")
		return agument1 != argument2;
	else if(sign == ">")
		return agument1 > argument2;
	else if(sign == ">=")
		return agument1 >= argument2;
	else if(sign == "<")
		return agument1 < argument2;
	
	return agument1 <= argument2;
}
