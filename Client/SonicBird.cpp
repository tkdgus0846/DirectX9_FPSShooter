#include "SonicBird.h"
#include "Export_Function.h"
#include "BulletMgr.h"

CSonicBird::CSonicBird(LPDIRECT3DDEVICE9 pGraphicDev) :
	CBullet(pGraphicDev)
{
	Set_ObjTag(L"SonicBird");
}

CSonicBird::~CSonicBird()
{
}

_int CSonicBird::Update_GameObject(const _float & fTimeDelta)
{
	if (m_pTransform->m_vInfo[INFO_POS].x < -50.f)
		SetDead();

	if (GetDead()) return OBJ_RETPOOL;

	m_pTransform->m_vInfo[INFO_POS].x -= m_fSpeed * 14.f * fTimeDelta;

	
	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);
	Add_RenderGroup(RENDER_ALPHA, this);
	__super::Update_GameObject(fTimeDelta);
	return OBJ_NOEVENT;
}

void CSonicBird::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSonicBird::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_ViewMat);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_Projmat);

	__super::Render_GameObject();
}

void CSonicBird::SetDead(_bool bDead /*= true*/)
{
	__super::SetDead(bDead);
	if (GetDead())
		CBulletMgr::GetInstance()->Push(L"SonicBird", this);
}

HRESULT CSonicBird::Add_Component()
{
	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMYBULLET));
	NULL_CHECK_RETURN(pCollider);
	m_uMapComponent[ID_ALL].emplace(L"BodyCollider", pCollider);
	pCollider->Set_BoundingBox({ 6.f,6.f,10.f });

	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Bird_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Bird_Texture", Texture });

	CAnimation* ani = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(ani, E_FAIL);

	ani->BindAnimation(ANIM_WALK, Texture, 0.1f);
	ani->SelectState(ANIM_WALK);

	m_uMapComponent[ID_ALL].insert({ L"Animation", ani });

	m_ViewMat.Identity();
	D3DXMatrixPerspectiveFovLH(&m_Projmat, D3DXToRadian(60.f), ((_float)WINCX / WINCY), 0.f, 1000.f);
	m_pTransform->Set_Scale({ 5.f,5.f,1.f });

	return S_OK;
}

CSonicBird * CSonicBird::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& pos)
{
	CSonicBird*		pInstance = new CSonicBird(pGraphicDev);
	pInstance->Set_Pos(pos);
	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CSonicBird* CSonicBird::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSonicBird*		pInstance = new CSonicBird(pGraphicDev);
	
	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
