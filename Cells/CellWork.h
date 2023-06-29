#ifndef CELLWORK_H
#define CELLWORK_H

#include "Cell.h"
#include "IntCell.h"
#include "DoubleCell.h"
#include "StringCell.h"
#include "EquationCell.h"

#include <new>

class CellWork{

public:

    static Cell* createCell(unsigned row, unsigned column, std::string value)
	{
		value = StringWork::removeWhiteSpaces(value);

		if(StringWork::isInt(value)){
			return new  (std::nothrow) IntCell(row, column, value);
		}
		else if(StringWork::isDouble(value)){
			return new  (std::nothrow) DoubleCell(row, column, value);
		}
		else if(StringWork::isString(value)){
			return new (std::nothrow) StringCell(row, column, value);
		}
		else if(StringWork::isEquation(value)){
			return new (std::nothrow) EquationCell(row, column, value);
		}

		throw std::invalid_argument(value);
	}
};

#endif // !CELLWORK_H 