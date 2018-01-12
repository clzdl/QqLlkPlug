#include "stdafx.h"
#include "GameData.h"

CBeePoint::CBeePoint(POINT point, byte value)
:m_x(point.x),
 m_y(point.y),
 m_value(value)
{
	
}

CBeePoint::CBeePoint(int x, int y)
:m_x(x),
 m_y(y),
 m_value(0x00)
{

}
bool CBeePoint::IsSamePoint(const CBeePoint &p2)
{
	if (m_x == p2.m_x && m_y == p2.m_y)
		return true;

	return false;
}


CBeeLine::CBeeLine(DirectionType direction)
:m_directionType(direction),
 m_start(-1,-1),
 m_end(-1,-1)
{
}

bool CBeeLine::IsCoincide(CBeeLine &othLine)
{
	if (m_directionType != othLine.m_directionType)
		return false;

	///µ•µ„≈–∂œ
	if (m_start.IsSamePoint(m_end) || othLine.m_start.IsSamePoint(othLine.m_end))
	{
		switch (m_directionType)
		{
		case horizontal:
			if (m_start.m_y == othLine.m_start.m_y && (m_start.m_x +1 == othLine.m_start.m_x || othLine.m_end.m_x + 1 == m_start.m_x))
				return true;
			break;
		case vertical:
			if (m_start.m_x == othLine.m_start.m_x && (m_start.m_y + 1 == othLine.m_start.m_y || othLine.m_end.m_y + 1 == m_start.m_y))
				return true;
			break;
		}
	}


	if (m_start.m_x == othLine.m_start.m_x && m_start.m_y == othLine.m_start.m_y
		&& m_end.m_x == othLine.m_end.m_x && m_end.m_y == othLine.m_end.m_y)
		return true;

	return false;
}

bool CBeeLine::IsVerticalIntersect(CBeeLine &othLine)
{

	if (m_directionType == othLine.m_directionType)
		return false;
	
	if (m_directionType == horizontal)
	{
		if (m_start.m_x <= othLine.m_start.m_x && m_end.m_x >= othLine.m_start.m_x  &&
			m_start.m_y >= othLine.m_start.m_y && m_start.m_y <= othLine.m_end.m_y)
			return true;
	}
	else
	{
		if (othLine.m_start.m_x <= m_start.m_x && othLine.m_end.m_x >= m_start.m_x  &&
			othLine.m_start.m_y >= m_start.m_y && othLine.m_start.m_y <= m_end.m_y)
			return true;

	}

	return false;
}

bool CBeeLine::IsParallelIntersect(CBeeLine &othLine)
{
	if (m_directionType != othLine.m_directionType)
		return false;

	if (m_directionType == horizontal)
	{
		if ((m_end.m_x >= othLine.m_start.m_x && m_end.m_x <= othLine.m_end.m_x) ||
			(othLine.m_end.m_x >= m_start.m_x && othLine.m_end.m_x <= m_end.m_x))
			return true;
	}
	else
	{
		if ((m_end.m_y >= othLine.m_start.m_y && m_end.m_y <= othLine.m_end.m_y) ||
			(othLine.m_end.m_y >= m_start.m_y && othLine.m_end.m_y <= m_end.m_y))
			return true;
	}

	return false;
}