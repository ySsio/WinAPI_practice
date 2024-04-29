#pragma once
#include "CState.h"
class CTraceState :
    public CState
{
private:


public:
	virtual void update() override;
	virtual void Enter() override;
	virtual void Exit() override;

public:
	CTraceState();
	~CTraceState();
};

