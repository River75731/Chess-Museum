#pragma once
#include "../Common/Common.h"

enum ExhibitType {
	EXHIBIT_EMPTY,
	EXHIBIT_CHESS_SET,
	EXHIBIT_CUBE,
	EXHIBIT_DOOR,
	EXHIBIT_WINDOW,
	EXHIBIT_PAWN,
	EXHIBIT_ROOK,
	EXHIBIT_KNIGHT,
	EXHIBIT_BISHOP,
	EXHIBIT_QUEEN,
	EXHIBIT_KING,
	EXHIBIT_CLASSICCHESS
};

class Exhibit final
{
private:
	// each time scale for *= scaleStep, with maximum of scaleMax
	static const float scaleSpeed;		// 1.05
	static const float scaleMax;		// 2
	// each time rotate for += rotateStep
	static const float rotateSpeed;		// 0.1
	// each time translate for += translateStep, with maximum of translateMax
	static const float translateSpeed;	// 0.05
	static const float translateMax;	// 1

	// translate -> rotate -> scale
	ExhibitType type;
	unsigned int textureNum; // # of texture, 0 for empty
	unsigned int lightNum;	// # of light, 0 for unable light
	Vector3f translate;	
	float rotate; // rotate through z-axis
	Vector3f scale;
	bool hasTable;
	bool isRotating;

public:
	// ExhibitTypeName to String
	static const std::map<const ExhibitType, const std::string> toString;
	static const std::map<const std::string, const ExhibitType> toType;

	// Constructor & Destructor
	Exhibit(const ExhibitType& type = EXHIBIT_EMPTY, const unsigned int& textureNum = 0, const unsigned int & lightNum = 0, const Vector3f& translate = Vector3f(), const float& rotate = 0, const Vector3f& scale = Vector3f(1, 1, 1), const bool& hasTable = true, const bool& isRotating = false);
	Exhibit(const Exhibit& that);
	~Exhibit();
	// Get - Set Method
	const ExhibitType getType() const;
	const unsigned int getTextureNum() const;
	const unsigned int getLightNum() const;
	const Vector3f getTranslate() const;
	const float getRotate() const;
	const Vector3f getScale() const;
	const bool getHasTable() const;
	const bool getIsRotating() const;
	Exhibit& setType(const ExhibitType& type);
	Exhibit& setTextureNum(const unsigned int& textureNum);
	Exhibit& setLightNum(const unsigned int& lightNum);
	Exhibit& setTranslate(const Vector3f& translate);
	Exhibit& setRotate(const float& rotate);
	Exhibit& setScale(const Vector3f& scale);
	Exhibit& setHasTable(const bool& hasTable);
	Exhibit& setIsRotating(const bool& isRotating);
	// Change State

	// whether the exhibit is empty
	const bool isEmpty();

	// change the light to unable
	Exhibit& clearLight();

	// change the texture to empty
	Exhibit& clearTexture();

	// change the type of exhibit
	Exhibit& changeType(const ExhibitType& type);

	// change the state of hastable to the opposite
	Exhibit& changeHasTable();

	// change the state of isrotating to the opposite
	Exhibit& changeIsRotating(); 

	// translate the model by time and direction(1 for positive, -1 for negative, 0 for keep current state)
	Exhibit& execTranslate(const float& time = 1, const int& directX = true, const int& directY = true, const int& directZ = true); 

	// rotate the model by time and direction (1 for counterclockwise and -1 for clockwise)
	Exhibit& execRotate(const float& time = 1, const int& direction = true);	

	// scale the model by direction(1 for enlarge, -1 for shrink, 0 for keep current state)
	Exhibit& execScale(const int& directX = true, const int& directY = true, const int& directZ = true); 

};

std::istream& operator>>(std::istream& is, Exhibit &exhibit);
std::ostream& operator<<(std::ostream& os, const Exhibit &exhibit);

/*
	*** Exhibit Data ***
	type textureNum lightNum;	
	translateX translateY translateZ
	rotate
	scaleX scaleY scaleZ
	hasTable(1/0) isRotating(1/0)
*/