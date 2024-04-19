#pragma once

class CMonster;

enum class MON_TYPE
{
	NORMAL,
	RANGER,
};

class CMonFactory
{
public:
	static CMonster* CreatMonster(MON_TYPE _eType, Vec2 _vPos);



public:
	CMonFactory() = delete;
	~CMonFactory() = delete;
};

