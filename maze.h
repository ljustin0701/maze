#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>

struct Location  {
	friend std::ostream &operator <<(std::ostream &os, const Location &location) {
		os << "(" << location.x << ", " << location.y << ")";
		return os;
	}
	bool operator ==(const Location &rhs) const {return x == rhs.x && y == rhs.y;}
	bool operator !=(const Location &rhs) const {return !(*this == rhs);}
	operator bool() const {return x >= 0;}
	Location(int x=-1, int y=-1) : x(x), y(y) {}
	int x, y;
};

class Maze;
Maze load(std::string filename);

class Maze {
	friend std::ostream &operator <<(std::ostream &os, const Maze &maze);
	friend Maze load(std::string filename);
public:
    Maze() {};
    bool solve();
private:
	int height() const {return spec.size();}
	int width() const {return spec[0].size();}
	std::vector<std::vector<bool> > spec;
	std::vector<std::vector<char> > map;
	Location start, finish, current;
};

#endif
