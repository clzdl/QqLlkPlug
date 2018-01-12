#pragma once
#include "stdafx.h"
enum DirectionType
{
	horizontal,   //ˮƽ
	vertical,   //��ֱ
};

class CBeePoint
{
public:
	CBeePoint(POINT point, byte value);
	CBeePoint(int x, int y);
	bool IsSamePoint(const CBeePoint &p2);
	

	int m_x;
	int m_y;
	byte m_value;

};

class CBeeLine
{
public:
	CBeeLine(DirectionType direction);
	//�ж��Ƿ�ֱ�ཻ
	bool IsVerticalIntersect(CBeeLine &othLine);

	//�ж��Ƿ�ƽ���ཻ
	bool IsParallelIntersect(CBeeLine &othLine);
	
	//�ж��Ƿ��غ�
	bool IsCoincide(CBeeLine &othLine);
	
	CBeePoint m_start;
	CBeePoint m_end;
	DirectionType m_directionType;
};
