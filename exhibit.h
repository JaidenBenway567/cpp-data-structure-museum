// ===========================================================================
//  exhibit.h  --  PART 1.  YOU WRITE THIS FILE.
//
//  Your full name : Jaiden Benway
//  Vandal email   : benw5602@vandals.uidaho.edu
//
//  ---------------------------------------------------------------------------
//  ONE exhibit in the museum. It has three pieces of data:
//
//        name    what the thing is called
//        year    the year it is from
//        value   what it is worth
//
//  All three are PRIVATE. Think of them as a locked display case: code outside
//  this class cannot reach in and change them directly. Every change has to go
//  through a setter, and the setter is the guard on the case.
//
//  THE TWO RULES THE GUARD ENFORCES
//      setYear  rejects anything before year 1 or after year 2026.
//      setValue rejects anything negative.
//
//  A REJECTED VALUE MUST LEAVE THE OLD VALUE ALONE.
//      Print the message, return, and change nothing.
//      If value is already 250 and someone calls setValue(-20),
//      then value must still be 250 afterwards.
//
//  Exhibit must have a default constructor. Vault stores its items in an
//  array made with new T[capacity], and that needs to build empty Exhibits.
//  An empty Exhibit is exactly:   name = ""    year = 2026    value = 0
// ===========================================================================

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

    // -- getters -----------------------------------------------------------
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

    // -- setters : this is where the rules live ----------------------------
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
