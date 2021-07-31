#include "snake.h"
#include <time.h>
#include <fstream>

#define WIDTH       (640)  //x
#define HEIGHT      (480)  //y
#define BIGWID      (50)
#define START_X     (BIGWID+10)
#define START_Y     (BIGWID+10)
#define HISTORY_X   (BIGWID+10)
#define HISTORY_Y   (START_Y+((HEIGHT - 2 * BIGWID - 40) / 3)+10)
#define GOVER_X     (BIGWID+10)
#define GOVER_Y     (HISTORY_Y+((HEIGHT - 2 * BIGWID - 40) / 3)+10)

#define RDOWN   _MYSNAKEINFO.GetImag("../Image/down.jpg")
#define RLEFT   _MYSNAKEINFO.GetImag("../Image/left.jpg")
#define RRIGHT  _MYSNAKEINFO.GetImag("../Image/right.jpg")
#define RUP     _MYSNAKEINFO.GetImag("../Image/up.jpg")
#define RSNAKE  _MYSNAKEINFO.GetImag("../Image/snake.png")
#define RFOOD  _MYSNAKEINFO.GetImag("../Image/food.png")

MYSNAKEINFO(gSnake)
gSnake::gSnake()
{
    m_bGameFlag = 1;
}

//setlinecolor(RGB(0, 0, 255));设置画线

gSnake::~gSnake()
{
    closegraph();
}

void gSnake::SnakeInit()
{
    initgraph(WIDTH, HEIGHT);

    setfillcolor(BLACK);
    bar(0, 0, WIDTH, HEIGHT);
    setfillcolor(RED);
    bar(BIGWID, BIGWID, WIDTH - BIGWID, HEIGHT - BIGWID);

    setfillcolor(BLUE);
    fillroundrect(START_X, START_Y, WIDTH - BIGWID - 10, START_Y + ((HEIGHT - 2 * BIGWID - 40) / 3), 5, 5); //画有边框矩形
    fillroundrect(HISTORY_X, HISTORY_Y, WIDTH - BIGWID - 10, HISTORY_Y + ((HEIGHT - 2 * BIGWID - 40) / 3), 5, 5);
    fillroundrect(GOVER_X, GOVER_Y, WIDTH - BIGWID - 10, GOVER_Y + ((HEIGHT - 2 * BIGWID - 40) / 3), 5, 5);

    setbkcolor(BLUE);
    settextcolor(GREEN);
    settextstyle(((HEIGHT - 2 * BIGWID - 40) / 3) - 40, 0, "宋体", 0, 0, 20, 0, 0, 0);
    outtextxy(START_X + 20, START_Y + 10, "START GAME");
    outtextxy(HISTORY_X + 20, HISTORY_Y + 10, "SHOW HISTORY");
    outtextxy(GOVER_X + 20, GOVER_Y + 10, "BREAK GAME");
}

void gSnake::SnakeRun()
{
    while (m_bGameFlag)
    {
        m_message = getmessage(EM_MOUSE | EM_KEY);
        switch (m_message.message)
        {
        case WM_LBUTTONDOWN:
            LeftButtonDown();
            break;
        default:
            break;
        }
    }

}

void gSnake::LeftButtonDown()
{
    if (m_message.x > START_X && m_message.y > START_Y && m_message.x < (WIDTH - BIGWID - 10) && m_message.y < START_Y + ((HEIGHT - 2 * BIGWID - 40) / 3))
    {
        GameInit();
        GameRun();
        closegraph(); //关闭
        SnakeInit();
    }
    else if (m_message.x > HISTORY_X && m_message.y > HISTORY_Y && m_message.x < (WIDTH - BIGWID - 10) && m_message.y < HISTORY_Y + ((HEIGHT - 2 * BIGWID - 40) / 3))
    {
        //rectangle(m_message.x - 10, m_message.y - 10, m_message.x + 10, m_message.y + 10); //测试
    }
    else if (m_message.x > GOVER_X && m_message.y > GOVER_Y && m_message.x < (WIDTH - BIGWID - 10) && m_message.y < GOVER_Y + ((HEIGHT - 2 * BIGWID - 40) / 3))
    {
        m_bGameFlag = 0;
    }
}

IMAGE &gSnake::GetImag(std::string strImage)
{
    static IMAGE m_image(20, 20);
    loadimage(&m_image, _T(strImage.c_str()));
    return m_image;
}

void gSnake::GameInit()
{
    closegraph();
    initgraph(WIDTH, WIDTH);
    cleardevice();
    setfillcolor(RGB(238, 95, 66));
    bar(0, 0, WIDTH, WIDTH);
    setfillcolor(0x00FFFF);
    bar(10, 10, WIDTH - 10, WIDTH - 10);
    setfillcolor(RGB(255, 0, 0));
    for (int i = 10; i < WIDTH - 10; i += 20)
    {
        for (int j = 10; j < WIDTH - 10; j += 20)
        {
            struct lattice sla = {(US)i, (US)j};
            fillrectangle(i, j, i + 20, j + 20); //画矩形
            m_vecLattice.push_back(sla);
        }
    }
}

void gSnake::SnakeGameInit()
{
    US usFlag;
    US usFlag2;
    DIRECTION ysDtion;
    srand((unsigned)time(NULL));
    usFlag = rand() % m_vecLattice.size();
    usFlag2 = rand() % m_vecLattice.size();
    ysDtion = (DIRECTION)(rand() % 4);
    m_Dtion = ysDtion;
    switch (ysDtion)
    {
    case UPDIREXTION:
        putimage(m_vecLattice[usFlag].x, m_vecLattice[usFlag].y, &RUP);
        break;
    case DOWNDIRECTION:
        putimage(m_vecLattice[usFlag].x, m_vecLattice[usFlag].y, &RDOWN);
        break;
    case LEFTDIRECTION:
        putimage(m_vecLattice[usFlag].x, m_vecLattice[usFlag].y, &RLEFT);
        break;
    case RIGHTDIRECTION:
        putimage(m_vecLattice[usFlag].x, m_vecLattice[usFlag].y, &RRIGHT);
        break;
    }
    if (usFlag == usFlag2)
    {
        usFlag2 = rand() % m_vecLattice.size();
    }
    putimage(m_vecLattice[usFlag2].x, m_vecLattice[usFlag2].y, &RFOOD);
}


void gSnake::GameRun()
{
    SnakeGameInit();
    _getch();
    /* while (1)
     {

     }*/
}

