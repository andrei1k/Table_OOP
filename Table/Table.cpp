#include "Table.h"

TableWork::Table::~Table()
{
	this->destroy();
}

void TableWork::Table::destroy()
{
	for (unsigned i = 0; i < this->valuesOfTable.size(); i++)
		if(this->valuesOfTable[i] != nullptr)
			delete this->valuesOfTable[i];

	this->valuesOfTable.resize(0);
	this->maxWidthOnColumn.resize(0);
	this->numOfColumns = 0;
	this->numOfRows = 0;
}

bool TableWork::load(const std::string& path){

	std::vector<std::string> tableVals = StringWork::fileToString(path);
	unsigned cols = 1, rows = 1;
    StringWork::numOfColumnsAndRowsInTable(path, cols, rows);

	for(int i = 0; i < tableVals.size(); i++){
        tableVals[i] = StringWork::removeWhiteSpacesFromBothSides(tableVals[i]);
    }

	if(!StringWork::allValidParts(tableVals, cols))
		return false;
	
	table.destroy();

	this->path = path;
	this->table.numOfColumns = cols;
	this->table.numOfRows = rows;

	for(unsigned i = 0; i < table.numOfRows; i++){

		for(unsigned j = 0; j < table.numOfColumns; j++){

			unsigned index = i*table.numOfColumns + j;
			table.valuesOfTable.push_back(CellWork::createCell(i, j, tableVals[index]));
			if(table.valuesOfTable.back() == nullptr){
				table.destroy();
				throw std::runtime_error("Coult not allocate memory and load table!\n");
			}
		}
	}

	return true;

}

void TableWork::save(const std::string* path = nullptr) const
{

	std::string copy = this->path;
	if(path != nullptr)
		copy = *path;

	std::ofstream out(copy);
	if (!out.is_open()) {
		std::cout << "Can not save table in this file.";
		return;
	}

	for (unsigned i = 0; i < this->table.valuesOfTable.size(); i++) {

		out << this->table.valuesOfTable[i]->val();
		if(!out.good()){
			std::cout << "Some problem with " << copy << " occured!\n";
			break;
		}

		if(((i + 1) % this->table.numOfColumns == 0) && (i != this->table.valuesOfTable.size() - 1)) out << '\n';
        else out << ',';

		if(!out.good()){
			std::cout << "Some problem with " << copy << " occured!\n";
			break;
		}
	}
	out.close();
}

void TableWork::print() const
{
	std::vector<std::string> printableValues;
	std::vector<unsigned> maxWidthOnCol;

	printableValues = tableValuesToPrintableValues(maxWidthOnCol);

	for(int i = 0; i < printableValues.size(); i++){

		std::cout << printableValues[i];

		for(unsigned j = 0; j < maxWidthOnCol[i % table.numOfColumns] - printableValues[i].size(); j++){
			std::cout << " ";
		}

		if((i + 1) % this->table.numOfColumns == 0) std::cout << "|\n";
        else std::cout << '|';
	}
}

void TableWork::edit(unsigned row, unsigned column, const std::string& newValue)
{
	if (StringWork::isInvalid(newValue) || column > this->table.numOfColumns || column < 1 || row > this->table.numOfRows || row < 1) {
		throw std::invalid_argument("Invalid arguments are entered.\n");
	}

	int index = (row - 1) * this->table.numOfColumns + column - 1;
	Cell* edited = CellWork::createCell(row, column, newValue);
	if(edited == nullptr){
		throw std::runtime_error("Coult not allocate memory and edit cell!\n");
	}
	delete this->table.valuesOfTable[index];
	this->table.valuesOfTable[index] = edited;
}

const std::string TableWork::getPath() const
{
    return path;
}

std::string TableWork::evaluateEquation(EquationCell *eq) const
{
	std::string err = "";
	double evaluated = evaluateEquation(eq, err);

	if(err == ""){
 
		std::string result = std::to_string(evaluated);
		result.erase(result.find_last_not_of('0') + 1, std::string::npos);
		result.erase(result.find_last_not_of('.') + 1, std::string::npos);
		return result;
	}
	
	return err;
}

double TableWork::evaluateEquation(EquationCell *eq, std::string& err) const
{

	if(eq->getIsRefered() == true){

		eq->setIsRefered(false);
		err = "SelfRegering!";
		return 0;
	}

    eq->setIsRefered(true);

	double argument1, argument2;

	try{
		argument1 = evaluateArgument(eq->getArguments()[0], err);
		argument2 = evaluateArgument(eq->getArguments()[1], err);

		eq->setIsRefered(false);
		return eq->calculateWithGivenSigh(argument1, argument2);
	}
	catch(const std::exception& ex){

		eq->setIsRefered(false);
		err = ex.what();
	}

	return 0;	
}

double TableWork::evaluateArgument(const std::string& argument, std::string& err) const
{
	if(StringWork::isReferingCell(argument)){

		Pair positionOfRef1 = StringWork::positionOfReferingCell(argument);

		int index = getIndexFromPosition(positionOfRef1);

		if(index < 0 || index >= this->table.numOfRows * this->table.numOfColumns || this->table.numOfColumns < positionOfRef1.snd)
			return 0;

		if(!StringWork::isEquation(table.valuesOfTable[index]->val())){
			return table.valuesOfTable[index]->compareValue();
		}
		else{

			EquationCell* arg1 =  dynamic_cast<EquationCell*>(table.valuesOfTable[index]);
			return evaluateEquation(arg1, err);
		}
	}

	return stod(argument);
}

std::vector<std::string> TableWork::tableValuesToPrintableValues(std::vector<unsigned>& maxWidthOnCol) const
{
	maxWidthOnCol.resize(0);
	for(int i = 0; i < table.numOfColumns; i++)
		maxWidthOnCol.push_back(0);

	std::vector<std::string> printableValues;
	for(int i = 0; i < this->table.valuesOfTable.size(); i++){

		if(StringWork::isString(this->table.valuesOfTable[i]->val()))
			printableValues.push_back(dynamic_cast<StringCell*>(this->table.valuesOfTable[i])->getValue());
		else if(StringWork::isEquation(this->table.valuesOfTable[i]->val())){
			
			EquationCell* eq = dynamic_cast<EquationCell*>(this->table.valuesOfTable[i]);
			printableValues.push_back(evaluateEquation(eq));
		}
		else 
			printableValues.push_back(this->table.valuesOfTable[i]->val());  

		if(maxWidthOnCol[i % table.numOfColumns] < printableValues.back().size())
			maxWidthOnCol[i % table.numOfColumns] = printableValues.back().size();

    }
 
	return printableValues;
}

int TableWork::getIndexFromPosition(const Pair& position) const
{
    return ((position.fst - 1) * this->table.numOfColumns) + (position.snd - 1);
}