#pragma once
#include <string>
#include <vector>
#include "User.h"

class Post {
public:
	class Comment {
	public:
		std::string content;

		int creatuserID;//������Comment�ѭ���user creat��                �b���ϥΪ̭n�ާ@�ɤ~assign
		User* current_real_user;//�Ҧ�user��vector����                  �b���ϥΪ̭n�ާ@�ɤ~assign
	};
	std::string content;
	std::vector<Comment> comments;
	void NewComment();//func for all user to create comment
	void DeleteComment();//func for admin or that user to delete comment
	long long this_postID;
	int creatuserID;//������post�ѭ���user creat��
	std::vector<int> pushuserID;//�����ӱ���post��userID
	std::vector<int> shuserID;//�����ӵ��post��userID

	int current_user=-1;//�����ثe�O����user�b�ާ@�o��post(�s�Wcomment��)  �b���ϥΪ̭n�ާ@�ɤ~assign
	std::vector<User*>* usersptr;//�Ҧ�user��vector����                  �b���ϥΪ̭n�ާ@�ɤ~assign
private:
};