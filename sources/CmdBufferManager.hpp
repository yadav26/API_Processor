
#include <deque>
#include <string>
#include <vector>
#include <mutex>

#pragma once

using namespace std;

class CmdBufferManager {

	deque<vector<string>> MsgQueue; // already tokenized command and attributes

	std::mutex m;
	CmdBufferManager() = default;

public:
	static CmdBufferManager& GetInstance() {
		static CmdBufferManager queue;
		return queue;
	}
	void Push(const vector<string>& cmd) {
		std::lock_guard l(m);
		MsgQueue.push_back(cmd);
	}
	void Pop() {
		if (MsgQueue.empty())
			return;
		std::lock_guard l(m);
		MsgQueue.pop_front();
	}
	const vector<string>& GetCmd() {
		return MsgQueue.front();
	}
	bool IsEmpty() {
		return MsgQueue.empty();
	}

};