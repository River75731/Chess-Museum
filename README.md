# Chess Museum

Project for ZJU-CG-2020

Contributors : 

3180101995 江昊翰

3180102060 王呈

3180103656 徐磊

3180105493 傅淄洋

3180106047 杨云皓

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

命名规则：

UpperCamelCase : 类名、命名空间名

lowerCamelCase : 变量名、函数名、方法名

全大写，下划线分隔：枚举类型变量名

尽量使用都看得懂的缩写：例如init

尽量不要 `using namespace std`

XX的数目 ： xxxCount

XX的编号 ： xxxIdx (index)

二维变量（坐标等）：xx2d, xx2i (double / int)

三维变量（坐标等）：xx3d, xx2d



## Version Control

12.11 : add `./obj_test` for .obj file test demo



## Program Structure

主要为MVC架构，分为下面五个层：

Layers : 

1. Common Layer : 包含所有层或大部分层都用得到的基础类，例如位置，向量等
2. Model Layer ：包含所有模型的关于**应用逻辑计算**的的信息，例如棋盘，可以开的门的状态，程序状态等，接收到View Layer的信息后，需要进行对应的信息更新等。
3. ViewModel Layer ：包含所有模型的用于绘制的**空间信息** ，例如棋盘中棋子的位置，包含绘制方法（调用View中的函数）等
4. View Layer ：封装OpenGL库的库函数，并将所有东西显示，处理用户输入的信息
5. App Layer ： 处理整个程序的初始化及绑定

实际运行中，首先完成函数绑定，随后View层接收到用户信息后，通知Model进行逻辑运算，Model进行逻辑运算结束后告诉ViewModel更新信息，ViewModel再调用View中的函数进行绘制

**除了View层以外的其他层不能调用OpenGL的库函数**，所有传递的参数均为自定义的类或枚举类（可以与OpenGL里的类定义对应）



### View Layer

只包含方法，不存放任何数据，数据由ViewModel传递而来



封装所有需要应用到绘制上的方法，包括OpenGL库里的方法、视频音频等



### ViewModel Layer

只包含绘图数据，调用View中的绘图方法进行绘图

主体结构为ViewScene->ViewGroup->ViewObject

一旦调用draw函数请先glMatrixMode, glPushMatrix

#### ViewObject

**TODO:**  添加材质板块

1. 包含一个**静态物体**的信息，即不包含任何空间位置，只包含一个物体模型，包括物体的模型组成和材质、颜色等

2. 所有静态物体均从ViewObject2d/ViewObject3d中继承并构造init和draw方法，这里**一定**是可以使用显示列表构造的（因为是静态的）。注释写清楚物体的起始位置和绘制的xyz轴及物体大小。

3. Object一旦产生便不能修改，每个Object只能有一个实体，建议使用const成员 & static函数

#### ViewGroup

1. 包含一个或一组物体的动态信息，包括空间位置（一个物体组合内的相对位置），摆放朝向，实际大小。

2. init中需要给一个初始位置，可以不允许空构造，绘制方法请以PushMatrix, LoadIdentity开始

3. 不同的group可以共用相同的object，类似 `glutSolidCube` 
4. 所有的实际在场景里的东西需要从ViewGroup2d或者ViewGroup3d继承

#### ViewScene

1. 包含一整个场景信息，场景是一整个独立的单元，
2. 场景必须由group组成，场景与场景之间不能共用group
3. 场景的绘制必须以MatrixMode，LoadIdentity开始，场景直接与Viewport相关联
4. 一个Window可以包含多个Subwindow, ViewScene直接和Subwindow相关（一个Subwindow只能展示一个Scene，多个Subwindow可以展示同一个Scene），例如小地图
5. 所有场景必须从ViewScene2d或者ViewScene3d继承
6. 任何一个group只能属于一个单独的场景（使用unique_ptr维护）



### Model Layer



### Common Layer

#### Chess

1. 对于每一种棋类，需要单独定义棋类的移动方式Move
2. 对于每一种棋类，需要单独定义棋盘从创建到现在的所有棋谱（用于回放），history可以是一个Move类型的vector
3. 每一种棋需要一种对应的ViewModel中的类，例如ViewClassicChess需要提供以ClassicChess类的实例为参数的构造函数，且这个ViewClassicChess应当是由ViewGroup继承而来
4. 对于每一种棋类，需要单独定义棋子类型（可有可无），棋盘状态
5. 对于每一种棋类，需从Chess继承，并实现 isValidMove 和 execMove 函数
6. 对于每一种棋类，可以使用static_cast实现Move

