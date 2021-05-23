#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "User.h"

class Post {
public:
	class Comment {
	public:
		Comment(std::string incmcontent, int increateuserID, std::vector<User*>* inusersptr);//construct comment with content, createuserID
		Comment(std::ifstream& ifile, std::vector<User*>* inusersptr);//construct comment with load file
		std::string cmcontent;

		int createuserID;//������Comment�ѭ���user creat��                �b���ϥΪ̭n�ާ@�ɤ~assign
		std::vector<User*>* usersptr;//�Ҧ�user��vector����

		void SaveCommentToFile(std::ofstream& file);
		void ReadCommentFromFile(std::ifstream& file);
	};
	Post(std::string incontent, int increateuserID, std::vector<User*>* inusersptr,int inthis_postID);//construct post with content, createuserID
	Post(std::ifstream& ifile, std::vector<User*>* inusersptr);//construct post with load file

	std::string content;
	std::vector<Comment> comments;
	void NewComment();//func for all user to create comment
	void DeleteComment();//func for admin or that user to delete comment
	long long this_postID;
	int createuserID;//������post�ѭ���user creat��
	std::vector<int> pushuserID;//�����ӱ���post��userID
	std::vector<int> shuserID;//�����ӵ��post��userID

	int current_user=-1;//�����ثe�O����user�b�ާ@�o��post(�s�Wcomment��)  �b���ϥΪ̭n�ާ@�ɤ~assign
	std::vector<User*>* usersptr;//�Ҧ�user��vector����

	void SavePostToFile(std::ofstream& ofile);//including num of comments
	void ReadPostFromFile(std::ifstream& ifile);
private:
};