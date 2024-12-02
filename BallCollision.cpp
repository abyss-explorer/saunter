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

// ȫ�ֱ���
Point ball; // ���λ��
Point speed; // ����ٶ�
int radius; // ��İ뾶
Point bar_pos; // �������������
int bar_high, bar_width; // ����ĸ߶ȺͿ��
int bar_left, bar_right, bar_top, bar_bottom; // ������������±߽�

int isBrickExisted[Brick_num]; // ש���Ƿ����, 0��ʾ�����ڣ�1��ʾ����
int brick_high, brick_width; // ש��ĸ߶ȺͿ��

void startup() // ���ݵĳ�ʼ��
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

void clean() // ��Բ
{
	// ���ƺ��ߡ���ɫ����Բ
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(ball.x, ball.y, radius);
	// ���ƺ�ɫ���ľ���
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

void show() // ��ʾ����
{
	// ���ƻ��ߡ���ɫ����Բ
	setcolor(YELLOW);
	setfillcolor(GREEN);
	fillcircle(ball.x, ball.y, radius);
	// ������ɫ���ľ���
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
	// ��ʱ
	Sleep(3);
}

void updateWithoutInput() // ���û������޹صĸ���
{
	// �����С����ײ��С�򷴵�
	if (((ball.y + radius >= bar_top) && (ball.y + radius < bar_bottom - bar_high / 3))
		|| ((ball.y - radius <= bar_bottom) && (ball.y - radius > bar_top + bar_high / 3)))
	{
		if ((ball.x >= bar_left) && (ball.x <= bar_right))
		{
			speed.y = -speed.y;
		}
	}

	// ����С������
	ball.x += speed.x;
	ball.y += speed.y;

	// С��߽���ײ��С�򷴵�
	if (ball.x <= radius || ball.x >= Width - radius)
	{
		speed.x = -speed.x;
	}

	if (ball.y <= radius || ball.y >= High - radius)
	{
		speed.y = -speed.y;
	}

	// С���ש����ײ��С�򷴵�
	int brick_left, brick_right, brick_top, brick_bottom;
	for (int i = 0; i < Brick_num; i++) {
		if (isBrickExisted[i] == 1) { // ש����ڲ��ж�
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

void updateWithInput() // ���û������йصĸ���
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

void gameover() // ��Ϸ����
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
