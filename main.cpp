#include <iostream>
#include <iomanip>
#include <string>

#include "counters.h"
#include "exhibit.h"
#include "vault.h"
#include "corridor.h"

using namespace std;


const int START_CAPACITY = 13;    
static int passedCount = 0;
static int failedCount = 0;

static void check(int number, const string& what, bool ok)
{
    cout << (ok ? "  PASS  " : "  FAIL  ")
         << setw(2) << number << ". " << what << "\n";
    if (ok) passedCount++; else failedCount++;
}

static Exhibit sample(int i)
{
    return Exhibit("Item", 1900 + (i % 100), 10.0 + i);
}


// ===========================================================================
//  PART 1 CHECKS - the Exhibit
// ===========================================================================
static void checkExhibit()
{
    cout << "\nPART 1 - Exhibit\n";
    cout << "  (the 'Rejected ...' lines below are supposed to appear)\n";

    // 1. default constructor
    Exhibit empty;
    check(1, "Exhibit() makes an empty exhibit (name \"\", year 2026, value 0)",
          empty.getName() == "" && empty.getYear() == 2026 && empty.getValue() == 0.0);

    // 2. three-argument constructor
    Exhibit m("Meteorite", 1969, 250.0);
    check(2, "Exhibit(name, year, value) stores all three",
          m.getName() == "Meteorite" && m.getYear() == 1969 && m.getValue() == 250.0);

    // 3. setters accept good values
    Exhibit s("Sneaker", 1985, 40.0);
    s.setName("Old Sneaker");
    s.setYear(1984);
    s.setValue(45.5);
    check(3, "setName / setYear / setValue accept good values",
          s.getName() == "Old Sneaker" && s.getYear() == 1984 && s.getValue() == 45.5);

    // 4. setYear rejects and keeps the old value
    m.setYear(0);
    bool keptA = (m.getYear() == 1969);
    m.setYear(2027);
    bool keptB = (m.getYear() == 1969);
    check(4, "setYear rejects year 0 and year 2027, and keeps the old year",
          keptA && keptB);

    // 5. setValue rejects and keeps the old value
    m.setValue(-20.0);
    check(5, "setValue rejects -20 and leaves the value at 250", m.getValue() == 250.0);
}


// ===========================================================================
//  PART 2 CHECKS - the Vault
// ===========================================================================
static void checkVault()
{
    cout << "\nPART 2 - Vault\n";

    // 6. a fresh Vault
    {
        Vault<Exhibit> v(START_CAPACITY);
        check(6, "a new Vault has size 0 and the capacity main.cpp handed it",
              v.size() == 0 && v.getCapacity() == START_CAPACITY);
    }

    // 7. pushBack keeps order, at() reads it back
    {
        Vault<Exhibit> v(START_CAPACITY);
        v.pushBack(Exhibit("A", 2000, 1.0));
        v.pushBack(Exhibit("B", 2000, 2.0));
        v.pushBack(Exhibit("C", 2000, 3.0));
        check(7, "pushBack puts items at the end: A B C",
              v.size() == 3 &&
              v.at(0).getName() == "A" &&
              v.at(1).getName() == "B" &&
              v.at(2).getName() == "C");
    }

    // 8. insertFront shifts the right way
    {
        Vault<Exhibit> v(START_CAPACITY);
        v.pushBack(Exhibit("A", 2000, 1.0));
        v.pushBack(Exhibit("B", 2000, 2.0));
        v.pushBack(Exhibit("C", 2000, 3.0));
        v.insertFront(Exhibit("N", 2000, 9.0));
        check(8, "insertFront gives N A B C, losing nothing",
              v.size() == 4 &&
              v.at(0).getName() == "N" &&
              v.at(1).getName() == "A" &&
              v.at(2).getName() == "B" &&
              v.at(3).getName() == "C");
    }

    // 9. insertAt in the middle
    {
        Vault<Exhibit> v(START_CAPACITY);
        v.pushBack(Exhibit("A", 2000, 1.0));
        v.pushBack(Exhibit("B", 2000, 2.0));
        v.pushBack(Exhibit("C", 2000, 3.0));
        v.insertAt(1, Exhibit("N", 2000, 9.0));
        check(9, "insertAt(1, N) gives A N B C",
              v.size() == 4 &&
              v.at(0).getName() == "A" &&
              v.at(1).getName() == "N" &&
              v.at(2).getName() == "B" &&
              v.at(3).getName() == "C");
    }

    // 10. insertAt at the very end
    {
        Vault<Exhibit> v(START_CAPACITY);
        v.pushBack(Exhibit("A", 2000, 1.0));
        v.pushBack(Exhibit("B", 2000, 2.0));
        v.insertAt(2, Exhibit("N", 2000, 9.0));
        check(10, "insertAt(size, N) behaves like pushBack: A B N",
              v.size() == 3 &&
              v.at(0).getName() == "A" &&
              v.at(1).getName() == "B" &&
              v.at(2).getName() == "N");
    }

    // 11. growth, and the destructor giving the array back
    int arraysBefore = arraysAlive();
    bool grewOk = false;
    {
        Vault<Exhibit> v(START_CAPACITY);
        int howMany = START_CAPACITY + 5;
        for (int i = 0; i < howMany; i++) v.pushBack(sample(i));

        bool capacityGrew = (v.getCapacity() > START_CAPACITY);
        bool allThere     = (v.size() == howMany);
        for (int i = 0; i < howMany && allThere; i++)
            if (v.at(i).getValue() != 10.0 + i) allThere = false;

        grewOk = capacityGrew && allThere;
    }
    bool arraysGivenBack = (arraysAlive() == arraysBefore);
    check(11, "the Vault grows past its start capacity, keeps every item in "
              "order, and gives the array back", grewOk && arraysGivenBack);

    // 12. the template, and the walk
    {
        Vault<int> numbers(START_CAPACITY);
        for (int i = 0; i < 10; i++) numbers.pushBack(i * i);

        numbers.goToStart();
        int seen = 0;
        bool inOrder = true;
        while (numbers.hasMore())
        {
            int value = numbers.nextItem();
            if (value != seen * seen) inOrder = false;
            seen++;
        }
        check(12, "Vault<int> works too, and walking it visits all 10 in order",
              seen == 10 && inOrder);
    }
}


