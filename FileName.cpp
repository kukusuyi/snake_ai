#include<iostream>
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

#define SNAKE_NUM 500  // �ߵ�������
// �ߵĽṹ
void Zerodays();
int kuku;// ������¼ û��500�����
int numnum[500];
int direction; //�������ж�����
int number = 1; // ��¼�ܴ���
struct Snake {
	int size;// �ߵĽ���
	int dir; //�ߵķ���
	int dir_com; // �ߵķ����¼��
	int dir_com_1;
	int dir_c; //��һ��ת���¼��
	int speed; // �ߵ��ٶ�
	POINT coor[SNAKE_NUM]; //����
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
	int r; // �뾶
	bool flag; // ʳ���Ƿ񱻳Ե�
	DWORD color; // ʳ����ɫ
}food;
enum DIR // ����
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};	

void food_coming() {
	// ʳ������   &  ʳ�������߼�
	
	food.x = (rand() % 64)*10;
	food.y = (rand() % 48)*10;
	
}
void GameInit();
void Exit() {
	std::cout << "     С�ߵ�" << number << "��������ǰ�߳���Ϊ��" << snake.size << std::endl;
	number++;
	GameInit(); // ���³�ʼ��
}
void die() {
	// �����жϺ���
	for (int i = 1; i < snake.size; i++) {
		if (snake.coor[0].x == snake.coor[i].x && snake.coor[0].y == snake.coor[i].y) {
			std::cout << "Game Over!" << std::endl;
			std::cout << "ײ�����꣬ͷ��" << snake.coor[1].x<<"," << snake.coor[1].y << ", ײ�����꣬ײ����λ��" << snake.coor[i].x << "," << snake.coor[i].y <<"��ǰ�ߵ��н�����"<<snake.dir << std::endl;
			
			Exit();
		}
	}
}
// ���ݵĳ�ʼ��
void GameInit() {
	// init ��ʼ��graphͼ�δ���
	initgraph(640, 480,SHOWCONSOLE);
	// ��ʼ����	
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;
	snake.dir_com = RIGHT;
	for (int i = 0; i <snake.size; i++)
	{
		// ѭ��ȷ����������
		snake.coor[i].x = 40 - 10*i;
		snake.coor[i].y = 10;
	} 
	food_coming();
	food.color = RGB(192, 10, 22);
	// ʳ����ɫ
	food.r = rand() % 10 + 5;
	food.flag = true;
}


void GameDraw() {
	//˫�����ͼ
	BeginBatchDraw();
	setbkcolor(RGB(255, 255, 255));
	// ��ʼ��������ɫ
	cleardevice();
	// ��ջ�ͼ�豸
	setfillcolor(RGB(196, 175, 118));
	solidcircle(snake.coor[0].x, snake.coor[0].y, 5);
	setfillcolor(RGB(53, 63, 72));
	for (int i = 1; i < snake.size; i++) {
		// ѭ��������
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	
	if (food.flag) {
		// ���ʳ���Ƿ����
		setfillcolor(RGB(192, 10, 22));
		solidcircle(food.x,food.y,5);
		//std::cout << "����" << std::endl;
	}
	else {
		// ��������ʳ������
		/*food.x = rand() % 640;
		food.y = rand() % 480;*/
		food_coming();

		food.flag = true;
	}
	EndBatchDraw();
	// ˫�������

}

int ku() {
	// ���С���Ƿ�һֱ��һ�������ƶ�������ǣ�����0
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


// �ߵ��ƶ�
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
				// �����ϱ߽�
				snake.coor[0].y = 480-5;
			}
			break;
		case DOWN:
			snake.coor[0].y+= snake.speed;
			
			if (snake.coor[0].y - 10 >= 480 - 5) {
				// �����½�
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
	// ���ʳ����ײ
	if (abs(snake.coor[0].x-food.x)<=5 && abs(snake.coor[0].y - food.y)<=5) {
		food.flag = false;	
		snake.size++;
	}
}


void keyControl() {
	// ����ʹ��(��С�������ƶ�ʱ��������ת��)
	// ͨ�������ı���̷���
	// �ж���û�а�������
	if (_kbhit()) {

		switch (_getch())
		{
			// ���������
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
	// �����һ���ȼ�������ײ����
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
				/*std::cout << "didi��ֵ��" << didi.a << didi.b << didi.c << didi.d << std::endl;*/

				Zerodays();
				
			}
		}
		break;
	case RIGHT:
		for (int i = 1; i < snake.size; i++)
		{
			if (snake.coor[0].x + 10 == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y || snake.coor[0].x - 620 == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y) {
				key1();
				/*std::cout << "didi��ֵ��" << didi.a << didi.b << didi.c << didi.d << std::endl;*/
				Zerodays();
				
			}
		}

		break;
	case UP:
		for (int i = 1; i < snake.size; i++)
		{
			if (snake.coor[0].x == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y - 10 || snake.coor[0].x == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y + 470) {
				key1();
				/*std::cout << "didi��ֵ��" << didi.a << didi.b << didi.c << didi.d << std::endl;*/
				Zerodays();

			}
		}
		break;
	case DOWN:
		for (int i = 1; i < snake.size; i++)
		{
			if (snake.coor[0].x == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y + 10 || snake.coor[0].x == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y - 470) {
				key1();
				/*std::cout << "didi��ֵ��" << didi.a << didi.b << didi.c << didi.d << std::endl;*/
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
	// ����ڶ����ȼ�������ײ����
	switch (snake.dir)
	{
	case LEFT:
		for (int i = 1; i < snake.size; i++) {
			if (snake.coor[0].x - 10 == snake.coor[i].x && snake.coor[i].y == snake.coor[0].y) {
				// ��ײ����
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
				// ��ײ����
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
				// ��ײ����
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
				// ��ײ����
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
// С���ƶ��߼�
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
	// ���ȵ���x��
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
