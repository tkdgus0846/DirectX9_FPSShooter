#include "BigJump.h"

#include "Export_Function.h"
#include "..\Engine\SoundMgr.h"

CBigJump::CBigJump(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev), m_bStop(false)
	, m_fTime(0.f), m_fForce(0.f), m_fInit(0.f)
	, m_bSetStop(false), m_bJump(true)
{
}

CBigJump::CBigJump(const CBigJump & rhs)
	: CBehavior(rhs), m_bStop(rhs.m_bStop)
	, m_fTime(rhs.m_fTime), m_fForce(rhs.m_fForce), m_fInit(rhs.m_fInit)
	, m_bSetStop(rhs.m_bSetStop), m_bJump(rhs.m_bJump)
{
}

CBigJump::~CBigJump()
{
}

HRESULT CBigJump::Ready_Behavior()
{
	m_fInit = m_pGameObject->m_pTransform->m_vScale.y;

	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CBigJump::Update_Component(const _float & fTimeDelta)
{
	CAnimation* pAnimation = dynamic_cast<CAnimation*>(m_pGameObject->Get_Component(L"Animation", ID_ALL));
	if (pAnimation)
		pAnimation->SelectState(ANIM_JUMP);

	if(m_bJump)
		m_fTime += fTimeDelta * 7.f;
	
	_float fY = m_fForce * m_fTime - 3.2f * m_fTime * m_fTime;

	if (fY < 0 && m_bStop)
	{
		m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y = 220.f;
		m_pGameObject->m_pTransform->Set_MoveType(CTransform::AIRCRAFT);
		m_fCurTime = Get_WorldTime();

		if (m_bJump)
		{
			m_bJump = false;
			return BEHAVIOR_SUCCES;
		}

		if (m_fCurTime - m_fPreTime >= m_fTimer)
		{
			m_pGameObject->m_pTransform->Set_MoveType(CTransform::LANDOBJECT);
			m_pGameObject->m_pTransform->Set_Dir(_vec3(1.f, 0.f, 0.f));
			m_bJump = true;
			m_bStop = false;
		}
	}
	else
		m_fPreTime = Get_WorldTime();

	if(m_bJump)
		m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y += fY / 8.f;

	if (m_fInit > m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y)
	{
		m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y = m_fInit;
		m_fPreTime = m_fCurTime;
		m_fTime = 0.f;
		m_bStop = m_bSetStop;
		Shake_Camera(SHAKE_Y, 3.f, 4.f);
		STOP_PLAY_SOUND(L"sfxvanquish.wav", SOUND_ENEMY, 1.f);
		return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_RUNNING;
}

void CBigJump::Render_Component(void)
{
	__super::Render_Component();
}

CBigJump * CBigJump::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBigJump* pInstance = new CBigJump(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CBigJump::Clone(void)
{
	return new CBigJump(*this);
}

void CBigJump::Free()
{
	__super::Free();
}
