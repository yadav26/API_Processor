#include "CmdStore.hpp"
#include "CmdAttributeStore.hpp"
#include "CmdAttributesMapper.hpp"

#pragma once

class CmdManager {

	CmdManager() = default;
public:
	static CmdManager& GetCmdManager() {
		static CmdManager mgr;
		return mgr;
	}
	void AddNewCommand(const string& c, const unordered_set<string>& attributes) {
		CmdStore::GetCmdStore().addNewCmd(c);
		CmdAttributeStore::GetInstance().addNewAttribs(attributes);
		CmdAttributesMapper::GetInstance().UpdateAttributes(ATTRIBUTES_OPID::NewCmdNewAttributes, c, attributes);
	}
	void DeleteCommand(const string& c) {
		CmdAttributesMapper::GetInstance().UpdateAttributes(ATTRIBUTES_OPID::DeleteCmdAndAllAttributes, c , {});
	}
	void AddAttributesInCmd(const string& c, const unordered_set<string>& attributes) {
		CmdAttributeStore::GetInstance().addNewAttribs(attributes);
		CmdAttributesMapper::GetInstance().UpdateAttributes(ATTRIBUTES_OPID::AddInExistingCmd,  c, attributes);
	}
	void RemoveAttributesInCmd(const string& c, const unordered_set<string>& attributes) {
		CmdAttributesMapper::GetInstance().UpdateAttributes(ATTRIBUTES_OPID::removeFromExistingCmd, c, attributes);
	}
};