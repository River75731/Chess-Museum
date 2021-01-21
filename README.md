# Chess Museum

Project for ZJU-CG-2020

Github : https://github.com/River75731/Chess-Museum

Contributors : 

3180101995 江昊翰

3180102060 王呈

3180103656 徐磊

3180105493 傅淄洋

3180106047 杨云皓

## Contribution

江昊翰：程序架构搭建及模块初始化，Common层的Vector类、Position类、MathBase.h，Model层的全部（ClassicChess类、Map类、Exhibit类、Model类）、文件格式设计（地图及棋盘导入文件的格式）

## Goal

场景编辑模式：（鼠标/键盘控制）

1. 添加/删除展品，移动展品
2. 展品大小修改，几何变换
3. 加墙壁/门/窗，窗先使用不透明的窗
4. 预设好样例，导入新的模型有空再考虑
5. 导入预设好的视频
6. 放大/缩小/移动视角
7. 光照：最多八个灯



场景执行模式：

1. 屏幕截图
2. 场景中自由移动（可以蹲下，暂时不能跳）
3. 走进棋盘，给提示，按键，平滑切换到下棋视角
4. 动画播放：棋谱重现
5. 视频播放（不知道能不能整）

光照、视频、截图等图像导入、音乐导入



## Rules of Programming

所有模块测试均放于/TEST/TEST_xxxx.h

命名规则：

尽量使用float而不是double

唯一指针：`std::unique_ptr`

共享指针：（方便内存管理）`std::shared_ptr`

定长数组：`std::array`

不定长数组：`std::vector`

UpperCamelCase : 类名、命名空间名

lowerCamelCase : 变量名、函数名、方法名

全大写，下划线分隔：枚举类型变量名

尽量使用都看得懂的缩写：例如init

尽量不要 `using namespace std`

XX的数目 ： xxxCount

XX的编号 ： xxxIdx (index)

二维变量（坐标等）：xx2f, xx2i (float / int), xx2d(不分类型)

三维变量（坐标等）：xx3f, xx3i, xx3d



## Program Structure

最终程序主要包含Model和View两个模块，Model负责撰写整个程序的逻辑以及存储各种信息（包括地图，棋盘状态等），View负责与Model交互，接收用户的输入并传递给Model告诉Model修改信息，Model修改完之后告诉View更新视图信息，最终View再负责将其绘制并展示给用户。而Common模块中包括了一些基础的类，例如向量类、位置类等。



### 

## Implementation

### Common Layer

#### Vector & Position

设计目标与提供的方法：

Position - Position = Vector

Position + Vector = Position

Vector + Position illegal!

inArea : (xmin, ymin, xlength, ylength)

inRange: (xmin, ymin, xmax, ymax)

int 和 float 不能混用计算，如果需要混用需要显式调用类型转换

在实际使用中主要用的是Vector2i和Vector3f

