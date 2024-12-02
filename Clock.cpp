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
		// 绘制一个简单的表盘
		setlinestyle(PS_SOLID, 1); // 画实线，宽度为1个像素
		setcolor(WHITE);
		circle(center.x, center.y, Width / 4);

		// 画刻度
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

		// 由角度决定秒针终点坐标
		secondEnd.x = center.x + secondLenth * sin(secondAngle);
		secondEnd.y = center.y - secondLenth * cos(secondAngle);

		// 由角度决定分针终点坐标
		minuteEnd.x = center.x + minuteLenth * sin(minuteAngle);
		minuteEnd.y = center.y - minuteLenth * cos(minuteAngle);

		// 由角度决定时针终点坐标
		hourEnd.x = center.x + hourLenth * sin(hourAngle);
		hourEnd.y = center.y - hourLenth * cos(hourAngle);

		// 画秒针
		setlinestyle(PS_SOLID, 2); // 画实线，宽度为2个像素
		setcolor(WHITE);
		line(center.x, center.y, secondEnd.x, secondEnd.y);

		// 画分针
		setlinestyle(PS_SOLID, 4); // 画实线，宽度为4个像素
		setcolor(BLUE);
		line(center.x, center.y, minuteEnd.x, minuteEnd.y);

		// 画时针
		setlinestyle(PS_SOLID, 6); // 画实线，宽度为6个像素
		setcolor(RED);
		line(center.x, center.y, hourEnd.x, hourEnd.y);

		FlushBatchDraw();
		Sleep(10); // 延时10毫秒

		setcolor(BLACK);
		setlinestyle(PS_SOLID, 2); // 画实线，宽度为2个像素
		line(center.x, center.y, secondEnd.x, secondEnd.y);
		setlinestyle(PS_SOLID, 4); // 画实线，宽度为4个像素
		line(center.x, center.y, minuteEnd.x, minuteEnd.y);
		setlinestyle(PS_SOLID, 6); // 画实线，宽度为6个像素
		line(center.x, center.y, hourEnd.x, hourEnd.y);
	}

	EndBatchDraw();
	int c = _getch();
	closegraph();

	return 0;
}
