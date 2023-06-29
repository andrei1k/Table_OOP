#ifndef TABLE_H
#define TABLE_H

#include <exception>
#include <fstream>
#include <vector>

#include "../Cells/Cell.h"
#include "../Cells/IntCell.h"
#include "../Cells/DoubleCell.h"
#include "../Cells/StringCell.h"
#include "../Cells/EquationCell.h"
#include "../Cells/CellWork.h"

class TableWork {

public:

	// copy and = are deleted;
	TableWork() = default;
	bool load(const std::string& path);
	void save(const std::string* path) const;
	void print() const;
	void edit(unsigned row, unsigned column, const std::string& newValue);

	const std::string getPath() const;

private:

	class Table{

		public:

			Table() = default;
			// This code will not be changed and cc and operator= will not be needed.
			// If someone override my code and needs them he has to write them!
			Table(const Table& copy) = delete;
			Table& operator=(const Table& copy) = delete;
			~Table();

		public:

			std::vector<Cell*> valuesOfTable{};
			std::vector<unsigned> maxWidthOnColumn{};
			unsigned numOfColumns{};
			unsigned numOfRows{};

			void destroy();
	};

	Table table{};
	std::string path{};
	bool isOpen = false;

private:
	// Methods for evaluating EquationCell because they have no meaning outside of tables
	std::string evaluateEquation(EquationCell *eq) const;
	double evaluateEquation(EquationCell* eq, std::string& err) const;
	int getIndexFromPosition(const Pair& position) const;
	double evaluateArgument(const std::string& argument, std::string& err) const;

	std::vector<std::string> tableValuesToPrintableValues(std::vector<unsigned>& maxWidthOnCol) const;

};

#endif // !TABLE_H

