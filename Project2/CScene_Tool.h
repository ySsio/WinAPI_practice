#pragma once
#include "CScene.h"

class CUI;

class CScene_Tool :
	public CScene
{
private:
	CUI*	m_pUI;

public:
	void Enter() override;
	void Exit() override;
	void update() override;

public:
	void SetTileIdx();
	void SaveTileData();	// ���� ������ ��θ� ���� (�����츦 �����)
	void SaveTile(const wstring& _strFilePath);
	void LoadTileData();
	
	

public:
	CScene_Tool();
	~CScene_Tool();
};

