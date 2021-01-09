#pragma once
#include "../Common/Common.h"

// Map Logic Model

#include "Exhibit.h"
#include "Map.h"

// Chess Logic Model

#include "Chess.h"
#include "ClassicChess.h"


enum ModelState {
	MODEL_PLAYMODE,
	MODEL_EDITMODE,
	MODEL_EDIT_EXHIBIT,			// Editing an exhibit
	MODEL_PLAY_CHESS,
	MODEL_PLAY_CHESS_HISTORY,	// chess history

};

class Model final
{
private:
	ModelState state;
	std::shared_ptr<Map> map;
	//std::vector<ClassicChess> chess;
	std::vector<Position2i> chessLocation;


	// Use in MODEL_EDITMODE
	int textureCnt;	// 0 : unset , other : the number of texture
	int lightCnt;	// 0 : unset , other : the number of light
	bool isChosen;			// the highlight block is chosen or not
	Position2i chosenBlock;	// highlight block
	Exhibit chosenExhibit;	// the chosen Exhibit
	   
	// Use in MODEL_PLAY_CHESS
	Position2i chosenBlock1;

	void loadMap(std::string address);
	void saveMap(std::string address);


public:
	// Constructor & Destructor
	Model();
	~Model();
	
	const ModelState getState() const;

	// Use in MODEL_PLAYMODE
	bool enterChess(const Position2i& pos);	// Enter Chess Mode which chess is placed at pos, return true if valid
	void enterEdit();		// Enter edit mode
	bool canEnter(const Position2i& pos);		// whether player can enter pos or not
	void resetPlay();		// Reset the play mode and go to the beginning position
	
	// Use in MODEL_EDITMODE
	bool getExhibit(const Position2i& pos, Exhibit& res);	// get Exhibit, return to res, true if valid and false if invalid(place is empty or not the center)
	void discardSaveExhibit();	// 
	void saveExhibit();	// save change to Exhibit		
	void clearLight();	// change the light to unable
	void clearTexture();	// change the texture to empty	
	void setTextureNum(const unsigned int& textureNum);
	void setLightNum(const unsigned int& lightNum);
	void changeHasTable();	// change the state of hastable to the opposite	
	void changeIsRotating();	// change the state of isrotating to the opposite	
	void execTranslate(const float& time = 1, const int& directX = true, const int& directY = true, const int& directZ = true); // translate the model by time and direction(1 for positive, -1 for negative, 0 for keep current state)	
	void execRotate(const float& time = 1, const int& direction = true);// rotate the model by time and direction (1 for counterclockwise and -1 for clockwise)
	void execScale(const int& directX = true, const int& directY = true, const int& directZ = true);// scale the model by direction(1 for enlarge, -1 for shrink, 0 for keep current state)

	// todo : add exhibit change
	
	bool moveExhibit(const Position2i& src, const Position2i& dest);	// move the Exhibit from src to dest, true if success 
	void resetMap();
	
};