#include "stdafx.h"
#include "CMyMain.h"
#include "CBackGround.h"
#include "CHero.h"
#include "CBullet_Mgr.h"
#include "CMonster_Mgr.h"
#include "CItem_Mgr.h"
#include "CUI_Manager.h"
#include "GlobalValue.h"

#include <Mmsystem.h>                //timeGetTime() �Լ� ����� ���Ͽ�...
#include <time.h>					 //<---�������� ��� ���Ͽ�...
#pragma comment(lib, "winmm.lib")    //timeGetTime() �Լ� ����� ���Ͽ�...

//----- GDI+ Image ����� ���� ��� �߰�
#include <ole2.h>  
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//----- GDI+ Image ����� ���� ��� �߰�

//----random����� ����
#include <time.h>
#include <stdlib.h>
//----random����� ����

CMyMain::CMyMain()
{
}

CMyMain::~CMyMain()
{
}

void CMyMain::MainInit(HWND hWnd)
{
	m_hWnd = hWnd;

	srand((unsigned)time(NULL));//----rand

	GetClientRect(hWnd, &m_Rect); // Ŭ���̾�Ʈ ȭ���� ũ�⸦ �޴´�

	//DeltaTime ��� ���� ���
	m_LastTime = timeGetTime();          //���� �ð� ��������

	//--- GDI+ �ʱ�ȭ
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
	//gdiplusToken <-- �������� GdiplusShutdown���� ����ϹǷ� �����ʼ�.
	//--- GDI+ �ʱ�ȭ

	//-------- �ĸ� BackDC ����
	HDC hdc = GetDC(hWnd); //���� DC ��������...
	m_hBackDC = CreateCompatibleDC(hdc);    //���� DC�� �ֵ��� ���纻 DC�� �ϳ� �����.
	m_hBackBitmap = CreateCompatibleBitmap(hdc, //BackDC�� �ٿ��� Bitmap(�̹���)�� �ϳ� ����� �´�.
		GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	SelectObject(m_hBackDC, m_hBackBitmap);     //BackDC�� Bitmap(�̹���)�� �ٿ��ش�.
	ReleaseDC(hWnd, hdc);
	//-------- �ĸ� BackDC ����

	for (int ii = 0; ii < CTT_Length; ii++)
	{
		CAnimData* a_Node = new CAnimData();
		a_Node->LoadAnimList((CT_Type)ii);
		m_CharAniList.push_back(a_Node);
	}

	//-------- GUI �ʱ�ȭ
	g_GUI_Mgr.UIMgr_Init();
	//-------- GUI �ʱ�ȭ

	//-------- ��׶��� �ʱ�ȭ
	g_BGround.BG_Init(hWnd);
	//-------- ��׶��� �ʱ�ȭ

	//-------- ���ΰ� �ʱ�ȭ
	g_Hero.Init_Unit(hWnd);
	//-------- ���ΰ� �ʱ�ȭ

	//-------- �Ѿ� �Ŵ��� �ʱ�ȭ
	g_Bullet_Mgr.BLMgr_Init();
	//-------- �Ѿ� �Ŵ��� �ʱ�ȭ

	//-------- ���� �Ŵ��� �ʱ�ȭ
	g_Mon_Mgr.MonMgr_Init(hWnd);
	//-------- ���� �Ŵ��� �ʱ�ȭ

	//-------- ������ �Ŵ��� �ʱ�ȭ
	g_ItemMgr.ItemMgr_Init();
	//-------- ������ �Ŵ��� �ʱ�ȭ
}

void CMyMain::MainUpdate(HWND hWnd)
{
	//DeltaTime ��� ���� ���
	timeBeginPeriod(1);         //���е��� ���̱� ���� �Լ� ���  
	m_CurTime = timeGetTime();
	m_DeltaTime = ((m_CurTime - m_LastTime)*0.001);
	m_LastTime = m_CurTime;
	timeEndPeriod(1);
	//DeltaTime ��� ���� ���

	if (m_hBackDC == NULL)
		return;

	GetClientRect(hWnd, &m_Rect);

	if (g_GameState == GAME_START)
	{
		static float a_TimeTic = 0;
		a_TimeTic = a_TimeTic + m_DeltaTime;
		if (1.0f <= a_TimeTic)
		{
			if (0 < g_TimeOut)
			{
				g_TimeOut--;
				if (g_TimeOut <= 0)
				{
					g_GameState = NEXT_LEVEL;
					g_GUI_Mgr.m_ShopOnOff = true;
					g_DiffLevel++;
					g_TimeOut = 0;
				}
			}
			a_TimeTic = 0;
		}

		////-------- ��׶��� ������Ʈ
		//g_BGround.BG_Update();
		////-------- ��׶��� ������Ʈ

		//-------- ���ΰ� ������Ʈ
		g_Hero.Update_Unit(m_DeltaTime, m_Rect);
		//-------- ���ΰ� ������Ʈ

		//-------- ���� �Ŵ��� ������Ʈ
		g_Mon_Mgr.MonMgr_Update(m_DeltaTime, hWnd, g_Hero);
		//-------- ���� �Ŵ��� ������Ʈ

		//-------- �Ѿ� �Ŵ��� ������Ʈ
		g_Bullet_Mgr.BLMgr_Update(m_DeltaTime, hWnd, g_Hero.m_CurPos, &g_Mon_Mgr);
		//-------- �Ѿ� �Ŵ��� ������Ʈ

		//-------- ������ �Ŵ��� ������Ʈ
		g_ItemMgr.ItemMgr_Update(m_DeltaTime);
		//-------- ������ �Ŵ��� ������Ʈ

	}//if (g_GameState == GAME_START)

	//-------- GUI ������Ʈ
	g_GUI_Mgr.UIMgr_Update(hWnd, m_DeltaTime, NextLevel, ReSetGame);
	//-------- GUI ������Ʈ
}

void CMyMain::MainRender(HWND hWnd)
{
	if (m_hBackDC == NULL)
		return;

	if (g_GameState == GAME_START)
	{
		//-------- ��׶��� ����
		g_BGround.BG_Render(m_hBackDC, m_Rect);
		//-------- ��׶��� ����

		//---- ������ �׷��ֱ�
		g_ItemMgr.ItemMgr_Render(m_hBackDC);
		//---- ������ �׷��ֱ�

		//--- ���� �̹��� �׸���...
		g_Mon_Mgr.MonMgr_Render(m_hBackDC);
		//--- ���� �̹��� �׸���...

		//----�Ѿ� �׷��ֱ�
		g_Bullet_Mgr.BLMgr_Render(m_hBackDC);
		//----�Ѿ� �׷��ֱ�

		//----���ΰ� �׷��ֱ�
		g_Hero.Render_Unit(m_hBackDC);
		//----���ΰ� �׷��ֱ�

	}//if (g_GameState == GAME_START)

	//----GUI �׷��ֱ�
	g_GUI_Mgr.UIMgr_Render(m_hBackDC, m_Rect);
	//----GUI �׷��ֱ�

	//------------------- ���� ���۸�
	static HDC hdc;
	hdc = GetDC(hWnd);
	//------- ȭ����ȯ
	BitBlt(hdc, 0, 0, m_Rect.right, m_Rect.bottom, m_hBackDC, 
													0, 0, SRCCOPY);
	//------- ȭ����ȯ
	ReleaseDC(hWnd, hdc);
	//------------------ ���� ���۸�
}

void CMyMain::MainDestroy()
{
	//------------�ִϸ��̼� ������ ���� �κ�
	for (int ii = 0; ii < m_CharAniList.size(); ii++)
	{
		if (m_CharAniList[ii] != NULL)
		{
			delete m_CharAniList[ii];
			m_CharAniList[ii] = NULL;
		}
	}
	m_CharAniList.clear();
	//------------�ִϸ��̼� ������ ���� �κ�

	//--- ������ �����...
	g_ItemMgr.ItemMgr_Destroy();
	//--- ������ �����...

	//--- ���� �����...
	g_Mon_Mgr.MonMgr_Destroy();
	//--- ���� �����...

	//----�Ѿ� �����
	g_Bullet_Mgr.BLMgr_Destroy();
	//----�Ѿ� �����

	//----���ΰ� �����
	g_Hero.Destroy_Unit();
	//----���ΰ� �����

	//-------- ��׶��� ����
	g_BGround.BG_Destroy();
	//-------- ��׶��� ����

	//-------- GUI �����...
	g_GUI_Mgr.UIMgr_Destroy();
	//-------- GUI �����...

	//-------- �ĸ� BackDC ����
	if (m_hBackBitmap != NULL)
	{
		DeleteObject(m_hBackBitmap);
		m_hBackBitmap = NULL;
	}

	if (m_hBackDC != NULL)
	{
		DeleteDC(m_hBackDC);
		m_hBackDC = NULL;
	}
	//-------- �ĸ� BackDC ����

	//--- GDI+ ����  
	if (m_gdiplusToken != NULL)
	{
		GdiplusShutdown(m_gdiplusToken);
		m_gdiplusToken = NULL;
	}
	//--- GDI+ ���� 
}

void CMyMain::NextLevel()
{
	//���� �ʱ�ȭ
	g_TimeOut = 30;

	//----���� �Ѿ� ���� 
	g_Bullet_Mgr.ReSrcClear();  //���ΰ� �ؽ��Ŀ� ���� �Ѿ� ����
	//----���� �Ѿ� ���� 

	//----���� ������ ����
	g_ItemMgr.ReSrcClear();
	//----���� ������ ����

	//----���� ���� ���� 
	g_Mon_Mgr.ReSrcClear();
	//----���� ���� ���� 

	//---------------���ΰ� �ʱ�ȭ 
	static RECT a_RT;
	GetClientRect(g_CMyMain.m_hWnd, &a_RT);
	g_Hero.m_CurPos.x = (float)(a_RT.right / 2.0f);
	g_Hero.m_CurPos.y = (float)(a_RT.bottom / 2.0f);

	g_Hero.m_SdOnTime = 0.0f;

	g_Hero.ChangeState(Idle);
	//---------------���ΰ� �ʱ�ȭ 

	g_GameState = GAME_START;
}

void CMyMain::ReSetGame()
{
	//���� �ʱ� ȭ
	g_TimeOut = 30;

	g_DiffLevel = 1;

	//----���� �Ѿ� ���� 
	g_Bullet_Mgr.ReSrcClear();  //���ΰ� �ؽ��Ŀ� ���� �Ѿ� ����
	//----���� �Ѿ� ���� 

	//----���� ������ ����
	g_ItemMgr.ReSrcClear();
	//----���� ������ ����

	//----���� ���� ���� 
	g_Mon_Mgr.ReSrcClear();
	//----���� ���� ���� 

	//---------------���ΰ� �ʱ�ȭ 
	static RECT a_RT;
	GetClientRect(g_CMyMain.m_hWnd, &a_RT);
	g_Hero.m_CurPos.x = (float)(a_RT.right / 2.0f);
	g_Hero.m_CurPos.y = (float)(a_RT.bottom / 2.0f);

	g_Hero.m_SdOnTime = 0.0f;

	g_Hero.ChangeState(Idle);

	g_Hero.m_CurHP = g_Hero.m_MaxHp;
	g_Hero.m_KillCount = 0;
	g_Hero.m_SkillCount = 5;
	g_Hero.m_ShieldCount = 5;
	g_Hero.m_STDelay = 0.5f;
	//---------------���ΰ� �ʱ�ȭ 

	g_GameState = GAME_READY;

}

CMyMain g_CMyMain;  //������ ����