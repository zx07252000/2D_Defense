#pragma once
#include "Vector2D.h"
#include "CUnit.h"

class CBossMon : public CUnit
{
	Vector2D m_DirVec;
	bool     IsAppearState;
	float    m_AttackSpeed = 0.7f;  //공격속도
	float    m_BLCycle = 0.0f;

	float	 m_SpawnTime = 3.0f;
	float    m_SkillTime = 0.0f;
	int      m_SkillCount = 0;

	HWND	 m_hWnd = NULL;
	float    m_Speed = 300.0f;

	HBRUSH	 m_R_brsh;
	HGDIOBJ  m_R_Old_brsh;
	Vector2D m_TargetPos;

public:
	bool	 m_isActive;
	Vector2D m_CurPos;
	////--- 주인공 좌표 계산용 변수들...
	float    m_HalfColl = 20.0f;  //주인공의 충돌 반경
	int      m_CurHP;
	int      m_MaxHp;

public:
	CBossMon();
	~CBossMon();

public:
	virtual void Init_Unit(HWND a_hWnd);
	virtual void Update_Unit(float a_DeltaTime);
	virtual void Render_Unit(HDC a_hDC);
	virtual void Destroy_Unit();

	void Spawn(float a_XX, float a_YY);
	void TakeDamage(float a_Damage = 10.0f);
	void SkillShoot();
	void ReSrcClear();	//라운드를 넘어갈 때 필드에 등장해 있는 모든 몬스터 삭제 함수
	bool BossLimitMove(RECT& a_RT);
};

