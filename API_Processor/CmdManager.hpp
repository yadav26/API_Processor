#include "CmdStore.hpp"
#include "CmdAttributeStore.hpp"
#include "CmdAttributesMapper.hpp"

class CmdManager {

	CmdStore mCmdStore;
	CmdAttributeStore mAttribStore;
	CmdAttributesMapper mCmdMapper;
	CmdManager() = default;
public:
	static CmdManager& GetCmdManager() {
		static CmdManager mgr;
		return mgr;
	}
	void AddNewCommand(const string& c, const unordered_set<string>& attributes) {
		mCmdStore.addNewCmd(c);
		mAttribStore.addNewAttribs(attributes);
		mCmdMapper.UpdateAttributes(ATTRIBUTES_OPID::NewCmdNewAttributes, c , attributes);
	}
	void DeleteCommand(const string& c) {
		mCmdMapper.UpdateAttributes(ATTRIBUTES_OPID::DeleteCmdAndAllAttributes, c , {});
	}
	void AddAttributesInCmd(const string& c, const unordered_set<string>& attributes) {
		mAttribStore.addNewAttribs(attributes);
		mCmdMapper.UpdateAttributes(ATTRIBUTES_OPID::AddInExistingCmd,  c, attributes);
	}
	void RemoveAttributesInCmd(const string& c, const unordered_set<string>& attributes) {
		mCmdMapper.UpdateAttributes(ATTRIBUTES_OPID::removeFromExistingCmd, c, attributes);
	}
};