// ===========================================================================
//  counters.h  --  GIVEN TO YOU.  DO NOT CHANGE THIS FILE.
//
//  This is the museum's work log. It counts two things:
//
//    1. STEPS   - how much work your code did.
//                 You call step() yourself, in your own loops, in the places
//                 the comments in vault.h and corridor.h tell you to.
//
//    2. MEMORY  - how many arrays and rooms are alive right now.
//                 You call bornArray()/diedArray() and bornNode()/diedNode()
//                 every time you call new[]/delete[] and new/delete.
//
//  Nothing in here measures seconds. Seconds depend on your laptop and on
//  what else is running. Steps are the same on every machine, every time.
// ===========================================================================

#ifndef COUNTERS_H
#define COUNTERS_H

// ---- work ----------------------------------------------------------------

// One step = your code had to touch one item.
//   sliding an item across a slot      -> one step
//   walking through one corridor door  -> one step
//   copying an item into a bigger array-> one step
void step();

// How many steps since the last resetSteps().
long long steps();

// Put the step counter back to zero. main.cpp calls this before each job.
void resetSteps();

// ---- memory --------------------------------------------------------------

// Call bornArray() straight after   new T[capacity]
// Call diedArray() straight after   delete[] items
void bornArray();
void diedArray();

// Call bornNode() straight after    new Room<T>
// Call diedNode() straight after    delete here
void bornNode();
void diedNode();

// How many are alive right now. Both must be 0 at the end of the program.
int arraysAlive();
int roomsAlive();

// Prints the final memory report:
//    Arrays still alive : 0
//    Rooms  still alive : 0
//    CLEAN. Everything you built, you took down.
// Returns true if everything was cleaned up.
bool memoryReport();

#endif
