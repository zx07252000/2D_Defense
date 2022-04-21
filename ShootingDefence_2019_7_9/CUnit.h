#pragma once
#include "CAnimData.h"

class CUnit
{
public:
	CT_Type m_CharicType;			  //ĳ���� ������ "����"����? "������"����?
	CAnimData* m_RefAniData;          //ĳ���� Ÿ�Կ� ���� �ִϸ��̼� �����͸� �ٲ� �� ����

	//---------------- �ִϸ��̼� ���� ���� 
	Image* m_SocketImg;				  //�ִ� ����ó�� ����� ������
	AniState m_CurAniState;           //���� �ִϸ��̼� ����

	int		m_NowImgCount;            //�ִ� ����ó�� ����� �̹��� ī��Ʈ
	float	m_EachAniDelay;			  //�÷��� ���� �ð�
	float	m_AniTickCount;           //���� �÷��ӱ��� �ð� Add
	int		m_CurAniInx;              //���� Ani Index
	//---------------- �ִϸ��̼� ���� ���� 

	int     m_ImgSizeX;				//�̹����� ���� ������
	int     m_ImgSizeY;				//�̹����� ���� ������
	int     m_HalfWidth = 15;		//�⺻ �̹����� ���� �ݻ�����
	int     m_HalfHeight = 15;		//�⺻ �̹����� ���� �ݻ�����

public:
	CUnit();
	~CUnit();

	virtual void Init_Unit(HWND a_hWnd);
	virtual void Update_Unit(float a_DeltaTime);
	virtual void Render_Unit(HDC a_hDC);
	virtual void Destroy_Unit();

	void SetAni_Rsc(CT_Type a_CharType);
	void LoadUnitSize();
	bool ChangeState(AniState newState);
	void AniFrameUpdate(double a_DeltaTime);
};

