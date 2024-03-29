#pragma once
#include "CScene.h"

class CScene_Tool :
	public CScene
{
private:

public:
	void Enter() override;
	void Exit() override;
	void update() override;

public:
	void SetTileIdx();

public:
	CScene_Tool();
	~CScene_Tool();
};

