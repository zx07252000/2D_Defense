#pragma once

#include <functional>  //function
using namespace std;   //function

#include "Vector2D.h"

//----- GDI+ Image ����� ���� ��� �߰�
#include <ole2.h>  
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//----- GDI+ Image ����� ���� ��� �߰�

//--------------------------- CButton class
class CButton
{
public:
	bool        m_isBtnDown;
	Image*		m_BtnUpImg;
	Image*		m_BtnDownImg;

	Vector2D	m_LT_Pos;   //Left Top Position
	Vector2D	m_WH_Size;  //Width Height

	ColorMatrix m_DownCM;   //DownImg�� ���� �� 
	function<void(void)> ClickCallback = NULL; //<---STL���� ������ �ִ� �Լ� ������ ���� ����

public:
	CButton();
	~CButton();
	void SetBtnRect(float a_LeftPos, float a_TopPos,
		float a_WSize = 0.0f, float a_HSize = 0.0f);

	void Load_Rsc(const TCHAR* a_BtnUpStr, const TCHAR* a_BtnDownStr = NULL);
	void BtnRender(HDC a_hDC);
	void Destroy();

	void LBtnDown(Vector2D a_MosPos);
	bool LBtnUp();
	void OnClick_AddListener(function<void(void)> Callback = NULL); //PointerUp
};
//--------------------------- CButton class

//--------------------------- CUI_Manager class
class CUI_Manager
{
	Image* m_GUIBack = NULL;
	Image* m_HP_Icon = NULL;

	float  m_DeltaTime = 0.0f;

	TCHAR m_StrBuff[128];
	HFONT m_Font_26Godic = NULL;
	HFONT hFont_100 = NULL;
	HFONT hFont_50 = NULL;
	HFONT m_OldFont;
	HBRUSH h_Old_Brush;

	HPEN h_Pen;
	HPEN h_OldPen;
	HBRUSH h_Brush;
	HBRUSH h_OldBrush;

	//----- Shop
public:
	bool         m_ShopOnOff;

private:
	Image*		 m_ShopBase;
	ColorMatrix  m_AlphaCM;

	HFONT		 m_HumanF;

	CButton      m_CloseBtn;  //�ݱ� ��ư

	Image*		 m_ShopBG[3];
	Image*		 m_Image[3];
	Image*		 m_CoinImg[3];
	CButton      m_AddBtn[3];   //Add��ư
	//----- Shop

public:
	CUI_Manager();
	~CUI_Manager();

public:
	void UIMgr_Init();          //�ʱ�ȭ �Լ�
	void UIMgr_Update(HWND a_hWnd, float a_DeltaTime,
			void(*NextLevelFunc)() = NULL, void(*ReSetGameFunc)() = NULL);    //������ ���� ���κ�
	void UIMgr_Render(HDC a_MainDC, RECT& a_RT);     //������ �׸��� �κ�
	void UIMgr_Destroy();       //���� ó�� �κ�

	void UserInfoPanel(HDC a_MainDC, Graphics& graphics, RECT& a_RT);

	void StoreInit();
	void StoreRender(HDC a_MainDC, Graphics& graphics, RECT& a_RT);
	void StoreDestroy();

	void LBtnDown(HWND a_hWnd);
	void LBtnUp();
};
//--------------------------- CUI_Manager class

extern CUI_Manager g_GUI_Mgr;