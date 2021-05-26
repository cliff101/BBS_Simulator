#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "User.h"


class Post {
public:
	class Comment {
	public:
		Comment(std::string incmcontent, int increateuserID, std::vector<User*>* inusersptr);//construct comment with content, createuserID
		Comment(std::ifstream& ifile, std::vector<User*>* inusersptr);//construct comment with load file
		std::string cmcontent;

		int createuserID;//������Comment�ѭ���user creat��                �b���ϥΪ̭n�ާ@�ɤ~assign
		std::vector<User*>* usersptr;

		void SaveCommentToFile(std::ofstream& ofile);
		void LoadCommentFromFile(std::ifstream& ifile);
	};
	Post(std::string inTopic, std::string incontent, int increateuserID, int inthis_postID, std::vector<User*>* inusersptr);//construct post with content, createuserID
	Post(std::ifstream& ifile, std::vector<User*>* inusersptr);//construct post with load file
	~Post();

	long long this_postID;
	int createuserID;//������post�ѭ���user creat��
	std::vector<int> pushuserID;//�����ӱ���post��userID
	std::vector<int> shuserID;//�����ӵ��post��userID
	std::string Topic = "";
	std::string Pocontent = "";
	std::vector<Comment*> comments;

	void NewComment();//func for all none guest to create comment
	void DeleteComment();//func for admin or that user to delete comment
	void DeleteAllComment();//func for admin to delete all comments

	int current_user = -1;//�����ثe�O����user�b�ާ@�o��post(�s�Wcomment��)  �b���ϥΪ̭n�ާ@�ɤ~assign
	std::vector<User*>* usersptr;

	void SavePostToFile(std::ofstream& ofile);//including num of comments
	void LoadPostFromFile(std::ifstream& ifile);
private:
};