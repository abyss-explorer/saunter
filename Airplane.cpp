#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>

// ����Windows Multimedia Library
#pragma comment(lib, "Winmm.lib")

#define High 864
#define Width 591

struct Point
{
	int x;
	int y;
};

struct fPoint 
{
	float x;
	float y;
};

IMAGE img_bk; // ����ͼƬ
Point position; // �ɻ�λ��
Point bullet; // �ӵ�λ��
fPoint enemy; // �л�λ��
IMAGE img_planeNormal1, img_planeNormal2; // �ɻ�ͼƬ
IMAGE img_planeExplode1, img_planeExplode2; // �ɻ���ըͼƬ
IMAGE img_bullet1, img_bullet2; // �ӵ�ͼƬ
IMAGE img_enemyPlane1, img_enemyPlane2; // �л�ͼƬ
bool isExpolde = false; // �ɻ��Ƿ�ը
int score = 0; // �÷�

void startup() 
{
	mciSendString(LPCWSTR("open res\\game_music.mp3 alias bkmusic"), NULL, 0, NULL); // �򿪱�������
	mciSendString(LPCWSTR("play bkmusic repeat"), NULL, 0, NULL); // ѭ�����ű�������
	initgraph(Width, High);
	loadimage(&img_bk, _T("res\\background.jpg"));
	loadimage(&img_planeNormal1, _T("res\\planeNormal_1.jpg"));
	loadimage(&img_planeNormal2, _T("res\\planeNormal_2.jpg"));
	loadimage(&img_bullet1, _T("res\\bullet1.jpg"));
	loadimage(&img_bullet2, _T("res\\bullet2.jpg"));
	loadimage(&img_enemyPlane1, _T("res\\enemyPlane1.jpg"));
	loadimage(&img_enemyPlane2, _T("res\\enemyPlane2.jpg"));
	loadimage(&img_planeExplode1, _T("res\\planeExplode_1.jpg"));
	loadimage(&img_planeExplode2, _T("res\\planeExplode_2.jpg"));
	position.x = High * 0.7;
	position.y = Width * 0.5;
	bullet.x = position.x;
	bullet.y = -85; // �ӵ���ʼλ��
	enemy.x = Width * 0.5;
	enemy.y = 10;
	BeginBatchDraw();
}

void show()
{
	putimage(0, 0, &img_bk);
	if (!isExpolde) {
		putimage(position.x - 50, position.y - 60, &img_planeNormal1, NOTSRCERASE);
		putimage(position.x - 50, position.y - 60, &img_planeNormal2, SRCINVERT);
		putimage(bullet.x - 7, bullet.y, &img_bullet1, NOTSRCERASE);
		putimage(bullet.x - 7, bullet.y, &img_bullet2, SRCINVERT);
		putimage(enemy.x, enemy.y, &img_enemyPlane1, NOTSRCERASE);
		putimage(enemy.x, enemy.y, &img_enemyPlane2, SRCINVERT);
	}
	else {
		putimage(position.x - 50, position.y - 60, &img_planeExplode1, NOTSRCERASE);
		putimage(position.x - 50, position.y - 60, &img_planeExplode2, SRCINVERT);
	}

	outtextxy(Width * 0.48, High * 0.95, _T("�÷�: "));
	char s[5] = { 0 };
	sprintf(s, "%d", score);
	outtextxy(Width * 0.55, High * 0.95, TCHAR(s));
	FlushBatchDraw();
	Sleep(2);
}

void updateWithoutInput()
{
	if (bullet.y > -25) {
		bullet.y -= 3;
	}

	if (enemy.y < High - 25) {
		enemy.y += 0.5;
	}
	else {
		enemy.y = 10;
	}

	if (fabs(bullet.x - enemy.x) + fabs(bullet.y - enemy.y) < 80) { // �ӵ����ел�
		enemy.x = rand() % Width;
		enemy.y = -40;
		bullet.y = -85;
		mciSendString(LPCWSTR("close gemusic"), NULL, 0, NULL); // �ر���һ�ε�����
		mciSendString(LPCWSTR("open gotEnemy.mp3 alias gemusic"), NULL, 0, NULL);

		mciSendString(LPCWSTR("play gemusic"), NULL, 0, NULL); // ��������
		score++;
		if (score > 0 && score % 5 == 0 && score % 2 != 0)
		{
			mciSendString(LPCWSTR("close 5music"), NULL, 0, NULL); // �ر���һ�ε�����
			mciSendString(LPCWSTR("open 5.mp3 alias 5music"), NULL, 0, NULL);

			mciSendString(LPCWSTR("play 5music"), NULL, 0, NULL); // ��������
		}

		if (score % 10 == 0)
		{
			mciSendString(LPCWSTR("close 10music"), NULL, 0, NULL); // �ر���һ�ε�����
			mciSendString(LPCWSTR("open 10.mp3 alias 10music"), NULL, 0, NULL);

			mciSendString(LPCWSTR("play 10music"), NULL, 0, NULL); // ��������
		}
	}

	if (fabs(position.x - enemy.x) + fabs(position.y - enemy.y) < 150) { // �л�ײ���һ�
		isExpolde = true;
		mciSendString(LPCWSTR("close exmusic"), NULL, 0, NULL); // �ر���һ�ε�����
		mciSendString(LPCWSTR("open explode.mp3 alias exmusic"), NULL, 0, NULL);

		mciSendString(LPCWSTR("play exmusic"), NULL, 0, NULL); // ��������
	}
}

void updateWithInput()
{
	MOUSEMSG m;
	while (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)
		{
			position.x = m.x;
			position.y = m.y;
		}
		else if (m.uMsg == WM_LBUTTONDOWN)
		{
			bullet.x = position.x;
			bullet.y = position.y - 85;
			mciSendString(LPCWSTR("close fgmusic"), NULL, 0, NULL); // �ر���һ�ε�����
			mciSendString(LPCWSTR("open f_gun.mp3 alias fgmusic"), NULL, 0, NULL);

			mciSendString(LPCWSTR("play fgmusic"), NULL, 0, NULL); // ��������
		}
	}
}

void gameover()
{
	EndBatchDraw();
	_getch();
	closegraph();
}

int main(void)
{
	startup();
	while (true)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}

	gameover();

	return 0;
}
