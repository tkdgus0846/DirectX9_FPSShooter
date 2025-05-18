#include "Cryder.h"

#include "Export_Function.h"

CCryder::CCryder(LPDIRECT3DDEVICE9 pGraphicDev)
	:CEnemy(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CCryder::~CCryder()
{
}

HRESULT CCryder::Ready_GameObject(const _vec3 & vPos)
{
	m_fSpeed = 10.f;
	m_iAttack = 1;
	m_iHp = 2;

	m_pTransform->m_vScale = { 0.7f, 0.7f, 0.7f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->m_vInfo[INFO_POS].y += 2.f;
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CCryder::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) return OBJ_DEAD;
	__super::Update_GameObject(fTimeDelta);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CCryder::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CCryder::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

HRESULT CCryder::Add_Component()
{
	CAnimation* animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(animation, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Animation", animation });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Cryder_Walk_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Cryder_Walk_Texture", texture });
	animation->BindAnimation(ANIM_WALK, texture, 0.3f);
	animation->SelectState(ANIM_WALK);

	texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Cryder_Stay_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Cryder_Stay_Texture", texture });
	animation->BindAnimation(ANIM_IDLE, texture, 0.1f);

	texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Cryder_Jump_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Cryder_Jump_Texture", texture });
	animation->BindAnimation(ANIM_JUMP, texture, 0.5f);

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({ 1.4f, 1.4f, 1.4f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 50.f, 10.f, 50.f });

	FAILED_CHECK_RETURN(Create_Root_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Set_PAF_LeapJumpAI(), E_FAIL);
	FAILED_CHECK_RETURN(Init_AI_Behaviours(), E_FAIL);

	return S_OK;
}

CCryder * CCryder::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CCryder* pInstance = new CCryder(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CGameObject * CCryder::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCryder* pInstance = new CCryder(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(_vec3{})))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CCryder::Free(void)
{
	__super::Free();
}
