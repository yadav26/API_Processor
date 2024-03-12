#pragma once
#include <string>
#include <vector>
#include "CmdStore.hpp"
#include "CmdAttributesValidator.hpp"

using namespace std;

class CmdValidator {

	std::string to_lower(const std::string& s) {
		std::string ns = s;
		for (char& c : ns)
			c = tolower(c);
		return move(ns);
	}

public:
	
	bool Validate(const vector<string>& v) {

		if (v[0] != "CMND") {
			cout << "\n Failed CMND identity.";
			return false;
		}

		auto cmdlen = atoi(v[1].c_str());
		if (v[2].size() != cmdlen) {
			cout << "\n CMDlen match failed.";
			return false;
		}
		
		if (!CmdStore::GetCmdStore().IsValidCmd(v[2])) {
			cout << "\n Failed cmd check from store: " << v[1];
			return false;
		}

		CmdAttributesValidator av;
		return av.Validate_Attributes(v[2], {v.begin() + 3, v.end()});
	}

};