
#include <iostream>
#include "CmdManager.hpp"
#include "CmdDispatcher.hpp"
#include "CmdStreamReader.hpp"

using namespace std;

int main()
{
    //auto mgr = CmdManager::GetCmdManager();
        
    std::thread process([&]() {
        CmdDispatcher dispatcher;
        dispatcher.start();
        });

    CmdStreamReader sr;
    sr.start();

    process.join();

    return 0;
}