```c++
class Vector2i {
protected:
	int x;
	int y;
public:
	// Constructor & Destructor
	Vector2i();
	Vector2i(const int &x, const int &y);
	Vector2i(const Vector2i &that);
	explicit Vector2i(const Vector2f &that);	// type convert from Vector2f to Vector2i construct by rounding
	~Vector2i();
	// Get - Set Method
	const int getX() const;
	const int getY() const;
	Vector2i& setX(const int &x);
	Vector2i& setY(const int &y);
	const float getAngle() const; // get angle in degree
	const float getLength() const;
	// Operations 
	Vector2i operator+(const Vector2i& that) const;
	Vector2i operator-(const Vector2i& that) const;
	Vector2i operator-() const;
	Vector2i operator*(const int& that) const;
	Vector2i operator/(const int& that) const;
	bool operator==(const Vector2i& that) const;
	bool operator!=(const Vector2i& that) const;
	Vector2i& operator= (const Vector2i& that);
	Vector2i& operator+=(const Vector2i& that);
	Vector2i& operator-=(const Vector2i& that);
	Vector2i& operator*=(const int& that);
	Vector2i& operator/=(const int& that);
	const int dot(const Vector2i& that) const;			// dot product
	Vector2i& scale(const int &scaleX, const int &scaleY);
	Vector2i& rotate(const int& angle);	// rotate in degree only multiple of 90
	const float angle(const Vector2i& that) const;	// angle from this rotate to that (in degree)
// Output
	void output(const std::string &name = "DEFAULT") const;
};

class Vector3f {
protected:
	float x;
	float y;
	float z;
public:
	// Constructor & Destructor
	Vector3f();
	Vector3f(const float &x, const float &y, const float &z);
	Vector3f(const Vector3f &that);
	explicit Vector3f(const Vector3i &that);
	~Vector3f();
	// Get - Set Method
	const float getX() const;
	const float getY() const;
	const float getZ() const;
	Vector3f& setX(const float &x);
	Vector3f& setY(const float &y);
	Vector3f& setZ(const float &z);
	const float getLength() const;
	// Operations 
	Vector3f operator+(const Vector3f& that) const;
	Vector3f operator-(const Vector3f& that) const;
	Vector3f operator-() const;
	Vector3f operator*(const float& that) const;
	Vector3f operator/(const float& that) const;
	bool operator==(const Vector3f& that) const;
	bool operator!=(const Vector3f& that) const;
	Vector3f& operator= (const Vector3f& that);
	Vector3f& operator+=(const Vector3f& that);
	Vector3f& operator-=(const Vector3f& that);
	Vector3f& operator*=(const float& that);
	Vector3f& operator/=(const float& that);
	const float dot(const Vector3f& that) const;			// dot product
	Vector3f& normalize();
	Vector3f& scale(const float &scaleX, const float &scaleY, const float &scaleZ);
	// Output
	void output(const std::string &name = "DEFAULT") const;
};
```

Vector2i 主要用在网格地图中作为向量参与计算，而Vector3i主要用于绘制中

对于每种vector会提供一个相应类型的Position类，提供了相应的基础运算方法以及一些判定（例如是否在某个区域内，用于写棋盘逻辑）

```c++
class Position2i {
protected:
	int x;
	int y;
public:
	// Constructor & Destructor
	Position2i();
	Position2i(const int &x, const int &y);
	Position2i(const Position2i& that);
	explicit Position2i(const Vector2i& that);
	explicit Position2i(const Position2f& that);
	~Position2i();
	// Get - Set Method
	const int getX() const;
	const int getY() const;
	Position2i& setX(const int& x);
	Position2i& setY(const int& y);
	// Operations
	Position2i operator+ (const Vector2i& that) const;
	Position2i operator- (const Vector2i& that) const;
	Vector2i operator- (const Position2i& that) const;
	bool operator== (const Position2i& that) const;
	bool operator!= (const Position2i& that) const;
	Position2i& operator= (const Position2i& that);
	Position2i& operator+=(const Vector2i& that);
	Position2i& operator-=(const Vector2i& that);
	bool inArea(const int& xmin, const int& ymin, const int& xlength, const int& ylength) const;
	Position2i& setInArea(const int& xmin, const int& ymin, const int& xlength, const int& ylength);
	bool inRange(const int& xmin, const int& ymin, const int& xmax, const int& ymax) const;
	Position2i& setInRange(const int& xmin, const int& ymin, const int& xmax, const int& ymax);
	// Output
	void output(const std::string &name = "DEFAULT") const;
};
```

### Model Layer

本来是封装了抽象的棋类，但是最终由于时间原因只实现了国际象棋

#### Chess

1. 对于每一种棋类，需要单独定义棋类的移动方式Move
2. 对于每一种棋类，需要单独定义棋盘从创建到现在的所有棋谱（用于回放），history可以是一个Move类型的vector
3. 每一种棋需要一种对应的ViewModel中的类，例如ViewClassicChess需要提供以ClassicChess类的实例为参数的构造函数，且这个ViewClassicChess应当是由ViewGroup继承而来
4. 对于每一种棋类，需要单独定义棋子类型（可有可无），棋盘状态
5. 对于每一种棋类，需从Chess继承，并实现 isValidMove 和 execMove 函数
6. 对于每一种棋类，可以使用static_cast实现Move

Chess是一个抽象类，不允许被实例化

```c++
#pragma once
#include <memory>

class ChessPosition {
public:
	virtual bool isValid() const = 0; // whether a position is valid (regardless of other objects)
};

class ChessMove{
public:
	virtual bool isValid() const = 0; // whether a move is valid (regardless of other objects)
};

class Chess {
protected:
public:
};
```

