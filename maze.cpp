#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include "maze.h"

std::ostream &operator <<(std::ostream &os, const Maze &maze) {
	for(int i = 0; i < maze.height(); i++){
		for(int k = 0; k < maze.width(); k++){
			os << maze.map[i][k];
		}
		os << "\n";
	}
	return os;
}

Maze load(std::string filename) {
	std::ifstream ifs(filename.c_str());
	int height = 0;
	std::string filedata;
	std::vector<char> tempc;
	std::vector<bool> tempb;
	Maze maze;
	Location starts, finishes;
	bool containsS = false, containsF = false;

	if(!ifs.is_open()) { 
		throw "Mazefile not found.\n";
	}

	while(getline(ifs, filedata)) {
		for(int i = 0; i < filedata.length(); i++) {
			if(filedata.at(i) == '+'){
				tempc.push_back('+');
				tempb.push_back(true);
			} else if(filedata.at(i) == '-'){
				tempc.push_back('-');
				tempb.push_back(true);
			} else if(filedata.at(i) == '|'){
				tempc.push_back('|');
				tempb.push_back(true);
			} else if(filedata.at(i) == '*'){
				tempc.push_back('*');
				tempb.push_back(false);
			} else if(filedata.at(i) == ' '){
				tempc.push_back(' ');
				tempb.push_back(true);
			} else if(filedata.at(i) == 'F'){
				containsF = true;
				tempc.push_back('F');
				tempb.push_back(false);
				finishes.x = height;
				finishes.y = i;
			} else if(filedata.at(i) == 'S'){
				containsS = true;
				tempc.push_back('S');
				tempb.push_back(false);
				starts.x = height;
				starts.y = i;
			}
		}
		maze.spec.push_back(tempb);
		maze.map.push_back(tempc);
		tempb.clear();
		tempc.clear();
		height++;
	}
	if(containsS == false || containsF == false){
		throw "Missing start or finish location\n";
	} else {
		maze.start = starts;
		maze.finish = finishes;
		ifs.close();
		return maze;
	}
}

bool Maze::solve(){
	std::stack<Location> sL;
	Location tempL, redrawL;
	redrawL = start;
	sL.push(start);
	while(!sL.empty()){
		current = sL.top();
		sL.pop();

		if(redrawL == start){
			map[start.x][start.y] = 'S';
		} else
			map[redrawL.x][redrawL.y] = '*';

		redrawL = current;
		map[current.x][current.y] = 'O';
		spec[current.x][current.y] = true;

		std::cout << *this << std::endl;

		if(current == finish){
			std::cout << "Maze Solved.\n";
			return true;
		}
		if(spec[current.x-1][current.y] == false){
			tempL.x = current.x - 1;
			tempL.y = current.y;
			sL.push(tempL);
		}
		if(spec[current.x][current.y+1] == false){
			tempL.x = current.x;
			tempL.y = current.y + 1;
			sL.push(tempL);
		}
		if(spec[current.x+1][current.y] == false){
			tempL.x = current.x + 1;
			tempL.y = current.y;
			sL.push(tempL);
		}
		if(spec[current.x][current.y-1] == false){
			tempL.x = current.x;
			tempL.y = current.y - 1;
			sL.push(tempL);
		}
	}
	return false;
}
