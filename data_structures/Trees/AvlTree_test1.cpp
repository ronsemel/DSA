#include <iostream>
#include <vector>
#include "Trees/AvlTree.h"
#include <ctime>
#include <cassert>
#define NUMBER_OF_TESTS 1

bool(*tests[])(void) = 
{
    testInsertKeepsOrder
};
const char* testNames[] = 
{
    "testInsertKeepsOrder"
};

int main(int argc, char* argv[])
{
    srand(time(NULL));
    if(argc == 1)
    {
        for(int test_idx = 0; test_idx<NUMBER_OF_TESTS;++test_idx)
        {
            
        }
    }
}