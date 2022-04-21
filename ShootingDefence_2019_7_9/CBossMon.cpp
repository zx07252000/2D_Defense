#include "stdafx.h"
#include "CBossMon.h"
#include "CHero.h"
#include "CBullet_Mgr.h"
#include "CItem_Mgr.h"

CBossMon::CBossMon()
{
	m_isActive = false;
	IsAppearState = false;

	m_Speed = 300.0f;
	m_HalfColl = 90;  //������ �浹 �ݰ�
	m_CurHP = 550;
	m_MaxHp = 550;
}

CBossMon::~CBossMon()
{
}

void CBossMon::Init_Unit(HWND a_hWnd)
{
	m_hWnd = a_hWnd;

	m_R_brsh = CreateSolidBrush(RGB(255, 0, 0));//brush �߰�. pen�� ���� �������
}

void CBossMon::Update_Unit(float a_DeltaTime)
{
	static RECT a_RT;
	GetClientRect(m_hWnd, &a_RT);   //Main DC �� ���� ���� ����� ������ �Լ� 

	float a_OldTime = m_SpawnTime;
	m_SpawnTime = m_SpawnTime - a_DeltaTime;
	if (0.0f < a_OldTime && m_SpawnTime <= 0.0f)
	{
		float a_XX = 0.0f;
		float a_YY = 0.0f;

		a_XX = (float)((rand() % 200) - 100);
		float a_PushVal = 50.0f;
		int a_YLenVal = (int)a_RT.bottom + 100;

		if (a_XX < 0.0f)
		{
			a_XX = a_XX - a_PushVal;
		}
		else
		{
			a_XX = a_XX + (float)a_RT.right + a_PushVal;
		}

		a_YY = (float)((rand() % a_YLenVal) + (100 / 2));

		Spawn(a_XX, a_YY);

		m_SpawnTime = 0.0f;
	}

	if (m_isActive == false)
		return;

	Vector2D a_CacVec = g_Hero.m_CurPos - m_CurPos;

	//-----------Boss AI
	if (IsAppearState == true)
	{
		//������ �ѷ��� ������ �ִ� �ڽ��� ȭ�� �ȿ� ������ ���� ����� �Ǵ��� ������.
		//Spawn �� Target �������� �̵� 
		static double a_CacStep;
		static Vector2D a_CacEndVec;

		// ������ ���⿡ �ð� ���� ���ؼ� ���ݾ� �̵��ϰ� �Ѵ�
		a_CacStep = a_DeltaTime * m_Speed; //�̹��� �Ѱ��� ���� (����)
		a_CacEndVec = m_TargetPos - m_CurPos;
		if (a_CacEndVec.Magnitude() <= a_CacStep)  //��ǥ�������� �Ÿ����� ������ ũ�ų� ������ �������� ����.
		{
			IsAppearState = false;
			//m_CurPos = m_TargetPos;  //<--�̰� ���ΰ��� ��ǥ
			m_SkillCount = 0; //�ʱ�ȭ
			m_SkillTime = (float)((rand() % 6) + 5);
		}
		else
		{
			m_DirVec = a_CacEndVec;
			m_DirVec.Normalize();
			m_CurPos = m_CurPos + (m_DirVec * a_CacStep);

			a_CacVec = m_TargetPos - m_CurPos;
		}

		if (BossLimitMove(a_RT) == true) //�̰͵� ���� �Ϸ�� ����.
		{
			IsAppearState = false;
			//m_CurPos = m_TargetPos;  //<--�̰� ���ΰ��� ��ǥ
			m_SkillCount = 0; //�ʱ�ȭ
			m_SkillTime = (float)((rand() % 6) + 5);
		}

	}//if (IsAppearState == true)
	else
	{
		//8�� �ڿ� �ߵ� �ñر� Ÿ��
		m_SkillTime = m_SkillTime - a_DeltaTime;
		if (m_SkillTime <= 0)
		{
			if (-2.5f < m_SkillTime && m_SkillTime <= -2.0f)
			{
				if (m_SkillCount == 0)
				{
					SkillShoot();
					m_SkillCount = 1;
				}
			}
			else if (-3.0f < m_SkillTime)
			{
				if (m_SkillCount == 1)
				{
					SkillShoot();
					m_SkillCount = 2;
				}
			}
			else if (-3.5f < m_SkillTime)
			{
				if (m_SkillCount == 2)
				{
					SkillShoot();
					m_SkillCount = 3;
				}
			}
			else if (-4.0f < m_SkillTime)
			{
				if (m_SkillCount == 3)
				{
					SkillShoot();
					m_SkillCount = 4;
				}
			}
			else if (-5.0f < m_SkillTime)
			{
				if (m_SkillCount == 4)
				{
					SkillShoot();
					m_SkillCount = 5;
				}
			}
			else if (-6.5f < m_SkillTime)
			{
				m_SkillCount = 0; //�ʱ�ȭ
				m_SkillTime = (float)((rand() % 6) + 5);
			}
		}
		else
		{
			//���ΰ��� ���Ͽ� �Ѿ˹߻� 
			//----�Ѿ� �߻� ������Ʈ
			m_BLCycle = m_BLCycle + a_DeltaTime;
			if (m_AttackSpeed < m_BLCycle)
				m_BLCycle = 100.0f;

			if (m_AttackSpeed < m_BLCycle)
			{
				Vector2D a_CurV;
				a_CurV.x = m_CurPos.x;		//���콺�� ��ǥ
				a_CurV.y = m_CurPos.y - 50.0f;

				g_Bullet_Mgr.SpawnBullet(a_CurV, g_Hero.m_CurPos, CT_Monster, BT_Normal);

				m_BLCycle = 0.0f;
			}
			////----�Ѿ� �߻� ������Ʈ
		}
	}
	//-----------Boss AI

	//------------------- �ִϸ��̼� �÷��� ��� �κ� 
	if (0.0f < a_CacVec.x)
	{
		ChangeState(Right_Walk);  //���� ���������� �־�� �Ѵ�. 
	}
	else
	{
		ChangeState(Left_Walk);
	}
	CUnit::Update_Unit(a_DeltaTime);	//�θ��� Update_Unit()�Լ� ȣ��
	//------------------- �ִϸ��̼� �÷��� ��� �κ� 

	//------- ���ΰ����� �浹ó��
	static float a_CacSDist;
	static float a_CacMargin = 0.0f;
	static float a_RadiusHap;
	static Vector2D a_CacMovePos;
	static Vector2D a_CacSNormal;
	static float a_CacShiftLen = 0.0f;
	a_CacVec = g_Hero.m_CurPos - m_CurPos;
	a_CacSDist = a_CacVec.Magnitude();
	a_RadiusHap = m_HalfColl + 4 + g_Hero.m_HalfColl + 4; //(���ݰ� + ���ݰ�) ���� ��Ȱ��

	a_CacMovePos = g_Hero.m_CurPos;

	if (a_CacSDist < a_RadiusHap)
	{
		a_CacMargin = a_RadiusHap - a_CacSDist;
		a_CacSNormal = a_CacVec; //�з����� ����
		a_CacSNormal.Normalize();

		a_CacShiftLen = a_CacMargin;
		if (a_RadiusHap < a_CacShiftLen) //������ġ �ð����ݵ� ���������� Ŀ���� �ȵȴ�. 
		{
			a_CacShiftLen = a_RadiusHap;
		}

		a_CacMovePos = a_CacMovePos + (a_CacSNormal * a_CacShiftLen);

	}//if (a_CacSDist < a_RadiusHap)

	g_Hero.m_CurPos = a_CacMovePos;
	//------- ���ΰ����� �浹ó��
}

