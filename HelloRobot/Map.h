/*
 * Map.h
 *
 *  Created on: Mar 22, 2016
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
using namespace std;

class Map {
private:
	unsigned int width;
	unsigned int height;
	vector<vector<bool> > map;
	vector<unsigned char> pixels;

	bool checkIfCellIsOccupied(int i, int j);
	void printMap() const;

public:
	Map();
	void loadMap(const char* mapFile);
	virtual ~Map();
};

#endif /* MAP_H_ */
