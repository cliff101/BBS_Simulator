#pragma once
#include <iostream>
#include <vector>
#include "User.h"
#include "Board.h"
#include "Viewer.h"

enum BoardState
{
	MENU,
	SELECT_BOARD,
	BOARD,
	POST
};

class BoardManager
{
public:
	void StartBoardManager();//call AccountManager
	void AccountManager();//login or reg, call Menu
	void Menu();//call Select Board || MiniGame || logout, back to AccoutManager
	void SelectBoard();//show boards and let user select board || back to Menu
	void MiniGame();//Play Minigame || back to Menu
	void SelectPost();//show posts and let user select post || back to SelectBoard
	void PostManagement();//show post, including comment

	void NewBoard();//func for admin to create board
	void DeleteBoard();//func for admin to delete board
private:
	std::vector<User*> users;
	std::vector<Board> boards;

	int current_user;

	long long current_max_postID;//目前的最高post id，用於紀錄postID用(User.h spec要求)

	BoardState state;//目前使用者所處的狀態
	Viewer viewer;
};