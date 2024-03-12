#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "CmdStore.hpp"
#include "CmdAttributeStore.hpp"
#include "CmdAttributesMapper.hpp"

using namespace std;

class CmdValidator {
	std::string to_lower(const std::string& s) {
		std::string ns = s;
		for (char& c : ns)
			c = tolower(c);
		return move(ns);
	}
	vector<string> Tokenizer(string& str) {
		vector<string> v;
		int start = 0;
		bool trimming = true;
		int cnt = 0;
		while (std::string::npos != start) {
			start = str.find('[');
			if (std::string::npos != start) {
				int end = str.find(']');
				auto s = str.substr(start + 1, end - start -1);
				auto tt = s;
				std::string::iterator end_pos = std::remove(tt.begin(), tt.end(), ' ');
				tt.erase(end_pos, tt.end());

				if (tt == "TXT") {
					trimming = false;
					cnt = 0;
					s = tt;
				}
				if (trimming || (!trimming && cnt < 2 )) {
					std::string::iterator end_pos = std::remove(s.begin(), s.end(), ' ');
					s.erase(end_pos, s.end());
				}
				v.emplace_back(s);
				++cnt;
				if (cnt == 3)
					trimming = true; //skip next 3 inserts for 
				str = str.substr(end+1, str.size() - (end +1) );
			}
		}
		return v;
	}

public:

	//auto s = "[  C M N D][8 ][ A C T I V A T E ][T  X T][20][TAAAA   AP YOUR CREDIT CARD][  AMO UNT ][3][400 ] [  T X  T  ][20][TAP YOUR CREDIT CARD]";
	bool Validate(string str) {

		auto v = Tokenizer(str);
		if (v[0] != "CMND") {
			cout << "\n Failed CMND";
			return false;
		}

		auto cmdlen = atoi(v[1].c_str());
		if (v[2].size() != cmdlen) {
			cout << "\n CMDlen match failed.";
			return false;
		}

		return Validate_Attributes(v[2], {v.begin() + 3, v.end()});
	}

	bool Validate_Attributes(string& cmd, vector<string> v) {

		CmdAttributeStore cas;
		CmdAttributesMapper mapper;
		for (int i = 0; i < v.size(); i = i+3) {
			//validate the att name
			string name = v[i];
			if (!cas.IsValidAttrib(name))
			{
				cout << "\n Invalid attribute name "<< name ;
				return false;
			}
			if (!mapper.ValidAttributeForCmd(cmd, name))
			{
				cout << "\n Invalid cmd attribute pair: " << cmd <<", " << name;
				return false;
			}
			auto len = atoi(v[i+1].c_str());
			if (v[i+2].size() != len) {
				cout << "\n attrib len match failed.";
				return false;
			}
			
			if (to_lower(name) != "amount")
				continue;
			for (auto& c : v[i + 2]) {
				if (c != '.' && !isdigit(c)) {
					cout << "\n attrib amount invlaid digit : " << v[i+2];
					return false;
				}
			}
		}
		return true;
	}
};