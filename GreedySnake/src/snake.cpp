#include "snake.h"
#include <windows.h>
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
#define RFOOD   _MYSNAKEINFO.GetImag("../Image/food.png")

#define KEYDOWN     0x28
#define KEYLEFT     0x25
#define KEYRIGHT    0x27
#define KEYUP       0x26

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

void gSnake::LeftButtonDown() //左键点击事件
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
        rectangle(m_message.x - 10, m_message.y - 10, m_message.x + 10, m_message.y + 10); //测试
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

    DIRECTION ysDtion;
    srand((unsigned)time(NULL));
    usFlag = rand() % m_vecLattice.size();

    ysDtion = (DIRECTION)(rand() % 4);
    m_Dtion = ysDtion;

    m_vecSnakeLa.push_back(m_vecLattice[usFlag]); //蛇头

    ShowHead(ysDtion, 0);

    ProduceFood();
}

void gSnake::ProduceFood()
{
    bool bFlag =  true;

    srand((unsigned)time(NULL));
    m_usFFlag = rand() % m_vecLattice.size();
    while (bFlag)
    {
        for (auto &it : m_vecSnakeLa)
        {
            if (it.x == m_vecLattice[m_usFFlag].x && it.y == m_vecLattice[m_usFFlag].y)
            {
                m_usFFlag = rand() % m_vecLattice.size();
                bFlag = true;
                break;
            }
            bFlag = false;
        }
    }
    putimage(m_vecLattice[m_usFFlag].x, m_vecLattice[m_usFFlag].y, &RFOOD);
}

void gSnake::ShowHead(DIRECTION dt, US flag) //显示头部
{
    US i = 0;
    switch (dt)
    {
    case UPDIREXTION:
        putimage(m_vecSnakeLa[flag].x, m_vecSnakeLa[flag].y, &RUP);
        break;
    case DOWNDIRECTION:
        putimage(m_vecSnakeLa[flag].x, m_vecSnakeLa[flag].y, &RDOWN);
        break;
    case LEFTDIRECTION:
        putimage(m_vecSnakeLa[flag].x, m_vecSnakeLa[flag].y, &RLEFT);
        break;
    case RIGHTDIRECTION:
        putimage(m_vecSnakeLa[flag].x, m_vecSnakeLa[flag].y, &RRIGHT);
        break;
    }
    for (auto &it : m_vecSnakeLa)
    {
        if (i++)
        {
            putimage(it.x, it.y, &RSNAKE);
        }
    }
}

void gSnake::SnakePosition()
{
    struct lattice it;
    for (int i = m_vecSnakeLa.size() - 1; i > 0; i--)
    {
        it = m_vecSnakeLa[i - 1];
        m_vecSnakeLa[i] = it;
    }
}

bool gSnake::SnakeIsDeath()
{
    US i = 0;
    for (auto &it : m_vecSnakeLa)
    {
        if (i++)
        {
            if (it.x == m_vecSnakeLa[0].x && it.y == m_vecSnakeLa[0].y)
            {
                return false;
            }
        }
    }
    return true;
}

bool gSnake::SnakeRunDirection(DIRECTION dt)
{
    bool bFlag = true;
    m_snakeEnd = m_vecSnakeLa.back();

    switch (dt)
    {
    case UPDIREXTION:
        if (m_vecSnakeLa[0].y == 10)
        {
            bFlag = false;
        }
        else
        {
            SnakePosition();
            m_vecSnakeLa[0].y -= 20;
        }
        break;
    case DOWNDIRECTION:
        if (m_vecSnakeLa[0].y == WIDTH - 30)
        {
            bFlag = false;
        }
        else
        {
            SnakePosition();
            m_vecSnakeLa[0].y += 20;
        }
        break;
    case LEFTDIRECTION:
        if (m_vecSnakeLa[0].x == 10)
        {
            bFlag = false;
        }
        else
        {
            SnakePosition();
            m_vecSnakeLa[0].x -= 20;
        }
        break;
    case RIGHTDIRECTION:
        if (m_vecSnakeLa[0].x == WIDTH - 30)
        {
            bFlag = false;
        }
        else
        {
            SnakePosition();
            m_vecSnakeLa[0].x += 20;
        }
        break;
    }

    if (m_vecSnakeLa.size() > 1)
    {
        if (m_Dtion == dt - 2 || m_Dtion == dt + 2)
        {
            bFlag = false;
        }
    }

    if (!SnakeIsDeath())
    {
        bFlag = false;
    }

    ShowHead(dt);
    return bFlag;
}

void gSnake::GameRun()
{
    bool bFlag = true;
    DIRECTION dt = NONEDIRECTION;
    US usTime = 1;
    SnakeGameInit();
    _getch();
    while (bFlag)
    {
        peekmessage(&m_message);
        if (m_message.message == WM_KEYDOWN)
        {
            switch (m_message.vkcode)
            {
            case KEYUP:
                dt = (UPDIREXTION);
                break;
            case KEYDOWN:
                dt = (DOWNDIRECTION);
                break;
            case KEYLEFT:
                dt = (LEFTDIRECTION);
                break;
            case KEYRIGHT:
                dt = (RIGHTDIRECTION);
                break;
            default:
                break;
            }
        }

        Sleep(1);
        usTime++;
        if (usTime > 100)
        {
            if (dt != NONEDIRECTION)
            {
                bFlag = SnakeRunOne(dt);
            }
            usTime = 1;
        }
    }

    m_vecLattice.swap(std::vector<struct lattice>());
    m_vecSnakeLa.swap(std::vector<struct lattice>());
}

bool gSnake::SnakeRunOne(DIRECTION dt)
{
    bool bFlag;

    if (!SnakeRunDirection(dt))
    {
        return false;
    }

    if (m_vecSnakeLa[0].x == m_vecLattice[m_usFFlag].x && m_vecSnakeLa[0].y == m_vecLattice[m_usFFlag].y)
    {
        ProduceFood();
        m_vecSnakeLa.push_back(m_snakeEnd);
        putimage(m_snakeEnd.x, m_snakeEnd.y, &RSNAKE);
    }
    else
    {
        setfillcolor(RGB(255, 0, 0));
        fillrectangle(m_snakeEnd.x, m_snakeEnd.y, m_snakeEnd.x + 20, m_snakeEnd.y + 20);
    }
    m_Dtion = dt;
    return true;
}
