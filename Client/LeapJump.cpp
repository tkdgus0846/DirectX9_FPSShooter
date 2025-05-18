#include "LeapJump.h"

#include "Export_Function.h"

CLeapJump::CLeapJump(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev), m_fTime(0.f),
	m_fInit(0.f), m_fForce(0.f)
{
}

CLeapJump::CLeapJump(const CLeapJump & rhs)
	: CBehavior(rhs), m_fTime(rhs.m_fTime),
	m_fInit(rhs.m_fInit), m_fForce(rhs.m_fForce)
{
}

CLeapJump::~CLeapJump()
{
}

HRESULT CLeapJump::Ready_Behavior()
{
	m_fInit = m_pGameObject->m_pTransform->m_vScale.y;

	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CLeapJump::Update_Component(const _float & fTimeDelta)
{
	m_fCurTime = Get_WorldTime();

	if (m_fCurTime - m_fPreTime < m_fTimer)
		return BEHAVIOR_FAIL;

	CAnimation* pAnimation = dynamic_cast<CAnimation*>(m_pGameObject->Get_Component(L"Animation", ID_ALL));
	if(pAnimation)
		pAnimation->SelectState(ANIM_JUMP);

	_float fSpeed = 0.f;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", fSpeed), BEHAVIOR_ERROR);

	m_fTime += fTimeDelta * 7.f;

	_float fY = m_fForce * m_fTime - 3.2f * m_fTime * m_fTime;

	m_pGameObject->m_pTransform->Move_Walk(fSpeed * 2.f, fTimeDelta);

	m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y += fY / 8.f;

	if (m_fInit > m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y)
	{
		m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y = m_fInit;
		m_fPreTime = m_fCurTime;
		m_fTime = 0.f;

		return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_RUNNING;
}

void CLeapJump::Render_Component(void)
{
	__super::Render_Component();
}

CLeapJump * CLeapJump::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLeapJump* pInstance = new CLeapJump(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CLeapJump::Clone(void)
{
	return new CLeapJump(*this);
}

void CLeapJump::Free()
{
	__super::Free();
}
