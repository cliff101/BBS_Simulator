#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "User.h"
#include "Board.h"
#include "Viewer.h"
#include "Guest.h"
#include "Member.h"
#include "Administrator.h"

enum BoardState
{
	MENU,
	SELECT_BOARD,
	BOARD,
	POST
};

/*
question:
帳號刪除後，保有紀錄，是否可取相同名稱?
如不保留，其posts、comments如何處理?
*/

class BoardManager
{
public:
	BoardManager();
	BoardManager(std::string& filename);//construct BoardManager with a saved file
	~BoardManager();

	void StartBoardManager();//call AccountManager
	void AccountManager();//login or reg, call Menu
	void CreateAccount();
	void LogIn();
	//void DeleteAccount();
	//void LogOut();
	void Menu();//call Select Board || MiniGame || logout || MessageManagement, back to AccoutManager
	void SelectBoard();//show boards and let user select board || back to Menu
	void MiniGame();//Play Minigame || back to Menu
	void MessageManagement();
	void SingleMessageManagement(std::string usernamekey);
	void SelectPost();//show posts and let user select post || back to SelectBoard
	void PostManagement();//show post, including comment

	void NewBoard();//func for admin to create board
	void DeleteBoard();//func for admin to delete board
	void DeleteAllBoard();
	void DeleteAllUser();
	void SendMessage(std::string tun = "");

	void SaveStatusToFile();//including num of boards, num of users
	void LoadStatusFromFile();
private:
	std::vector<User*> users;//0 is guest!!
	std::vector<Board*> boards;

	Board* Selectedboard;
	Post* Selectedpost;
	Post::Comment* Selectedcomment;

	int current_user = -1;
	long long max_postID = 0;//目前的最高post id，用於紀錄postID用(User.h spec要求)

	BoardState state = MENU;//目前使用者所處的狀態
	Viewer viewer;
	std::string datafilename = "data.dat";
};