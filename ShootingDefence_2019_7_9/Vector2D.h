#pragma once

class Vector2D
{
public:
	float    x;
	float    y;

public:
	Vector2D();
	Vector2D(float a_X, float a_Y) //������ �Լ��� �����ε�
	{
		x = a_X;
		y = a_Y;
	}
	~Vector2D();

	//-----�۷ι� ������ �������̵� �Լ� ����� ����
	friend Vector2D operator +(const Vector2D &T1, const Vector2D &T2);
	friend Vector2D operator -(const Vector2D &T1, const Vector2D &T2);
	friend Vector2D operator *(const Vector2D &T1, const float &T2);
	friend Vector2D operator *(const float &T1, const Vector2D &T2);
	//-----�۷ι� ������ �������̵� �Լ� ����� ����

	float Magnitude();    //������ ũ�⸸ ���ؿ��� �Լ�
	void Normalize();     //��� ���ͷ� �����...
};

float GetAngle(Vector2D& a_A, Vector2D& a_B); //�۷ι� �Լ�, ������ ���̰��� ���ϴ� �Լ� ����
