// ===========================================================================
//  corridor.h  --  PART 3.  YOU WRITE THIS FILE.
//
//  Your full name : Jaiden Benway
//  Vandal email   : benw5602@vandals.uidaho.edu
//
//  ---------------------------------------------------------------------------
//  CONTRACTOR B's design: A CHAIN OF SMALL ROOMS.
//
//      first
//        |
//        v
//      [ A | * ] --> [ B | * ] --> [ C | 0 ]
//
//  Each Room holds ONE item and a door (a pointer) to the next Room.
//  The last Room's door points to nullptr. There are no room numbers.
//
//  "Want to add a room at the start? I just build it and point the door.
//   Nothing else moves."
//
//  The price: to reach room number N you must WALK. Start at the first room
//  and go through one door at a time until you arrive.
//
//  It is also a TEMPLATE, like the Vault. Write it once, and it works for
//  Corridor<Exhibit> and Corridor<int> alike.
// ===========================================================================

#ifndef CORRIDOR_H
#define CORRIDOR_H

#include "counters.h"

// ---------------------------------------------------------------------------
//  One room. Holds one item, and one door to the next room.
//  This is a struct on purpose: the Corridor is the only thing that touches
//  it, so there is nothing to hide from.
// ---------------------------------------------------------------------------
template <typename T>
struct Room
{
    T       item;   // what is on display in this room
    Room*   next;   // the door to the next room, or nullptr at the end

    Room(const T& value)
    {
        item = value;
        next = 0;   // a brand new room is the end of the chain until it is linked
        (void)value;
    }
};


template <typename T>
class Corridor
{
private:
    Room<T>* first;    // the front door of the whole corridor
    int      count;    // how many rooms exist
    Room<T>* cursor;   // used only by the walk at the bottom of this file

public:
    // -- constructor -------------------------------------------------------
    Corridor()
    {
        first  = 0;
        count  = 0;
        cursor = 0;
    }

    // -- destructor --------------------------------------------------------
    //
    //  THE MOST IMPORTANT FIVE LINES IN THIS FILE. READ THEM TWICE.
    //
    //  You are standing in a room, and the ONLY way to the rest of the
    //  corridor is the door in this room. If you knock this room down first,
    //  you have destroyed the door too, and everything past it is lost
    //  forever - still allocated, still taking memory, unreachable.
    //
    //      SAVE THE NEXT POINTER BEFORE YOU DELETE THE CURRENT ROOM.
    //
    ~Corridor()
    {
        Room<T>* here = first;
        while (here != 0)
        {
            Room<T>* nextOne = here->next;    
            delete here;
            diedNode();                       
            here = nextOne;
        }
        first = 0;  count = 0;
    }

    // -- simple question ---------------------------------------------------
    int size() const
    {
        return count;
    }

    // -- add at the FRONT --------------------------------------------------
    void insertFront(const T& value)
    {
        Room<T>* room = new Room<T>(value);
        bornNode();                         
        room->next = first;
        first = room;
        count++;
        step();                           
        (void)value;
    }

    // -- add at the END ----------------------------------------------------
    void pushBack(const T& value)
    {
        if(count == 0)
        {
            insertFront(value); 
        }    
        else 
        {
            Room<T>* here = first;
            while (here->next != 0)
            {
                here = here->next;
                step();                       
            }
            Room<T>* room = new Room<T>(value);
            bornNode();                        
            here->next = room;
            count++;
            step();                           
            (void)value;
        }
    }

    // -- add in the MIDDLE -------------------------------------------------
    void insertAt(int index, const T& value)
    {
        
        if (index == 0) insertFront(value);
        if (index == count) pushBack(value);
        else
        {
            Room<T>* before = first;
            for (int i = 0; i < index - 1; i++)
            {
                before = before->next;
                step();                   
            }
            Room<T>* room = new Room<T>(value);
            bornNode();                       
            room->next   = before->next;      
            before->next = room;              
            count++;
            step();                           
        (void)index; (void)value;
        }
    }

    // -- look one up -------------------------------------------------------
    T& at(int index)
    {
        Room<T>* here = first;
        for (int i = 0; i < index; i++)
        {
            here = here->next;
            step();                           
        }
        step();                               
        return here->item;
    }

    // -- walking the whole thing, front to back ----------------------------
    void goToStart()
    {
        cursor = first;
    }

    bool hasMore() const
    {
        if (cursor == nullptr)
        return false;
        else return true;
    }

    T& nextItem()
    {
        step();         

      T& item = cursor->item;
      cursor = cursor->next;
      return item;
      
    }
};

#endif
