#include "LookAtTarget.h"

#include "Export_Function.h"

CLookAtTarget::CLookAtTarget(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CLookAtTarget::CLookAtTarget(const CLookAtTarget & rhs)
	: CBehavior(rhs)
{
}

CLookAtTarget::~CLookAtTarget()
{
}

HRESULT CLookAtTarget::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CLookAtTarget::Update_Component(const _float & fTimeDelta)
{
	if(Get_Player())
		m_pGameObject->m_pTransform->Set_Target(Get_Player()->m_pTransform->m_vInfo[INFO_POS]);

	return BEHAVIOR_SUCCES;
}

void CLookAtTarget::Render_Component(void)
{
}

CComponent * CLookAtTarget::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLookAtTarget* pInstance = new CLookAtTarget(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CLookAtTarget::Clone(void)
{
	return new CLookAtTarget(*this);
}

void CLookAtTarget::Free()
{
	__super::Free();
}