#### ClassicChess

这个类里实现了国际象棋的基本逻辑，首先定义了国际象棋的棋子类型、玩家类型、棋局状态、棋子状态、棋谱类型

```c++
enum ClassicChessObjectType {
	CLASSICCHESS_EMPTY,
	CLASSICCHESS_PAWN,
	CLASSICCHESS_ROOK,
	CLASSICCHESS_KNIGHT,
	CLASSICCHESS_BISHOP,
	CLASSICCHESS_QUEEN,
	CLASSICCHESS_KING
};

enum ClassicChessPlayerType {
	CLASSICCHESS_WHITE,
	CLASSICCHESS_BLACK
};

enum ClassicChessStatus {
	CLASSICCHESS_INTERRUPT_UPGRADEPAWN_WHITE,
	CLASSICCHESS_INTERRUPT_UPGRADEPAWN_BLACK,
	CLASSICCHESS_WHITE_TURN,
	CLASSICCHESS_BLACK_TURN,
	CLASSICCHESS_WHITE_CHECK,	// white being checked
	CLASSICCHESS_BLACK_CHECK,	// black being checked
	CLASSICCHESS_WHITE_WIN,
	CLASSICCHESS_BLACK_WIN
};

enum ClassicChessObjectStatus {
	CLASSICCHESS_DEAD,
	CLASSICCHESS_ALIVE
};

enum ClassicChessMoveType {
	CLASSICCHESS_PASSIVEMOVE,
	CLASSICCHESS_ACTIVEMOVE
};
```

随后通过ClassicChessPosition类继承了Position2i类，并提供了一个合法性的判定：判断坐标是否在(1,8)内

```c++
class ClassicChessPosition final : public Position2i, public ChessPosition{
public:
	ClassicChessPosition();
	ClassicChessPosition(const int& x, const int& y);
	ClassicChessPosition(const Position2i& that);
	ClassicChessPosition(const ClassicChessPosition& that);
	~ClassicChessPosition();
	bool isValid() const; // whether it's on board
	void output(const std::string &name = "DEFAULT") const;
};
```

随后通过ClassicChessObject类定义一个棋子，并将其封装为常量，即棋子一旦产生即不可改变

```c++
// const type ClassicChessObject : object cannot be modified
class ClassicChessObject final {	
private:
	const int index;
	const ClassicChessObjectStatus status;
	const ClassicChessObjectType type;
	const ClassicChessPlayerType player;
	const ClassicChessPosition position;
public:
	// Constructor & Destructor
	ClassicChessObject();
	ClassicChessObject(const int& index, const ClassicChessPlayerType& player, const ClassicChessPosition& position, const ClassicChessObjectType& type, const ClassicChessObjectStatus& status = CLASSICCHESS_ALIVE);
	ClassicChessObject(const ClassicChessObject& that);
	~ClassicChessObject();
	// Get Method
	const int getIndex() const;
	const ClassicChessObjectStatus getStatus() const;
	const ClassicChessObjectType getType() const;
	const ClassicChessPlayerType getPlayer() const;
	const ClassicChessPosition getPosition() const;
};
```

ClassicChessMove从ChessMove中继承，用来存储棋子的移动（棋谱中可以使用）

其中每个实例包含一个ClassicChessObject表示正在移动的棋子，ClassicChessPosition表示移动的目的地，ClassicChessMoveType表示移动的属性（这里本来用于表示一步移动产生多个棋子位置变化的场景方便棋谱播放，但是最终并没有时间实现棋谱播放就没有加进去，例如王车易位或者吃子时，一步移动会造成多个棋子的位置变化）。

这个类中还提供了一个判断该移动是否合法的函数，因为只有一个棋子的信息，只能用于判断该移动类型是否是合法的，而不能判断小兵吃子、车移动路径被挡等情况。所以这个判断函数只适用于筛选出能够行走的粗略范围，判断移动是否合法还需要结合棋盘上其他位置的信息。更加详细的判断逻辑已经写在注释中

