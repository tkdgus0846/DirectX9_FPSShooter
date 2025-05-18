#include "WormHead.h"

#include "WormBody.h"
#include "WormTail.h"
#include "EffectManager.h"
#include "ItemManager.h"
#include "Export_Function.h"
#include "..\Engine\SoundMgr.h"
#include "DiscItem.h"

CWormHead::CWormHead(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev), m_bMove(true), m_pTail(nullptr)
	, m_fCurAngle(0.f), m_fPreAngle(0.f), m_fCurTime1(0.f), m_fPreTime1(0.f)
{
	Set_LayerID(LAYER_BOSS);
	Set_ObjTag(L"WormHead");
}

CWormHead::~CWormHead()
{
}

HRESULT CWormHead::Ready_GameObject(const _vec3 & vPos)
{
	m_fSpeed = 9.f;
	m_iAttack = 1;
	m_iHp = 0;

	m_pTransform->m_vScale = { 1.5f, 1.5f, 1.5f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;

	m_pTransform->Set_MoveType(CTransform::AIRCRAFT);
	_vec3 vBodyPos = m_pTransform->m_vInfo[INFO_POS];

	m_fCurTime1 = Get_WorldTime();
	m_fPreTime1 = Get_WorldTime();
	m_fCurTime2 = Get_WorldTime();
	m_fPreTime2 = Get_WorldTime();

	for (_int i = 0; i < 10; ++i)
		m_vecBody.push_back(dynamic_cast<CWormBody*>(CWormBody::Create(m_pGraphicDev, _vec3(vBodyPos.x + i + 1.f, vBodyPos.y, vBodyPos.z + i + 1.f))));
		

	for (auto iter : m_vecBody)
	{
		Add_Static_GameObject(iter); 
		m_iHp += iter->Get_HP();
	}

	m_pTransform->Set_BillMode(true);
	m_pTransform->Rot_Bill(0.01f);

	m_pTail = dynamic_cast<CWormTail*>(CWormTail::Create(m_pGraphicDev, _vec3(vBodyPos.x + 13.f, vBodyPos.y, vBodyPos.z + 13.f)));

	Add_Static_GameObject(m_pTail);
	m_iHp += m_pTail->Get_HP() + 50;
	m_iMaxHp = m_iHp;

	_int iSize = m_vecBody.size();

	m_vecBody[0]->Chain_Head(this);
	m_vecBody[0]->Set_Dest(m_pTransform->m_vInfo[INFO_POS]);
	m_vecBody[0]->Chain_Back(m_vecBody[1]);
	for (_int i = 1; i < iSize - 1; ++i)
	{
		m_vecBody[i]->Chain_Head(this);
		m_vecBody[i]->Chain_Back(m_vecBody[i + 1]);
		m_vecBody[i]->Chain_Front(m_vecBody[i - 1]);
		m_vecBody[i]->Set_Dest(m_vecBody[i - 1]->m_pTransform->m_vInfo[INFO_POS]);
	}
	m_vecBody[iSize - 1]->Chain_Head(this);
	m_vecBody[iSize - 1]->Chain_Front(m_vecBody[iSize - 2]);
	m_vecBody[iSize - 1]->Set_Dest(m_vecBody[iSize - 2]->m_pTransform->m_vInfo[INFO_POS]);
	m_vecBody[iSize - 1]->Chain_Tail(m_pTail);

	m_pTail->Chain_Head(this);
	m_pTail->Chain_Front(m_vecBody[iSize - 1]);
	m_pTail->Set_Dest(m_vecBody[iSize - 1]->m_pTransform->m_vInfo[INFO_POS]);
	HRESULT result = __super::Ready_GameObject();

	static _int iIndexX = _int(m_pTransform->m_vInfo[INFO_POS].x / 60.f);
	static _int iIndexZ = _int(m_pTransform->m_vInfo[INFO_POS].z / 60.f);

	Get_BlackBoard()->Add_Type(L"iIndexX", iIndexX);
	Get_BlackBoard()->Add_Type(L"iIndexZ", iIndexZ);

	m_bCutScene = true;

	Get_BlackBoard()->Add_Type(L"bCutScene", m_bCutScene);
	return result;
}

_int CWormHead::Update_GameObject(const _float & fTimeDelta)
{
	if (!Get_Player())
		return OBJ_NOEVENT;

	if (GetDead() && Dead_Production())
		return OBJ_DEAD;
	else if (!GetDead())
		m_fPreTime2 = Get_WorldTime();

	__super::Update_GameObject(fTimeDelta);

	if(m_bMove)
		m_pTransform->Move_Walk(m_fSpeed, fTimeDelta);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CWormHead::LateUpdate_GameObject(void)
{
	if (GetDead())
		return;

	if (!Get_Player())
		return;

	m_fCurTime1 = Get_WorldTime();

	_vec3 vLook = m_pTransform->m_vInfo[INFO_LOOK];
	_vec3 vLookXZ = { vLook.x, 0.f, vLook.z };
	vLook.Normalize();
	vLookXZ.Normalize();
	m_fCurAngle = vLook.Dot(vLookXZ);

	_float fResult = 0.f;

	if (m_fCurTime1 - m_fPreTime1 > 0.1f)
	{
		fResult = m_fCurAngle - m_fPreAngle;
		m_fPreAngle = m_fCurAngle;
		m_fPreTime1 = m_fCurTime1;
	}

	if (!isnan(m_fCurAngle) && fResult != 0)
	{
		if (fResult > 0)
			m_pTransform->Rot_Bill(-D3DXToDegree(acosf(m_fCurAngle)));
		else
			m_pTransform->Rot_Bill(D3DXToDegree(acosf(m_fCurAngle)));
	}

	m_pTransform->m_vScale.x = 1.5f;

	_vec3 vPos = Get_Player()->m_pTransform->m_vInfo[INFO_POS];
	_vec3 vDir = vPos - m_pTransform->m_vInfo[INFO_POS];
	vDir.Normalize();

	_float fAngleRight = vDir.Degree(m_pTransform->m_vInfo[INFO_RIGHT]);
	_float fAngleUp = vDir.Degree(m_pTransform->m_vInfo[INFO_UP]);
	_float fAngleLook = vDir.Degree(m_pTransform->m_vInfo[INFO_LOOK]);

	if (isnan(fAngleLook))
		return;

	if (fAngleRight < 45.f)
		m_pAnimation->SelectState(ANIM_SIDE);
	else if (fAngleUp < 45.f)
	{
		m_pTransform->Rot_Bill(90.f);
		m_pAnimation->SelectState(ANIM_TOP);
	}
	else if (fAngleLook < 45.f)
		m_pAnimation->SelectState(ANIM_FACE);

	else if (fAngleRight > 135.f)
	{
		if (!isnan(m_fCurAngle) && fResult != 0)
		{
			if (fResult > 0)
				m_pTransform->Rot_Bill(D3DXToDegree(acosf(m_fCurAngle)));
			else
				m_pTransform->Rot_Bill(-D3DXToDegree(acosf(m_fCurAngle)));
		}
		m_pTransform->m_vScale.x = -1.5f;
		m_pAnimation->SelectState(ANIM_SIDE);
	}
	else if (fAngleLook > 135.f)
	{
		m_pTransform->m_vScale.x = -1.5f;
		m_pAnimation->SelectState(ANIM_BACK);
	}

	else if (fAngleUp < 135.f)
	{
		m_pTransform->Rot_Bill(90.f);
		m_pAnimation->SelectState(ANIM_TOP);
	}
	else
		m_pAnimation->SelectState(ANIM_FACE);

	__super::LateUpdate_GameObject();
}

void CWormHead::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

_bool CWormHead::Dead_Production()
{
	m_fSpeed = 0.f;
	static _float fDest = 0.2f;
	m_fCurTime2 = Get_WorldTime();

	Engine::Shake_Camera(SHAKE_LR, 2.f, 3.4f);
	if (m_fCurTime2 - m_fPreTime2 < 3.5f)
	{
		STOP_ALL_BGM;
		_vec3 vEPos{};
		GetRandomVector(&vEPos, &_vec3(-3.f, -3.f, -3.f), &_vec3(3.f, 3.f, 3.f));
		_vec3 vPos = m_pTransform->m_vInfo[INFO_POS] + vEPos;
		GetRandomVector(&vEPos, &_vec3(1.f, 1.f, 1.f), &_vec3(1.7f, 1.7f, 1.7f));

		CEffect* pEffect = CEffectManager::GetInstance()->Pop(m_pGraphicDev, L"Explosion_Texture", vPos, vEPos, 0.1f);
		Add_GameObject(pEffect);

		if (m_fCurTime2 - m_fPreTime2 > fDest)
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

HRESULT CWormHead::Add_Component()
{
	m_pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_pAnimation, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"Animation", m_pAnimation);

	CTexture* pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Drill_Side_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Drill_Side_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_SIDE, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Drill_Top_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Drill_Top_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_TOP, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Drill_Face_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Drill_Face_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_FACE, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Drill_Back_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Drill_Back_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_BACK, pTexture, 0.05f);

	m_pAnimation->SelectState(ANIM_FACE);

	CRcTex* pBufferCom1 = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom1, E_FAIL);
	m_uMapComponent[ID_RENDER].emplace(L"RcTex", pBufferCom1);

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"BodyCollider", pCollider);
	pCollider->Set_BoundingBox({ 2.7f, 2.7f, 2.7f });

	FAILED_CHECK_RETURN(Create_Root_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Set_Boss3_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Init_AI_Behaviours(), E_FAIL);

	return S_OK;
}

CWormHead * CWormHead::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CWormHead* pInstance = new CWormHead(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CWormHead::Free(void)
{
	__super::Free();
}
