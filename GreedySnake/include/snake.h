#pragma once
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <string>
#include <vector>

#ifndef US
#define US unsigned short
#endif
#define VEC std::vector

#define INITCLASS(classname) \
                private:\
                    classname();\
                    ~classname();\
                public:\
                    static classname &GetInstance();

#define MYSNAKEINFO(classname) \
            classname &classname::GetInstance()\
            {\
                static classname snakeInfo;    \
                return snakeInfo;\
            }

#define GETMYSNAKEINFO(classname) classname::GetInstance()


enum DIRECTION
{
    UPDIREXTION = 0,
    LEFTDIRECTION,
    DOWNDIRECTION,
    RIGHTDIRECTION,
    NONEDIRECTION
};

struct lattice
{
    US x;
    US y;
};

class gSnake
{
public:
    INITCLASS(gSnake)

public:
    void SnakeInit();
    void SnakeRun();

private:
    void LeftButtonDown();
    void GameInit();
    void SnakeGameInit();
    void ProduceFood();  //产生食物
    void ShowHead(DIRECTION dt, US flag = 0);
    void SnakePosition();
    bool SnakeRunDirection(DIRECTION dt);
    void GameRun();
    bool SnakeRunOne(DIRECTION dt);
    bool SnakeIsDeath();

    IMAGE &GetImag(std::string strImage);

private:
    bool                m_bGameFlag; //游戏开始标志
    DIRECTION           m_Dtion; //蛇头方向
    US                  m_usFFlag; //食物标志
    struct lattice      m_snakeEnd;  //蛇尾部数据
    struct ExMessage    m_message; //鼠标键盘消息
    VEC<struct lattice> m_vecLattice; //所有格子数据
    VEC<struct lattice> m_vecSnakeLa; //蛇身坐标数据
};

#define _MYSNAKEINFO GETMYSNAKEINFO(gSnake)
