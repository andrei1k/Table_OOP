#include <iostream>
#include <fstream>
#include "Cells/Cell.h"
#include "Cells/IntCell.h"
#include "Cells/DoubleCell.h"
#include "Cells/StringCell.h"

#include "Table/Table.h"

#include "MyProgram/MyProgram.h"

#include "StringWork/StringWork.h"


int main()
{

    // Testing type recognition

    // std::ifstream in("Txt tests/o.txt");
    // if(in.is_open()){
    //     char buffer[128];
    //     in.getline(buffer, 128);
    //     std::string s = buffer;
    //     std::cout << StringWork::typeOfString(s);
    //     in.close();

    //     return 0;
    // }
    // std::cout << "Can not open o.txt";

    // Test zapisvane vuv vektor ot stringove
    // std::string path = "table.txt";
    // std::vector<std::string> tableVals = StringWork::fileToString(path);

    // int cols = 1, rows = 1;
    // StringWork::numOfColumnsAndRowsInTable(path, cols, rows);
    // std::cout << "Cols: " << cols << " rows: " << rows << '\n';

    // std::cout << std::boolalpha << (cols*rows == tableVals.size()) << '\n';

    // for(int i = 0; i < tableVals.size(); i++){
    //     std::cout << tableVals[i];

    //     if((i + 1) % cols == 0) std::cout << '\n';
    //     else std::cout << '|';
    // }

    // division and typerecognition test
    // std::string path = "table.txt";
    // std::vector<std::string> tableVals = StringWork::fileToString(path);
    // unsigned cols = 1, rows = 1;
    // StringWork::numOfColumnsAndRowsInTable(path, cols, rows);

    // for(int i = 0; i < tableVals.size(); i++){
    //     std::cout << StringWork::typeOfString(StringWork::removeWhiteSpacesFromBothSides(tableVals[i]));

    //     if((i + 1) % cols == 0) std::cout << '\n';
    //     else std::cout << '|';
    // }
    
    
    // Error recognition test
    // std::string path = "table.txt";
    // std::vector<std::string> tableVals = StringWork::fileToString(path);
    // unsigned cols = 1, rows = 1;
    // StringWork::numOfColumnsAndRowsInTable(path, cols, rows);

    // for(int i = 0; i < tableVals.size(); i++){
    //     tableVals[i] = StringWork::removeWhiteSpacesFromBothSides(tableVals[i]);
    // }

    // StringWork::allValidParts(tableVals, cols);

    // Refering position check
    // Pair pos = StringWork::positionOfReferingCell("R1234C3222");
    // std::cout << pos.fst << ' ' << pos.snd;

    // std::string path = "table.txt", otherPath = "SavedAs.txt";
    // TableWork table;

    // table.load(path);
    // table.print();
    // table.edit(3, 2, "\"100.25\"");
    // table.print();
    // std::string* pPath = &otherPath;
    // table.save(pPath);

    MyProgram myProgram;
    MyProgram myProgram1;

    myProgram.running();

    return 0;
}
