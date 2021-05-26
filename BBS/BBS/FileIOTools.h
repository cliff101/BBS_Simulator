#pragma once
#include <string>
#include <fstream>



template<class T>
void SaveVectorToFile(T& data, std::ofstream& ofile) {
	std::string::size_type sizeofdata = sizeof(data);
	long long lenofdata = data.size();
	ofile.write((char*)&sizeofdata, sizeof(sizeofdata));
	ofile.write((char*)&lenofdata, sizeof(lenofdata));
	if (lenofdata > 0) {
		ofile.write((char*)data.data(), sizeofdata);
	}
}
template <class T>
void LoadVectorFromFile(T& data, std::ifstream& ifile) {
	std::string::size_type sizeofdata = 0;
	long long lenofdata = 0;
	ifile.read((char*)&sizeofdata, sizeof(std::string::size_type));
	ifile.read((char*)&lenofdata, sizeof(lenofdata));
	data.resize(lenofdata);
	if (lenofdata > 0) {
		ifile.read((char*)data.data(), sizeofdata);
	}
}

template <class T>
void SaveNormDataToFile(T& data, std::ofstream& ofile) {
	ofile.write((char*)&data, sizeof(data));
}
template <class T>
void LoadNormDataFromFile(T& data, std::ifstream& ifile) {
	ifile.read((char*)&data, sizeof(data));
}

template <class T>
void SaveStrToFile(T& data, std::ofstream& ofile) {
	long long lenofdata = data.size();
	ofile.write((char*)&lenofdata, sizeof(lenofdata));
	if (lenofdata > 0) {
		ofile.write((char*)data.data(), lenofdata);
	}
}
template <class T>
void LoadStrFromFile(T& data, std::ifstream& ifile) {
	long long lenofdata = 0;
	ifile.read((char*)&lenofdata, sizeof(lenofdata));
	data.resize(lenofdata);
	if (lenofdata > 0) {
		ifile.read((char*)data.data(), lenofdata);
	}
}