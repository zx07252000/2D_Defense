#pragma once

#include <vector>
using namespace std;

//----- GDI+ Image ����� ���� ��� �߰�
#include <ole2.h>      
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//----- GDI+ Image ����� ���� ��� �߰�

enum CT_Type   //CharicType
{
	CT_None = 0,
	CT_Nanami,
	CT_Zombi1,
	CT_Zombi2,
	CT_Zombi3,
	CT_Zombi4,
	CT_Zombi6,
	CT_Zombi8,
	CT_Boss,
	CTT_Length,
};

enum AniState
{
	AS_None,
	Idle,
	Front_Walk,
	Back_Walk,
	Left_Walk,
	Right_Walk,
	AniLength,
};

//------------------------- class CMotion
class CMotion
{
public:
	vector<Image*> m_ImgList;  //�÷��� �ε�

public:
	CMotion()
	{
	}
	~CMotion()
	{
		for (int ii = 0; ii < m_ImgList.size(); ii++)
		{
			//--- GDI+ ���� 
			if (m_ImgList[ii] != NULL)
			{
				delete m_ImgList[ii];
				m_ImgList[ii] = NULL;
			}
			//--- GDI+ ���� 
		}
		m_ImgList.clear();
	}

	void LoadTexImg(const TCHAR* a_FName)
	{
		//�ش� ��ο��� �̹��� �ҷ�����
		Image* a_pBitmap = Image::FromFile(a_FName);
		m_ImgList.push_back(a_pBitmap);
	}
};
//------------------------- class CMotion

//------------------------- class CAnimData
class CAnimData
{
public:
	vector<CMotion*> m_MotionList;

public:
	CAnimData();
	~CAnimData();

	void LoadAnimList(CT_Type a_CharicType);   //ĳ���� ������ "����"����? "������"����?
};
//------------------------- class CAnimData
