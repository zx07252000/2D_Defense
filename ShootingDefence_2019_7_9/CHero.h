#pragma once
#include "Vector2D.h"
#include "CUnit.h"

class CHero : public CUnit
{
	HBRUSH	 m_R_brsh;
	HGDIOBJ  m_R_Old_brsh;

	float    m_Speed = 300.0f;

	HWND	m_hWnd;
	float   m_AttackSpeed = 0.1f;  //���ݼӵ�
	float   m_BLCycle = 0.0f;

	//------ ����
	float  m_DeltaTime = 0.0f;
	Image* m_Shield;
	float  m_SdDuration = 8.0f;

public:
	float  m_SdOnTime = 0.0f;
	float  m_SdHalfSize;
	//------ ����

public:
	int      m_CurHP;
	int      m_MaxHp;
	Vector2D m_CurPos;
	float    m_HalfColl = 20.0f;    //���ΰ��� �浹 �ݰ�

	//------ �ɷ�ġ
	float m_CurAttack = 10.0f;	//���ΰ��� ���ݷ�
	int   m_KillCount = 0;		//ų�� 
	int   m_SkillCount = 5;		//���� ��ų �� 
	int   m_ShieldCount = 5;	//���� ��ȣ�� ��
	int   m_MyMoney = 0;		//������ ���
	//------ �ɷ�ġ

	float m_STDelay = 0.5f;     //���� ����ŸƮ�ÿ� �ñر� ������ �ֱ�

public:
	CHero();
	~CHero();

public:
	virtual void Init_Unit(HWND a_hWnd);
	virtual void Update_Unit(float a_DeltaTime, RECT& a_RT);
	virtual void Render_Unit(HDC a_hDC);
	virtual void Destroy_Unit();

	void HeroLimitMove(RECT& a_RT);
	void TakeDamage(float a_Damage = 10.0f);

	void Load_Shield();
	void ShieldUpdate();
	void ShieldRender(Graphics& graphics);
	void ShieldDestroy();

	static void BuyHP();
	static void BuySkill();
	static void BuyShield();
};

extern CHero g_Hero;