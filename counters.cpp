#include "counters.h"
#include <iostream>
using namespace std;

namespace {
    long long g_steps   = 0;   // work done since the last reset
    int       g_arrays  = 0;   // arrays alive right now
    int       g_rooms   = 0;   // rooms alive right now
}

// ---- work ----------------------------------------------------------------

void step()           { g_steps++; }
long long steps()     { return g_steps; }
void resetSteps()     { g_steps = 0; }

// ---- memory --------------------------------------------------------------

void bornArray()      { g_arrays++; }
void diedArray()      { g_arrays--; }
void bornNode()       { g_rooms++; }
void diedNode()       { g_rooms--; }

int arraysAlive()     { return g_arrays; }
int roomsAlive()      { return g_rooms; }

bool memoryReport()
{
    cout << "\n";
    cout << "Arrays still alive : " << g_arrays << "\n";
    cout << "Rooms  still alive : " << g_rooms  << "\n";

    if (g_arrays == 0 && g_rooms == 0)
    {
        cout << "CLEAN. Everything you built, you took down.\n";
        return true;
    }

    cout << "LEAK.  Something you built is still standing.\n";
    if (g_arrays > 0) cout << "       " << g_arrays << " array(s) were never delete[]'d.\n";
    if (g_rooms  > 0) cout << "       " << g_rooms  << " room(s) were never delete'd.\n";
    if (g_arrays < 0 || g_rooms < 0)
        cout << "       A negative count means you reported more deaths than births.\n";
    return false;
}
