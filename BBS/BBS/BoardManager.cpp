#include "BoardManager.h"

BoardManager::BoardManager() {
	users.push_back(new User("guest", "", 2));
}
BoardManager::BoardManager(std::string& filename) {
	///*/*login*/*/
}

void BoardManager::StartBoardManager() {
	AccountManager();
}
void BoardManager::AccountManager() {
	while (true) {
		int select;
		std::cout << "1. login\n2. create account\n5. exit\nPlease Select:";
		std::cin >> select;
		if (select == 1) {//if successful, directly call menu in login func
			LogIn();
		}
		else if (select == 2) {
			CreateAccount();
		}
		else if (select == 3) {
			//DeleteAccount();
			SaveStatusToFile("test.dat");
			LoadStatusFromFile("test.dat");
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
		if (usn == "guest") {
			std::cout << "Cannot nameed guest!\nEnter anything to continue:";
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
	std::cout << "This is menu.\nYour Premission level: " << users[current_user]->GetPermission_level() << std::endl;

}

void BoardManager::SaveStatusToFile(std::string filename){
	std::ofstream ofile(filename);
	int nusers = users.size();
	ofile.write((char*)&nusers, sizeof(nusers));
	for (int i = 0; i < nusers; i++) {
		users[i]->SaveUserToFile(ofile);
	}
	//then board
}
void BoardManager::LoadStatusFromFile(std::string filename){
	for (int i = 0; i < users.size(); i++) {
		delete users[i];
	}
	users.clear();

	std::ifstream ifile(filename);
	int nusers = 0;
	ifile.read((char*)&nusers, sizeof(nusers));
	for (int i = 0; i < nusers; i++) {
		users.push_back(new User(ifile));
	}
	//then board
}