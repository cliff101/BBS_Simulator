#include "BoardManager.h"
#include "FileIOTools.h"

BoardManager::BoardManager() :datafilename("data.dat"), current_user(-1), max_postID(0), state(MENU), Selectedboard(nullptr), Selectedpost(nullptr), Selectedcomment(nullptr) {
	LoadStatusFromFile();
}
BoardManager::BoardManager(std::string& filename) : datafilename(filename), state(MENU), current_user(-1), max_postID(0), Selectedboard(nullptr), Selectedpost(nullptr), Selectedcomment(nullptr) {
	LoadStatusFromFile();
}
BoardManager::~BoardManager() {
	SaveStatusToFile();
}

void BoardManager::StartBoardManager() {
	AccountManager();
}
void BoardManager::AccountManager() {
	while (true) {
		system("cls");
		int select;
		std::cout << "1. login\n2. create account\n5. exit\nPlease Select:";
		std::cin >> select;
		if (select == 1) {//if successful, directly call menu in login func
			LogIn();
		}
		else if (select == 2) {
			CreateAccount();
		}
		else if (select == 5) {
			break;
		}
	}
}
void BoardManager::LogIn() {
	bool succ = false;
	std::string usn, pw;
	std::cout << "UserName: ";
	std::cin >> usn;
	if (usn == "guest") {
		current_user = 0;
		succ = true;
	}
	else {
		std::cout << "Password: ";
		std::cin >> pw;
		for (int i = 1; i < users.size(); i++) {
			if (users[i]->CheckUserName(usn) && users[i]->CheckPassword(pw)) {
				current_user = i;
				succ = true;
				break;

			}
		}
	}
	if (succ) {
		Menu();
	}
	else {
		std::cout << "Wrong UserName or Password!\nEnter anything to continue:";
		std::getline(std::cin, usn);
		std::getline(std::cin, usn);
	}
}
void BoardManager::CreateAccount() {
	int select, prl = 1;
	std::cout << "1. admin\n2. normal\n5. exit\nPlease Select:";
	std::cin >> select;
	std::string admin_key, usn, pw, pwc;
	switch (select) {
	case 1:
		std::cout << "Please enter admin key:";
		std::cin >> admin_key;
		if (admin_key != "12345") {
			return;
		}
		prl = 0;
	case 2:
		std::cout << "UserName: ";
		std::cin >> usn;
		if (usn == "guest" || usn == "You") {
			std::cout << "Name not allow!\nEnter anything to continue:";
			std::getline(std::cin, pwc);
			std::getline(std::cin, pwc);
			return;
		}
		for (int i = 0; i < users.size(); i++) {
			if (users[i]->CheckUserName(usn)) {
				std::cout << "Username have been registed!\nEnter anything to continue:";
				std::getline(std::cin, pwc);
				std::getline(std::cin, pwc);
				return;
			}
		}
		std::cout << "Password: ";
		std::cin >> pw;
		std::cout << "Enter Password Again: ";
		std::cin >> pwc;
		if (pw == pwc) {
			users.push_back(new User(usn, pw, prl));
			std::cout << "Successful!\nEnter anything to continue:";
			std::getline(std::cin, pwc);
			std::getline(std::cin, pwc);
		}
		else {
			std::cout << "Different password!\nEnter anything to continue:";
			std::getline(std::cin, pwc);
			std::getline(std::cin, pwc);
		}
		break;
	}
}
/*void BoardManager::DeleteAccount() {
	bool succ = false;
	int deleteuser;
	std::string usn, pw;
	std::cout << "UserName: ";
	std::cin >> usn;
	if (usn == "guest") {
		return;
	}
	else {
		std::cout << "Password: ";
		std::cin >> pw;
		for (int i = 1; i < users.size(); i++) {
			if (users[i]->CheckUserName(usn) && users[i]->CheckPassword(pw)) {
				deleteuser = i;
				succ = true;
				break;

			}
		}
	}
	if (succ) {
		users.erase(users.begin() + deleteuser);
		std::cout << "Delete Successful!\nEnter anything to continue:";
		std::getline(std::cin, usn);
		std::getline(std::cin, usn);
	}
	else {
		std::cout << "Wrong UserName or Password!\nEnter anything to continue:";
		std::getline(std::cin, usn);
		std::getline(std::cin, usn);
	}
}*/
void BoardManager::Menu() {
	int select = 0;
	while (true) {
		system("cls");
		state = MENU;
		std::cout << "User Name: " << users[current_user]->GetUserName() << "\nPermission level: " << users[current_user]->GetPermission_level() << std::endl;
		std::cout << "\n1. Select board\n2. Mini game\n3. Message\n5. logout\nPlease Select: ";
		std::cin >> select;
		if (select == 1) {
			SelectBoard();
		}
		else if (select == 2) {
			MiniGame();
		}
		else if (users[current_user]->GetPermission_level() < 2 && select == 3) {
			MessageManagement();
		}
		else if (select == 5) {
			break;
		}
	}
}
void BoardManager::MessageManagement() {
	while (true) {
		system("cls");
		auto msgs = users[current_user]->Getmsg();
		std::vector<std::string> key(0);
		int i = 0,
			select = 0;
		std::cout << "-1. back\n";
		std::cout << "0. write message\n";
		for (std::map<std::string, std::vector<std::string>>::iterator it = msgs.begin(); it != msgs.end(); ++it) {
			key.push_back(it->first);
			std::cout << ++i << ".  " << it->first << "  " << it->second[it->second.size() - 1] << "\n";
		}
		std::cout << "\nPlease select:";
		std::cin >> select;
		if (select == 0) {
			SendMessage();
		}
		else if (select == -1) {
			break;
		}
		else if (select > 0 && select <= key.size()) {
			SingleMessageManagement(key[select - 1]);
		}
	}
}
void BoardManager::SingleMessageManagement(std::string usernamekey) {
	while (true) {
		system("cls");
		std::vector<std::string> msg = users[current_user]->Getmsg()[usernamekey];
		for (int i = 0; i < msg.size(); i++) {
			std::cout << msg[i] << "\n";
		}
		int select = 0;
		std::cout << "\n-1. back\n0. write message\n\nPlease select:";
		std::cin >> select;
		if (select == -1) {
			break;
		}
		else if (select == 0) {
			SendMessage(usernamekey);
		}
	}
}
void BoardManager::MiniGame() {
	std::cout << "this is a game." << std::endl;
}
void BoardManager::SelectBoard() {
	int select = 0;
	while (true) {
		system("cls");
		state = SELECT_BOARD;
		if (users[current_user]->GetPermission_level() == 0) {
			std::cout << "-3 Delete Board" << std::endl;
			std::cout << "-2 Delete Board" << std::endl;
		}
		std::cout << "-1. Back" << std::endl;
		if (users[current_user]->GetPermission_level() == 0) {
			std::cout << "0. Create Board" << std::endl;
		}
		for (int i = 0; i < boards.size(); i++) {
			std::cout << i + 1 << ". " << boards[i]->Topic << std::endl;
		}
		std::cout << "Please select: ";
		std::cin >> select;
		if (select == 0 && users[current_user]->GetPermission_level() == 0) {
			NewBoard();
		}
		else if (select > 0 && select <= boards.size()) {
			Selectedboard = boards[static_cast<std::vector<Board, std::allocator<Board>>::size_type>(select) - 1];
			Selectedboard->current_user = current_user;
			SelectPost();
		}
		else if (select == -1) {
			break;
		}
		else if (users[current_user]->GetPermission_level() == 0 && select == -2) {
			DeleteBoard();
		}
		else if (users[current_user]->GetPermission_level() == 0 && select == -3) {
			DeleteAllBoard();
		}
	}
}
void BoardManager::SelectPost() {
	int select = 0;
	while (true) {
		system("cls");
		state = BOARD;
		if (users[current_user]->GetPermission_level() == 0) {
			std::cout << "-5. Admin Delete Post" << std::endl;
			std::cout << "-4. Delete All Posts" << std::endl;
		}
		std::cout << "-3. Delete Post" << std::endl;
		std::cout << "-2. Edit Post" << std::endl;
		std::cout << "-1. Back" << std::endl;
		std::cout << "0. Create Post" << std::endl;
		for (int i = 0; i < Selectedboard->posts.size(); i++) {
			std::cout << i + 1 << ". " << Selectedboard->posts[i]->Topic << " Author: " << users[Selectedboard->posts[i]->createuserID]->GetUserName() << "  ±À: " << Selectedboard->posts[i]->pushuserID.size() << "  µê: " << Selectedboard->posts[i]->shuserID.size() << std::endl;
		}
		std::cout << "Please select: ";
		std::cin >> select;
		if (users[current_user]->GetPermission_level() < 2 && select == 0) {
			Selectedboard->NewPost(max_postID);
		}
		else if (select > 0 && select <= Selectedboard->posts.size() && !Selectedboard->posts[static_cast<std::vector<Board, std::allocator<Board>>::size_type>(select) - 1]->delete_by_admin) {
			Selectedpost = Selectedboard->posts[static_cast<std::vector<Board, std::allocator<Board>>::size_type>(select) - 1];
			Selectedpost->current_user = current_user;
			PostManagement();
		}
		else if (select == -1) {
			break;
		}
		else if (users[current_user]->GetPermission_level() < 2 && select == -2) {
			Selectedboard->EditPost();
		}
		else if (users[current_user]->GetPermission_level() < 2 && select == -3) {
			Selectedboard->DeletePost();
		}
		else if (users[current_user]->GetPermission_level() == 0 && select == -4) {
			Selectedboard->DeleteAllPost();
		}
		else if (users[current_user]->GetPermission_level() == 0 && select == -5) {
			Selectedboard->AdminDeletePost();
		}
	}
}
void BoardManager::PostManagement() {
	int select = 0;
	while (true) {
		system("cls");
		state = POST;
		std::cout << "\n" << Selectedpost->Topic << "\tAuthor: " << users[Selectedpost->createuserID]->GetUserName() << "  ±À: " << Selectedpost->pushuserID.size() << "  µê: " << Selectedpost->shuserID.size() << "\n\n" << Selectedpost->Pocontent << "\n\n";
		for (int i = 0; i < Selectedpost->comments.size(); i++) {
			std::cout << "--> " << users[Selectedpost->comments[i]->createuserID]->GetUserName() << ": " << Selectedpost->comments[i]->cmcontent << "\n";
		}
		std::cout << "\n\n";
		if (users[current_user]->GetPermission_level() == 0) {
			std::cout << "-6. Admin Delete Post" << std::endl;
			std::cout << "-5. Delete All Comments" << std::endl;
		}
		std::cout << "-4. µê Post" << std::endl;
		std::cout << "-3. ±À Post" << std::endl;
		std::cout << "-2. Delete Comment" << std::endl;
		std::cout << "-1. Back" << std::endl;
		std::cout << "0. Create Comment" << std::endl;
		std::cout << "Please select: ";
		std::cin >> select;
		if (select == -1) {
			break;
		}
		else if (users[current_user]->GetPermission_level() < 2 && select == 0) {
			Selectedpost->NewComment();
		}
		else if (users[current_user]->GetPermission_level() < 2 && select == -2) {
			Selectedpost->DeleteComment();
		}
		else if (users[current_user]->GetPermission_level() < 2 && select == -3) {
			Selectedpost->PushThisPost();
		}
		else if (users[current_user]->GetPermission_level() < 2 && select == -4) {
			Selectedpost->ShThisPost();
		}
		else if (users[current_user]->GetPermission_level() == 0 && select == -5) {
			Selectedpost->DeleteAllComment();
		}
		else if (users[current_user]->GetPermission_level() == 0 && select == -6) {
			Selectedpost->AdminDeleteComment();
		}
	}
}

