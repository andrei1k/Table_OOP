#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <exception>
#include <vector>
#include <string>

#include "../StringWork/StringWork.h"
#include "Pair.h"

class Cell {

public:

    Cell() = default;
    Cell(unsigned row, unsigned column, std::string value);
    virtual ~Cell() = default;
    // operatoor=() and copy ctor are by defaut

    std::string val() const;
    Pair getPosition() const;
    virtual double compareValue() const = 0;

protected:

    Pair position{};
    std::string value{};

};
#endif // !CELL_H
