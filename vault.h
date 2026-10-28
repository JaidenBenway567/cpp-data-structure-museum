// ===========================================================================
//  vault.h  --  PART 2.  YOU WRITE THIS FILE.
//
//  Your full name : Jaiden Benway
//  Vandal email   : benw5602@vandals.uidaho.edu
//
//  ---------------------------------------------------------------------------
//  CONTRACTOR A's design: ONE LONG SHELF.
//
//      slot:   0     1     2     3     4     5   ...
//            [ A ] [ B ] [ C ] [   ] [   ] [   ]
//             <-- count = 3 -->
//             <------------ capacity = 6 ------------>
//
//  "Want exhibit number 400? I walk straight to slot 400. Instant."
//
//  The Vault owns a dynamic array made with new[]. It tracks two numbers:
//      count     how many items are actually stored
//      capacity  how many slots exist
//  When count reaches capacity it must build a BIGGER array, copy everything
//  across, delete[] the old one, and carry on with the new one.
//
//  It is also a TEMPLATE. You write the logic once and it works for
//  Vault<Exhibit>, Vault<int>, or anything else. Do not write a Vault that
//  only knows about Exhibit.
//
//  WHERE DOES YOUR PERSONAL CAPACITY GO?
//      Not here. main.cpp hands it to your constructor. Your job is to STORE
//      and USE whatever number you are handed. Do not put a fixed 19, or 10,
//      or 11 inside this file.
// ===========================================================================

#ifndef VAULT_H
#define VAULT_H

#include "counters.h"

template <typename T>
class Vault
{
private:
    T*  items;       // the shelf itself, made with new[]
    int count;       // how many items are stored
    int capacity;    // how many slots exist
    int cursor;      // used only by the walk at the bottom of this file

    // -- grow --------------------------------------------------------------
    void grow()
    {
        int newCapacity = (capacity + 1) * 2;
        T* bigger = new T[newCapacity]; 
        bornArray();                      
        
        for (int i = 0; i < count; i++) 
        {
            bigger[i] = items[i];
            step();
        }
        delete[] items;
        diedArray();  
        items = bigger;  
        capacity = newCapacity;
    }

public:
    // -- constructor -------------------------------------------------------
    Vault(int startCapacity)
    {
        capacity = startCapacity;
        count    = 0;
        cursor   = 0;
        items    = new T[capacity];
        bornArray();
    }

    // -- destructor --------------------------------------------------------
    ~Vault()
    {
        delete[] items;
        diedArray();  
        items = 0;
    }

    // -- simple questions --------------------------------------------------
    int size() const
    {
        return count;
    }

    int getCapacity() const
    {
        return capacity;
    }

    // -- add at the END ----------------------------------------------------
    void pushBack(const T& value)
    {
       if (count == capacity) grow();
       items[count] = value;
       step(); 
       count++;
       (void)value;
    }

    // -- add at the FRONT --------------------------------------------------
    void insertFront(const T& value)
    {
        if (count == capacity) grow();
        for (int i = count; i > 0; i--)
        {
            items[i] = items[i - 1];
            step();   
        }
     
        items[0] = value;
        step();   
        count++;
        (void)value;
    }

    // -- add in the MIDDLE -------------------------------------------------
    void insertAt(int index, const T& value)
    {
        if (count == capacity) grow();
        for (int i = count; i > index; i--)
        {
            items[i] = items[i - 1];
            step();   
        }
        items[index] = value;
        step();    
        count++;
        (void)index; (void)value;
    }

    // -- look one up -------------------------------------------------------
    T& at(int index)
    {
        step();   
        return items[index];
    }

    // -- walking the whole thing, front to back ----------------------------
    void goToStart()
    {
        cursor = 0;
    }

    bool hasMore() const
    {
        if (cursor == count) 
            return false;
        else return true;
    }

    T& nextItem()
    {
        step();    
        return items[cursor++];
    }
};

#endif
