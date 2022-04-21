#include "stdafx.h"
#include "CUnit.h"
#include "CMyMain.h"

CUnit::CUnit()
{
	m_SocketImg = NULL;
	m_RefAniData = NULL;

	m_CurAniState = AS_None;
	m_NowImgCount = 0;
	m_CurAniInx = 0;		//���� Ani Index
	m_AniTickCount = 0;     //���� �÷��ӱ��� �ð� Add
	m_EachAniDelay = 0.2f;  //�÷��� ���� �ð�
}

CUnit::~CUnit()
{
}

void CUnit::Init_Unit(HWND a_hWnd)
{
}

void CUnit::Update_Unit(float a_DeltaTime)
{
	//------------------- �ִϸ��̼� �÷��� ��� �κ� 
	AniFrameUpdate(a_DeltaTime);
	//------------------- �ִϸ��̼� �÷��� ��� �κ� 
}

void CUnit::Render_Unit(HDC a_hDC)
{
}

void CUnit::Destroy_Unit()
{
}

void CUnit::SetAni_Rsc(CT_Type a_CharType)
{
	if (a_CharType <= CT_None || CTT_Length <= a_CharType)
		return;

	m_CharicType = a_CharType;

	if (a_CharType < g_CMyMain.m_CharAniList.size())
		m_RefAniData = g_CMyMain.m_CharAniList[(int)a_CharType];

	ChangeState(Idle);

	LoadUnitSize();
}

void CUnit::LoadUnitSize()
{
	if (m_SocketImg != NULL)
	{
		m_ImgSizeX = m_SocketImg->GetWidth();     //�⺻ �̹����� ���� ������
		m_ImgSizeY = m_SocketImg->GetHeight();	  //�⺻ �̹����� ���� ������

		m_HalfWidth = m_ImgSizeX / 2;			  //�⺻ �̹����� ���� �ݻ�����
		m_HalfHeight = m_ImgSizeY / 2;			  //�⺻ �̹����� ���� �ݻ�����
	}
}

bool CUnit::ChangeState(AniState newState)
{
	if (m_CurAniState == newState)
		return false;

	if (newState <= AS_None || AniLength <= newState)
		return false;

	if (m_RefAniData == NULL)
		return false;

	if (m_RefAniData->m_MotionList[(int)newState]->m_ImgList.size() <= 0)
		return false;

	m_NowImgCount = m_RefAniData->m_MotionList[(int)newState]->m_ImgList.size();
	m_CurAniInx = 0;
	m_AniTickCount = 0;

	if (newState == Idle)
	{
		m_EachAniDelay = 0.4f;
	}
	else
	{
		m_EachAniDelay = 0.12f;
	}

	m_SocketImg = m_RefAniData->m_MotionList[(int)newState]->m_ImgList[0]; //ù �̹��� ����

	m_CurAniState = newState;

	return true;
}

void CUnit::AniFrameUpdate(double a_DeltaTime)
{
	//------------------- �ִϸ��̼� �÷��� ��� �κ� 
	if (m_CurAniState == AS_None)
		return;

	if (m_NowImgCount <= 0)  //�ִ� ���Ͽ� ���� ���� �ִ��� Ȯ���� ���� ������ġ
		return;

	m_AniTickCount = m_AniTickCount + a_DeltaTime;
	if (m_EachAniDelay < m_AniTickCount)  //���� �÷���
	{
		m_CurAniInx++;
		if (m_NowImgCount <= m_CurAniInx) //������ �÷����� ��
		{
			m_CurAniInx = 0;
		}

		m_SocketImg = m_RefAniData->m_MotionList[(int)m_CurAniState]->m_ImgList[m_CurAniInx];

		m_AniTickCount = 0;
	}
	//------------------- �ִϸ��̼� �÷��� ��� �κ� 
}
