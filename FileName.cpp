#include<iostream>
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

#define SNAKE_NUM 500  // 蛇的最大节数
// 蛇的结构
void Zerodays();
int kuku;// 步长记录 没到500后归零
int numnum[500];
int direction; //方向性判定参数
int number = 1; // 记录总次数
struct Snake {
	int size;// 蛇的节数
	int dir; //蛇的方向
	int dir_com; // 蛇的方向记录器
	int dir_com_1;
	int dir_c; //上一次转向记录器
	int speed; // 蛇的速度
	POINT coor[SNAKE_NUM]; //坐标
}snake;

struct ding {
	int a;
	int b;
	int c;
	int d;

}didi;
struct Food {
	int x;
	int y;
	int r; // 半径
	bool flag; // 食物是否被吃掉
	DWORD color; // 食物颜色
}food;
enum DIR // 方向
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};	

void food_coming() {
	// 食物生成   &  食物生成逻辑
	
	food.x = (rand() % 64)*10;
	food.y = (rand() % 48)*10;
	
}
void GameInit();
void Exit() {
	std::cout << "     小蛇第" << number << "死亡，当前蛇长度为：" << snake.size << std::endl;
	number++;
	GameInit(); // 重新初始化
}
void die() {
	// 死亡判断函数
	for (int i = 1; i < snake.size; i++) {
		if (snake.coor[0].x == snake.coor[i].x && snake.coor[0].y == snake.coor[i].y) {
			std::cout << "Game Over!" << std::endl;
			std::cout << "撞击坐标，头：" << snake.coor[1].x<<"," << snake.coor[1].y << ", 撞击坐标，撞击部位：" << snake.coor[i].x << "," << snake.coor[i].y <<"当前蛇的行进方向："<<snake.dir << std::endl;
			
			Exit();
		}
	}
}
// 数据的初始化
void GameInit() {
	// init 初始化graph图形窗口
	initgraph(640, 480,SHOWCONSOLE);
	// 初始化蛇	
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;
	snake.dir_com = RIGHT;
	for (int i = 0; i <snake.size; i++)
	{
		// 循环确定蛇身坐标
		snake.coor[i].x = 40 - 10*i;
		snake.coor[i].y = 10;
	} 
	food_coming();
	food.color = RGB(192, 10, 22);
	// 食物颜色
	food.r = rand() % 10 + 5;
	food.flag = true;
}


