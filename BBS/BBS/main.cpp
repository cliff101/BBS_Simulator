#include <iostream>
#include "BoardManager.h"
#include <functional>

using namespace std;

//void myterminate(BoardManager& bm) {
//	bm.SaveStatusToFile();
//	abort();
//}

int main() {
	BoardManager bm;
	//auto myterminatefunc = std::bind(myterminate, bm);
	//myterminatefunc();
	//set_terminate(myterminatefunc);
	bm.StartBoardManager();
	stop:
	return 0;
}