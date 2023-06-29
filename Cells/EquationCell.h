#ifndef EQUATIONCELL_H
#define EQUATIONCELL_H

#include "Cell.h"


class EquationCell : public Cell {

public:

    EquationCell() = default;
    EquationCell(unsigned row, unsigned column, std::string value);

    std::string getValue() const;
    virtual double compareValue() const override;

    bool getIsRefered() const;
    void setIsRefered(bool isRefered);

    const std::string* getArguments() const;
    double calculateWithGivenSigh(double agument1, double argument2) const;

private:

    std::string myValue{};
    std::string arguments[2];
    std::string sign;

    bool isRefered = false;

};

#endif // !EQUATIONCELL_H