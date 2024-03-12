#pragma once

#include "CmdBufferManager.hpp"
#include <sstream>
#include <vector>

using namespace std;

//This class reads the byte stream and organise into buffer format
//Buffer is tokenized for the input stream
//since the termination of the command is unknown only new command arrival
//hence buffer will always have one residual command unfurnish untill it 
//all exit

class CmdStreamReader {
	stringstream stream;
	static inline bool done = false;

	//auto s = "[  C M N D][8 ][ A C T I V A T E ][T  X T][20][TAAAA   AP YOUR CREDIT CARD][  AMO UNT ][3][400 ] [  T X  T  ][20][TAP YOUR CREDIT CARD]";
	vector<string> Tokenizer(string str, string& nt) {
		vector<string> v;
		int start = 0;
		bool trimming = true;
		int cnt = 0;
		while (std::string::npos != start) {
			start = str.find('[');
			if (std::string::npos != start) {
				int end = str.find(']');
				if (end == std::string::npos) {
					// we have incomplete string.
					nt = str.substr(start, str.size() - start );
					break;
				}
					

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

public:
	void start() {
		vector<string> vs = {
			"[  C M N D][8 ][ A C T I V A T E ][T  X T][2 7][TAAAA   AP YOUR CREDIT CARD][  AMO UNT ][3][400 ] [  T X  T  ][2 2][ T AP YOUR CREDIT CARD]",
			"[  C M N D][8 ][ A C T I V A T E ][T  X T][2 7][TAAAA   ",
			"AP YOUR CREDIT CARD][  AMO",
			" UNT ][3][400][T X  T][2 2][T AP YOUR CREDIT CARD]"
		};

		int i = -1;
		while (!done ) {
			string s;
			cout << "\n Enter api byte stream e.g. [CMND][9][START_LOG][CMND][8][ACTIVATE][AMOUNT][3][400][TXT][20][TAP YOUR CREDIT CARD][TERMINATE]: ";
			std::getline(std::cin, s);
			int pos = s.find("[TERMINATE]");
			if (pos != string::npos)
				done = true;
			stream << s;
			extractCMND();
		}
		extractLastCMND();
		//signal dispatcher to finish
		CmdDispatcher cd;
		cd.finish();
		
	}

	void finish() {

	}

	void extractCMND() {
		auto s = stream.str();
		string nontokenized;
		int opencnt = 0;
		for (auto& p : s) {
			if (p == '[' && opencnt >= 1) {
				cout << "\n Corrupted stream, [[ clear it now. " << s;
				stream = std::stringstream();
				return;
			}
			if (p == ']' && opencnt < 0) {
				cout << "\n Corrupted stream, ]] clear it now. " << s;
				stream = std::stringstream();
				return;
			}
			if (p == '[' )++opencnt;
			if (p == ']') --opencnt;
		}
		vector<string> v = Tokenizer(s, nontokenized);

		int start = -1, end = -1;
		for (int i = 0; i < v.size(); ++i) {
			if (v[i] == "CMND") {
				if (start != -1) end = i ;
				if (start == -1) start = i;

			}
		}
		if (start != -1 && end > start)
		{
			auto& buffer = CmdBufferManager::GetInstance();
			buffer.Push({ v.begin() + start, v.begin() + end });
			//now reset stream
			string ns;
			for (int i = end; i < v.size(); ++i)
				ns += "[" + v[i] + "]";
			ns += nontokenized;
			stream = std::stringstream();
			stream << ns;
		}
	}

	void extractLastCMND() {
		auto s = stream.str();
		string nontokenized;
		vector<string> v = Tokenizer(s, nontokenized);

		auto& buffer = CmdBufferManager::GetInstance();
		buffer.Push({ v.begin() , v.end() });
		stream = std::stringstream();
	}
	
};