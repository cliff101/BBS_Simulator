#pragma once
#include "Post.h"
#include "User.h"
#include <fstream>
#include <vector>
#include <string>

class Board {
public:
	Board();
	Board(std::string inTopic, int increateuserID, std::vector<User*>* inusersptr);//construct board with topic, createuserID
	Board(std::ifstream& ifile, std::vector<User*>* inusersptr);//construct board with load file

	std::vector <Post*> posts;
	std::string Topic = "";
	void NewPost(long long this_postID);//func for all user to create post
	void DeletePost(long long this_postID);//func for admin or that user to delete post
	void DeleteAll();//func for admin to delete all posts in a board
	int createuserID = -1;//������board�ѭ���user(admin) creat��

	int current_user = -1;//�����ثe�O����user�b�ާ@�o��board(�s�Wpost��)  �b���ϥΪ̭n�ާ@�ɤ~assign
	std::vector<User*>* usersptr;//�Ҧ�user��vector����

	void SaveBoardToFile(std::ofstream& ofile);//including num of posts
	void ReadBoardFromFile(std::ifstream& ifile);
private:
};
