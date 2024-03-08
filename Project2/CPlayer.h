#pragma once
#include "CObject.h"

class CPlayer :
    public CObject
{

public:
    void CreateMissile();

public :
    void update() override;
};

