
#include <iostream>
#include "CmdManager.hpp"
#include "CmdDispatcher.hpp"
#include "CmdStreamReader.hpp"

using namespace std;

int main()
{
    std::thread cmdEditor([&]() {
        auto mgr = CmdManager::GetCmdManager();
        mgr.start();
    });

    cmdEditor.join();
    std::thread process([&]() {
        cout << "\n------Dispatcher successfully started.\n"; 
        CmdDispatcher dispatcher;
        dispatcher.start();
    });
    
    std::thread byteFeeder([&]() {
        cout << "\n------Stream bytes reader successfully started.\n";
        CmdLineStreamReader sr;
        sr.start();
    });


    process.join();
    byteFeeder.join();

    return 0;
}

