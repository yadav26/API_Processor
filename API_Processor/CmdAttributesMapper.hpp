
#include <iostream>
#include <map>
using namespace std;

enum class ATTRIBUTES_OPID {
	AddInExistingCmd,
	removeFromExistingCmd,
	NewCmdNewAttributes,
	DeleteCmdAndAllAttributes
};

class CmdAttributesMapper {
	std::map<std::string, std::unordered_set<std::string> > CmdsAttributesMap;
	std::string to_lower(const std::string& s) {
		std::string ns = s;
		for (char& c : ns)
			c = tolower(c);
		return move(ns);
	}
	bool AddInExistingCmd(const string& cmd, const unordered_set<string>& attributes) {
		for (auto& att : attributes) 
			CmdsAttributesMap[cmd].insert(att);
		
		return true;
	}

	bool removeFromExistingCmd(const string& cmd, const unordered_set<string>& attributes) {
		auto att = CmdsAttributesMap[to_lower(cmd)];
		for (auto& a : attributes) {
			for (auto it = att.begin(); it != att.end();)
			{
				if (*it == a) {
					it = att.erase(it);
					break;
				}
				else
					++it;
			}
		}
		return true;
	}

	bool NewCmdNewAttributes(const string& cmd, const unordered_set<string>& attributes, bool addDefault = true) {
		auto c = to_lower(cmd);
		CmdsAttributesMap[c] = attributes;
		if (addDefault) {
			AddDefaultAttributes(c);
		}
	}

	void DeleteCmdAndAllAttributes(const string& cmd) {
		auto c = to_lower(cmd);
		if (auto it = CmdsAttributesMap.find(c); it != CmdsAttributesMap.end()) {
			CmdsAttributesMap.erase(it);
		}
	}

public:
	
	CmdAttributesMapper() {
		const CmdStore store;
		for (auto& cmd : store.GetAllCmds()) 
			AddDefaultAttributes(cmd);
	}

	CmdAttributesMapper(const CmdAttributesMapper&) = default;
	CmdAttributesMapper& operator=(const CmdAttributesMapper&) = default;
	CmdAttributesMapper(CmdAttributesMapper&&) = default;
	CmdAttributesMapper& operator=(CmdAttributesMapper&&) = default;

	CmdAttributesMapper(const CmdStore& store, const CmdAttributeStore& attributes) {
		//link all attributes by default to all default cmds
		for (auto& cmds : store.GetAllCmds()) {
			for (auto& att : attributes.GetAllAtrribs()) {
				CmdsAttributesMap[cmds].insert(att);
			}
		}
	}
	
	void AddDefaultAttributes(const string& cmd) {
		const CmdAttributeStore attributes;
		for (auto& att : attributes.GetAllAtrribs()) {
			CmdsAttributesMap[cmd].insert(att);
		}
	}

	void UpdateAttributes(ATTRIBUTES_OPID opn, const string& cmd, const unordered_set<string>& attributes) {

		switch (opn) {
			case ATTRIBUTES_OPID::AddInExistingCmd : 
			{
				AddInExistingCmd(cmd,attributes);
			}break;
			case ATTRIBUTES_OPID::removeFromExistingCmd:
			{
				removeFromExistingCmd(cmd, attributes);
			}break;
			case ATTRIBUTES_OPID::NewCmdNewAttributes:
			{
				NewCmdNewAttributes(cmd, attributes);
			}break;
			case ATTRIBUTES_OPID::DeleteCmdAndAllAttributes:
			{
				DeleteCmdAndAllAttributes(cmd);
			}break;
			default:
				cout << "\n Invalid attribute update operation.";
		}
	}

	bool ValidAttributeForCmd(const string& cmd, const string& att) {
		auto a = to_lower(att);
		auto c = to_lower(cmd);
		if (auto it = CmdsAttributesMap[c].find(a); it != CmdsAttributesMap[c].end()) {
			return true;
		}
		return false;
	}
};