void GameDraw() {
	//双缓冲绘图
	BeginBatchDraw();
	setbkcolor(RGB(255, 255, 255));
	// 初始化窗口颜色
	cleardevice();
	// 清空绘图设备
	setfillcolor(RGB(196, 175, 118));
	solidcircle(snake.coor[0].x, snake.coor[0].y, 5);
	setfillcolor(RGB(53, 63, 72));
	for (int i = 1; i < snake.size; i++) {
		// 循环绘制蛇
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	
	if (food.flag) {
		// 检测食物是否存在
		setfillcolor(RGB(192, 10, 22));
		solidcircle(food.x,food.y,5);
		//std::cout << "存在" << std::endl;
	}
	else {
		// 重新生成食物坐标
		/*food.x = rand() % 640;
		food.y = rand() % 480;*/
		food_coming();

		food.flag = true;
	}
	EndBatchDraw();
	// 双缓冲结束

}

int ku() {
	// 检测小蛇是否一直向一个方向移动，如果是，返回0
	int k = 0;
	for (int i = 0; i < 500; i++)
	{
		if (numnum[i] == snake.dir) {
			k++;
		}
		if (k > 480) {
			return 0;
		}
	}
	return 1;
}


// 蛇的移动
void snakeMove() {
	Zerodays();
	for (int i = snake.size; i>0; i--) {
		snake.coor[i] = snake.coor[i - 1];
	}

	int a = ku();
	if (a == 0)
	{
		snake.dir = UP;
	}
		switch (snake.dir)
		{
		case UP:
			snake.coor[0].y-= snake.speed;

		
			if(snake.coor[0].y+5 <= 0) {
				// 超出上边界
				snake.coor[0].y = 480-5;
			}
			break;
		case DOWN:
			snake.coor[0].y+= snake.speed;
			
			if (snake.coor[0].y - 10 >= 480 - 5) {
				// 超出下界
				snake.coor[0].y = 0 + 5;
			}
			break;
		case LEFT:
			if (snake.coor[0].x + 10 <= 0) {
				snake.coor[0].x = 640;
			}
			snake.coor[0].x -= snake.speed;
		
			
			break;
		case RIGHT:
			if (snake.coor[0].x + 10 >= 640) {
				snake.coor[0].x = 0;
			}
		

			snake.coor[0].x+= snake.speed;
			
			break;
		}

			if (snake.dir_com != snake.dir) {
				snake.dir_c = snake.dir_com;

			}

			numnum[kuku] = snake.dir_com;
			snake.dir_com = snake.dir;
			kuku++;
			if (kuku == 500) {
				kuku = 0;
			}
}

void EatFood() {
	// 检测食物碰撞
	if (abs(snake.coor[0].x-food.x)<=5 && abs(snake.coor[0].y - food.y)<=5) {
		food.flag = false;	
		snake.size++;
	}
}


void keyControl() {
	// 测试使用(在小蛇自主移动时不会听从转向)
	// 通过按键改变键盘方向
	// 判断有没有按键操作
	if (_kbhit()) {

		switch (_getch())
		{
			// 方向控制区
		case 'w':
		case 'W':
		case 72:
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			
			break;
		case 'S':
		case 's':
		case 80:
			if (snake.dir != UP) {
				snake.dir = DOWN;
			}
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.dir != RIGHT) {
				snake.dir = LEFT;
			}
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dir != LEFT) {
				snake.dir = RIGHT;
			}
			break;
		case 'p':
			Sleep(100000000);
			break;
		}
	}
}
void key1() {
	int a;
	//a = direction;
	a = rand() % 4;
	switch (a)
	{
	case 1:
		snake.dir = LEFT;
		break;
	case 2:
		snake.dir = UP;
		break;
	case 3:
		snake.dir = DOWN;
		break;
	case 0:
		snake.dir = RIGHT;
		break;
	}
	direction++;
	if (direction == 4) {
		direction = 0;
	}
	
 }
