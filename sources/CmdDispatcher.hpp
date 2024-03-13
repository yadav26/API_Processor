#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>
#include "CmdBufferManager.hpp"
#include "CommandHandlers/CmdValidator.hpp"
#include "Response.hpp"

class CmdDispatcher {
    static inline long cmdid = 0;
    static inline bool done = false;
public:
	void start() {
        auto& buffer = CmdBufferManager::GetInstance();
        
        while (!done ) {
            if (buffer.IsEmpty()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                continue;
            }
            //wait till buffer available;
            vector<string> cmdTokens = buffer.GetCmd();
            buffer.Pop();
            int sp = 0;
            vector<pair<int, int>> positions;
            
            for (int i = 1; i < (int)cmdTokens.size();++i) {

                if (cmdTokens[i] == "CMND")
                {
                    pair<int, int> p = { sp,i - 1 };
                    positions.push_back(p);
                    sp = i;
                }
            }
            
            positions.push_back({sp,cmdTokens.size()-1});

            // Call the process here
            // share the buffer
            string reply;
            for (int i = 0; i < (int)positions.size(); ++i) {
                vector<string> vcmd = { cmdTokens.begin() + positions[i].first, cmdTokens.begin() + positions[i].second + 1 };
                reply = ProcessCmdValidation(vcmd);
                cout << "\n id(" << ++cmdid << ") :  ";
                string scmd;
                for (auto& p : vcmd)
                    scmd += '[' + p + ']';
                    
                cout << scmd << ":===>" << reply ;
             }
            
        }
        
        //residual buffer processing.
        while(!buffer.IsEmpty()){
            vector<string> cmdTokens = buffer.GetCmd();
            buffer.Pop();
            cmdTokens.pop_back();
            auto reply = ProcessCmdValidation(cmdTokens);
            cout << "\n Residual :CmdID(" << ++cmdid << ") : " << reply << endl;
        }
	}

    void finish()
    {
        done = true;
    }

    string ProcessCmdValidation(vector<string> txt) {
        CmdValidator cv;
        string reason;
        auto status = cv.Validate(txt, reason);
        if (status)
            return Response::GetSuccessResp();

        return Response::GetFailedResp(reason);
    }
};