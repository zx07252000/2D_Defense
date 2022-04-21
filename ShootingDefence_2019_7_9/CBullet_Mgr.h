#pragma once
#include "Vector2D.h"

#include <vector>
using namespace std;

class CMonster_Mgr;

enum UClassType
{
	CT_Unit = 0,
	CT_Hero,
	CT_Monster,
};

enum BulletType
{
	BT_Normal = 0,
	BT_Skill1,
};

//----------------------------- CBullet
class CBullet
{
public:
	bool	    m_BLActive;   //�Ѿ��� ��Ƽ�� ����
	BulletType  m_BL_Type;    //�Ѿ��� �Ϲ� �Ѿ�����? ��ų �Ѿ�����?
	UClassType  m_UC_Type;	  //���� �� �Ѿ�����?

	float		m_LifeTime;   //�Ѿ��� ������ Ÿ��(�Ѿ��� ���ʵ��� ���ư��� �� �������� �ð�)
	Vector2D	m_CurPos;     //�Ѿ��� ���� ��ġ
	Vector2D	m_DirVec;     //�Ѿ��� ���ư��� ���⺤��
	float		m_MoveSpeed;  //�Ѿ��� �̵� �ӵ�

	float       m_HalfColl;   //�浹 �ݰ�

	static HBRUSH	m_R_brsh;
	static HBRUSH	m_G_brsh;
	HGDIOBJ		a_R_Old_brsh;

public:
	CBullet();
	~CBullet();

	bool BulletUpdate(float a_DeltaTime);
	void BulletRender(HDC a_hDC);
};
//----------------------------- CBullet

//----------------------------- CBullet_Mgr
class CBullet_Mgr
{
private:
	vector<CBullet*> m_BullList;  //<--- �Ѿ� Ǯ ���

	HBRUSH	m_h_brsh = NULL;
	HGDIOBJ m_h_Old_brsh = NULL;
	HPEN	m_h_pen = NULL;  //������(�Ǽ�), �β�(1), RGB��
	HGDIOBJ	m_h_Oldpen = NULL;

public:
	CBullet_Mgr();
	~CBullet_Mgr();

public:
	void BLMgr_Init();
	void BLMgr_Update(float a_DeltaTime, HWND a_hWnd, Vector2D a_HeroV, 
					  CMonster_Mgr* a_MonMgr = NULL);
	void BLMgr_Render(HDC a_hDC);
	void BLMgr_Destroy();

	void SpawnBullet(Vector2D a_StartV, Vector2D a_TargetV,
					UClassType a_Own_Type = CT_Hero, BulletType a_BLTP = BT_Normal);

	void ReSrcClear();
};
//----------------------------- CBullet_Mgr

extern CBullet_Mgr g_Bullet_Mgr;
