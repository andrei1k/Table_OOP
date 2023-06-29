#include "StringCell.h"

StringCell::StringCell(unsigned row, unsigned column, std::string value) : Cell(row, column, value)
{
	this->myValue = value;

	if(this->myValue == "")
		return;

	bool first = true;
	for (unsigned i = 0; i < this->myValue.size(); i++) {
		if (this->myValue[i] == '\\') {
			if (first) {
				
				this->myValue.erase(i, 1);
				i--;
			}
			if (first)
				first = false;
			else
				first = true;
			continue;
		}
		first = true;

	}
	
	this->myValue.erase(0, 1);
	this->myValue.pop_back();
}

const std::string StringCell::getValue() const
{
	return this->myValue;
}

double StringCell::compareValue() const
{
	if (StringWork::isInt(this->getValue()) || StringWork::isDouble(this->getValue())) {

		return stod(this->getValue());
	}
	
	return 0;
}