#define _CRT_SECURE_NO_WARNINGS

#define WIDTH 1080
#define HEIGHT 640
#define PI 3.1415926
#define MAX_ANGLE 80
#define MINE_NUM 10
#define IMAGE_MAX 21
#include<iostream>
#include<chrono>
#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<string>
#include <mmsystem.h>
#include <conio.h>

using namespace std;
using namespace std::chrono;


IMAGE img[21];
int music_flag = 0;
int short_speed = 500000;
enum Index
{
	i_goldsmall = 1,
	i_goldmiddle = 3,
	i_goldbig = 5,
	i_stonesmall = 7,
	i_stonebig = 9,
	i_money = 11,
	i_diamond = 13,
	i_roleDown = 15,
	i_roleUp = 17
};
/*
钩子状态：摆动、伸长、缩短、停止
*/
enum ATTR
{
	//物品类型
	LITTLEGOLD,
	MIDGOLD,
	BIGGOLD,
	LITTLESTONE,
	BIGSTONE,
	MONEY,
	DIAMOND,
	//钩子方向
	LEFT,
	RIGHT,
	//钩子状态
	M_NORMAL,
	M_LONG,
	M_SHORT
};

enum MINE {//图片数组下标
	littlegold = 1,
	midgold = 3,
	biggold = 5,
	littlestone = 7,
	bigstone = 9,
	money = 11,
	diamond = 13,
	role_down = 15,
	role_up = 17,
	over = 18,
	bk = IMAGE_MAX - 1,
};

struct Role
{
	int x;
	int y;
	int width;
	int height;
	int coin;
};

struct Role role;

struct Hook
{
	double x;
	double y;
	double endx;
	double endy;
	double len; //钩子长度
	double angle; //钩子当前角度
	int dir;//钩子摆动方向
	double vx;//速度变化量
	double vy;
	int state; //当前状态
	int index;//抓住的物品下标
};

struct Hook hook;

struct Mine  //物品
{
	double x;
	double y;
	double sizex;
	double sizey;
	int type;
	bool flag;
	int gold;
};

Mine mine[MINE_NUM];

double Dis(int A, int B) {
	double x2 = (mine[A].x - mine[B].x) * (mine[A].x - mine[B].x);
	double y2 = (mine[A].y - mine[B].y) * (mine[A].y - mine[B].y);
	return sqrt(x2 + y2);
}

bool CheckForCover(int x) {
	for (int i = 0; i < x; ++i) {
		double dix = Dis(x, i);
		if (fabs(mine[x].x - mine[i].x) < mine[x].sizex + mine[i].sizex
			&& fabs(mine[x].y - mine[i].y) < mine[x].sizey + mine[i].sizey) {
			return false;
		}
	}
	return true;
}


void gameinit()
{
	srand(GetTickCount());//用系统时间做随机种子
	role.width = 140;
	role.height = 120;
	role.x = WIDTH / 2 - role.width / 2;
	role.y = 0;
	hook.len = 50;
	hook.x = role.x + 40;
	hook.y = role.y + 90;
	hook.endx = hook.x;
	hook.endy = hook.y + hook.len;
	hook.angle = 0;
	hook.dir = RIGHT;
	hook.state = M_NORMAL;
	hook.index = -1;

	for (int i = 0; i < MINE_NUM; i+=CheckForCover(i))
	{
		mine[i].x = rand() % (WIDTH - 220) + 110;
		mine[i].y = rand() % (HEIGHT - 220) + 110;
		mine[i].flag = true;
		mine[i].type = rand() % 7;
		switch (mine[i].type) {
		case LITTLEGOLD:
			mine[i].sizex = 32;
			mine[i].sizey = 30;
			mine[i].gold = 50;
			break;
		case MIDGOLD:
			mine[i].sizex = 59;
			mine[i].sizey = 55;
			mine[i].gold = 100;
			break;
		case BIGGOLD:
			mine[i].sizex = 155;
			mine[i].sizey = 144;
			mine[i].gold = 500;
			break;
		case LITTLESTONE:
			mine[i].sizex = 67;
			mine[i].sizey = 57;
			mine[i].gold = 11;
			break;
		case BIGSTONE:
			mine[i].sizex = 94;
			mine[i].sizey = 83;
			mine[i].gold = 20;
			break;
		case MONEY:
			mine[i].sizex = 73;
			mine[i].sizey = 83;
			mine[i].gold = rand() % 500 + 100;
			//if (!CheckForCover(i)) i--;
			
			break;
		case DIAMOND:
			mine[i].sizex = 33;
			mine[i].sizey = 27;
			mine[i].gold = 600;
			break;
		}
	}
}

