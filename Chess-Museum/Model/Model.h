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
	MODEL_PLAY_CHESS,
	MODEL_PLAY_CHESS_HISTORY,	// chess history

};

class Model final
{
private:
	ModelState state;

public:
};