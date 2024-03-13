/***********************************************************************************************
        Anshul Yadav
        er.anshulyadav@gmail.com
        yadav26@github
        This is for tritium api processor
************************************************************************************************/

#include <thread>
#include <iostream>
#include "CmdManager.hpp"
#include "CmdStreamReader.hpp"

using namespace std;

int main()
{
    //std::thread cmdEditor([&]() {
    //    auto mgr = CmdManager::GetCmdManager();
    //    mgr.start();
    //});
    //cmdEditor.join();
  
    std::thread byteFeeder([&]() {
        cout << "\n------Byte stream reader started successfully.\n";
        CmdLineStreamReader sr;
        sr.start();
    });
    byteFeeder.join();
    return 0;
}

