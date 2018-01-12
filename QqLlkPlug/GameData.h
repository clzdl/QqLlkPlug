#pragma once
#include "stdafx.h"
enum DirectionType
{
	horizontal,   //水平
	vertical,   //垂直
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
	//判断是否垂直相交
	bool IsVerticalIntersect(CBeeLine &othLine);

	//判断是否平行相交
	bool IsParallelIntersect(CBeeLine &othLine);
	
	//判断是否重合
	bool IsCoincide(CBeeLine &othLine);
	
	CBeePoint m_start;
	CBeePoint m_end;
	DirectionType m_directionType;
};
