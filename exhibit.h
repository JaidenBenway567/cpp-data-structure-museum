#ifndef EXHIBIT_H
#define EXHIBIT_H

#include <string>
#include <iostream>

class Exhibit
{
private:
    std::string name;
    int year;
    double value;

public:
    // -- constructors ------------------------------------------------------
    Exhibit()
    {
        name = "";
        year  = 2026; 
        value = 0;
    }

    Exhibit(std::string startName, int startYear, double startValue)
    {
        name = "";
        year  = 2026;     
        value = 0;
        setName(startName);
        setYear(startYear);
        setValue(startValue);
    }

    std::string getName() const
    {
        return name;
    }

    int getYear() const
    {
        return year;
    }

    double getValue() const
    {
        return value;
    }

    void setName(std::string newName)
    {
        name = newName;
    }

    void setYear(int newYear)
    {
        if (newYear < 1 || newYear > 2026)
        {
            std::cout << "Rejected year: " << newYear << "\n";
            return;
        }
       else
        year = newYear;
    }

    void setValue(double newValue)
    {
        if (newValue < 0.0)
        {
            std::cout << "Rejected value: " << newValue << "\n";
            return;
        }
        else
        value = newValue;
    }
};

#endif
