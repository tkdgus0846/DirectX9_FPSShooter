#include "WalkerBoss.h"

#include "ItemManager.h"
#include "EffectManager.h"
#include "Export_Function.h"
#include "..\Engine\SoundMgr.h"
#include "DiscItem.h"

CWalkerBoss::CWalkerBoss(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
	Set_LayerID(LAYER_BOSS);
	Set_ObjTag(L"WalkerBoss");
}

CWalkerBoss::~CWalkerBoss()
{
}

HRESULT CWalkerBoss::Ready_GameObject(const _vec3 & vPos)
{
	m_fSpeed = 20.f;
	m_iAttack = 1;
	m_iHp = 200;
	m_iMaxHp = 200;

	m_pTransform->m_vScale = { 3.f, 3.f, 3.f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	m_fCurTime1 = Get_WorldTime();
	m_fPreTime1 = Get_WorldTime();

	m_bCutScene = true;

	HRESULT result = __super::Ready_GameObject();

	Get_BlackBoard()->Add_Type(L"bCutScene", m_bCutScene);
	m_pShadow->Set_RenderFlag();

	return result;
}

_int CWalkerBoss::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead() && Dead_Production())
		return OBJ_DEAD;
	else if(!GetDead())
		m_fPreTime1 = Get_WorldTime();

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	__super::Update_GameObject(fTimeDelta);

	return OBJ_NOEVENT;
}

void CWalkerBoss::LateUpdate_GameObject(void)
{
	if (GetDead())
		return;

	__super::LateUpdate_GameObject();
}

void CWalkerBoss::Render_GameObject(void)
{
	static _float fCurTime = 0.f, fPreTime = 0.f;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();

	_vec3 vPos = m_pTransform->m_vInfo[INFO_POS];
	_matrix matWorld, matScale, matRot, matTrans;
	matWorld.Identity();
	
	_float fScale = vPos.y / 2.3;

	if (fScale < 3.f)
		fScale = 3.f;
	else if (fScale > 80.f)
	{
		fCurTime = Get_WorldTime();
		if (fCurTime - fPreTime > 4.2f)
			fScale -= (fCurTime - fPreTime) * 5.5f;
	}
	else
		fPreTime = Get_WorldTime();

	D3DXMatrixScaling(&matScale, fScale, fScale, fScale);

	D3DXMatrixRotationX(&matRot, D3DXToRadian(90.f));

	D3DXMatrixTranslation(&matTrans, vPos.x, 0.1f, vPos.z);

	matWorld = matScale * matRot * matTrans;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pTextureCom->Render_Component();
	m_pShadow->Render_Component();
}

_bool CWalkerBoss::Dead_Production()
{
	static _float fDest = 0.2f;
	m_fCurTime1 = Get_WorldTime();

	Engine::Shake_Camera(SHAKE_LR, 2.f, 3.4f);
	if (m_fCurTime1 - m_fPreTime1 < 3.5f)
	{
		STOP_ALL_BGM;
		_vec3 vEPos{};
		GetRandomVector(&vEPos, &_vec3(-3.f, -3.f, -3.f), &_vec3(3.f, 3.f, 3.f));
		_vec3 vPos = m_pTransform->m_vInfo[INFO_POS] + vEPos;
		GetRandomVector(&vEPos, &_vec3(1.f, 1.f, 1.f), &_vec3(1.7f, 1.7f, 1.7f));

		CEffect* pEffect = CEffectManager::GetInstance()->Pop(m_pGraphicDev, L"Explosion_Texture", vPos, vEPos, 0.1f);
		Add_GameObject(pEffect);

		if (m_fCurTime1 - m_fPreTime1 > fDest)
		{
			STOP_PLAY_SOUND(L"sfxExplode.wav", SOUND_ENEMY, 1.f);
			_vec3 pSpawnPos = m_pTransform->m_vInfo[INFO_POS];
			pSpawnPos.y += 3.f;
			CItem* item = CItemManager::GetInstance()->Pop(m_pGraphicDev, L"BulletItem", pSpawnPos);
			Add_GameObject(item);
			item = CItemManager::GetInstance()->Pop(m_pGraphicDev, L"CoinItem", pSpawnPos);
			Add_GameObject(item);
			fDest += 0.2f;
		}
		return false;
	}

	CDiscItem* discItem = CDiscItem::Create(m_pGraphicDev);
	Add_GameObject(discItem);

	__super::SetDead(true);
	return true;
}

HRESULT CWalkerBoss::Add_Component()
{
	CTexture* pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WalkerBoss_Walk_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WalkerBoss_Walk_Texture", pTexture);
	
	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"BossShadow_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"BossShadow_Texture", pTexture);

	CAnimation* pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(pAnimation, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"Animation", pAnimation);

	pAnimation->BindAnimation(ANIM_WALK, pTexture, 0.3f);
	pAnimation->SelectState(ANIM_WALK);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WalkerBoss_Idle_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WalkerBoss_Idle_Texture", pTexture);
	pAnimation->BindAnimation(ANIM_IDLE, pTexture, 0.3f);

	CRcTex* pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].emplace(L"RcTex", pBufferCom);

	m_pShadow = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_pShadow, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"RcTexShadow", m_pShadow);

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"BodyCollider", pCollider);
	pCollider->Set_BoundingBox({ 6.f, 6.f, 6.f });

	FAILED_CHECK_RETURN(Create_Root_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Set_Boss2_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Init_AI_Behaviours(), E_FAIL);

	return S_OK;
}

CWalkerBoss * CWalkerBoss::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CWalkerBoss* pInstance = new CWalkerBoss(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CWalkerBoss::Free(void)
{
	__super::Free();
}