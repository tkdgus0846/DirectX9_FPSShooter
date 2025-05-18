#include "WormTail.h"

#include "WormHead.h"
#include "WormBody.h"
#include "EffectManager.h"
#include "ItemManager.h"
#include "Export_Function.h"

CWormTail::CWormTail(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev), m_pFrontBody(nullptr), m_bMove(false), m_pHead(nullptr)
	, m_fCurAngle(0.f), m_fPreAngle(0.f), m_fCurTime1(0.f), m_fPreTime1(0.f)
{
	ZeroMemory(m_vDest, sizeof(_vec3));
}

CWormTail::~CWormTail()
{
}

HRESULT CWormTail::Ready_GameObject(const _vec3 & vPos)
{
	m_fSpeed = 9.f;
	m_iAttack = 1;
	m_iHp = 20;
	m_iMaxHp = 20;

	m_pTransform->m_vScale = { 1.5f, 1.5f, 1.5f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::AIRCRAFT);

	m_pTransform->Set_BillMode(true);
	m_pTransform->Rot_Bill(0.01f);

	m_fCurTime1 = Get_WorldTime();
	m_fPreTime1 = Get_WorldTime();
	m_fCurTime2 = Get_WorldTime();
	m_fPreTime2 = Get_WorldTime();

	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CWormTail::Update_GameObject(const _float & fTimeDelta)
{
	if (nullptr == Get_Player())
		return OBJ_NOEVENT;

	__super::Update_GameObject(fTimeDelta);

	if (m_iHp != m_iMaxHp)
	{
		m_pHead->Get_Damaged(m_iMaxHp - m_iHp);
		m_iMaxHp = m_iHp;
	}

	if (GetDead() && Dead_Production())
		return OBJ_DEAD;
	else if (!GetDead())
		m_fPreTime2 = Get_WorldTime();

	m_fSpeed = m_pHead->Get_Speed();
	if (m_pHead->Get_Move() != m_bMove)
		m_bMove = m_pHead->Get_Move();

	if (m_bMove)
		Move(fTimeDelta);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CWormTail::LateUpdate_GameObject(void)
{

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

void CWormTail::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

_bool CWormTail::Dead_Production()
{
	static _float fDest = 0.3f;
	m_fCurTime2 = Get_WorldTime();
	if (m_fCurTime2 - m_fPreTime2 < 1.f)
	{
		_vec3 vEPos{};
		GetRandomVector(&vEPos, &_vec3(-3.f, -3.f, -3.f), &_vec3(3.f, 3.f, 3.f));
		_vec3 vPos = m_pTransform->m_vInfo[INFO_POS] + vEPos;
		GetRandomVector(&vEPos, &_vec3(1.f, 1.f, 1.f), &_vec3(1.7f, 1.7f, 1.7f));

		CEffect* pEffect = CEffectManager::GetInstance()->Pop(m_pGraphicDev, L"Explosion_Texture", vPos, vEPos, 0.1f);
		Add_GameObject(pEffect);

		if (m_fCurTime2 - m_fPreTime2 > fDest)
		{
			_vec3 pSpawnPos = m_pTransform->m_vInfo[INFO_POS];
			pSpawnPos.y += 3.f;
			CItem* item = CItemManager::GetInstance()->Pop(m_pGraphicDev, L"BulletItem", pSpawnPos);
			Add_GameObject(item);
			item = CItemManager::GetInstance()->Pop(m_pGraphicDev, L"CoinItem", pSpawnPos);
			Add_GameObject(item);
			fDest += 0.3f;
		}
		return false;
	}
	__super::SetDead(true);
	return true;
}

HRESULT CWormTail::Add_Component()
{
	m_pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_pAnimation, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"Animation", m_pAnimation);

	CTexture* pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Tail_Side_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Tail_Side_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_SIDE, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Tail_Top_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Tail_Top_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_TOP, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Drill_Back_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Body_Face_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_FACE, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Tail_Back_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Body_Back_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_BACK, pTexture, 0.05f);

	m_pAnimation->SelectState(ANIM_FACE);

	CRcTex* pBufferCom1 = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom1, E_FAIL);
	m_uMapComponent[ID_RENDER].emplace(L"RcTex", pBufferCom1);

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"BodyCollider", pCollider);
	pCollider->Set_BoundingBox({ 2.9f, 2.9f, 2.9f });

	return S_OK;
}

void CWormTail::Move(const _float & fTimeDelta)
{
	_vec3 vPos = m_pTransform->m_vInfo[INFO_POS];
	_vec3 vDir = m_vDest - vPos;
	_float fLength = 0.f;

	if (m_pFrontBody)
	{
		fLength = _vec3(m_pFrontBody->m_pTransform->m_vInfo[INFO_POS] - m_pTransform->m_vInfo[INFO_POS]).Length();
		if (vDir.Length() < 0.5f)
			m_vDest = m_pFrontBody->m_pTransform->m_vInfo[INFO_POS];
	}
	else
	{
		fLength = _vec3(m_pHead->m_pTransform->m_vInfo[INFO_POS] - m_pTransform->m_vInfo[INFO_POS]).Length();
		if (vDir.Length() < 0.5f)
			m_vDest = m_pHead->m_pTransform->m_vInfo[INFO_POS];
	}

	m_pTransform->Set_Target(m_vDest);

	if (fLength < 2.5f)
		m_pTransform->Move_Walk(0.1f, fTimeDelta);
	else if (fLength > 4.f)
		m_pTransform->Move_Walk(m_fSpeed * 1.5f, fTimeDelta);
	else
		m_pTransform->Move_Walk(m_fSpeed, fTimeDelta);
}

CWormTail * CWormTail::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CWormTail* pInstance = new CWormTail(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CWormTail::Free(void)
{
	__super::Free();
}
