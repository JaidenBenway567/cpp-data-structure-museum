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

    int size() const
    {
        return count;
    }

    int getCapacity() const
    {
        return capacity;
    }

    void pushBack(const T& value)
    {
       if (count == capacity) grow();
       items[count] = value;
       step(); 
       count++;
       (void)value;
    }

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
