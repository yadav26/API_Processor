/***********************************************************************************************
        Anshul Yadav
        er.anshulyadav@gmail.com
        yadav26@github
        This is for tritium api processor
************************************************************************************************/
#include <string>
using namespace std;

struct Response {

	static string GetSuccessResp() {
		return "[RESP][7][SUCCESS]";
	}
	static string GetFailedResp(string& err) {
		return "[RESP][6][FAILED][ERR][11][BAD_COMMAND][REASON][" +err + "]";
	}

};