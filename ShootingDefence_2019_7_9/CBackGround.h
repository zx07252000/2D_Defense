#pragma once

class CBackGround
{
	HDC		m_BGImgDC;
	HBITMAP	m_hTexImgBMP;      //�ε��� BMP ������ �ڵ� 
	int     m_TexImgWidth;     //�̹����� ���� ������
	int     m_TexImgHeight;    //�̹����� ���� ������

public:
	CBackGround();
	~CBackGround();

public:
	void BG_Init(HWND a_hWnd);				//�ʱ�ȭ �Լ�
	void BG_Update();						//������ ���� ���κ�
	void BG_Render(HDC a_hdc, RECT& a_RT);	//������ �׸��� �κ�
	void BG_Destroy();						//���� ó�� �κ�
};

extern CBackGround g_BGround;