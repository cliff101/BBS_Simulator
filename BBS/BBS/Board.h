#pragma once
#include "Post.h"
#include "User.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

class Board {
public:
	Board(std::string inTopic, int increateuserID, std::vector<User*>* inusersptr);//construct board with topic, createuserID
	Board(std::ifstream& ifile, std::vector<User*>* inusersptr);//construct board with load file
	~Board();

	std::vector<Post*> posts;
	std::string Topic = "";
	int createuserID = -1;//紀錄本board由哪位user(admin) creat的

	void NewPost(long long& this_postID, bool edit = false);//func for all user to create post
	void DeletePost();//func for admin or that user to delete post
	void AdminDeletePost();
	void DeleteAllPost();//func for admin to delete all posts in a board
	void EditPost();//func for that user to edit post

	int current_user = -1;//紀錄目前是哪個user在操作這個board(新增post用)  在有使用者要操作時才assign
	std::vector<User*>* usersptr;

	void SaveBoardToFile(std::ofstream& ofile);//including num of posts
	void LoadBoardFromFile(std::ifstream& ifile);
};
