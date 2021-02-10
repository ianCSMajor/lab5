#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const =0;
};
class Select_Contain: public Select_Column
{
  private:
        const Spreadsheet* sheet;
        int  column;
        std::string  cell_string;

  public:
        Select_Contain(const Spreadsheet* sheet1, const std::string& column1, const std::string& s)
        {
                sheet=sheet1;
                column= sheet->get_column_by_name(column1);
                cell_string=s;

        }
        virtual bool select(const Spreadsheet* sheet1, int row) const
        {
                if(sheet->cell_data(row,column).find(cell_string)!= std::string::npos)
                {
                        return true;
                }
                return false;
        }

};
class Select_Not: public Select_Contains
{
	private:

	public:
		Select_Not(Select_Contains obj*)
			:Select_Contains(sheet1, column1, substring){}

		virtual bool select(const Spreadsheet* sheet1, int row) const{		
			return !(Select_Contains->select(sheet, row));
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
