#include <graphics.h>
#include <conio.h>
#include <cmath>

using namespace std;

struct Point
{
	int x;
	int y;
};

#define High 480
#define Width 640
#define PI 3.1415926

int main(void)
{
	initgraph(Width, High);
	Point center, secondEnd, minuteEnd, hourEnd;
	center.x = Width / 2;
	center.y = High / 2;
	int secondLenth = Width / 5;
	int minuteLenth = Width / 6;
	int hourLenth = Width / 8;

	double secondAngle;
	double minuteAngle;
	double hourAngle;

	SYSTEMTIME ti;

	BeginBatchDraw();
	while (true)
	{
		// ����һ���򵥵ı���
		setlinestyle(PS_SOLID, 1); // ��ʵ�ߣ����Ϊ1������
		setcolor(WHITE);
		circle(center.x, center.y, Width / 4);

		// ���̶�
		int x, y, i;
		for (i = 0; i < 60; i++)
		{
			x = center.x + int(Width/4.3*sin(PI*2*i/60));
			y = center.y - int(Width/4.3*cos(PI*2*i/60));

			if (i % 15 == 0) {
				bar(x - 5, y -5, x + 5, y + 5);
			}
			else if (i % 5 == 0) {
				circle(x, y, 3);
			}
			else {
				putpixel(x, y, WHITE);
			}
		}

		GetLocalTime(&ti);

		secondAngle = ti.wSecond * 2 * PI / 60;
		minuteAngle = ti.wMinute * 2 * PI / 60 + secondAngle / 60;
		hourAngle = ti.wHour*2*PI/12 + minuteAngle / 12;

		// �ɽǶȾ��������յ�����
		secondEnd.x = center.x + secondLenth * sin(secondAngle);
		secondEnd.y = center.y - secondLenth * cos(secondAngle);

		// �ɽǶȾ��������յ�����
		minuteEnd.x = center.x + minuteLenth * sin(minuteAngle);
		minuteEnd.y = center.y - minuteLenth * cos(minuteAngle);

		// �ɽǶȾ���ʱ���յ�����
		hourEnd.x = center.x + hourLenth * sin(hourAngle);
		hourEnd.y = center.y - hourLenth * cos(hourAngle);

		// ������
		setlinestyle(PS_SOLID, 2); // ��ʵ�ߣ����Ϊ2������
		setcolor(WHITE);
		line(center.x, center.y, secondEnd.x, secondEnd.y);

		// ������
		setlinestyle(PS_SOLID, 4); // ��ʵ�ߣ����Ϊ4������
		setcolor(BLUE);
		line(center.x, center.y, minuteEnd.x, minuteEnd.y);

		// ��ʱ��
		setlinestyle(PS_SOLID, 6); // ��ʵ�ߣ����Ϊ6������
		setcolor(RED);
		line(center.x, center.y, hourEnd.x, hourEnd.y);

		FlushBatchDraw();
		Sleep(10); // ��ʱ10����

		setcolor(BLACK);
		setlinestyle(PS_SOLID, 2); // ��ʵ�ߣ����Ϊ2������
		line(center.x, center.y, secondEnd.x, secondEnd.y);
		setlinestyle(PS_SOLID, 4); // ��ʵ�ߣ����Ϊ4������
		line(center.x, center.y, minuteEnd.x, minuteEnd.y);
		setlinestyle(PS_SOLID, 6); // ��ʵ�ߣ����Ϊ6������
		line(center.x, center.y, hourEnd.x, hourEnd.y);
	}

	EndBatchDraw();
	int c = _getch();
	closegraph();

	return 0;
}
