#include "Map.h"

Map::Map(int width, int height) : width(width), height(height)
{
	if (width <= 0 || height <= 0) {
		std::cout << "ERROR : Invalid width = " << width << ", height = " << height << std::endl;
		return;
	}
	data.reset(new Exhibit[width * height]);
}

Map::~Map()
{
	data.release();
}

const int Map::getWidth() const
{
	return this->width;
}

const int Map::getHeight() const
{
	return this->height;
}

Exhibit Map::getData(const Position2i & pos)
{
	return getData(toIndex(pos));
}

Exhibit Map::getData(const int &idx) const
{
	if (!isValidIdx(idx)) return Exhibit();
	else return data[idx];
}

Map & Map::setData(const Position2i & pos, const Exhibit & newdata)
{
	return setData(toIndex(pos), newdata);
}

Map & Map::setData(const int &idx, const Exhibit & newdata)
{
	if (!isValidIdx(idx))	return *this;
	data[idx] = newdata;
	return *this;
}

const bool Map::isValidIdx(int idx) const
{
	if (idx >= 0 && idx < width * height) return true;
	std::cout << "ERROR : idx = " << idx << " out of range [0, " << width * height - 1 << "]!" << std::endl;
	return false;
}

const int Map::toIndex(const Position2i & pos) const
{
	return pos.getY() * width + pos.getX() - width - 1;
}

const Position2i Map::toPosition(const int & idx) const
{
	return Position2i(idx % width + 1, idx / width + 1);
}

const bool Map::isEmpty(const Position2i & pos) const
{
	int idx = toIndex(pos);
	if (!isValidIdx(idx)) return false;
	return data[idx].getType() == EXHIBIT_EMPTY;
}
