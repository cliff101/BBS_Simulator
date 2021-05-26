#include "Board.h"
#include "FileIOTools.h"

Board::Board(std::string inTopic, int increateuserID, std::vector<User*>* inusersptr) :usersptr(inusersptr), Topic(inTopic), createuserID(increateuserID) {}
Board::Board(std::ifstream& ifile, std::vector<User*>* inusersptr) : usersptr(inusersptr), Topic(""), createuserID(-1) {
	LoadBoardFromFile(ifile);
}
Board::~Board() {
	DeleteAllPost();
}

void Board::NewPost(long long& this_postID) {
	std::string nTopic, content, temp;
	bool cancel = false;
	std::getline(std::cin, nTopic);
	std::cout << "Post Topic Name: ";
	std::getline(std::cin, nTopic);
	if (nTopic != "") {
		std::cout << "Enter Content\ncancel: */*/*/*/_CONTENT_CANCEL_/*/*/*/*\nend: */*/*/*/_CONTENT_END_/*/*/*/*\n\n";
		while (true) {
			std::cout << "--> ";
			std::getline(std::cin, temp);
			if (temp == "*/*/*/*/_CONTENT_CANCEL_/*/*/*/*") {
				cancel = true;
				break;
			}
			else if (temp == "*/*/*/*/_CONTENT_END_/*/*/*/*") {
				break;
			}
			content += temp + '\n';
		}
		if (!cancel) {
			posts.push_back(new Post(nTopic, content, current_user, this_postID, usersptr));
			this_postID++;
		}
	}
}
void Board::DeletePost() {
	system("cls");
	int count = 0,
		select = 0;
	std::vector<int> indarr(0);
	for (int i = 0; i < posts.size(); i++) {
		if (posts[i]->createuserID == current_user || (*usersptr)[current_user]->GetPermission_level() == 0) {
			indarr.push_back(i);
				std::cout << ++count << ". ";
		}
		std::cout << posts[i]->Topic << " Author: " << (*usersptr)[posts[i]->createuserID]->GetUserName() << std::endl;
	}
	if (indarr.size() == 0) {
		system("cls");
			return;
	}
	std::cout << "Please select post want to delete: ";
		std::cin >> select;
	if (select > 0 && select <= indarr.size()) {
		delete posts[indarr[select - 1]];
		posts.erase(posts.begin() + indarr[select - 1]);
	}
}
void Board::DeleteAllPost() {
	for (int i = 0; i < posts.size(); i++) {
		delete posts[i];
	}
	posts.clear();
}

void Board::SaveBoardToFile(std::ofstream& ofile) {
	SaveNormDataToFile(createuserID, ofile);
	SaveStrToFile(Topic, ofile);
	int nposts = posts.size();
	SaveNormDataToFile(nposts, ofile);
	for (int i = 0; i < nposts; i++) {
		posts[i]->SavePostToFile(ofile);
	}
}
void Board::LoadBoardFromFile(std::ifstream& ifile) {
	LoadNormDataFromFile(createuserID, ifile);
	LoadStrFromFile(Topic, ifile);
	int nposts = 0;
	LoadNormDataFromFile(nposts, ifile);
	DeleteAllPost();
	for (int i = 0; i < nposts; i++) {
		posts.push_back(new Post(ifile, usersptr));
	}
}