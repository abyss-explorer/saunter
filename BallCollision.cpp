#include <graphics.h>
#include <conio.h>

#define High 480
#define Width 640
#define Brick_num 10

struct Point
{
	int x;
	int y;
};

// 全局变量
Point ball; // 球的位置
Point speed; // 球的速度
int radius; // 球的半径
Point bar_pos; // 挡板的中心坐标
int bar_high, bar_width; // 挡板的高度和宽度
int bar_left, bar_right, bar_top, bar_bottom; // 挡板的左右上下边界

int isBrickExisted[Brick_num]; // 砖块是否存在, 0表示不存在，1表示存在
int brick_high, brick_width; // 砖块的高度和宽度

void startup() // 数据的初始化
{
	ball.x = Width / 2;
	ball.y = High / 2;
	speed.x = 1;
	speed.y = 1;
	radius = 20;

	bar_high = High / 20;
	bar_width = Width / 5;
	bar_pos.x = Width / 2;
	bar_pos.y = High - bar_high / 2;
	bar_left = bar_pos.x - bar_width / 2;
	bar_right = bar_pos.x + bar_width / 2;
	bar_top = bar_pos.y - bar_high / 2;
	bar_bottom = bar_pos.y + bar_high / 2;

	brick_width = Width / Brick_num;
	brick_high = High / Brick_num;

	for (int i = 0; i < Brick_num; i++) {
		isBrickExisted[i] = 1;
	}

	initgraph(Width, High);
	BeginBatchDraw();
}

void clean() // 画圆
{
	// 绘制黑线、黑色填充的圆
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(ball.x, ball.y, radius);
	// 绘制黑色填充的矩形
	bar(bar_left, bar_top, bar_right, bar_bottom);

	int brick_left, brick_right, brick_top, brick_bottom;
	for (int i = 0; i < Brick_num; i++) {
		if (isBrickExisted[i] == 0) {
			brick_left = i * brick_width;
			brick_right = brick_left + brick_width;
			brick_top = 0;
			brick_bottom = brick_high;
			bar(brick_left, brick_top, brick_right, brick_bottom);
		}
	}
}

void show() // 显示画面
{
	// 绘制黄线、绿色填充的圆
	setcolor(YELLOW);
	setfillcolor(GREEN);
	fillcircle(ball.x, ball.y, radius);
	// 绘制绿色填充的矩形
	bar(bar_left, bar_top, bar_right, bar_bottom);

	int brick_left, brick_right, brick_top, brick_bottom;
	for (int i = 0; i < Brick_num; i++) {
		if (isBrickExisted[i] == 1) {
			brick_left = i * brick_width;
			brick_right = brick_left + brick_width;
			brick_top = 0;
			brick_bottom = brick_high;
			bar(brick_left, brick_top, brick_right, brick_bottom);
		}
	}

	FlushBatchDraw();
	// 延时
	Sleep(3);
}

void updateWithoutInput() // 与用户输入无关的更新
{
	// 挡板和小球碰撞，小球反弹
	if (((ball.y + radius >= bar_top) && (ball.y + radius < bar_bottom - bar_high / 3))
		|| ((ball.y - radius <= bar_bottom) && (ball.y - radius > bar_top + bar_high / 3)))
	{
		if ((ball.x >= bar_left) && (ball.x <= bar_right))
		{
			speed.y = -speed.y;
		}
	}

	// 更新小球坐标
	ball.x += speed.x;
	ball.y += speed.y;

	// 小球边界碰撞，小球反弹
	if (ball.x <= radius || ball.x >= Width - radius)
	{
		speed.x = -speed.x;
	}

	if (ball.y <= radius || ball.y >= High - radius)
	{
		speed.y = -speed.y;
	}

	// 小球和砖块碰撞，小球反弹
	int brick_left, brick_right, brick_top, brick_bottom;
	for (int i = 0; i < Brick_num; i++) {
		if (isBrickExisted[i] == 1) { // 砖块存在才判断
			brick_left = i * brick_width;
			brick_right = brick_left + brick_width;
			brick_top = 0;
			brick_bottom = brick_high;
			if ((ball.y == brick_bottom + radius) && (ball.x >= brick_left) && (ball.x <= brick_right)) {
				speed.y = -speed.y;
				isBrickExisted[i] = 0;
			}
		}
	}
}

void updateWithInput() // 与用户输入有关的更新
{
	char input;
	if (_kbhit())
	{
		input = _getch();
		if (input == 'a' && bar_left > 0) {
			bar_pos.x = bar_pos.x - 15;
			bar_left = bar_pos.x - bar_width / 2;
			bar_right = bar_pos.x + bar_width / 2;
		}
		if (input == 'd' && bar_right < Width) {
			bar_pos.x = bar_pos.x + 15;
			bar_left = bar_pos.x - bar_width / 2;
			bar_right = bar_pos.x + bar_width / 2;
		}
		if (input == 'w' && bar_top > 0) {
			bar_pos.y = bar_pos.y - 15;
			bar_top = bar_pos.y - bar_high / 2;
			bar_bottom = bar_pos.y + bar_high / 2;
		}
		if (input == 's' && bar_bottom < High) {
			bar_pos.y = bar_pos.y + 15;
			bar_top = bar_pos.y - bar_high / 2;
			bar_bottom = bar_pos.y + bar_high / 2;
		}
	}
}

void gameover() // 游戏结束
{
	EndBatchDraw();
	closegraph();
}

int main(void)
{
	startup();

	while (true)
	{
		clean();
		updateWithoutInput();
		updateWithInput();
		show();
	}

	gameover();

	return 0;
}
