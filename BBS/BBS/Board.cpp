#include "Board.h"
#include "FileIOTools.h"

Board::Board(std::string inTopic, int increateuserID, std::vector<User*>* inusersptr) :usersptr(inusersptr), Topic(inTopic), createuserID(increateuserID) {}
Board::Board(std::ifstream& ifile, std::vector<User*>* inusersptr) : usersptr(inusersptr), Topic(""), createuserID(-1) {
	LoadBoardFromFile(ifile);
}
Board::~Board() {
	DeleteAllPost();
}

void Board::NewPost(long long& this_postID, bool edit) {
	system("cls");
	std::string nTopic, content, temp;
	bool cancel = false;
	if (edit) {
		std::cout << "Old Topic: " << posts[this_postID]->Topic << "\n\n" << posts[this_postID]->Pocontent << "\n\n\nNew ";
	}
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
			if (!edit) {
				posts.push_back(new Post(nTopic, content, current_user, this_postID, usersptr));
				(*usersptr)[current_user]->NewpostID(this_postID);
				this_postID++;
			}
			else {
				Post* temp = new Post(nTopic, content, current_user, posts[this_postID]->this_postID, usersptr);
				for (int i = 0; i < posts[this_postID]->comments.size(); i++) {
					temp->comments.push_back(new Post::Comment(*posts[this_postID]->comments[i]));
				}
				delete posts[this_postID];
				posts[this_postID] = temp;
			}
		}
	}
}
void Board::DeletePost() {
	system("cls");
	int count = 0,
		select = 0;
	std::vector<int> indarr(0);
	for (int i = 0; i < posts.size(); i++) {
		if (posts[i]->createuserID == current_user) {
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
		(*usersptr)[posts[indarr[select - 1]]->createuserID]->DeletepostID(posts[indarr[select - 1]]->this_postID);
		delete posts[indarr[select - 1]];
		posts.erase(posts.begin() + indarr[select - 1]);
	}
}
void Board::DeleteAllPost() {
	for (int i = 0; i < posts.size(); i++) {
		(*usersptr)[posts[i]->createuserID]->DeletepostID(posts[i]->this_postID);
		delete posts[i];
	}
	posts.clear();
}
void Board::EditPost() {
	system("cls");
	int count = 0,
		select = 0;
	std::vector<long long> indarr(0);
	for (int i = 0; i < posts.size(); i++) {
		if (posts[i]->createuserID == current_user) {
			indarr.push_back(i);
			std::cout << ++count << ". ";
		}
		std::cout << posts[i]->Topic << " Author: " << (*usersptr)[posts[i]->createuserID]->GetUserName() << std::endl;
	}
	if (indarr.size() == 0) {
		system("cls");
		return;
	}
	std::cout << "Please select post want to edit: ";
	std::cin >> select;
	if (select > 0 && select <= indarr.size()) {
		NewPost(indarr[static_cast<std::vector<long long, std::allocator<long long>>::size_type>(select) - 1], true);
	}
}
void Board::AdminDeletePost() {
	system("cls");
	int count = 0,
		select = 0;
	std::vector<int> indarr(0);
	for (int i = 0; i < posts.size(); i++) {
		if (!posts[i]->delete_by_admin) {
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
		std::string reason;
		std::getline(std::cin, reason);
		std::cout << "Delete reason: ";
		std::getline(std::cin, reason);
		Post* temp = new Post(" (Deleted by admin(" + (*usersptr)[current_user]->GetUserName() + "). Reason: " + reason + " )", posts[indarr[select - 1]]->createuserID, usersptr);
		delete posts[indarr[select - 1]];
		posts[indarr[select - 1]] = temp;
	}
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