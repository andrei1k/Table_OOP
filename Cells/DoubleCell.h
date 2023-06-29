#ifndef DOUBLECELL_H
#define DOUBLECELL_H

#include "Cell.h"

class DoubleCell : public Cell {

public:

    DoubleCell() = default;
    DoubleCell(unsigned row, unsigned column, std::string value);

    double getValue() const;
    virtual double compareValue() const override;

private:

    double myValue{};
};

#endif // !DOUBLECELL_H