void BoardManager::NewBoard() {
	std::string nTopic;
	std::getline(std::cin, nTopic);
	std::cout << "New Topic Name: ";
	std::getline(std::cin, nTopic);
	if (nTopic != "") {
		boards.push_back(new Board(nTopic, current_user, &users));
	}
}
void BoardManager::DeleteBoard() {
	system("cls");
	int count = 0,
		select = 0;
	std::vector<int> indarr(0);
	for (int i = 0; i < boards.size(); i++) {
		indarr.push_back(i);
		std::cout << ++count << ". ";
		std::cout << boards[i]->Topic << std::endl;
	}
	std::cout << "Please select post want to delete: ";
	std::cin >> select;
	if (select > 0 && select <= indarr.size()) {
		delete boards[indarr[select - 1]];
		boards.erase(boards.begin() + indarr[select - 1]);
	}
}
void BoardManager::DeleteAllBoard() {
	for (int i = 0; i < boards.size(); i++) {
		delete boards[i];
	}
	boards.clear();
}
void BoardManager::DeleteAllUser() {
	for (int i = 0; i < users.size(); i++) {
		delete users[i];
	}
	users.clear();
}
void BoardManager::SendMessage(std::string tun) {
	//system("cls");
	std::string target_user_name = tun,
		content = "";
	std::string current_user_name = users[current_user]->GetUserName();
	std::getline(std::cin, content);
	if (target_user_name == "") {
		std::cout << "UserName: ";
		std::getline(std::cin, target_user_name);
	}
	std::cout << "Content(single line): ";
	std::getline(std::cin, content);
	for (int i = 0; i < users.size(); i++) {
		if (users[i]->GetUserName() == target_user_name) {
			users[i]->Addmsg(current_user_name, current_user_name + ": " + content);
			users[current_user]->Addmsg(target_user_name, "You: " + content);
			std::cout << "Succ! Enter anything to continue: ";
			std::getline(std::cin, content);
			return;
		}
	}
	std::cout << "Failed! Enter anything to continue: ";
	std::getline(std::cin, content);
}

