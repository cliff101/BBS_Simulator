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
	int creatuserID;//紀錄本board由哪位user(admin) creat的

	int current_user=-1;//紀錄目前是哪個user在操作這個board(新增post用)  在有使用者要操作時才assign
	std::vector<User*>* users;//所有user的vector指標                   在有使用者要操作時才assign
private:
};
