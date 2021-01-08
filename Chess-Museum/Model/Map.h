#pragma once
#include "../Common/Common.h"
#include "Exhibit.h"


class Map final
{
	// All Position2i in class Map is start with 1
	// All index is start with 0
private:
	const int width;	// X in Position2i
	const int height;	// Y in Position2i
	std::unique_ptr<Exhibit[]> data;

	// Get - Set Method
	Exhibit getData(const int &idx) const;		// 0 to width * height - 1
	Map& setData(const int &idx, const Exhibit& newdata);
	const bool isValidIdx(int idx) const;

public:
	// Constructor & Destructor
	Map(int width, int height);
	~Map();
	
	// Get - Set Method
	const int getWidth() const;
	const int getHeight() const;
	Exhibit getData(const Position2i &pos);		// (1 to width, 1 to height)
	Map& setData(const Position2i &pos, const Exhibit& newdata);
	
	// Index transfer
	const int toIndex(const Position2i& pos) const;	// position to index
	const Position2i toPosition(const int& idx) const;	// index to position
	
	// Check if a place is empty
	const bool isEmpty(const Position2i& pos) const;

};