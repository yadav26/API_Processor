#include "CmdStore.hpp"
#include "CmdAttributeStore.hpp"
#include "CmdAttributesMapper.hpp"

#include <sstream>
#pragma once

class CmdManager {

	std::string to_lower(const std::string& s) {
		std::string ns = s;
		for (char& c : ns)
			c = tolower(c);
		return ns;
	}
	CmdManager() = default;
	void AddNewCommand(const string& c, const unordered_set<string>& attributes) {
		CmdStore::GetCmdStore().addNewCmd(c);
		CmdAttributeStore::GetInstance().addNewAttribs(attributes);
		CmdAttributesMapper::GetInstance().UpdateAttributes(ATTRIBUTES_OPID::NewCmdNewAttributes, c, attributes);
	}
	void DeleteCommand(const string& c) {
		CmdAttributesMapper::GetInstance().UpdateAttributes(ATTRIBUTES_OPID::DeleteCmdAndAllAttributes, c, {});
	}
	void AddAttributesInCmd(const string& c, const unordered_set<string>& attributes) {
		CmdAttributeStore::GetInstance().addNewAttribs(attributes);
		CmdAttributesMapper::GetInstance().UpdateAttributes(ATTRIBUTES_OPID::AddInExistingCmd, c, attributes);
	}
	void RemoveAttributesInCmd(const string& c, const unordered_set<string>& attributes) {
		CmdAttributesMapper::GetInstance().UpdateAttributes(ATTRIBUTES_OPID::RemoveFromExistingCmd, c, attributes);
	}
    void PrintCmdsAttributes()
    {
        CmdAttributesMapper::GetInstance().DumpCmdsAttributes();
    }
	string ListAllAttributes(const string& c) {
		return CmdAttributesMapper::GetInstance().ListAllAttributes(c);
	}
    string ListAllCommands() {
		return CmdAttributesMapper::GetInstance().ListAllCommands();
	}
    
public:
	static CmdManager& GetCmdManager() {
		static CmdManager mgr;
		return mgr;
	}
	void start() {
        long op = -1;
        string sin;
        bool done = false;
        while (!done) {
            cout << "\n" << "Add below operation id\n0: Print attributes of command,\n1: Add a new command, \n2: Add an attribute to existing command, \n3: Delete Command \n4: Remove attributes from command \n5: Anything else to exit";
            std::getline(std::cin, sin);
            op = std::atoi(sin.c_str());
            switch (op) {
            case 0://edit cmd remove att
            {
                cout << "\n";
                PrintCmdsAttributes();
                cout << "\n";
            }
            break;
            case 1://add
            {
                cout << "\n1-Add a new command :";
                string cmdname;
                std::getline(std::cin, cmdname);
                cout << "\n1-Add attribute/s to this (e.g att1,att2,att3):";
                string atts;
                std::getline(std::cin, atts);
                std::unordered_set<string> attriblists;
                std::stringstream ss(atts);
                while (ss.good())
                {
                    string a;
                    getline(ss, a, ',');
                    a = to_lower(a);
                    attriblists.insert(a);
                }
                AddNewCommand(cmdname, attriblists);
            }
            break;
            case 2://edit cmds
            {
                cout << "\n2-Command name to add new attributes:";
                string cmdname;
                std::getline(std::cin, cmdname);
                cout << "\n2-Add attribute/s names(e.g att1,att2,att3):";
                string atts;
                std::getline(std::cin, atts);
                std::unordered_set<string> attriblists;
                std::stringstream ss(atts);
                while (ss.good())
                {
                    string a;
                    getline(ss, a, ',');
                    a = to_lower(a);
                    attriblists.insert(a);
                }
                AddAttributesInCmd(cmdname, attriblists);
            }
            break;
            case 3://edit cmds
            {
                cout << "\n3-Delete command :";
                string cmdname;
                std::getline(std::cin, cmdname);
                DeleteCommand(cmdname);
            }

            break;
            case 4://edit cmd remove att
            {
                cout << "\n4-Remove attributes from command [" << ListAllCommands() << "]:";
                string cmdname;
                std::getline(std::cin, cmdname);
                cout << "\n4- Attributes to be removed [ " << ListAllAttributes(to_lower(cmdname)) << "]: ";
                string atts;
                std::getline(std::cin, atts);
                std::unordered_set<string> attriblists;
                std::stringstream ss(atts);

                while (ss.good())
                {
                    string a;
                    getline(ss, a, ',');
                    a = to_lower(a);
                    attriblists.insert(a);
                }
                RemoveAttributesInCmd(cmdname, attriblists);
            }
            break;

            default:
                done = true;
                break;
            }
        }
	}
	void finish() {

	}
};