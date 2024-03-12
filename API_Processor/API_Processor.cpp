
#include <iostream>
#include "CmdValidator.hpp"
#include "CmdManager.hpp"

using namespace std;

int main()
{
    auto mgr = CmdManager::GetCmdManager();
    CmdValidator c;
    auto s = "[  C M N D][8 ][ A C T I V A T E ][T  X T][2 7][TAAAA   AP YOUR CREDIT CARD][  AMO UNT ][3][4AB ] [  T X  T  ][2 2][ T AP YOUR CREDIT CARD]";
    c.Validate(s);

    return 0;
}

