#pragma once
#include "Vector2D.h"

//----- GDI+ Image ����� ���� ��� �߰�
#include <ole2.h>  
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//----- GDI+ Image ����� ���� ��� �߰�

#include <list>
#include <vector>
using namespace std;

enum ItemType
{
	IT_Gold = 0,
	IT_Silver,
	IT_Potion,
	IT_Length
};

//--------------------------- CItem class
class CItem
{
public:
	ItemType	m_IT_Type;
	float		m_Duration;
	Vector2D	m_CurPos;
	float       m_HalfWidth;
	float		m_HalfHeight;
	Vector2D	a_CacIVec;
	Image*		m_ItemImg;

public:
	CItem();
	~CItem();

	bool ItemUpdate(float a_DeltaTime);
	void ItemRender(HDC a_hDC);
};
//--------------------------- CItem class

//--------------------------- CItem_Mgr class
class CItem_Mgr
{
	//------ Item List
	list <CItem*> m_ItemList;
	list <CItem*>::iterator m_Iiter;
	//------ Item List

	vector<Image*>    m_ImgList;  //������ �̹��� ����Ʈ

public:
	CItem_Mgr();
	~CItem_Mgr();

	void ItemMgr_Init();						//�ʱ�ȭ �Լ�
	void ItemMgr_Update(float a_DeltaTime);		//������ ���� ���κ�
	void ItemMgr_Render(HDC a_MainDC);			//�ƾ��� �׸��� �κ�
	void ItemMgr_Destroy();						//������ ���ҽ� ���� �κ�

	void SpawnItem(Vector2D a_StartV);			//������ ����
	void ReSrcClear();							//���带 �Ѿ �� �ʵ忡 �ѷ��� �ִ� ��� ������ ���� �Լ�
};
//--------------------------- CItem_Mgr class

extern CItem_Mgr g_ItemMgr;