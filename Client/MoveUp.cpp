#include "MoveUp.h"

#include "Export_Function.h"

CMoveUp::CMoveUp(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CMoveUp::CMoveUp(const CMoveUp & rhs)
	: CBehavior(rhs)
{
}

CMoveUp::~CMoveUp()
{
}

HRESULT CMoveUp::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CMoveUp::Update_Component(const _float & fTimeDelta)
{
	//cout << m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y << endl;
	_float fY = m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y;
	if (fY <= 4.f)
	{
		m_pGameObject->m_pTransform->Set_MoveType(CTransform::AIRCRAFT);
		m_pGameObject->m_pTransform->Move_Fly(3.f, fTimeDelta);
		Shake_Camera(SHAKE_X);
		return BEHAVIOR_RUNNING;
	}
	m_pGameObject->m_pTransform->Set_MoveType(CTransform::LANDOBJECT);
	dynamic_cast<CCollider*>(m_pGameObject->Get_Component(L"BodyCollider", ID_ALL))->Set_Enable(true);
	return BEHAVIOR_SUCCES;
}

void CMoveUp::LateUpdate_Component(void)
{
	__super::LateUpdate_Component();
}

CMoveUp * CMoveUp::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMoveUp* pInstance = new CMoveUp(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CMoveUp::Clone(void)
{
	return new CMoveUp(*this);
}

void CMoveUp::Free()
{
	__super::Free();
}
