#include <cstring>
#include <iostream>
#include "Spreadsheet.hpp"
using namespace std;
class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

class Select_Not: public Select
{
	private:
	Select *select_ptr = nullptr; 
	public:
		Select_Not(Select* new_select){
		select_ptr = new_select;}
		
			//:Select(sheet1, column1, substring){}

		virtual bool select(const Spreadsheet* sheet1, int row) const{		
			return !(select_ptr->select(sheet1, row));
				}
~Select_Not(){ delete select_ptr;}

};
// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
	Spreadsheet* sheet_new;
	std::string& name1;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
		sheet_new = sheet;
		name1 = name; 
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};
class Select_Contains: public Select_Column
{
	private:
	//int column;
	std::string cell_string;
	public:

	Select_Contains(const Spreadsheet* sheetl, std::string column1, std::string substring, const std::string& name)
		:Select_Column(sheet_new, name1)
		{
		//sheet = sheet1;	
		//column = sheet->get_column_by_name(column1);
		cell_string = substring;	
		}
	virtual bool select(const Spreadsheet* sheet, int row) const 
	{
		if(sheet->cell_data(row, column).find(cell_string) != std::string::npos){
			return true;
		}
		return false;
	}
		~Select_Contains(){}
};
class Select_And: public Select
{
	//different constructor //two select pointers //two differerent select contains //two different deletes //if statement if it contains the object
		private:
	Select* arg;
	Select* arg2;
	public:
	Select_And(Select* obj, Select* obj2)
		:Select(){ arg = obj; arg2 = obj2;}
	virtual bool select(const Spreadsheet* sheet1, int row) const{
		return (arg->select(sheet1, row) || arg2->select(sheet1, row)); 
		}
	~Select_And(){delete arg;
		delete arg2;}
};
class Select_Or: public Select
{
	private:
	Select* arg;
	Select* arg2;
	public:
	Select_Or(Select* obj, Select* obj2)
		:Select(){ arg = obj; arg2 = obj2;}
	virtual bool select(const Spreadsheet* sheet1, int row) const{
		return (arg->select(sheet1, row) || arg2->select(sheet1, row)); 
		}
	~Select_Or(){delete arg;
		delete arg2;}


};	