void Zerodays() {
	// 方向第一优先级，不碰撞蛇身
	int a;

	for (int i = 1; i < snake.size; i++)
	{
		if (snake.coor[0].x - 10 == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y || snake.coor[0].x + 620 == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y) {
			didi.a = 1;
		}
	}
	for (int m = 1; m < snake.size; m++) {

		if (snake.coor[0].x + 10 == snake.coor[m].x && snake.coor[m].y == snake.coor[0].y || snake.coor[0].x - 620 == snake.coor[m].x && snake.coor[m].y == snake.coor[0].y) {
			didi.b = 1;
		}
	}
	for (int q = 1; q < snake.size; q++) {

		if (snake.coor[0].x == snake.coor[q].x && snake.coor[q].y == snake.coor[0].y - 10 || snake.coor[0].x == snake.coor[q].x && snake.coor[q].y == snake.coor[0].y + 470) {
			didi.c = 1;
		}
	}
	for (int w = 1; w < snake.size; w++) {

		if (snake.coor[0].x == snake.coor[w].x && snake.coor[w].y == snake.coor[0].y + 10 || snake.coor[0].x == snake.coor[w].x && snake.coor[w].y == snake.coor[0].y - 470) {
			didi.d = 1;
		}
	}
	if (didi.a == 1 && didi.b == 1 && didi.c == 1 && didi.d == 1) {
		std::cout << "Game Over!";
		//Sleep(1000000);
		Exit();
	}

	switch (snake.dir)
	{
	case LEFT:
		for (int i = 1; i < snake.size; i++)
		{
			if (snake.coor[0].x - 10 == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y || snake.coor[0].x + 620 == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y) {
				key1();
				/*std::cout << "didi的值：" << didi.a << didi.b << didi.c << didi.d << std::endl;*/

				Zerodays();
				
			}
		}
		break;
	case RIGHT:
		for (int i = 1; i < snake.size; i++)
		{
			if (snake.coor[0].x + 10 == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y || snake.coor[0].x - 620 == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y) {
				key1();
				/*std::cout << "didi的值：" << didi.a << didi.b << didi.c << didi.d << std::endl;*/
				Zerodays();
				
			}
		}

		break;
	case UP:
		for (int i = 1; i < snake.size; i++)
		{
			if (snake.coor[0].x == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y - 10 || snake.coor[0].x == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y + 470) {
				key1();
				/*std::cout << "didi的值：" << didi.a << didi.b << didi.c << didi.d << std::endl;*/
				Zerodays();

			}
		}
		break;
	case DOWN:
		for (int i = 1; i < snake.size; i++)
		{
			if (snake.coor[0].x == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y + 10 || snake.coor[0].x == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y - 470) {
				key1();
				/*std::cout << "didi的值：" << didi.a << didi.b << didi.c << didi.d << std::endl;*/
				Zerodays();
				
			}
		}
		break;
	}
	didi.a = 0;
	didi.b = 0;
	didi.c = 0;
	didi.d = 0;
}
void First() {
	// 方向第二优先级，不碰撞蛇身
	switch (snake.dir)
	{
	case LEFT:
		for (int i = 1; i < snake.size; i++) {
			if (snake.coor[0].x - 10 == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y) {
				// 碰撞蛇身
				if (snake.dir_c == UP) {
					snake.dir = UP;
				}
				else if (snake.dir_c == DOWN) {
					snake.dir = DOWN;
				}
				
			}
		}
		break;
	case RIGHT:
		for (int i = 1; i < snake.size; i++)
		{
			if (snake.coor[0].x +10 == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y){
				// 碰撞蛇身
				if (snake.dir_c == DOWN) {
					snake.dir = DOWN;
				}
				else if (snake.dir_c == UP) {
					snake.dir = UP;
				}
				
			}

		}
		break;
	case UP:
		for (int i = 1; i < snake.size; i++)
		{
			if (snake.coor[0].y - 10 == snake.coor[i].y && snake.coor[i].x == snake.coor[0].x) {
				// 碰撞蛇身
				if (snake.dir_c == RIGHT) {
					snake.dir = RIGHT;
				}
				else if (snake.dir_c == LEFT) {
					snake.dir = LEFT;
				}
			}
		}
		break;
	case DOWN:
		for (int i = 0; i < snake.size; i++)
		{
			if (snake.coor[0].y+10 == snake.coor[i].y && snake.coor[i].x == snake.coor[0].x) {
				// 碰撞蛇身
				if (snake.dir_c == LEFT) {
					snake.dir = LEFT;
				}
				else if (snake.dir_c == RIGHT) {
					snake.dir = RIGHT;
				}
			}
		}

		break;
	}
	Zerodays();
}
// 小蛇移动逻辑
void Compute() {
		
	if (snake.coor[0].x - food.x > 0) {
		if (snake.dir != RIGHT) {
			snake.dir = LEFT;
			First();
		}
	}
	else if (food.x - snake.coor[0].x > 0) {
		if (snake.dir != LEFT) {
			snake.dir = RIGHT;
			First();
		}
	}
	// 优先调整x轴
	if (food.x == snake.coor[0].x) {
		if (food.y < snake.coor[0].y) {
			if (snake.dir != DOWN) {
				snake.dir = UP;
				First();
			}
		}
		else if (food.y > snake.coor[0].y) {
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
				First();
			}
		}
	}
}
int main() {
	
	
	GameInit();
	GameDraw();

	srand(time(NULL));
	while (1) {
		GameDraw();
		snakeMove();
		keyControl();
		EatFood();
		die();
		Compute();
		Sleep(1);
	}
	return 0;
}