void BoardManager::SaveStatusToFile() {
	std::ofstream ofile(datafilename);
	int nusers = users.size(),
		thisusertype = 0,
		nboards = boards.size();
	SaveNormDataToFile(max_postID, ofile);
	SaveNormDataToFile(nboards, ofile);
	for (int i = 0; i < nboards; i++) {
		boards[i]->SaveBoardToFile(ofile);
	}

	SaveNormDataToFile(nusers, ofile);
	for (int i = 0; i < nusers; i++) {
		thisusertype = users[i]->GetPermission_level();
		SaveNormDataToFile(thisusertype, ofile);
		users[i]->SaveUserToFile(ofile);
	}

	ofile.close();
}
void BoardManager::LoadStatusFromFile() {
	int nusers = 0,
		thisusertype = 0,
		nboards = 0;
	std::ifstream ifile(datafilename);

	LoadNormDataFromFile(max_postID, ifile);
	LoadNormDataFromFile(nboards, ifile);
	DeleteAllBoard();
	for (int i = 0; i < nboards; i++) {
		boards.push_back(new Board(ifile, &users));
	}

	LoadNormDataFromFile(nusers, ifile);
	DeleteAllUser();
	users = std::vector<User*>(0);
	for (int i = 0; i < nusers; i++) {
		LoadNormDataFromFile(thisusertype, ifile);
		if (thisusertype == 0) {
			users.push_back(new Administrator(ifile));
		}
		else if (thisusertype == 1) {
			users.push_back(new Member(ifile));
		}
		else if (thisusertype == 2) {
			users.push_back(new Guest(ifile));
		}
	}

	ifile.close();
}