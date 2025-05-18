#pragma once
#include "include.h"

class CCalculator
{
public:
	CCalculator();
	~CCalculator();

	static _float	DistanceToPlayer(_vec3 pPos);
	static _float	CalculateFOV(LPDIRECT3DDEVICE9 pGraphicDevice);

};