```c++
// const type ClassicChessMove : move cannot be modified
class ClassicChessMove final : public ChessMove{
private:
	const ClassicChessObject object;
	const ClassicChessPosition dest;
	const ClassicChessMoveType type;
public:
	// Constructor & Destructor
	ClassicChessMove(const ClassicChessObject& object, const ClassicChessPosition& dest, const ClassicChessMoveType& type = CLASSICCHESS_ACTIVEMOVE);
	ClassicChessMove(const ClassicChessObject& object, const int& x, const int& y, const ClassicChessMoveType& type = CLASSICCHESS_ACTIVEMOVE);
	ClassicChessMove(const ClassicChessMove& that);
	~ClassicChessMove();
	// Get Method
	const ClassicChessObject getObject() const;
	const ClassicChessPosition getDest() const;
	const ClassicChessMoveType getType() const;
	/*
		Valid Move :
		1 > Both Position of Object and Destination should be valid and shouldn't be the same
		2 > Object should be ALIVE
		3 > PAWN is allowed to move forward 1 step or 2 steps(beginning), and horizontally 1 step (kill other) or 0 step
		4 > ROOK goes straight forward horizontally or vertically
		5 > KNIGHT goes straight forward for 2 steps and horizontally one step
		6 > BISHOP goes horizontally n steps and vertically n steps
		7 > QUEEN goes for BISHOP unions ROOK
		8 > KING goes one step for any direction , two steps for castling
	*/
	bool isValid() const;	
};
```

最终整个棋盘的类由Chess类继承，这里通过一个成员status记录当前棋盘的状态（白方移动、黑方移动、白方胜利、黑方胜利、白方升变、黑方升变），通过objest将32个棋子映射到棋盘上对应的坐标，棋盘由64个unique_ptr组成，每个指向对应位置的棋子，如果没有棋子则用ClassicChessObject的空构造构造一个属性为CLASSICCHESS_EMPTY类型的棋子。history存储了历史上的每一步移动，在棋谱复原的时候每有一个类型为CLASSICCHESS_ACTIVE（主动移动）

在棋盘类中主要使用的方法有： toIndex（从Position类转换为数组下标），execMove（执行一个行动），isValidMove（判断一个行动是否合法），tryMove（判断行动是否合法，如果是，则执行行动）

```c++
class ClassicChess final : public Chess{
private:
	ClassicChessStatus status;
	std::array<int, 32> objects;		// store the object locations in array board, -1 if dead
	std::array<std::unique_ptr<ClassicChessObject>, 64> board;	// store the board
	std::vector<std::unique_ptr<ClassicChessMove>> history; // chess history

	// functions
	ClassicChessPosition toPosition(const int& index) const; // index to position
	int toIndex(const ClassicChessPosition& position) const; // position to index
	int toIndex(const Position2i& position) const;
	bool validIndex(const Position2i& position, const Vector2i& delta) const;

	void loadMsg(std::string address);
	void saveMsg(std::string address);

	bool isBlocked(const Position2i &src, const Position2i& dest) const;
	bool isChecked(const ClassicChessPlayerType player) const;
	void execMove(const std::unique_ptr<ClassicChessMove> &move);	// execute a move
	bool isValidMove(const std::unique_ptr<ClassicChessMove>& move) const; // whether a move is valid (consider all objects)
	void tryMove(const std::unique_ptr<ClassicChessMove>& move);	// execute a move after judging whether it's valid
public:
	static const std::map<const std::string, const ClassicChessStatus> stringToStatus;
	static const std::map<const std::string, const ClassicChessMoveType> stringToMoveType;
	static const std::map<const std::string, const ClassicChessObjectStatus> stringToObjectStatus;
	static const std::map<const std::string, const ClassicChessPlayerType> stringToPlayerType;
	static const std::map<const std::string, const ClassicChessObjectType> stringToObjectType;

	// Constructors & Destructor
	ClassicChess(const std::string &address = "./Data/DefaultChess.txt");
	ClassicChess(const ClassicChess& that);
	~ClassicChess();
	// functions to public
	void reset(std::string address);
	void tryUpgradePawn(const ClassicChessObjectType& type);	// upgrade a pawn after judging whether it's valid
	void tryMove(const Position2i &src, const Position2i& dest);	
	// Get Method
	const ClassicChessStatus getStatus() const;
	const std::array<int, 32> getIndex() const;

	const ClassicChessObject getObject(const Position2i& position) const;
	const bool isEmpty(const Position2i& position) const;
	const bool isValidChoice(const Position2i& position) const;
	const ClassicChessObjectType getObjectType(const Position2i& position) const;
	const ClassicChessPlayerType getPlayerType(const Position2i& position) const;

};
```

