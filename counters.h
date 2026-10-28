#ifndef COUNTERS_H
#define COUNTERS_H

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
// Returns true if everything was cleaned up.
bool memoryReport();

#endif