void CBossMon::Render_Unit(HDC a_hDC)
{
	if (m_isActive == false)
		return;

	if (m_SocketImg == NULL)
		return;

	//---- HP Bar Render
	static HBRUSH h_Old_Brush;
	h_Old_Brush = (HBRUSH)SelectObject(a_hDC, m_R_brsh);
	static float a_CacMXX = 0.0f;
	static float a_CacMYY = (int)(m_HalfHeight * 0.8f);
	static float a_HpBSize = 50;
	static float a_CurHpSize = 0;
	a_CacMXX = a_HpBSize / 2.0f;
	a_CurHpSize = a_HpBSize * ((float)m_CurHP / (float)m_MaxHp);

	a_CacMYY = (int)(m_HalfHeight * 0.97f);

	Rectangle(a_hDC, m_CurPos.x - a_CacMXX, m_CurPos.y - a_CacMYY,
		m_CurPos.x - a_CacMXX + a_CurHpSize,
		m_CurPos.y - (a_CacMYY + 10.0f));
	SelectObject(a_hDC, h_Old_Brush);//���� �귯���� ��ü
	//---- HP Bar Render

	Graphics graphics(a_hDC);
	graphics.DrawImage(m_SocketImg, m_CurPos.x - m_HalfWidth,
		m_CurPos.y - (int)(m_HalfHeight * 1.2f),
		(float)m_ImgSizeX, (float)m_ImgSizeY);
}