// ===========================================================================
//  PART 3 CHECKS - the Corridor
// ===========================================================================
static void checkCorridor()
{
    cout << "\nPART 3 - Corridor\n";

    // 13. a fresh Corridor
    {
        Corridor<Exhibit> c;
        check(13, "a new Corridor has size 0", c.size() == 0);
    }

    // 14. pushBack keeps order
    {
        Corridor<Exhibit> c;
        c.pushBack(Exhibit("A", 2000, 1.0));
        c.pushBack(Exhibit("B", 2000, 2.0));
        c.pushBack(Exhibit("C", 2000, 3.0));
        check(14, "pushBack links rooms in order: A B C",
              c.size() == 3 &&
              c.at(0).getName() == "A" &&
              c.at(1).getName() == "B" &&
              c.at(2).getName() == "C");
    }

    // 15. insertFront
    {
        Corridor<Exhibit> c;
        c.pushBack(Exhibit("A", 2000, 1.0));
        c.pushBack(Exhibit("B", 2000, 2.0));
        c.insertFront(Exhibit("N", 2000, 9.0));
        check(15, "insertFront gives N A B, and the old first room is still there",
              c.size() == 3 &&
              c.at(0).getName() == "N" &&
              c.at(1).getName() == "A" &&
              c.at(2).getName() == "B");
    }

    // 16. insertAt in the middle
    {
        Corridor<Exhibit> c;
        c.pushBack(Exhibit("A", 2000, 1.0));
        c.pushBack(Exhibit("B", 2000, 2.0));
        c.pushBack(Exhibit("C", 2000, 3.0));
        c.insertAt(1, Exhibit("N", 2000, 9.0));
        check(16, "insertAt(1, N) gives A N B C, and the tail is not lost",
              c.size() == 4 &&
              c.at(0).getName() == "A" &&
              c.at(1).getName() == "N" &&
              c.at(2).getName() == "B" &&
              c.at(3).getName() == "C");
    }

    // 17. insertAt at the very end
    {
        Corridor<Exhibit> c;
        c.pushBack(Exhibit("A", 2000, 1.0));
        c.pushBack(Exhibit("B", 2000, 2.0));
        c.insertAt(2, Exhibit("N", 2000, 9.0));
        check(17, "insertAt(size, N) puts N last: A B N",
              c.size() == 3 &&
              c.at(0).getName() == "A" &&
              c.at(1).getName() == "B" &&
              c.at(2).getName() == "N");
    }

  
    //  NOTE: there is deliberately no check here for the Corridor destructor.
    {
        Corridor<Exhibit> c;
        for (int i = 0; i < 50; i++) c.pushBack(sample(i));
        check(18, "50 rooms link up in order: first, middle and last all right",
              c.size() == 50 &&
              c.at(0).getValue()  == 10.0 &&
              c.at(25).getValue() == 35.0 &&
              c.at(49).getValue() == 59.0);
    }

    // 19. the template, and the walk
    {
        Corridor<int> numbers;
        for (int i = 0; i < 10; i++) numbers.pushBack(i * i);

        numbers.goToStart();
        int seen = 0;
        bool inOrder = true;
        while (numbers.hasMore())
        {
            int value = numbers.nextItem();
            if (value != seen * seen) inOrder = false;
            seen++;
        }
        check(19, "Corridor<int> works too, and walking it visits all 10 in order",
              seen == 10 && inOrder);
    }
}

template <typename BoxType>
static void loadBox(BoxType& box, int n)
{
    for (int i = 0; i < n; i++) box.pushBack(sample(i));
    resetSteps();
}

