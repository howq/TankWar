// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <ctime>
#include <opencv2\opencv.hpp> 
#include "Base.h"
#include "Tank.h"
#include "MyTank.h"
#include "Tool.h"
#include "Plane.h"
#include "Wall.h"
#include "Game.h"
#include <time.h>

#include <iostream>
using namespace std;


#define Tank_Image_Count 24

#define Fire_Image_Count 16

#define  SCOUNT 88

#define BACKGROUND_WIDHT 600 
#define BACKGROUND_HEIGHT 600 
#define TANK_WIDHT 60
#define TANK_HEIGHT 60 
#define FIRE_WIDHT 16
#define FIRE_HEIGHT 16
#define PLANE_WIDHT 100
#define PLANE_HEIGHT 100
#define WALL_WIDHT 30
#define WALL_HEIGHT 30 
#define TOOL_WIDHT 30
#define TOOL_HEIGHT 30
#define BOSS_HEIGHT 100
#define BOSS_WIDHT 80

#define TANKSPEEDX_LEVEL0 4
#define TANKSPEEDY_LEVEL0 4

#define TANKSPEEDX_LEVEL1 6
#define TANKSPEEDY_LEVEL1 6

#define FIRESPEEDX_LEVEL0 8
#define FIRESPEEDY_LEVEL0 8

#define FIRESPEEDX_LEVEL1 10
#define FIRESPEEDY_LEVEL1 10

#define PLANESPEEDY 10


// TODO:  在此处引用程序需要的其他头文件
