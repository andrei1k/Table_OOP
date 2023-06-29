#ifndef STRINGCELL_H
#define STRINGCELL_H

#include "Cell.h"

class StringCell : public Cell {

public:

	StringCell() = default;
	StringCell(unsigned row, unsigned column, std::string value);

	const std::string getValue() const;
	virtual double compareValue() const override;

private:

	std::string myValue{};
};

#endif // !STRINGCELL_H