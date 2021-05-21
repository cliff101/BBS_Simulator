#pragma once
#include "Post.h"
#include "User.h"
#include <vector>
#include <string>

class Board {
public:
	std::vector <Post*> posts;
	std::string Topic;
	void NewPost(long long this_postID);//func for all user to create post
	void DeletePost(long long this_postID);//func for admin or that user to delete post
	void DeleteAll();//func for admin to delete all posts in a board
	int creatuserID;//������board�ѭ���user(admin) creat��

	int current_user=-1;//�����ثe�O����user�b�ާ@�o��board(�s�Wpost��)  �b���ϥΪ̭n�ާ@�ɤ~assign
	std::vector<User*>* users;//�Ҧ�user��vector����                   �b���ϥΪ̭n�ާ@�ɤ~assign
private:
};
