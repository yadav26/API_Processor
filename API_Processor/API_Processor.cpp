// API_Processor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include "CmdManager.hpp"

using namespace std;

int main()
{
    auto mgr = CmdManager::GetCmdManager();

    std::cout << "Hello World!\n";
}