void CBossMon::Destroy_Unit()
{
	if (m_R_brsh != NULL)
	{
		DeleteObject(m_R_brsh);
		m_R_brsh = NULL;
	}
}

void CBossMon::Spawn(float a_XX, float a_YY)
{
	m_CharicType = CT_Boss;

	m_CurPos.x = a_XX;
	m_CurPos.y = a_YY;

	m_isActive = true;
	IsAppearState = true;

	static RECT a_Crt;
	GetClientRect(m_hWnd, &a_Crt);   //Main DC �� ���� ���� ����� ������ �Լ� 
	//static Vector2D m_CacDir;
	static Vector2D m_CenterPos;
	m_CenterPos.x = (float)(a_Crt.right / 2);
	m_CenterPos.y = (float)(a_Crt.bottom / 2); //ȭ�� �߾� ��
	//m_CacDir = m_CurPos - m_CenterPos;
	//m_CacDir.Normalize();
	m_TargetPos = m_CenterPos; //+ (m_CacDir * 500.0f);

	m_CurHP = m_MaxHp;

	SetAni_Rsc(m_CharicType);

	m_ImgSizeX = m_SocketImg->GetWidth() * 0.4f;     //�⺻ �̹����� ���� ������
	m_ImgSizeY = m_SocketImg->GetHeight() * 0.5f;	  //�⺻ �̹����� ���� ������

	m_HalfWidth = m_ImgSizeX / 2;			  //�⺻ �̹����� ���� �ݻ�����
	m_HalfHeight = m_ImgSizeY / 2;			  //�⺻ �̹����� ���� �ݻ�����
}

void CBossMon::TakeDamage(float a_Damage)
{
	//���Ͱ� ���ΰ� ���� ���� 
	m_CurHP = m_CurHP - (int)a_Damage;

	if (m_CurHP <= 0)   //���ó��
	{
		m_SpawnTime = 5.0f;
		//IsAppearState = true;
		m_isActive = false;

		for (int ii = 0; ii < 5; ii++)
		{
			Vector2D a_CacPos = m_CurPos;
			a_CacPos.x = m_CurPos.x + (float)((rand() % 60) - 30);
			a_CacPos.y = m_CurPos.y + (float)((rand() % 60) - 30);
			//--------- Item ����
			g_ItemMgr.SpawnItem(a_CacPos);
			//--------- Item ����
		}

		m_CurHP = 0;
	}
}

void CBossMon::SkillShoot()
{
	float Radius = 100.0f;
	float Angle = 0.0f;
	static Vector2D a_CacStartV;
	static Vector2D a_TargetV;
	////--12���  16��� 
	for (Angle = 0; Angle < (2.0f * 3.141592f); Angle += (3.141592f / 12))
	{
		a_CacStartV = m_CurPos;

		a_TargetV.x = a_CacStartV.x + (Radius * cos(Angle));
		a_TargetV.y = a_CacStartV.y + (Radius * sin(Angle));

		g_Bullet_Mgr.SpawnBullet(a_CacStartV, a_TargetV, CT_Monster, BT_Normal);
	}
}

void CBossMon::ReSrcClear()	//���带 �Ѿ �� �ʵ忡 ������ �ִ� ��� ���� ���� �Լ�
{
	m_isActive = false;
	m_SpawnTime = 3.0f;
}

bool CBossMon::BossLimitMove(RECT& a_RT)
{
	static float a_CacLXXX = 0.0f;
	static float a_CacLYYY = 0.0f;

	a_CacLXXX = m_CurPos.x - (m_HalfColl + 50.0f);
	if (a_CacLXXX < a_RT.left)
	{
		return false;
	}

	a_CacLYYY = m_CurPos.y - (m_HalfColl + 50.0f);
	if (a_CacLYYY < a_RT.top)
	{
		return false;
	}

	a_CacLXXX = m_CurPos.x + (m_HalfColl + 50.0f);
	if (a_RT.right < a_CacLXXX)
	{
		return false;
	}

	a_CacLYYY = m_CurPos.y + (m_HalfColl + 50.0f);
	if (a_RT.bottom < a_CacLYYY)
	{
		return false;
	}

	return true;
}