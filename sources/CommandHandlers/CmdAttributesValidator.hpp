#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "CmdStore.hpp"
#include "CmdAttributeStore.hpp"
#include "CmdAttributesMapper.hpp"

using namespace std;
#pragma once

class CmdAttributesValidator {
	std::string to_lower(const std::string& s) {
		std::string ns = s;
		for (char& c : ns)
			c = tolower(c);
		return ns;
	}

public:
	bool Validate_Attributes(const string& cmd, vector<string> v, string& err) {

		for (int i = 0; i < (int)v.size(); i = i + 3) {
			//validate the att name
			string name = v[i];
			if (!CmdAttributeStore::GetInstance().IsValidAttrib(name))
			{
				cout << "\n Invalid attribute name " << name;
				err = "Invalid attribute name" ;
				return false;
			}
			if (!CmdAttributesMapper::GetInstance().ValidAttributeForCmd(cmd, name))
			{
				cout << "\n Invalid cmd attribute pair: " << cmd << ", " << name;
				err = "Attribute not associated.";
				return false;
			}
			auto len = atoi(v[i + 1].c_str());
			if ((int)v[i + 2].size() != len) {
				printf("\n attrib len match failed. expected(%d), actual(%d)", (int)v[i + 2].size(), len);
				stringstream ss;
				ss << ("Attribute len match failed.expected(");
				ss << (int)v[i + 2].size();
				ss << "), actual(" << len << ")";
				err = ss.str();
				return false;
			}

			if (to_lower(name) != "amount")
				continue;
			for (auto& c : v[i + 2]) {
				if (c != '.' && !isdigit(c)) {
					cout << "\n attrib amount invlaid digit : " << v[i + 2];
					err = "Attrib amount is not a valid digit.(" + v[i + 2] + ")";
					return false;
				}
			}
		}
		return true;
	}
};