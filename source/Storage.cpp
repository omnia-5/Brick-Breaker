#include "../headers/Storage.h"

// Constructor
Storage::Storage() {
	std::ifstream dataBaseFile("./storage/data.txt");
	if (dataBaseFile.is_open()) {
		std::string line, key, value;
		while (std::getline(dataBaseFile, line)) {
			std::istringstream in(line);
			in >> key >> value;
			leaderBoard.push_back(Score(key, std::stoi(value)));
		}
	}
	dataBaseFile.close();
};

// Destructor
Storage::~Storage() {};

void Storage::addData(std::string data) {
	std::ofstream dataBaseFile("./storage/data.txt", std::ios_base::app);
	if (dataBaseFile.is_open()) dataBaseFile << data + " \n";
	dataBaseFile.close();
};


std::string left(const std::string s, const int w) {
	std::stringstream ss, spaces;
	int padding = w - s.size();
	for (int i = 0; i < padding; ++i) spaces << " ";
	ss << s << spaces.str();
	return ss.str();
}

std::string Storage::getStringLeaderBoard() {
	std::string data = "";
	int dataEnterd = 0;
	std::sort(leaderBoard.begin(), leaderBoard.end(), [&](Score& a, Score& b) {
		return a.getValue() > b.getValue();
	});

	for (unsigned int i = 0; i < leaderBoard.size(); i++) {
		if (dataEnterd >= 10) break;
		data += left(std::to_string(i + 1), 2) + "-" + left(leaderBoard[i].getName(), 10) + "-" + std::to_string(leaderBoard[i].getValue()) + "\n";
		dataEnterd++;
	}
	return data;
};