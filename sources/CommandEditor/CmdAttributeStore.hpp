#include <string>
#include <unordered_set>
#include <locale> 

#pragma once


using namespace std;


class CmdAttributeStore {
	const std::vector<std::string> DEFAULT_ATTRIB = {
	"amount", "txt"
};
	std::unordered_set<std::string> m_Attributes;
	std::string to_lower(const std::string& s) {
		std::string ns = s;
		for (char& c : ns)
			c = tolower(c);
		return ns;
	}
	CmdAttributeStore() {
		for (auto& c : DEFAULT_ATTRIB)
			m_Attributes.insert(c);
	}
public:
	
	static CmdAttributeStore& GetInstance(){
		static CmdAttributeStore cas;
		return cas;
	}
	const std::unordered_set<std::string>& GetAllAtrribs() const {
		return m_Attributes;
	}

	bool IsValidAttrib(const std::string& att)
	{
		auto c = to_lower(att);
		if (auto search = m_Attributes.find(c); search != m_Attributes.end())
			return true;
		else
			return false;
	}

	bool addNewAttribs(const unordered_set<string>& atts) {
		for (auto& a : atts) {
			auto c = to_lower(a);
			m_Attributes.insert(c);
		}
		return true;
	}

	bool removeAttrib(const std::string& att) {
		auto c = to_lower(att);
		for (auto it = m_Attributes.begin(); it != m_Attributes.end();)
		{
			if (*it == c) {
				it = m_Attributes.erase(it);
				return true;
			}
			else
				++it;
		}
		return false;
	}
};
