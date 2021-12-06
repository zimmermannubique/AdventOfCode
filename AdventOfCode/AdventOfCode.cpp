//
//  main.cpp
//  AdventOfCode
//
//  Created by Marco Zimmermann on 01.12.21.
//

#include "AdventTask1.h"
#include "AdventTask2.h"
#include "AdventTask3.h"
#include "AdventTask4.h"
#include "AdventTask5.h"
#include "AdventTask6.h"

int main(int argc, const char * argv[])
{
    startAdventOfCode();
    
    AdventTask1 t1;
    t1.solveSilverTask();
    t1.solveGoldTask();

    AdventTask2 t2;
    t2.solveSilverTask();
    t2.solveGoldTask();

    AdventTask3 t3;
    t3.solveSilverTask();
    t3.solveGoldTask();

    AdventTask4 t4;
    t4.solveSilverTask();
    t4.solveGoldTask();

    AdventTask5 t5;
    t5.solveSilverTask();
    t5.solveGoldTask();

    AdventTask6 t6;
    t6.solveSilverTask();
    t6.solveGoldTask();

    return 0;
}
