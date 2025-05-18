#include "WormMoveCtrl.h"

#include "Export_Function.h"
#include "WormHead.h"

CWormMoveCtrl::CWormMoveCtrl(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CWormMoveCtrl::CWormMoveCtrl(const CWormMoveCtrl & rhs)
	: CBehavior(rhs)
{
}

CWormMoveCtrl::~CWormMoveCtrl()
{
}

HRESULT CWormMoveCtrl::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();
	
	return result;
}

_int CWormMoveCtrl::Update_Component(const _float & fTimeDelta)
{
	if (m_bStart)
		dynamic_cast<CWormHead*>(m_pGameObject)->Set_Move(true);
	else
		dynamic_cast<CWormHead*>(m_pGameObject)->Set_Move(false);

	return BEHAVIOR_SUCCES;
}

CWormMoveCtrl * CWormMoveCtrl::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWormMoveCtrl* pInstance = new CWormMoveCtrl(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CWormMoveCtrl::Clone(void)
{
	return new CWormMoveCtrl(*this);
}

void CWormMoveCtrl::Free()
{
	__super::Free();
}
