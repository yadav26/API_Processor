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
            // Call the process here
            // share the buffer
            auto reply = ProcessCmdValidation(cmdTokens);
            cout << "\n CmdID(" << ++cmdid << ") : " << reply << endl;
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

    string ProcessCmdValidation(vector<string>& txt) {
        CmdValidator cv;
        auto status = cv.Validate(txt);
        if (status)
            return Response::GetSuccessResp();

        return Response::GetFailedResp();
    }
};