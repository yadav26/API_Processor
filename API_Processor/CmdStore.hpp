#include <string>
#include <unordered_set>
#include <locale> 

const std::vector<std::string> DEFAULT_CMDS = {
	"activate",
	"activate_rd",
	"settle",
	"clear_session"
};

class CmdStore {

	std::unordered_set<std::string> m_Cmds;

	std::string to_lower(const std::string& s) {
		std::string ns = s;
		for (char& c : ns)
			c = tolower(c);
		return move(ns);
	}

public:
	CmdStore() {
		for (auto& c : DEFAULT_CMDS)
			m_Cmds.insert(c);
	}
	const std::unordered_set<std::string>& GetAllCmds() const{
		return m_Cmds;
	}

	bool IsValidCmd(const std::string& cmd)
	{
		auto c = to_lower(cmd);
		if (auto search = m_Cmds.find(c); search != m_Cmds.end())
			return true;
		else
			return false;
	}
	
	bool IsValidCmdLen(const std::string& cmd, int len)
	{
		auto c = to_lower(cmd);
		if (auto search = m_Cmds.find(c); search != m_Cmds.end())
		{
			auto cmd = *search;
			if (cmd.size() == len) 
				return true;
			else
				return false;
		}
		else
			return false;
	}

	bool addNewCmd(const std::string& cmd) {
		auto c = to_lower(cmd);
		return m_Cmds.insert(c).second;
	}

	bool removeCmd(const std::string& cmd) {
		auto c = to_lower(cmd);
		for (auto it = m_Cmds.begin(); it != m_Cmds.end();)
		{
			if (*it == c) {
				it = m_Cmds.erase(it);
				return true;
			}	
			else
				++it;
		}
		return false;
	}


};