/***********************************************************************************************
        Anshul Yadav
        er.anshulyadav@gmail.com
        yadav26@github
        This is for tritium api processor
************************************************************************************************/
#pragma once
#include <string>
#include <vector>
#include "CmdAttributesValidator.hpp"
#include "CmdStore.hpp"

using namespace std;

class CmdValidator {

	std::string to_lower(const std::string& s) {
		std::string ns = s;
		for (char& c : ns)
			c = tolower(c);
		return ns;
	}

public:
	
	bool Validate(const vector<string>& v, string& reason) {

		if (v[0] != "CMND") {
			//cout << "\n Failed CMND identity.";
			reason = "Failed CMND identity";
			return false;
		}

		auto cmdlen = atoi(v[1].c_str());
		if ((int)v[2].size() != cmdlen) {
			//cout << "\n CMDlen match failed.";
			reason = "Cmdlen match failed";
			return false;
		}
		
		if (!CmdStore::GetCmdStore().IsValidCmd(v[2])) {
			//cout << "\n Failed cmd check from store: " << v[2];
			reason = "Command didnot exists";
			return false;
		}

		CmdAttributesValidator av;
		
		return av.Validate_Attributes(v[2], {v.begin() + 3, v.end()}, reason);
	}

};