// Job 1 - Load from the front. n new exhibits, each one goes at the very front.
template <typename BoxType>
static long long job1(BoxType& box, int n)
{
    resetSteps();
    for (int i = 0; i < n; i++) box.insertFront(sample(i));
    return steps();
}

// Job 2 - Look up every item. Ask for exhibit 0, then 1, then 2, all the way up.
template <typename BoxType>
static long long job2(BoxType& box, int n)
{
    loadBox(box, n);
    double sink = 0;
    for (int i = 0; i < n; i++) sink += box.at(i).getValue();
    if (sink < 0) cout << "";          // stops the compiler discarding the loop
    return steps();
}

// Job 3 - 200 inserts in the middle.
template <typename BoxType>
static long long job3(BoxType& box, int n)
{
    loadBox(box, n);
    for (int i = 0; i < 200; i++) box.insertAt(box.size() / 2, sample(i));
    return steps();
}

// Job 4 - Walk once and total. Add up the value of the whole collection.
template <typename BoxType>
static long long job4(BoxType& box, int n)
{
    loadBox(box, n);
    double total = 0;
    box.goToStart();
    while (box.hasMore()) total += box.nextItem().getValue();
    if (total < 0) cout << "";         // same reason as above
    return steps();
}


static void raceHeader(const string& title, const string& what)
{
    cout << "\n" << title << "\n";
    cout << "  " << what << "\n";
    cout << "  " << setw(8) << "n"
         << setw(18) << "Vault steps"
         << setw(18) << "Corridor steps" << "\n";
}

static void raceRow(int n, long long vaultSteps, long long corridorSteps)
{
    cout << "  " << setw(8) << n
         << setw(18) << vaultSteps
         << setw(18) << corridorSteps << "\n";
}

static void runTheRace()
{
    const int sizes[3] = { 1000, 2000, 4000 };

    cout << "\n";
    cout << "===========================================================\n";
    cout << " THE RACE - steps, not seconds\n";
    cout << "===========================================================\n";

    raceHeader("Job 1 - Load from the front",
               "every new exhibit goes at the very front");
    for (int k = 0; k < 3; k++)
    {
        int n = sizes[k];
        Vault<Exhibit>    v(START_CAPACITY);
        Corridor<Exhibit> c;
        long long a = job1(v, n);
        long long b = job1(c, n);
        raceRow(n, a, b);
    }

    raceHeader("Job 2 - Look up every item",
               "ask for exhibit 0, then 1, then 2, all the way up");
    for (int k = 0; k < 3; k++)
    {
        int n = sizes[k];
        Vault<Exhibit>    v(START_CAPACITY);
        Corridor<Exhibit> c;
        long long a = job2(v, n);
        long long b = job2(c, n);
        raceRow(n, a, b);
    }

    raceHeader("Job 3 - 200 inserts in the middle",
               "the curator adds 200 exhibits halfway along the tour");
    for (int k = 0; k < 3; k++)
    {
        int n = sizes[k];
        Vault<Exhibit>    v(START_CAPACITY);
        Corridor<Exhibit> c;
        long long a = job3(v, n);
        long long b = job3(c, n);
        raceRow(n, a, b);
    }

    raceHeader("Job 4 - Walk once and total",
               "add up the value of the whole collection");
    for (int k = 0; k < 3; k++)
    {
        int n = sizes[k];
        Vault<Exhibit>    v(START_CAPACITY);
        Corridor<Exhibit> c;
        long long a = job4(v, n);
        long long b = job4(c, n);
        raceRow(n, a, b);
    }

    cout << "\n  Look DOWN each column. When n doubles, does the number stay\n"
         << "  about the same, roughly double, or roughly quadruple?\n";
}


// ===========================================================================
int main()
{
    cout << "===========================================================\n";
    cout << " THE MUSEUM OF EVERYTHING\n";
    cout << " Starting Vault capacity in use: " << START_CAPACITY << "\n";
    cout << "===========================================================\n";

    if (START_CAPACITY <= 0)
    {
        cout << "\nSTART_CAPACITY must be a positive number. "
                "Set it at the top of main.cpp.\n";
        return 1;
    }

    checkExhibit();
    checkVault();
    checkCorridor();

    cout << "\n-----------------------------------------------------------\n";
    cout << " " << passedCount << " of " << (passedCount + failedCount)
         << " checks passed.\n";
    cout << "-----------------------------------------------------------\n";

    if (failedCount > 0)
    {
        cout << "\nThe race does NOT run until all 19 checks pass.\n";
        cout << "Fix ONE failing check, rebuild, and run again.\n";
        memoryReport();
        return 1;
    }

    runTheRace();

    cout << "\n===========================================================\n";
    cout << " MEMORY\n";
    cout << "===========================================================";
    bool clean = memoryReport();

    return clean ? 0 : 1;
}
