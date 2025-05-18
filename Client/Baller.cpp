#include "Baller.h"

#include "ItemManager.h"
#include "EffectManager.h"
#include "Export_Function.h"

CBaller::CBaller(LPDIRECT3DDEVICE9 pGraphicDev)
	:CEnemy(pGraphicDev), m_fTime(0.f)
{
	Set_ObjTag(Tag());
}

CBaller::~CBaller()
{
}

HRESULT CBaller::Ready_GameObject(const _vec3& vPos)
{
	m_fSpeed = 10.f;
	m_iHp = 3.f;

	m_pTransform->m_vScale = { 1.f, 3.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CBaller::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) 
		return OBJ_DEAD;
	__super::Update_GameObject(fTimeDelta);

	m_fTime += fTimeDelta * 2.f;
	_float fVal = cosf(m_fTime) * 2.f;

	dynamic_cast<CCollider*>(Get_Component(L"BodyCollider", ID_ALL))->
		Set_BoundingBox({ 2.f, 2.f, 2.f }, { 0.f, fVal, 0.f });

	/*cout << fVal << endl;*/
	m_pTransform->m_vInfo[INFO_POS].y = 3.f;
	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return S_OK;
}

void CBaller::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CBaller::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CBaller::SetDead(_bool bDead)
{
	CGameObject::SetDead(bDead);

	if (bDead == true)
	{
		_vec3 pos = m_pTransform->m_vInfo[INFO_POS];	// 출력 위치 변경필
		_vec3 scale = _vec3(1.f, 1.f, 1.f);
		CEffect* effect = CEffectManager::GetInstance()->Pop(m_pGraphicDev, L"Explosion_Texture", pos, scale, 0.1f);
		Add_GameObject(effect);

		_vec3 pSpawnPos = m_pTransform->m_vInfo[INFO_POS];
		pSpawnPos.y += 3.f;
		CItem* item = CItemManager::GetInstance()->Pop(m_pGraphicDev, L"BulletItem", pSpawnPos);
		Add_GameObject(item);
		item = CItemManager::GetInstance()->Pop(m_pGraphicDev, L"CoinItem", pSpawnPos);
		Add_GameObject(item);
	}
}

HRESULT CBaller::Add_Component()
{
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Baller_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Bub_Texture", texture });

	CAnimation* animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(animation, E_FAIL);

	animation->BindAnimation(ANIM_WALK, texture, 0.07f);
	animation->SelectState(ANIM_WALK);
	m_uMapComponent[ID_ALL].insert({ L"Animation", animation });

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({ 2.f, 2.f, 2.f }, { 0.f, -2.f, 0.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 50.f, 10.f, 50.f });
	
	FAILED_CHECK_RETURN(Create_Root_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Set_PatrolAndFollow_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Init_AI_Behaviours(), E_FAIL);

	return S_OK;
}

CBaller * CBaller::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos)
{
	CBaller* pInstance = new CBaller(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CGameObject * CBaller::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBaller* pInstance = new CBaller(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(_vec3{})))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBaller::Free(void)
{
	__super::Free();
}
