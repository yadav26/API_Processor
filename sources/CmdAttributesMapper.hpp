
#include <iostream>
#include <map>

#pragma once


using namespace std;

enum class ATTRIBUTES_OPID {
	AddInExistingCmd,
	RemoveFromExistingCmd,
	NewCmdNewAttributes,
	DeleteCmdAndAllAttributes,
	ShowAttributesFromCmd
};

class CmdAttributesMapper {
	std::map<std::string, std::unordered_set<std::string> > CmdsAttributesMap;
	std::string to_lower(const std::string& s) {
		std::string ns = s;
		for (char& c : ns)
			c = tolower(c);
		return ns;
	}
	bool AddInExistingCmd(const string& cmd, const unordered_set<string>& attributes) {
		auto& v = CmdsAttributesMap[cmd];
		for (auto& att : attributes) {
			v.insert(att);
		}
		return true;
	}

	bool RemoveFromExistingCmd(const string& cmd, const unordered_set<string>& attributes) {
		auto& att = CmdsAttributesMap[to_lower(cmd)];
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
		return true;
	}

	void DeleteCmdAndAllAttributes(const string& cmd) {
		auto c = to_lower(cmd);
		if (auto it = CmdsAttributesMap.find(c); it != CmdsAttributesMap.end()) {
			CmdsAttributesMap.erase(it);
		}
	}
	CmdAttributesMapper() {
		for (auto& cmd : CmdStore::GetCmdStore().GetAllCmds())
			AddDefaultAttributes(cmd);
	}

	CmdAttributesMapper(const CmdAttributesMapper&) = default;
	CmdAttributesMapper& operator=(const CmdAttributesMapper&) = default;
	CmdAttributesMapper(CmdAttributesMapper&&) = default;
	CmdAttributesMapper& operator=(CmdAttributesMapper&&) = default;

public:
	
	static CmdAttributesMapper& GetInstance() {
		static CmdAttributesMapper mapper;
		return mapper;
	}

	void AddDefaultAttributes(const string& cmd) {
		for (auto& att : CmdAttributeStore::GetInstance().GetAllAtrribs()) {
			CmdsAttributesMap[cmd].insert(att);
		}
	}
	void DumpCmdsAttributes(){
		for(auto& [k,v]: CmdsAttributesMap){
			cout << "\n[" << k <<"]  [";
			cout << ListAllAttributes(k) <<"]";
		}
	}
	string ListAllAttributes(const string& cmd) {
		string s;
		for (auto& a : CmdsAttributesMap[cmd])
			s = s + a + ",";
		
		return s.empty()? s: s.erase(s.size()-1,1);
	}
	string ListAllCommands() {
		string s;
		for (auto& [k,v] : CmdsAttributesMap)
			s = s + k + ",";
		return s.empty()? s: s.erase(s.size()-1,1);
	}
	void UpdateAttributes(ATTRIBUTES_OPID opn, const string& cmd, const unordered_set<string>& attributes) {

		switch (opn) {
			case ATTRIBUTES_OPID::AddInExistingCmd : 
			{
				AddInExistingCmd(cmd,attributes);
			}break;
			case ATTRIBUTES_OPID::RemoveFromExistingCmd:
			{
				RemoveFromExistingCmd(cmd, attributes);
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