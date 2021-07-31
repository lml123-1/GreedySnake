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
    DOWNDIRECTION,
    LEFTDIRECTION,
    RIGHTDIRECTION
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
    void GameRun();

    IMAGE &GetImag(std::string strImage);

private:
    bool                m_bGameFlag;
    DIRECTION           m_Dtion;
    struct ExMessage    m_message;
    VEC<struct lattice> m_vecLattice;
    VEC<struct lattice> m_vecSnakeLa;
};

#define _MYSNAKEINFO GETMYSNAKEINFO(gSnake)