void loadImg()
{
	for (int i = 0; i < 20; i++)
	{
		char filename[20] = "";
		sprintf(filename, "G:\\images\\%d.jpg", i);
		loadimage(img + i, filename);
	}
	loadimage(img + 20, "G:\\images\\bk.jpg", WIDTH, HEIGHT);
}


steady_clock::time_point StartTime, IntTime;

typedef int Mode_t;
duration<double> time_span;


int TimeCal(Mode_t Mode) {
	IntTime = steady_clock::now();
	switch (Mode){
		case 1:
			time_span = duration_cast<duration<double>>(IntTime - StartTime);
			return time_span.count();
			break;
		
		case 2:
			break;
		default:
			break;
	}

}

void gamedraw()
{

	//绘制背景
	setfillcolor(YELLOW);
	solidrectangle(0, 0, WIDTH, role.height);
	putimage(0, role.height, img + 20);
	//绘制人物
	putimage(role.x, role.y, img + i_roleDown - 1, SRCAND);
	putimage(role.x, role.y, img + i_roleDown, SRCPAINT);

	//输出钱
	setbkmode(TRANSPARENT);//设置背景透明
	settextstyle(40, 0, "黑体");
	settextcolor(BLACK);
	char coin[20] = "";
	char timer[20] = "";
	sprintf(coin, "金钱：%d", role.coin);
	sprintf(timer, "时间：%d", TimeCal(1));
	outtextxy(20, 10, coin);
	outtextxy(20, 60, timer);

	//绘制钩子
	setlinecolor(RED);
	setlinestyle(PS_SOLID, 5);
	line(hook.x, hook.y, hook.endx, hook.endy);
	setfillcolor(YELLOW);
	solidcircle(hook.endx, hook.endy, 5);

	//画金子
	for (int i = 0; i < MINE_NUM; i++) {
		if (mine[i].flag == true) {
			switch (mine[i].type) {
			case LITTLEGOLD:
				putimage(mine[i].x, mine[i].y, &img[littlegold - 1], SRCAND);
				putimage(mine[i].x, mine[i].y, &img[littlegold], SRCPAINT);
				break;
			case MIDGOLD:
				putimage(mine[i].x, mine[i].y, &img[midgold - 1], SRCAND);
				putimage(mine[i].x, mine[i].y, &img[midgold], SRCPAINT);
				break;
			case BIGGOLD:
				putimage(mine[i].x, mine[i].y, &img[biggold - 1], SRCAND);
				putimage(mine[i].x, mine[i].y, &img[biggold], SRCPAINT);
				break;
			case LITTLESTONE:
				putimage(mine[i].x, mine[i].y, &img[littlestone - 1], SRCAND);
				putimage(mine[i].x, mine[i].y, &img[littlestone], SRCPAINT);
				break;
			case BIGSTONE:
				putimage(mine[i].x, mine[i].y, &img[bigstone - 1], SRCAND);
				putimage(mine[i].x, mine[i].y, &img[bigstone], SRCPAINT);
				break;
			case MONEY:
				putimage(mine[i].x, mine[i].y, &img[money - 1], SRCAND);
				putimage(mine[i].x, mine[i].y, &img[money], SRCPAINT);
				break;
			case DIAMOND:
				putimage(mine[i].x, mine[i].y, &img[diamond - 1], SRCAND);
				putimage(mine[i].x, mine[i].y, &img[diamond], SRCPAINT);
				break;
			}
		}
	}
}
//钩子摆动
void hookRock()
{
	if (hook.state == M_NORMAL)
	{
		if (hook.dir == RIGHT)
			hook.angle += 0.1;
		else if (hook.dir == LEFT)
			hook.angle -= 0.1;
		if (hook.angle > MAX_ANGLE)
			hook.dir = LEFT;
		else if (hook.angle < -MAX_ANGLE)
			hook.dir = RIGHT;
		hook.endx = hook.x + sin(PI / 180 * hook.angle) * hook.len;
		hook.endy = hook.y + cos(PI / 180 * hook.angle) * hook.len;
	}
}

