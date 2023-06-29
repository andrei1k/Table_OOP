#include "Cell.h"
Cell::Cell(unsigned row, unsigned column, std::string value) : position(row, column), value(value) {}

std::string Cell::val() const 
{
	return this->value;
}

Pair Cell::getPosition() const
{
	return this->position;
}