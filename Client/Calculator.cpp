#include "Calculator.h"
#include "Export_Function.h"
#include "Player.h"

CCalculator::CCalculator()
{
}


CCalculator::~CCalculator()
{
}

_float CCalculator::DistanceToPlayer(_vec3 pPos)
{
	if (Engine::Get_Player() == nullptr) { return 0; }
	_vec3 PlayerPos = dynamic_cast<CPlayer*>(Engine::Get_Player())->m_pTransform->m_vInfo[INFO_POS];

	_vec3 vLength = PlayerPos - pPos;
	_float fLength = D3DXVec3Length(&vLength);

	return fLength;
}

_float CCalculator::CalculateFOV(LPDIRECT3DDEVICE9 pGraphicDevice)
{
	D3DVIEWPORT9 Viewport;
	pGraphicDevice->GetViewport(&Viewport);

	_float fFovY = D3DXToRadian(60.f); // 수직 시야각
	_float fAspect = static_cast<_float>(Viewport.Width) / static_cast<_float>(Viewport.Height);

	_float fFovX = 2.f * atanf(tanf(fFovY * 0.5f) * fAspect); // 수평 시야각

	return fFovX;
}