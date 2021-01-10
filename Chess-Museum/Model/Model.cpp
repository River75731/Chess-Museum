#include "Model.h"

const std::map<const ModelState, const std::string> Model::toString = {
	{MODEL_PLAYMODE, "MODEL_PLAYMODE"},
	{MODEL_EDITMODE, "MODEL_EDITMODE"},
	{MODEL_EDIT_EXHIBIT, "MODEL_EDIT_EXHIBIT"},	
	{MODEL_PLAY_CHESS, "MODEL_PLAY_CHESS"},
	{MODEL_PLAY_CHESS_HISTORY, "MODEL_PLAY_CHESS_HISTORY"}
};
const std::map<const std::string, const ModelState> Model::toState = {
	{"MODEL_PLAYMODE", MODEL_PLAYMODE},
	{"MODEL_EDITMODE", MODEL_EDITMODE},
	{"MODEL_EDIT_EXHIBIT", MODEL_EDIT_EXHIBIT},
	{"MODEL_PLAY_CHESS", MODEL_PLAY_CHESS},
	{"MODEL_PLAY_CHESS_HISTORY", MODEL_PLAY_CHESS_HISTORY}
};

void Model::loadMap(const std::string& address)
{
	std::ifstream fin;
	fin.open(address);
	if (fin.fail()) {
		std::cout << "Open File failed!" << std::endl;
		return;
	}
	std::string stateIn;
	fin >> stateIn;
	this->state = toState.at(stateIn);
	unsigned int width, height, itemNum, chessNum, item;
	fin >> width >> height >> itemNum >> chessNum;
	map.reset(new Map(width, height));
	std::unique_ptr<Exhibit[]> exhibit(new Exhibit[itemNum + 1]);
	exhibit[0] = Exhibit();
	for (unsigned int i = 1; i <= itemNum; i++) fin >> exhibit[i];
	// todo : Chess Input
	for (unsigned int i = 1; i <= height; i++) {
		for (unsigned int j = 1; j <= width; j++) {
			fin >> item;
			if (item > itemNum) 
			{
				std::cout << "ERROR : item out of range!" << std::endl;
				return;
			}
			map->setData(Position2i(j, i), exhibit[item]);
		}
	}
	fin.close();
}

Model::Model()
{
	loadMap();
	chosenBlock = Position2i(1, 1);
	chosenExhibit = Exhibit();
}

Model::~Model()
{
}

const ModelState Model::getState() const
{
	return state;
}

void Model::enterEdit()
{
	if (state == MODEL_PLAYMODE) state = MODEL_EDITMODE;
	return;
}

bool Model::canEnter(const Position2i & pos)
{
	return map->isEmpty(pos);
}


void Model::chooseBlock(const Position2i & pos)
{
	if (state == MODEL_EDITMODE)
	{
		chosenBlock = pos;
		chosenExhibit = map->getData(pos);
	}
	return;
}

void Model::editExhibit()
{
	if (state == MODEL_EDITMODE)
	{
		state = MODEL_EDIT_EXHIBIT;
	}
}

void Model::deleteExhibit()
{
	if (state == MODEL_EDITMODE) 
	{
		map->setData(chosenBlock, Exhibit());
	}
}

void Model::enterPlay()
{
	if (state == MODEL_EDITMODE)
	{
		state = MODEL_PLAYMODE;
	}
}

void Model::discardSaveExhibit()
{
	if (state == MODEL_EDIT_EXHIBIT)
	{
		state = MODEL_EDITMODE;
		chosenExhibit = map->getData(chosenBlock);
	}
}

void Model::saveExhibit()
{
	if (state == MODEL_EDIT_EXHIBIT)
	{
		state = MODEL_EDITMODE;
		map->setData(chosenBlock, chosenExhibit);
	}
}

void Model::changeType(const ExhibitType & type)
{
	if (state == MODEL_EDIT_EXHIBIT)
	{
		chosenExhibit.changeType(type);
	}
}

void Model::clearLight()
{
	if (state == MODEL_EDIT_EXHIBIT)
	{
		chosenExhibit.clearLight();
	}
}

void Model::clearTexture()
{
	if (state == MODEL_EDIT_EXHIBIT)
	{
		chosenExhibit.clearTexture();
	}
}

void Model::setTextureNum(const unsigned int & textureNum)
{
	if (state == MODEL_EDIT_EXHIBIT)
	{
		chosenExhibit.setTextureNum(textureNum);
	}
}

void Model::setLightNum(const unsigned int & lightNum)
{
	if (state == MODEL_EDIT_EXHIBIT)
	{
		chosenExhibit.setLightNum(lightNum);
	}
}

void Model::changeHasTable()
{
	if (state == MODEL_EDIT_EXHIBIT)
	{
		chosenExhibit.changeHasTable();
	}
}

void Model::changeIsRotating()
{
	if (state == MODEL_EDIT_EXHIBIT)
	{
		chosenExhibit.changeIsRotating();
	}
}

void Model::execTranslate(const float & time, const int & directX, const int & directY, const int & directZ)
{
	if (state == MODEL_EDIT_EXHIBIT)
	{
		chosenExhibit.execTranslate(time, directX, directY, directZ);
	}
}

void Model::execRotate(const float & time, const int & direction)
{
	if (state == MODEL_EDIT_EXHIBIT)
	{
		chosenExhibit.execRotate(time, direction);
	}
}

void Model::execScale(const int & directX, const int & directY, const int & directZ)
{
	if (state == MODEL_EDIT_EXHIBIT)
	{
		chosenExhibit.execScale(directX, directY, directZ);
	}
}

bool Model::getExhibit(const Position2i & pos, Exhibit & res) const
{
	res = map->getData(pos);
	return !res.isEmpty();
}

const Exhibit Model::getEditingExhibit() const
{
	if(state == MODEL_EDIT_EXHIBIT) return chosenExhibit;
	else return Exhibit();
}
