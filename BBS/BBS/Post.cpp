#include "Post.h"
#include "FileIOTools.h"

Post::Comment::Comment(std::string incmcontent, int increateuserID, std::vector<User*>* inusersptr) :usersptr(inusersptr), cmcontent(incmcontent), createuserID(increateuserID),delete_by_admin(false) {}
Post::Comment::Comment(std::ifstream& ifile, std::vector<User*>* inusersptr) : usersptr(inusersptr), cmcontent(""), createuserID(-1), delete_by_admin(false) {
	LoadCommentFromFile(ifile);
}
Post::Comment::Comment(const Comment& other){
	cmcontent = other.cmcontent;
	createuserID = other.createuserID;
	usersptr = other.usersptr;
	delete_by_admin = other.delete_by_admin;

}

void Post::Comment::SaveCommentToFile(std::ofstream& ofile) {
	SaveStrToFile(cmcontent, ofile);
	SaveNormDataToFile(createuserID, ofile);
	SaveNormDataToFile(delete_by_admin, ofile);
}
void Post::Comment::LoadCommentFromFile(std::ifstream& ifile) {
	LoadStrFromFile(cmcontent, ifile);
	LoadNormDataFromFile(createuserID, ifile);
	LoadNormDataFromFile(delete_by_admin, ifile);
}

Post::Post(std::string inTopic, std::string incontent, int increateuserID, int inthis_postID, std::vector<User*>* inusersptr) :usersptr(inusersptr), Topic(inTopic), Pocontent(incontent), createuserID(increateuserID), this_postID(inthis_postID), delete_by_admin(false) {}
Post::Post(std::ifstream& ifile, std::vector<User*>* inusersptr) : usersptr(inusersptr), Topic(""), Pocontent(""), createuserID(-1), pushuserID(0), shuserID(0), this_postID(-1), delete_by_admin(false) {
	LoadPostFromFile(ifile);
}
Post::Post(std::string deletebyadminreason, int originID, std::vector<User*>* inusersptr) : usersptr(inusersptr), Topic(deletebyadminreason), Pocontent(""), createuserID(originID), this_postID(-1), delete_by_admin(true) {}
Post::~Post() {
	DeleteAllComment();
}

void Post::NewComment() {
	std::string cmcontent, temp;
	std::getline(std::cin, cmcontent);
	std::cout << "Comment: ";
	std::getline(std::cin, cmcontent);
	if (cmcontent != "") {
		comments.push_back(new Comment(cmcontent, current_user, usersptr));
	}
}
void Post::DeleteComment() {
	system("cls");
	int count = 0,
		select = 0;
	std::vector<int> indarr(0);
	for (int i = 0; i < comments.size(); i++) {
		if (comments[i]->createuserID == current_user) {
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
void Post::AdminDeleteComment() {
	system("cls");
	int count = 0,
		select = 0;
	std::vector<int> indarr(0);
	for (int i = 0; i < comments.size(); i++) {
		if (!comments[i]->delete_by_admin) {
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
		std::string reason;
		std::getline(std::cin, reason);
		std::cout << "Delete reason: ";
		std::getline(std::cin, reason);
		Comment* temp = new Comment(" (Deleted by admin(" + (*usersptr)[current_user]->GetUserName() + "). Reason: " + reason + " )", comments[indarr[select - 1]]->createuserID, usersptr);
		delete comments[indarr[select - 1]];
		comments[indarr[select - 1]] = temp;
	}
}
void Post::ShThisPost() {
	pushshpostoprate(shuserID, pushuserID);
}
void Post::PushThisPost() {
	pushshpostoprate(pushuserID, shuserID);
}
void Post::pushshpostoprate(std::vector<int>& selectedvec, std::vector<int>& othervec) {
	for (int i = 0; i < othervec.size(); i++) {
		if (othervec[i] == current_user) {
			othervec.erase(othervec.begin() + i);
			selectedvec.push_back(current_user);
			return;
		}
	}
	for (int i = 0; i < selectedvec.size(); i++) {
		if (selectedvec[i] == current_user) {
			selectedvec.erase(selectedvec.begin() + i);
			return;
		}
	}
	selectedvec.push_back(current_user);
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
	SaveNormDataToFile(delete_by_admin, ofile);
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
	LoadNormDataFromFile(delete_by_admin, ifile);
}