double distance(Hook h)
{
	int dis = sqrt((double)(hook.endx - hook.x) * (hook.endx - hook.x) + (hook.endy - hook.y) * (hook.endy - hook.y));
	return dis <= h.len;
}

void HookMove() {//钩子位置变化
	static int cnt = 0;
	if (hook.state == M_LONG) {//出勾时，钩子位置一直变化
		hook.endx += hook.vx;
		hook.endy += hook.vy;
		DWORD o;
		cnt++;
		if (cnt & 1)
			Sleep(1);
		else cnt = 0;
	}
	else if (hook.state == M_SHORT) {//收勾时，钩子位置一直变化
		hook.endx -= hook.vx;
		hook.endy -= hook.vy;
		for (int i = 0; i < short_speed; i++);
		if (distance(hook)) {//钩子复原时，绳子回到正常状态
			hook.state = M_NORMAL;
			short_speed = 500000;
		}
	}
}

void keycontrol(double speed)
{
	if (GetAsyncKeyState(VK_DOWN) && hook.state == M_NORMAL)
	{
		hook.state = M_LONG;
		hook.vx = sin(PI / 180 * hook.angle) * speed;
		hook.vy = cos(PI / 180 * hook.angle) * speed;
	}
	//返回边界条件
	if (hook.endx<0 || hook.endx>WIDTH || hook.endy > HEIGHT)
		hook.state = M_SHORT;
}

void JudgeGrap() {// 判断是否抓住物品
	for (int i = 0; i < MINE_NUM; i++) {
		if (mine[i].flag == true &&//物品存在，且钩子在金块内部，则视为抓住金块，记录金块下标。
			hook.endx > mine[i].x && hook.endx <(mine[i].x + mine[i].sizex) &&
			hook.endy> mine[i].y && hook.endy < (mine[i].y + mine[i].sizey))
		{
			hook.index = i;
			break;
		}
	}
	if (hook.index != -1) {//如果抓住金块，绳子缩短
		hook.state = M_SHORT;
		mine[hook.index].x = hook.endx - mine[hook.index].sizex / 2;
		mine[hook.index].y = hook.endy - mine[hook.index].sizey / 2;
		if (distance(hook)) {//如果绳子收缩为原长
			mine[hook.index].flag = false;//物品不存在
			role.coin += mine[hook.index].gold;//人物金币增加
			hook.state = M_NORMAL;//绳子状态为原长
			hook.index = -1;//钩子变为没抓金子
			short_speed = 500000;
		}
		else
		{
			switch (mine[hook.index].type) {
			case LITTLEGOLD:
				short_speed = 100000;
				break;
			case MIDGOLD:
				short_speed = 1000000;
				break;
			case BIGGOLD:
				short_speed = 3000000;
			case LITTLESTONE:
				short_speed = 1000000;
				break;
			case BIGSTONE:
				short_speed = 3000000;
				break;
			case MONEY:
				short_speed = 100000;
				break;
			case DIAMOND:
				short_speed = 100000;
				break;
			}
		}
	}

}

int main()
{

	initgraph(WIDTH, HEIGHT);   // 创建绘图窗口，大小为 640x480 像素
	loadImg();
	gameinit();


	StartTime = steady_clock::now();
	while (1)
	{
		hookRock();
		HookMove();
		BeginBatchDraw();
		gamedraw();
		EndBatchDraw();
		keycontrol(2);
		JudgeGrap();
	}
	_getch();
	closegraph();
}
