#include "Post.h"
#include "FileIOTools.h"

Post::Comment::Comment(std::string incmcontent, int increateuserID, std::vector<User*>* inusersptr) :usersptr(inusersptr), cmcontent(incmcontent), createuserID(increateuserID) {}
Post::Comment::Comment(std::ifstream& ifile, std::vector<User*>* inusersptr) : usersptr(inusersptr), cmcontent(""), createuserID(-1) {
	LoadCommentFromFile(ifile);
}

void Post::Comment::SaveCommentToFile(std::ofstream& ofile) {
	SaveStrToFile(cmcontent, ofile);
	SaveNormDataToFile(createuserID, ofile);
}
void Post::Comment::LoadCommentFromFile(std::ifstream& ifile) {
	LoadStrFromFile(cmcontent, ifile);
	LoadNormDataFromFile(createuserID, ifile);
}

Post::Post(std::string inTopic, std::string incontent, int increateuserID, int inthis_postID, std::vector<User*>* inusersptr) :usersptr(inusersptr), Topic(inTopic), Pocontent(incontent), createuserID(increateuserID), this_postID(inthis_postID) {}
Post::Post(std::ifstream& ifile, std::vector<User*>* inusersptr) : usersptr(inusersptr), Topic(""), Pocontent(""), createuserID(-1), pushuserID(0), shuserID(0), this_postID(-1) {
	LoadPostFromFile(ifile);
}
Post::~Post() {
	DeleteAllComment();
}

void Post::NewComment() {
	std::string cmcontent, temp;
	std::getline(std::cin, cmcontent);
	std::cout << "Comment: ";
	std::getline(std::cin, cmcontent);
	if (cmcontent != "") {
		comments.push_back(new Comment(cmcontent, current_user,usersptr));
	}
}
void Post::DeleteComment() {
	system("cls");
	int count = 0,
		select = 0;
	std::vector<int> indarr(0);
	for (int i = 0; i < comments.size(); i++) {
		if (comments[i]->createuserID == current_user || (*usersptr)[current_user]->GetPermission_level() == 0) {
			indarr.push_back(i);
			std::cout << ++count << ". ";
		}
		std::cout << "--> " << (*usersptr)[comments[i]->createuserID]->GetUserName() << ": " << comments[i]->cmcontent << "\n";
	}
	if (indarr.size() == 0) {
		system("cls");
		return;
	}
	std::cout << "Please select comment want to delete: ";
	std::cin >> select;
	if (select > 0 && select <= indarr.size()) {
		delete comments[indarr[select - 1]];
		comments.erase(comments.begin() + indarr[select - 1]);
	}
}
void Post::DeleteAllComment() {
	for (int i = 0; i < comments.size(); i++) {
		delete comments[i];
	}
	comments.clear();
}

void Post::SavePostToFile(std::ofstream& ofile) {
	SaveStrToFile(Pocontent, ofile);
	SaveVectorToFile(pushuserID, ofile);
	SaveVectorToFile(shuserID, ofile);
	SaveStrToFile(Topic, ofile);
	SaveNormDataToFile(this_postID, ofile);
	SaveNormDataToFile(createuserID, ofile);
	int ncomments = comments.size();
	SaveNormDataToFile(ncomments, ofile);
	for (int i = 0; i < ncomments; i++) {
		comments[i]->SaveCommentToFile(ofile);
	}
}
void Post::LoadPostFromFile(std::ifstream& ifile) {
	LoadStrFromFile(Pocontent, ifile);
	LoadVectorFromFile(pushuserID, ifile);
	LoadVectorFromFile(shuserID, ifile);
	LoadStrFromFile(Topic, ifile);
	LoadNormDataFromFile(this_postID, ifile);
	LoadNormDataFromFile(createuserID, ifile);
	DeleteAllComment();
	int ncomments = 0;
	LoadNormDataFromFile(ncomments, ifile);
	for (int i = 0; i < ncomments; i++) {
		comments.push_back(new Comment(ifile, usersptr));
	}
}

