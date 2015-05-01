#include <iostream>
#include <stack>
#include <cstdlib>
#include <string>
#include "maze.h"

using namespace std;

int main(int argc, char **argv){
	if(argc != 2){
		cerr << "Missing maze file." << endl;
		exit(1);
	}
	
	try{
		string mazeFile = string(argv[1]);
		Maze maze = load(mazeFile);
		cout << maze << endl;
		if(!maze.solve()) {cout << "Maze cannot be solved.." << endl;}
	} catch (const char* m) {
		cerr << m << endl;
	}
}
