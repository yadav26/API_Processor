#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "CmdStore.hpp"
#include "CmdAttributeStore.hpp"
#include "CmdAttributesMapper.hpp"
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
	vector<string> Tokenizer( string str) {
		vector<string> v;
		int start = 0;
		bool trimming = true;
		int cnt = 0;
		while (std::string::npos != start) {
			start = str.find('[');
			if (std::string::npos != start) {
				int end = str.find(']');
				auto s = str.substr(start + 1, end - start - 1);
				auto tt = s;
				std::string::iterator end_pos = std::remove(tt.begin(), tt.end(), ' ');
				tt.erase(end_pos, tt.end());

				if (tt == "TXT") {
					trimming = false;
					cnt = 0;
					s = tt;
				}
				if (trimming || (!trimming && cnt < 2)) {
					std::string::iterator end_pos = std::remove(s.begin(), s.end(), ' ');
					s.erase(end_pos, s.end());
				}
				v.emplace_back(s);
				++cnt;
				if (cnt == 3)
					trimming = true; //skip next 3 inserts for 
				str = str.substr(end + 1, str.size() - (end + 1));
			}
		}
		return move(v);
	}

	//auto s = "[  C M N D][8 ][ A C T I V A T E ][T  X T][20][TAAAA   AP YOUR CREDIT CARD][  AMO UNT ][3][400 ] [  T X  T  ][20][TAP YOUR CREDIT CARD]";
	bool Validate(const vector<string>& v) {

		//auto v = Tokenizer(str);
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