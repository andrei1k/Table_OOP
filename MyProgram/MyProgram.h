#ifndef MYPROGRAM_H
#define MYPROGRAM_H

#include <iostream>
#include "../Table/Table.h"

class MyProgram{

public:

    // copy and = are deleted;
    MyProgram() = default;

    void running();

private:

    void open(const std::string& path);
    void close();
    void exit();
    void save(const std::string* path) const;
    bool getIsOpen() const;
private:

    bool isOpen = false;
    bool toExit = false;
    TableWork table{};
};


#endif // !MYPROGRAM_H