这里的isValidMove中加入了更多判断行动是否合法的条件，例如车/主教/后在移动过程中是否有棋子阻挡，移动的目的地是否有己方棋子，是否为合法的吃子（例如小兵不能向前走来吃子）等。



#### Exhibit

Exhibit类是整个展览馆里所有物品的类，由于设计目标中提到，展品可以自由切换纹理、移动、旋转，因此只要创建一个Exhibit类用来存放展品信息，再通过函数接口将这些信息传出给View，便能实现物体的绘制

Exhibit里面存储了一些静态的成员变量：旋转速度、缩放速度、平移速度、平移和缩放的最大值

而每个展品本身的信息有：物品类型（用于选取obj，例如棋盘、门、窗、墙等）、纹理的编号、光源的编号、平移向量、旋转角度、缩放向量、是否有桌子（每个展品下面有桌子托起、而门窗墙等则没有）、是否正在旋转

而方法里除了Get-Set外，提供了一些易于使用的接口，以及与文件流交互的方法，方便文件读写

```c++
enum ExhibitType {
	EXHIBIT_EMPTY,
	EXHIBIT_CHESS_SET,
	EXHIBIT_CUBE,
	EXHIBIT_DOOR_1,
	EXHIBIT_DOOR_2,
	EXHIBIT_DOOR_3,
	EXHIBIT_DOOR_4,
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

```



#### Map

map类用于存储整个展览馆的地图，其成员包括必须在初始化时指定的宽度和高度，以及网格地图上每个点的展品信息

Map类通过一组Get-Set方法设置地图上每个位置的信息。用一组toIndex和toPosition完成数组下标和Position2i之间的转换

```c++
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
```



#### Model

Model是整个Model Layer中的核心类，整个展览馆，不论有多少个Map信息，最终只能由一个Model类的实体来控制所有的信息，并且与View进行交互

Model在设计目标上有五个状态：

```c++
enum ModelState {
	MODEL_PLAYMODE,
	MODEL_EDITMODE,
	MODEL_EDIT_EXHIBIT,			// Editing an exhibit
	MODEL_PLAY_CHESS,
	MODEL_PLAY_CHESS_HISTORY	// chess history
};
```

playmode是场景执行模式，editmode是场景编辑模式，edit_exhibit是场景编辑模式下编辑单个物体的模式，play_chess是场景执行模式下下棋的模式，play_chess_history是场景执行模式

由于暂时只设定博物馆只有一层，那么只有一个Map类型的成员变量，尽量避免Map的拷贝，因此采用共享指针进行存储，然后支持多个ClassicChess类型的实体，用一个vector存储chess，用Position2i类型的vector存储这些棋盘的位置，以便于修改信息，最后用Exhibit类型的数组保存所有的可添加展品信息

```c++
class Model final
{
private:
	ModelState state;
	std::shared_ptr<Map> map;
	std::vector<ClassicChess> chess;
	std::vector<Position2i> chessLocation;
	std::shared_ptr<Exhibit[]> exhibit;
};
```

本质上Model是一个状态机，随着View的输入改变当前的状态，再将状态中需要用到的变量传输给View

场景执行模式：

这个状态提供的方法有：enterChess(pos)进入pos位置的棋盘的下棋模式、enterEdit()进入编辑模式、canEnter(pos)判断是否能进入pos位置的区域（碰撞检测）

```c++
	// Use in MODEL_PLAYMODE
	bool enterChess(const Position2i& pos);	// Enter Chess Mode which chess is placed at pos, return true if valid
	void enterEdit();		// Enter edit mode
	bool canEnter(const Position2i& pos);		// whether player can enter pos or not
```

场景执行模式-下棋模式：

这个状态下需要用到的成员变量有：选择的格子一号、选择的格子二号（大部分的移动式棋类游戏也是通过选定一个目标棋子，然后选择目标来进行棋子的移动），以及当前选中的棋盘号

