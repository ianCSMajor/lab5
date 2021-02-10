#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};
class Select_Contains: public Select_Column
{
	private:
	//int column;
	std::string cell_string;
	public:

	Select_Contains(const Spreadsheet* sheetl, std::string column1, std::string substring)
		:Select_Column(sheet, name)
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
		
};	
class Select_Not: public Select
{
	private:
	Select *select = nullptr; 
	public:
		Select_Not(Select* new_select){
		select = new_select;}
		
			//:Select(sheet1, column1, substring){}

		virtual bool select(const Spreadsheet* sheet1, int row) const{		
			return !(select->select(sheet1, row));
				}
~Select_Not(){ delete select;}
};
class Select_And: public Select_Not
{
	private:
	//different constructor //two select pointers //two differerent select contains //two different deletes //if statement if it contains the object
	public:
	Select_And(Select_Contains obj*, Select_Not obj2*)
		:Select_Contains(sheet1, column1, substring){}
	virtual bool select(const Spreadsheet* sheet1, int row) const{
		
		}		


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
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

#endif //__SELECT_HPP__
