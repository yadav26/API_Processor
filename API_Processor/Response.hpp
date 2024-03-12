#include <string>
using namespace std;

struct Response {

	static string GetSuccessResp() {
		return "[RESP][7][SUCCESS]";
	}
	static string GetFailedResp() {
		return "[RESP][6][FAILED][ERR][11][BAD_COMMAND]";
	}

};