这个状态提供的方法有：quitChess()退出下棋模式回到场景执行模式，chooseChessBlock(pos)选定pos位置的方块，连续选定两次

```c++
	// Use in MODEL_PLAYMODE
	int chosenChess;
	Position2i chosenBlock1;
	Position2i chosenBlock2;
	bool chosenOne;		// if true, highlight chosenBlock1
	// Use in MODEL_PLAY_CHESS
	void quitChess();
	void chooseChessBlock(const Position2i& pos);	// change the chosen block (1-8)
	void execChoose();	// choose a block
```

场景编辑模式：

这个状态下需要用到的成员变量有选中的区块

这个状态提供的方法有：chooseBlock(pos)进行pos位置的区块的选中，editExhibit()进入展品编辑模式，deleteExhibit()是删除一个展品，enterPlay()是进入场景执行模式

```c++
	// Use in MODEL_EDITMODE
	Position2i chosenBlock;	// highlight block
	// Use in MODEL_EDITMODE
	void chooseBlock(const Position2i& pos);	// choose a highlight block, each time when changing the highlight block, this func should be called
	void editExhibit();	// enter edit exhibit mode (edit the exhibit on the highlight block)
	void deleteExhibit();	// delete an exhibit
	void enterPlay();	// enter play mode
```

场景编辑模式-物体编辑模式：

这个状态下需要用到的成员变量有选中的展品的拷贝，因为我们的展品是保存机制的，即修改完之后需要保存才会生效，不保存不生效。

这个状态下需要用到的方法有所有在Exhibit类中声明过的方法，用于修改这个展品的拷贝，以及resetMap(重置地图)

```c++
	Exhibit chosenExhibit;	// the chosen Exhibit
	// Use in MODEL_EDIT_EXHIBIT
	const Exhibit getEditingExhibit() const;

	void discardSaveExhibit();	 
	void saveExhibit();	// save change to Exhibit
	void changeType();	// create an exhibit of specified type or change the exhibit type
	void clearLight();	// change the light to unable
	void clearTexture();	// change the texture to empty	
	void setTextureNum(const unsigned int& textureNum);
	void setLightNum(const unsigned int& lightNum);
	void changeHasTable();	// change the state of hastable to the opposite	
	void changeIsRotating();	// change the state of isrotating to the opposite	
	void execTranslate(const float& time = 1, const int& directX = true, const int& directY = true, const int& directZ = true); // translate the model by time and direction(1 for positive, -1 for negative, 0 for keep current state)	
	void execRotate(const float& time = 1, const int& direction = true);// rotate the model by time and direction (1 for counterclockwise and -1 for clockwise)
	void execScale(const int& directX = true, const int& directY = true, const int& directZ = true);// scale the model by direction(1 for enlarge, -1 for shrink, 0 for keep current state)
	bool moveExhibit(const Position2i& src, const Position2i& dest);	// move the Exhibit from src to dest, true if success 
	void resetMap();
```

最后Model类里提供根据文件导入信息的接口loadMap(std::string)，格式可以参考/Data/DefaultMap.txt

```c++
void Model::loadMap(const std::string& address)
{
	std::ifstream fin;
	fin.open(address);
	if (fin.fail()) {
		std::cout << "Open Map File failed!" << std::endl;
		return;
	}
	std::string stateIn;
	fin >> stateIn;
	this->state = toState.at(stateIn);
	unsigned int width, height, itemNum, chessNum, item;
	fin >> width >> height >> itemNum >> chessNum;
	map.reset(new Map(width, height));
	exhibit.reset(new Exhibit[itemNum + 1]);
	exhibit[0] = Exhibit();
	for (unsigned int i = 1; i <= itemNum; i++)	fin >> exhibit[i];
	for (unsigned int i = 1; i <= height; i++) {
		for (unsigned int j = 1; j <= width; j++) {
			fin >> item;
			if (item > itemNum) 
			{
				std::cout << "ERROR : item out of range!" << std::endl;
				return;
			}
			map->setData(Position2i(j, i), exhibit[item]);
			if (exhibit[item].getType() == EXHIBIT_CLASSICCHESS) {
				chessLocation.push_back(Position2i(j, i));
				chess.push_back(ClassicChess());
			}
		}
	}
	fin.close();
}
```







