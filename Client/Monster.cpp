#include "stdafx.h"
#include "Monster.h"

#include "Export_Function.h"
#include "MonoBehaviors.h"
#include "Player.h"
#include "Bullet.h"
#include "EffectManager.h"
#include "..\Engine\SoundMgr.h"
#include "ItemManager.h"
#include "WormHead.h"
#include "WormBody.h"
#include "WormTail.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev) : 
	CCreature(pGraphicDev),
	m_pRoot(nullptr), 
	m_redTexture(false)
{
	Set_LayerID(LAYER_MONSTER);
}

CMonster::~CMonster()
{
}

HRESULT CMonster::Ready_GameObject(void)
{
	
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CMonster::Update_GameObject(const _float& fTimeDelta)
{
	if (GetDead()) 
		return OBJ_DEAD;

	_matrix view;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &view);

	__super::Update_GameObject(fTimeDelta);
	return 0;
}

void CMonster::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CMonster::Render_GameObject(void)
{
	if (m_redTexture)
	{
		m_fCurTime = Get_WorldTime();
		m_pGraphicDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		m_pGraphicDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		m_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

		m_pGraphicDev->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE2X);
		m_pGraphicDev->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		m_pGraphicDev->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);
		m_pGraphicDev->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		m_pGraphicDev->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
		m_pGraphicDev->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
		float sparkleIntensity = 1.0f; // 0.0 (약함) ~ 1.0 (강함)
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA(static_cast<int>(255 * sparkleIntensity), 255, 255, 255));
	}

	__super::Render_GameObject();

	if (m_redTexture)
	{
		m_pGraphicDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		m_pGraphicDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pGraphicDev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		m_pGraphicDev->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);

		if (m_fCurTime - m_fPreTime > m_fDuration)
			m_redTexture = false;
	}
}

void CMonster::OnCollisionEnter(const Collision * collsion)
{
	__super::OnCollisionEnter(collsion);

	CPlayer* player = dynamic_cast<CPlayer*>(collsion->OtherGameObject);

	if (player && collsion->MyCollider == Get_Component(L"BodyCollider", ID_ALL))
		player->Get_Damaged(Get_Attack());
}

void CMonster::OnCollisionStay(const Collision * collision)
{
	if (dynamic_cast<CWormHead*>(collision->OtherGameObject) ||
		dynamic_cast<CWormBody*>(collision->OtherGameObject) ||
		dynamic_cast<CWormTail*>(collision->OtherGameObject))
		return;

	__super::OnCollisionStay(collision);

	if (dynamic_cast<CBullet*>(collision->OtherGameObject) &&
		collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL) &&
		collision->MyCollider == Get_Component(L"BodyCollider", ID_ALL))
	{
		m_redTexture = true;
		m_fCurTime = Get_WorldTime();
		m_fPreTime = Get_WorldTime();
	}
}

void CMonster::OnCollisionExit(const Collision * collision)
{
	__super::OnCollisionExit(collision);
}

void CMonster::SetDead(_bool bDead /*= true*/)
{
	__super::SetDead(bDead);

	if (bDead == true)
	{
		_vec3 pos = m_pTransform->m_vInfo[INFO_POS];
		_vec3 scale = m_pTransform->Get_Scale();
		CEffect* effect = CEffectManager::GetInstance()->Pop(m_pGraphicDev, L"Explosion_Texture", pos, scale, 0.1f);
		Add_GameObject(effect);

		_vec3 pSpawnPos = m_pTransform->m_vInfo[INFO_POS];
		pSpawnPos.y += 3.f;

		_int randNum = rand() % 10;
		
		switch (randNum)
		{
		case 0:
		{
			CItem* item = CItemManager::GetInstance()->Pop(m_pGraphicDev, L"BulletItem", pSpawnPos);
			Add_GameObject(item);

			item = CItemManager::GetInstance()->Pop(m_pGraphicDev, L"HeartItem", pSpawnPos);
			Add_GameObject(item);
			break;
		}
		default:
		{
			CItem* item = CItemManager::GetInstance()->Pop(m_pGraphicDev, L"BulletItem", pSpawnPos);
			Add_GameObject(item);

			item = CItemManager::GetInstance()->Pop(m_pGraphicDev, L"CoinItem", pSpawnPos);
			Add_GameObject(item);
			break;
		}
			
		}
	}
}

void CMonster::Get_Damaged(_int Damage)
{
	if (GetDead()) return;

	m_iHp -= Damage;	
	if (m_iHp <= 0)
	{
		STOP_PLAY_SOUND(L"sfxKill.wav", SOUND_ENEMY, 1.f);
		m_iHp = 0;
		SetDead();
	}
}

HRESULT CMonster::Add_Component(void)
{
	return S_OK;
}

CMonster* CMonster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMonster*		pInstance = new CMonster(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMonster::Free(void)
{
	__super::Free();
}

Engine::CBlackBoard * CMonster::Get_BlackBoard()
{
	return m_pRoot->m_pBlackBoard; 
}

HRESULT CMonster::Create_Root_AI()
{
	m_pRoot = dynamic_cast<CRoot*>(Engine::Clone_Proto(L"Root", this));
	NULL_CHECK_RETURN(m_pRoot, E_FAIL);
	m_uMapComponent[ID_UPDATE].emplace(L"Root", m_pRoot);

	return S_OK;
}

// AI	구현부
CSequence* CMonster::Make_Patrol_AI(const _float& fWaitTime, const _float& fMoveTime)
{
	// 부품 생성
	CSequence* pSQPatrol = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPatrol, nullptr);
	
	CMoveLook* pTaskMovePatrol = dynamic_cast<CMoveLook*>(Engine::Clone_Proto(L"TSK_Move", this));
	NULL_CHECK_RETURN(pTaskMovePatrol, nullptr);
	CRandomLook* pTaskRandomLook = dynamic_cast<CRandomLook*>(Engine::Clone_Proto(L"TSK_RandomLook", this));
	NULL_CHECK_RETURN(pTaskRandomLook, nullptr);
	CWait* pTaskWait = dynamic_cast<CWait*>(Engine::Clone_Proto(L"TSK_Wait", this));
	NULL_CHECK_RETURN(pTaskWait, nullptr);

	CRangeInPlayer* pDecFunc = dynamic_cast<CRangeInPlayer*>(Engine::Clone_Proto(L"DEC_RangeInPlayer", this));
	NULL_CHECK_RETURN(pDecFunc, nullptr);

	// 부품 초기설정
	pTaskWait->Set_Timer(fWaitTime);
	pTaskMovePatrol->Set_Timer(fMoveTime);
	pTaskMovePatrol->Set_Magnifi();
	pTaskRandomLook->Set_IsLook_Aircraft(false);
	pDecFunc->Set_ReturnVal(false);

	// 부품 조립
	FAILED_CHECK_RETURN(pSQPatrol->Add_Component(ID_UPDATE, L"DEC_", pDecFunc), nullptr);
	FAILED_CHECK_RETURN(pSQPatrol->Add_Component(ID_UPDATE, L"TSK_RandomLook", pTaskRandomLook), nullptr);
	FAILED_CHECK_RETURN(pSQPatrol->Add_Component(ID_UPDATE, L"TSK_MovePatrol", pTaskMovePatrol), nullptr);
	FAILED_CHECK_RETURN(pSQPatrol->Add_Component(ID_UPDATE, L"TSK_Wait", pTaskWait), nullptr);

	return pSQPatrol;
}

CSequence* CMonster::Make_Follow_AI(const _float& fTimer, _bool bIsRangeCheck)
{
	// 부품 생성
	CSequence* pSQChase = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQChase, nullptr);

	CMoveLook* pTskMovePlayer = dynamic_cast<CMoveLook*>(Engine::Clone_Proto(L"TSK_Move", this));
	NULL_CHECK_RETURN(pTskMovePlayer, nullptr);
	CLookAtTarget* pTskLookAtTarget = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pTskLookAtTarget, nullptr);

	CRangeInPlayer* pDecIsRangeInPlayer = dynamic_cast<CRangeInPlayer*>(Engine::Clone_Proto(L"DEC_RangeInPlayer", this));
	NULL_CHECK_RETURN(pDecIsRangeInPlayer, nullptr);
	CTimeInLimit* pDecTimeInLimit = dynamic_cast<CTimeInLimit*>(Engine::Clone_Proto(L"DEC_TimeInLimit", this));
	NULL_CHECK_RETURN(pDecTimeInLimit, nullptr);

	// 부품 초기설정
	pDecTimeInLimit->Set_Timer(fTimer);
	pTskMovePlayer->Set_Magnifi(2.f);
	pDecIsRangeInPlayer->Set_ReturnVal(true);

	// 부품 조립
	if (bIsRangeCheck)
	{
		FAILED_CHECK_RETURN(pSQChase->Add_Decorator(pDecIsRangeInPlayer), nullptr);
	}
	else
		Safe_Release(pDecIsRangeInPlayer);

	FAILED_CHECK_RETURN(pSQChase->Add_Component(ID_UPDATE, L"DEC_TimeLimit", pDecTimeInLimit), nullptr);
	FAILED_CHECK_RETURN(pSQChase->Add_Component(ID_UPDATE, L"TSK_LookAtTarget", pTskLookAtTarget), nullptr);
	FAILED_CHECK_RETURN(pSQChase->Add_Component(ID_UPDATE, L"TSK_MovePlayer", pTskMovePlayer), nullptr);

	return pSQChase;
}

CJump* CMonster::Make_JumpAI(const _float& fForce, const _float& fTimer)
{
	// 부품 생성
	CJump* pTskJump = dynamic_cast<CJump*>(Engine::Clone_Proto(L"TSK_Jump", this));
	NULL_CHECK_RETURN(pTskJump, nullptr);

	// 부품 초기설정
	pTskJump->Set_Force(fForce);
	pTskJump->Set_Timer(fTimer);

	// 부품 조립
	return pTskJump;
}

CBigJump * CMonster::Make_BigJumpAI(const _float & fForce, const _float & fTimer)
{
	// 부품 생성
	CBigJump* pTskBigJump = dynamic_cast<CBigJump*>(Engine::Clone_Proto(L"TSK_BigJump", this));
	NULL_CHECK_RETURN(pTskBigJump, nullptr);

	// 부품 초기설정
	pTskBigJump->Set_Force(fForce);
	pTskBigJump->Set_Timer(fTimer);

	return pTskBigJump;
}

CSequence * CMonster::Make_DBJumpAI(const _float& fForce, const _float & fTimer)
{
	// 부품 생성
	CSequence* pSQJump = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQJump, nullptr);

	CJump* pTskJump1 = dynamic_cast<CJump*>(Engine::Clone_Proto(L"TSK_Jump", this));
	NULL_CHECK_RETURN(pTskJump1, nullptr);
	CJump* pTskJump2 = dynamic_cast<CJump*>(Engine::Clone_Proto(L"TSK_Jump", this));
	NULL_CHECK_RETURN(pTskJump2, nullptr);

	// 부품 초기설정
	pTskJump1->Set_Timer(fTimer);
	pTskJump1->Set_Force(fForce);
	pTskJump2->Set_Timer(0.f);
	pTskJump2->Set_Force(fForce);

	// 부품 조립
	FAILED_CHECK_RETURN(pSQJump->Add_Component(ID_UPDATE, L"TSK_BackJump", pTskJump1), nullptr);
	FAILED_CHECK_RETURN(pSQJump->Add_Component(ID_UPDATE, L"TSK_BackJump", pTskJump2), nullptr);

	return pSQJump;
}

CSequence * CMonster::Make_DBBackJumpAI(const _float& fForce, const _float & fTimer)
{
	// 부품 생성
	CSequence* pSQJump = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQJump, nullptr);

	CBackJump* pTskJump1 = dynamic_cast<CBackJump*>(Engine::Clone_Proto(L"TSK_BackJump", this));
	NULL_CHECK_RETURN(pTskJump1, nullptr);
	CBackJump* pTskJump2 = dynamic_cast<CBackJump*>(Engine::Clone_Proto(L"TSK_BackJump", this));
	NULL_CHECK_RETURN(pTskJump2, nullptr);

	// 부품 초기설정
	pTskJump1->Set_Timer(fTimer);
	pTskJump1->Set_Force(fForce);
	pTskJump2->Set_Timer(0.f);
	pTskJump2->Set_Force(fForce);

	// 부품 조립
	FAILED_CHECK_RETURN(pSQJump->Add_Component(ID_UPDATE, L"TSK_Jump", pTskJump1), nullptr);
	FAILED_CHECK_RETURN(pSQJump->Add_Component(ID_UPDATE, L"TSK_Jump", pTskJump2), nullptr);

	return pSQJump;
}

CLeapJump * CMonster::Make_LeapJumpAI(const _float& fForce, const _float & fTimer)
{
	// 부품 생성
	CLeapJump* pTskLeapJump = dynamic_cast<CLeapJump*>(Engine::Clone_Proto(L"TSK_LeapJump", this));
	NULL_CHECK_RETURN(pTskLeapJump, nullptr);

	// 부품 초기설정
	pTskLeapJump->Set_Timer(fTimer);
	pTskLeapJump->Set_Force(fForce);

	return pTskLeapJump;
}

CSequence * CMonster::Make_JumpToPlayer()
{
	// 부품 생성
	CSequence* pSQJump = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQJump, nullptr);

	CLookAtTarget* pTskLookAt = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pTskLookAt, nullptr);

	// 부품 초기설정

	// 부품 조립
	FAILED_CHECK_RETURN(pSQJump->Add_Component(ID_UPDATE, L"TSK_LookAtPlayer", pTskLookAt), nullptr);
	FAILED_CHECK_RETURN(pSQJump->Add_Component(ID_UPDATE, L"TSK_LeapJump", Make_LeapJumpAI(8.f)), nullptr);

	return pSQJump;
}

CAttack * CMonster::Make_Attack(const _tchar * BulletKey, const _float & fSpeed, const _float & fCoolTime)
{
	// 부품 생성
	CAttack* pTskAttack = dynamic_cast<CAttack*>(Engine::Clone_Proto(L"TSK_Attack", this));
	NULL_CHECK_RETURN(pTskAttack, nullptr);

	// 부품 초기설정
	pTskAttack->Set_BulletKey(BulletKey);
	pTskAttack->Set_BulletSpeed(fSpeed);
	pTskAttack->Set_Timer(fCoolTime);
	
	return pTskAttack;
}

CSequence * CMonster::Make_RushAI()
{
	// 부품 생성
	CSequence* pSQRush = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQRush, nullptr);

	CLookAtTarget* pTskLookatTarget = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pTskLookatTarget, nullptr);
	CRush* pTskRush = dynamic_cast<CRush*>(Engine::Clone_Proto(L"TSK_Rush", this));
	NULL_CHECK_RETURN(pTskRush, nullptr);

	// 부품 초기설정

	// 부품 조립
	FAILED_CHECK_RETURN(pSQRush->Add_Component(ID_UPDATE, L"TSK_LookAtTarget", pTskLookatTarget), nullptr);
	FAILED_CHECK_RETURN(pSQRush->Add_Component(ID_UPDATE, L"TSK_Rush", pTskRush), nullptr);

	return pSQRush;
}

// 돌진 패턴
CSequence* CMonster::Make_BossPattern1(const _float& fCoolTime)
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);

	CCoolTime* pDecCoolTime = dynamic_cast<CCoolTime*>(Engine::Clone_Proto(L"DEC_CoolTime", this));
	NULL_CHECK_RETURN(pDecCoolTime, nullptr);

	// 부품 초기설정
	pDecCoolTime->Set_Timer(fCoolTime);

	// 부품 조립
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"DEC_CoolTime", pDecCoolTime), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"SQ_DBJump", Make_JumpAI(6.f)), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"SQ_DBJump", Make_LeapJumpAI(4.f)), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"SQ_Rush", Make_RushAI()), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"SQ_Jump", Make_JumpAI(6.f)), nullptr);

	return pSQPattern;
}

// 5연 돌진 패턴
CSequence * CMonster::Make_BossPattern1_1(const _float & fCoolTime)
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);

	CBackJump* pTskBackJump = dynamic_cast<CBackJump*>(Engine::Clone_Proto(L"TSK_BackJump", this));
	NULL_CHECK_RETURN(pTskBackJump, nullptr);

	CLookAtTarget* pTskLook = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));

	CCoolTime* pDecCoolTime = dynamic_cast<CCoolTime*>(Engine::Clone_Proto(L"DEC_CoolTime", this));
	NULL_CHECK_RETURN(pDecCoolTime, nullptr);

	// 부품 초기설정
	pDecCoolTime->Set_Timer(fCoolTime);
	pTskBackJump->Set_Force(6.f);

	// 부품 조립
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"DEC_CoolTime", pDecCoolTime), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_LookAt", pTskLook), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"SQ_LeapJump", Make_LeapJumpAI(6.f)), nullptr);

	for (_uint i = 0; i < 5; ++i)
	{
		FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"SQ_Rush", Make_RushAI()), nullptr);
		FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"SQ_BackJump", pTskBackJump), nullptr);
	}
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"SQ_Jump", Make_JumpAI(5.f)), nullptr);

	return pSQPattern;
}

// 지렁이 패턴 크게 포물선 이동
CSequence * CMonster::Make_BossPattern3(const _float & fCoolTime)
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);

	CParabola* pTskParabola = dynamic_cast<CParabola*>(Engine::Clone_Proto(L"TSK_Parabola", this));
	NULL_CHECK_RETURN(pTskParabola, nullptr);
	CMoveY* pTskMoveDown = dynamic_cast<CMoveY*>(Engine::Clone_Proto(L"TSK_MoveY", this));
	NULL_CHECK_RETURN(pTskMoveDown, nullptr);
	CMoveY* pTskMoveUp = dynamic_cast<CMoveY*>(Engine::Clone_Proto(L"TSK_MoveY", this));
	NULL_CHECK_RETURN(pTskMoveUp, nullptr);
	CMovePoint* pTskMovePoint = dynamic_cast<CMovePoint*>(Engine::Clone_Proto(L"TSK_MovePoint", this));
	NULL_CHECK_RETURN(pTskMovePoint, nullptr);

	CCoolTime* pDecCoolTime = dynamic_cast<CCoolTime*>(Engine::Clone_Proto(L"DEC_CoolTime", this));
	NULL_CHECK_RETURN(pDecCoolTime, nullptr);

	// 부품 초기설정
	pDecCoolTime->Set_Timer(fCoolTime);
	pTskMoveDown->Set_Dir_Down();
	pTskMoveUp->Set_Dir_Up(0.f);

	// 부품 조립

	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"DEC_CoolTime", pDecCoolTime), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MoveUp", pTskMoveUp), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_Parabola", pTskParabola), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MoveDown", pTskMoveDown), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MovePoint", pTskMovePoint), nullptr);

	return pSQPattern;
}

// 지렁이 코사인 이동
CSequence * CMonster::Make_BossPattern3_1(const _float & fCoolTime)
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);

	CMoveCos* pTskMoveCos = dynamic_cast<CMoveCos*>(Engine::Clone_Proto(L"TSK_MoveCos", this));
	NULL_CHECK_RETURN(pTskMoveCos, nullptr);
	CMoveY* pTskMoveY = dynamic_cast<CMoveY*>(Engine::Clone_Proto(L"TSK_MoveY", this));
	NULL_CHECK_RETURN(pTskMoveY, nullptr);
	CMoveY* pTskMoveUp = dynamic_cast<CMoveY*>(Engine::Clone_Proto(L"TSK_MoveY", this));
	NULL_CHECK_RETURN(pTskMoveUp, nullptr);
	CMovePoint* pTskMovePoint = dynamic_cast<CMovePoint*>(Engine::Clone_Proto(L"TSK_MovePoint", this));
	NULL_CHECK_RETURN(pTskMovePoint, nullptr);

	CCoolTime* pDecCoolTime = dynamic_cast<CCoolTime*>(Engine::Clone_Proto(L"DEC_CoolTime", this));
	NULL_CHECK_RETURN(pDecCoolTime, nullptr);

	// 부품 초기설정
	pDecCoolTime->Set_Timer(fCoolTime);
	pTskMoveY->Set_Dir_Down();
	pTskMoveUp->Set_Dir_Up(1.f);

	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"DEC_CoolTime", pDecCoolTime), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MoveUp", pTskMoveUp), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MoveCos", pTskMoveCos), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MoveDown", pTskMoveY), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MovePoint", pTskMovePoint), nullptr);

	return pSQPattern;
}

// 지렁이 플레이어 쫒아오는거임
CSequence * CMonster::Make_BossPattern3_2(const _float & fCoolTime)
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);

	CMoveY* pTskMoveUp = dynamic_cast<CMoveY*>(Engine::Clone_Proto(L"TSK_MoveY", this));
	NULL_CHECK_RETURN(pTskMoveUp, nullptr);
	CLookAtPlayer* pTskLookAt = dynamic_cast<CLookAtPlayer*>(Engine::Clone_Proto(L"TSK_LookAtPlayer", this));
	NULL_CHECK_RETURN(pTskLookAt, nullptr);
	CMoveY* pTskMoveDown = dynamic_cast<CMoveY*>(Engine::Clone_Proto(L"TSK_MoveY", this));
	NULL_CHECK_RETURN(pTskMoveDown, nullptr);
	CMovePoint* pTskMovePoint = dynamic_cast<CMovePoint*>(Engine::Clone_Proto(L"TSK_MovePoint", this));
	NULL_CHECK_RETURN(pTskMovePoint, nullptr);

	CCoolTime* pDecCoolTime = dynamic_cast<CCoolTime*>(Engine::Clone_Proto(L"DEC_CoolTime", this));
	NULL_CHECK_RETURN(pDecCoolTime, nullptr);

	// 부품 초기설정
	pDecCoolTime->Set_Timer(fCoolTime);
	pTskLookAt->Set_Timer(16.f);
	pTskMoveUp->Set_Dir_Up();
	pTskMoveDown->Set_Dir_Down();

	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"DEC_CoolTime", pDecCoolTime), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MoveUp", pTskMoveUp), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_FollowPlayer", pTskLookAt), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MoveDown", pTskMoveDown), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MovePoint", pTskMovePoint), nullptr);

	return pSQPattern;
}

// 위로 올라가서 플레이어한테 총알 발사
CSequence * CMonster::Make_BossPattern3_3(const _float & fCoolTime)
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);

	CMoveY* pTskMoveUp = dynamic_cast<CMoveY*>(Engine::Clone_Proto(L"TSK_MoveY", this));
	NULL_CHECK_RETURN(pTskMoveUp, nullptr);
	CLookAtTarget* pTskLookAt = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pTskLookAt, nullptr);
	CAttack* pTskAttack = dynamic_cast<CAttack*>(Engine::Clone_Proto(L"TSK_Attack", this));
	NULL_CHECK_RETURN(pTskAttack, nullptr);
	CWait* pTskWait = dynamic_cast<CWait*>(Engine::Clone_Proto(L"TSK_Wait", this));
	NULL_CHECK_RETURN(pTskWait, nullptr);
	CWormMoveCtrl* pTskMove = dynamic_cast<CWormMoveCtrl*>(Engine::Clone_Proto(L"TSK_WormMoveCtrl", this));
	NULL_CHECK_RETURN(pTskMove, nullptr);
	CWormMoveCtrl* pTskStop = dynamic_cast<CWormMoveCtrl*>(Engine::Clone_Proto(L"TSK_WormMoveCtrl", this));
	NULL_CHECK_RETURN(pTskStop, nullptr);

	CCoolTime* pDecCoolTime = dynamic_cast<CCoolTime*>(Engine::Clone_Proto(L"DEC_CoolTime", this));
	NULL_CHECK_RETURN(pDecCoolTime, nullptr);

	// 부품 초기설정
	pDecCoolTime->Set_Timer(fCoolTime);
	pTskMoveUp->Set_Dir_Up(15.f);
	pTskAttack->Set_BulletKey(L"EnemyBullet");
	pTskAttack->Set_BulletSpeed(30.f);
	pTskWait->Set_ReturnValue(true);
	pTskWait->Set_Timer(0.1f);
	pTskMove->Set_Move();
	pTskStop->Set_Stop();

	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"DEC_CoolTime", pDecCoolTime), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MoveUp", pTskMoveUp), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_Stop", pTskStop), nullptr);

	for (_int i = 0; i < 30; ++i)
	{
		FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_LookAtPlayer", pTskLookAt), nullptr);
		FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_Attack", pTskAttack), nullptr);
		FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_Wait", pTskWait), nullptr);
	}
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TskMove", pTskMove), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"SQ_Parabola", Make_BossPattern3(0.f)), nullptr);

	return pSQPattern;
}

// 코사인으로 플레이어 쫒아옴
CSequence * CMonster::Make_BossPattern3_4(const _float & fCoolTime)
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);

	CMoveCos* pTskMoveCos = dynamic_cast<CMoveCos*>(Engine::Clone_Proto(L"TSK_MoveCos", this));
	NULL_CHECK_RETURN(pTskMoveCos, nullptr);
	CMoveY* pTskMoveY = dynamic_cast<CMoveY*>(Engine::Clone_Proto(L"TSK_MoveY", this));
	NULL_CHECK_RETURN(pTskMoveY, nullptr);
	CMoveY* pTskMoveUp = dynamic_cast<CMoveY*>(Engine::Clone_Proto(L"TSK_MoveY", this));
	NULL_CHECK_RETURN(pTskMoveUp, nullptr);
	CMovePoint* pTskMovePoint = dynamic_cast<CMovePoint*>(Engine::Clone_Proto(L"TSK_MovePoint", this));
	NULL_CHECK_RETURN(pTskMovePoint, nullptr);

	CCoolTime* pDecCoolTime = dynamic_cast<CCoolTime*>(Engine::Clone_Proto(L"DEC_CoolTime", this));
	NULL_CHECK_RETURN(pDecCoolTime, nullptr);

	// 부품 초기설정
	pDecCoolTime->Set_Timer(fCoolTime);
	pTskMoveY->Set_Dir_Down();
	pTskMoveUp->Set_Dir_Up(3.f);
	pTskMoveCos->Set_Follow();
	pTskMoveCos->Set_MoveTime(6.f);

	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"DEC_CoolTime", pDecCoolTime), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MoveUp", pTskMoveUp), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MoveCos", pTskMoveCos), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MoveDown", pTskMoveY), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MovePoint", pTskMovePoint), nullptr);

	return pSQPattern;
}

// 플레이어를 향해 뿌리 공격
CSequence * CMonster::Make_BossPattern4(const _float & fCoolTime)
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);

	CSpreadShot* pTskSpreadLook = dynamic_cast<CSpreadShot*>(Engine::Clone_Proto(L"TSK_SpreadShot", this));
	NULL_CHECK_RETURN(pTskSpreadLook, nullptr);

	CCoolTime* pDecCoolTime = dynamic_cast<CCoolTime*>(Engine::Clone_Proto(L"DEC_CoolTime", this));
	NULL_CHECK_RETURN(pDecCoolTime, nullptr);

	// 부품 초기설정
	pDecCoolTime->Set_Timer(fCoolTime);
	pTskSpreadLook->Setting_Option(L"RootAttack", 13.f);
	pTskSpreadLook->Setting_Spread_Option(SPRD_LOOK);

	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"DEC_CoolTime", pDecCoolTime), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_SpreadShot", pTskSpreadLook), nullptr);

	return pSQPattern;
}

CSequence * CMonster::Make_NubBossCutScene()
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);
	
	CWait* pTskWait = dynamic_cast<CWait*>(Engine::Clone_Proto(L"TSK_Wait", this));
	NULL_CHECK_RETURN(pTskWait, nullptr);

	CCutSceneCheck* pDecCutSceneCheck = dynamic_cast<CCutSceneCheck*>(Engine::Clone_Proto(L"DEC_CutSceneCheck", this));
	NULL_CHECK_RETURN(pDecCutSceneCheck, nullptr);

	pTskWait->Set_ReturnValue(true);
	pTskWait->Set_Timer(0.5f);
	pDecCutSceneCheck->Bind_Switch(L"bCutScene");

	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"DEC_CutSceneCheck", pDecCutSceneCheck), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"SQ_BigJump1", Make_BigJumpAI(6.f)), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_Wait", pTskWait), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"SQ_BigJump2", Make_BigJumpAI(6.f)), nullptr);

	return pSQPattern;
}

CSequence * CMonster::Make_TreeBossCutScene()
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);

	CMoveUp* pTskMoveUp = dynamic_cast<CMoveUp*>(Engine::Clone_Proto(L"TSK_MoveUp", this));
	NULL_CHECK_RETURN(pTskMoveUp, nullptr);

	CCutSceneCheck* pDecCutSceneCheck = dynamic_cast<CCutSceneCheck*>(Engine::Clone_Proto(L"DEC_CutSceneCheck", this));
	NULL_CHECK_RETURN(pDecCutSceneCheck, nullptr);

	pDecCutSceneCheck->Bind_Switch(L"bCutScene");

	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"DEC_CutSceneCheck", pDecCutSceneCheck), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MoveUp", pTskMoveUp), nullptr);

	return pSQPattern;
}

CSequence * CMonster::Make_WormBossCutScene()
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);

	CParabola* pTskParabola = dynamic_cast<CParabola*>(Engine::Clone_Proto(L"TSK_Parabola", this));
	NULL_CHECK_RETURN(pTskParabola, nullptr);
	CMoveY* pTskMoveDown = dynamic_cast<CMoveY*>(Engine::Clone_Proto(L"TSK_MoveY", this));
	NULL_CHECK_RETURN(pTskMoveDown, nullptr);
	CMoveY* pTskMoveUp = dynamic_cast<CMoveY*>(Engine::Clone_Proto(L"TSK_MoveY", this));
	NULL_CHECK_RETURN(pTskMoveUp, nullptr);
	CMovePoint* pTskMovePoint = dynamic_cast<CMovePoint*>(Engine::Clone_Proto(L"TSK_MovePoint", this));
	NULL_CHECK_RETURN(pTskMovePoint, nullptr);

	CCutSceneCheck* pDecCutSceneCheck = dynamic_cast<CCutSceneCheck*>(Engine::Clone_Proto(L"DEC_CutSceneCheck", this));
	NULL_CHECK_RETURN(pDecCutSceneCheck, nullptr);

	pTskMoveDown->Set_Dir_Down();
	pTskMoveUp->Set_Dir_Up(0.f);
	pDecCutSceneCheck->Bind_Switch(L"bCutScene");

	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"DEC_CutSceneCheck", pDecCutSceneCheck), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MoveUp", pTskMoveUp), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_Parabola", pTskParabola), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MoveDown", pTskMoveDown), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_MovePoint", pTskMovePoint), nullptr);

	return pSQPattern;
}

CSequence * CMonster::Make_WalkerBossCutScene()
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);

	CBigJump* pTskBigJump = dynamic_cast<CBigJump*>(Engine::Clone_Proto(L"TSK_BigJump", this));
	NULL_CHECK_RETURN(pTskBigJump, nullptr);
	CWait* pTskWait = dynamic_cast<CWait*>(Engine::Clone_Proto(L"TSK_Wait", this));
	NULL_CHECK_RETURN(pTskWait, nullptr);
	CWait* pTskEndWait = dynamic_cast<CWait*>(Engine::Clone_Proto(L"TSK_Wait", this));
	NULL_CHECK_RETURN(pTskEndWait, nullptr);
	CLookAtTarget* pTskLook = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pTskWait, nullptr);

	CCutSceneCheck* pDecCutSceneCheck = dynamic_cast<CCutSceneCheck*>(Engine::Clone_Proto(L"DEC_CutSceneCheck", this));
	NULL_CHECK_RETURN(pDecCutSceneCheck, nullptr);

	pDecCutSceneCheck->Bind_Switch(L"bCutScene");
	pTskBigJump->Set_Force(30.f);
	pTskWait->Set_ReturnValue(true);
	pTskEndWait->Set_Timer(2.f);

	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"DEC_CutSceneCheck", pDecCutSceneCheck), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_BigJump1", pTskBigJump), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_LookAt", pTskLook), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_Wait", pTskEndWait), nullptr);

	return pSQPattern;
}

// 보스2번 빅점프 패턴
CSequence * CMonster::Make_BossPattern2(const _float & fCoolTime)
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);

	CBigJump* pTskBigJump = dynamic_cast<CBigJump*>(Engine::Clone_Proto(L"TSK_BigJump", this));
	NULL_CHECK_RETURN(pTskBigJump, nullptr);
	CLookAtTarget* pTskLook = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pTskLook);
	CSpreadShot* pTskSprdShot = dynamic_cast<CSpreadShot*>(Engine::Clone_Proto(L"TSK_SpreadShot", this));
	NULL_CHECK_RETURN(pTskSprdShot);
	CSpreadShot* pTskSprdShotPlus = dynamic_cast<CSpreadShot*>(Engine::Clone_Proto(L"TSK_SpreadShot", this));
	NULL_CHECK_RETURN(pTskSprdShotPlus);
	CSpreadShot* pTskSprdShotX = dynamic_cast<CSpreadShot*>(Engine::Clone_Proto(L"TSK_SpreadShot", this));
	NULL_CHECK_RETURN(pTskSprdShotX);

	CCoolTime* pDecCoolTime = dynamic_cast<CCoolTime*>(Engine::Clone_Proto(L"DEC_CoolTime", this));
	NULL_CHECK_RETURN(pDecCoolTime, nullptr);

	// 부품 초기설정
	pTskBigJump->Set_Force(40.f);
	pTskBigJump->Set_Stop(true);
	pTskBigJump->Set_Timer(15.f);
	pDecCoolTime->Set_Timer(fCoolTime);
	pTskSprdShot->Setting_Option(L"ShockWave", 30.f);
	pTskSprdShot->Setting_Spread_Option(SPRD_CIRCLE);
	pTskSprdShotPlus->Setting_Option(L"ShockWave", 30.f);
	pTskSprdShotPlus->Setting_Spread_Option(SPRD_PLUS);
	pTskSprdShotX->Setting_Option(L"ShockWave", 30.f);
	pTskSprdShotX->Setting_Spread_Option(SPRD_X);

	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"DEC_CoolTime", pDecCoolTime), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"SQ_Jump1", Make_JumpAI(9.f)), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_SpreadShot", pTskSprdShotPlus), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"SQ_Jump2", Make_BigJumpAI(14.f)), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_SpreadShot", pTskSprdShotX), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_BigJump", pTskBigJump), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_SpreadShot", Make_BossPattern2_2()), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_BigJump", pTskBigJump), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_SpreadShot", pTskSprdShot), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_LookAt", pTskLook), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_LastJump", Make_JumpAI(7.f)), nullptr);

	return pSQPattern;
}

// 레이저 발사 패턴
CSequence * CMonster::Make_BossPattern2_1(const _float & fCoolTime)
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);

	CLookAtTarget* pTskLook = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pTskLook);
	CAttack* pTskAttack = dynamic_cast<CAttack*>(Engine::Clone_Proto(L"TSK_Attack", this));
	NULL_CHECK_RETURN(pTskAttack);
	CWait* pTskWait = dynamic_cast<CWait*>(Engine::Clone_Proto(L"TSK_Wait", this));
	NULL_CHECK_RETURN(pTskWait);
	CBackJump* pTskBackJump = dynamic_cast<CBackJump*>(Engine::Clone_Proto(L"TSK_BackJump", this));
	NULL_CHECK_RETURN(pTskBackJump, nullptr);
	CMoveLook* pTskMoveLook = dynamic_cast<CMoveLook*>(Engine::Clone_Proto(L"TSK_Move", this));
	NULL_CHECK_RETURN(pTskMoveLook, nullptr);

	CCoolTime* pDecCoolTime = dynamic_cast<CCoolTime*>(Engine::Clone_Proto(L"DEC_CoolTime", this));
	NULL_CHECK_RETURN(pDecCoolTime, nullptr);

	// 부품 초기설정
	pTskAttack->Set_BulletKey(L"RedLaserBullet");
	pTskAttack->Set_BulletSpeed(100.f);
	pTskWait->Set_Timer(0.25f);
	pDecCoolTime->Set_Timer(fCoolTime);
	pTskWait->Set_ReturnValue(true);
	pTskBackJump->Set_Timer(0.f);
	pTskBackJump->Set_Force(6.f);
	pTskMoveLook->Set_Timer(0.6f);

	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"DEC_CoolTime", pDecCoolTime), nullptr);

	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"SQ_BackJump", pTskBackJump), nullptr);
	for (_int i = 0; i < 20; ++i)
	{
		FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"Tsk_LookAtPlayer", pTskLook), nullptr);
		FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"Tsk_Attack", pTskAttack), nullptr);
		FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"Tsk_Wait", pTskWait), nullptr);
	}
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"Tsk_Move", pTskMoveLook), nullptr);

	return pSQPattern;
}

// 하늘에서 레이저 포격
CSequence * CMonster::Make_BossPattern2_2(const _float & fCoolTime)
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, nullptr);

	COnPlayer* pTskOnPlayer = dynamic_cast<COnPlayer*>(Engine::Clone_Proto(L"TSK_OnPlayer", this));
	NULL_CHECK_RETURN(pTskOnPlayer, nullptr);
	CRandomLook* pTskLook = dynamic_cast<CRandomLook*>(Engine::Clone_Proto(L"TSK_RandomLook", this));
	NULL_CHECK_RETURN(pTskLook);
	CAttack* pTskAttack = dynamic_cast<CAttack*>(Engine::Clone_Proto(L"TSK_Attack", this));
	NULL_CHECK_RETURN(pTskAttack);
	CWait* pTskWait = dynamic_cast<CWait*>(Engine::Clone_Proto(L"TSK_Wait", this));
	NULL_CHECK_RETURN(pTskWait);

	// 부품 초기설정
	pTskLook->Set_IsLook_Aircraft(true);
	pTskAttack->Set_BulletKey(L"RedLaserBullet");
	pTskAttack->Set_Scale(_vec3(3.f, 6.f, 3.f));
	pTskAttack->Set_BulletSpeed(2000.f);
	pTskAttack->Set_AttackPoint();
	pTskWait->Set_Timer(0.1f);
	pTskWait->Set_ReturnValue(true);

	for (_int i = 0; i < 50; ++i)
	{
		FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_OnPlayer", pTskOnPlayer), nullptr);
		FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"Tsk_RandomLook", pTskLook), nullptr);
		FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"Tsk_Attack", pTskAttack), nullptr);
		FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"Tsk_Wait", pTskWait), nullptr);
	}
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_OnPlayer", pTskOnPlayer), nullptr);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_LookAt", pTskLook), nullptr);

	return pSQPattern;
}

HRESULT CMonster::Set_AttackToPlayer(const _tchar * BulletKey, const _float & fSpeed, const _float & fCoolTime)
{
	CAttackToPlayer* pTskAtkToPlayer = dynamic_cast<CAttackToPlayer*>(Engine::Clone_Proto(L"TSK_ATKToPlayer", this));
	NULL_CHECK_RETURN(pTskAtkToPlayer, E_FAIL);

	pTskAtkToPlayer->Set_BulletKey(BulletKey);
	pTskAtkToPlayer->Set_BulletSpeed(fSpeed);
	pTskAtkToPlayer->Set_Timer(fCoolTime);

	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pTskAtkToPlayer), E_FAIL);
	return S_OK;
}

HRESULT CMonster::Set_PatrolAndFollow_AI()
{
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI), E_FAIL);

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI()), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Patrol", Make_Patrol_AI()), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_PAF_JumpAI()
{
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI), E_FAIL);

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI(4.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Jump", Make_JumpAI(3.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Patrol", Make_Patrol_AI()), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_PAF_DBJumpAI()
{
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI), E_FAIL);

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI(4.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_DBJump", Make_DBJumpAI(5.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Patrol", Make_Patrol_AI()), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_PAF_AttckAI(const _tchar* pBulletKey)
{
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI), E_FAIL);

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI(4.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"TSK_Attack", Make_Attack(pBulletKey, 20.f, 5.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Patrol", Make_Patrol_AI()), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_PAF_LeapJumpAI()
{
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	CWait* pTaskWait = dynamic_cast<CWait*>(Engine::Clone_Proto(L"TSK_Wait", this));
	NULL_CHECK_RETURN(pTaskWait, E_FAIL);

	// 부품 초기설정
	pTaskWait->Set_Timer(0.2f);

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI), E_FAIL);

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI(4.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"TSK_Wait", pTaskWait), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_LeapJump", Make_LeapJumpAI(6.f, 3.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Patrol", Make_Patrol_AI()), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_JumpFollowAI(const _float& fJumpTime, _bool bIsBoolCheck, const _tchar* pBindBoolTypename)
{
	CSequence* pSQRootAI = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQRootAI, E_FAIL);

	CLookAtTarget* pTskLook = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pTskLook, E_FAIL);
	CBoolCheck* pDecBoolCheck = dynamic_cast<CBoolCheck*>(Engine::Clone_Proto(L"DEC_BoolCheck", this));
	NULL_CHECK_RETURN(pDecBoolCheck, E_FAIL);
	CWait* pTskWait = dynamic_cast<CWait*>(Engine::Clone_Proto(L"TSK_Wait", this));
	NULL_CHECK_RETURN(pTskWait, E_FAIL);

	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SQ_RootAI", pSQRootAI), E_FAIL);

	if (bIsBoolCheck == true)
	{
		if (pBindBoolTypename == nullptr)
		{
			Safe_Release(pSQRootAI);
			Safe_Release(pTskLook);
			Safe_Release(pDecBoolCheck);
			return E_FAIL;
		}
		pDecBoolCheck->Bind_Typename(pBindBoolTypename);
		FAILED_CHECK_RETURN(pSQRootAI->Add_Component(ID_UPDATE, L"DEC_BoolCheck", pDecBoolCheck), E_FAIL);
	}
	else
		Safe_Release(pDecBoolCheck);

	pTskWait->Set_ReturnValue(true);
	pTskWait->Set_Timer(fJumpTime);

	FAILED_CHECK_RETURN(pSQRootAI->Add_Component(ID_UPDATE, L"TSK_LookAt", pTskLook), E_FAIL);
	FAILED_CHECK_RETURN(pSQRootAI->Add_Component(ID_UPDATE, L"SQ_LeapJump", Make_LeapJumpAI(4.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSQRootAI->Add_Component(ID_UPDATE, L"SQ_LeapJump", pTskWait), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_PAF_RushAI()
{
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	CWait* pTaskWait = dynamic_cast<CWait*>(Engine::Clone_Proto(L"TSK_Wait", this));
	NULL_CHECK_RETURN(pTaskWait, E_FAIL);

	// 부품 초기설정
	pTaskWait->Set_Timer(0.2f);

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI), E_FAIL);

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI(4.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"TSK_Wait", pTaskWait), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Rush", Make_BossPattern1(5.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Patrol", Make_Patrol_AI()), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_EvasionAndAttack()
{
	// 부품 생성
	CSequence* pSQPattern = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern, E_FAIL);

	CLookAtTarget* pLookAt = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pLookAt, E_FAIL);
	CEvasion* pTskEvasion = dynamic_cast<CEvasion*>(Engine::Clone_Proto(L"TSK_Evasion", this));
	NULL_CHECK_RETURN(pTskEvasion, E_FAIL);

	// 부품 초기설정

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SQ_RootAI", pSQPattern), E_FAIL);

	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_LookAtPlayer", pLookAt), E_FAIL);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_Evasion", pTskEvasion), E_FAIL);
	FAILED_CHECK_RETURN(pSQPattern->Add_Component(ID_UPDATE, L"TSK_Attack", Make_Attack(L"EnemyBullet", 40.f, 5.f)), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_JumpFollow(const _float& fJumpTime, _bool bIsBoolCheck, const _tchar* pBindBoolTypename)
{
	CSequence* pSQRootAI = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQRootAI, E_FAIL);

	CLookAtTarget* pTskLook = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pTskLook, E_FAIL);

	CBoolCheck* pDecBoolCheck = dynamic_cast<CBoolCheck*>(Engine::Clone_Proto(L"DEC_BoolCheck", this));
	NULL_CHECK_RETURN(pDecBoolCheck, E_FAIL);

	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SQ_RootAI", pSQRootAI), E_FAIL);

	if (bIsBoolCheck == true)
	{
		if (pBindBoolTypename == nullptr)
		{
			Safe_Release(pSQRootAI);
			Safe_Release(pTskLook);
			Safe_Release(pDecBoolCheck);
			return E_FAIL;
		}
		pDecBoolCheck->Bind_Typename(pBindBoolTypename);
		FAILED_CHECK_RETURN(pSQRootAI->Add_Component(ID_UPDATE, L"DEC_BoolCheck", pDecBoolCheck), E_FAIL);
	}
	else
		Safe_Release(pDecBoolCheck);

	FAILED_CHECK_RETURN(pSQRootAI->Add_Component(ID_UPDATE, L"TSK_LookAt", pTskLook), E_FAIL);
	FAILED_CHECK_RETURN(pSQRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI(0.f, false)), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_TurretAI(const _float& fCoolTime, _bool bIsCheckPlayer)
{
	// 부품 생성
	CSequence* pSQChaseAtk = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQChaseAtk, E_FAIL);

	CLookAtTarget* pTskRot = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pTskRot, E_FAIL);
	CAttack* pTskAttack = dynamic_cast<CAttack*>(Engine::Clone_Proto(L"TSK_Attack", this));
	NULL_CHECK_RETURN(pTskAttack, E_FAIL);

	CRangeInPlayer* pDecIsRangeInPlayer = dynamic_cast<CRangeInPlayer*>(Engine::Clone_Proto(L"DEC_RangeInPlayer", this));
	NULL_CHECK_RETURN(pDecIsRangeInPlayer, E_FAIL);

	// 부품 초기설정
	pTskAttack->Set_BulletKey(L"EnemyBullet");
	pTskAttack->Set_BulletSpeed(50.f);
	pTskAttack->Set_Timer(fCoolTime); 
	pDecIsRangeInPlayer->Set_ReturnVal(true);

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SQ_ChaseAtk", pSQChaseAtk), E_FAIL);

	if (bIsCheckPlayer)
	{
		FAILED_CHECK_RETURN(pSQChaseAtk->Add_Decorator(pDecIsRangeInPlayer), E_FAIL);
	}
	else
		Safe_Release(pDecIsRangeInPlayer);

	FAILED_CHECK_RETURN(pSQChaseAtk->Add_Component(ID_UPDATE, L"TSK_Rot", pTskRot), E_FAIL);
	FAILED_CHECK_RETURN(pSQChaseAtk->Add_Component(ID_UPDATE, L"TSK_Attack", pTskAttack), E_FAIL);

	return S_OK;
}

// Nub_Boss
HRESULT CMonster::Set_Boss1_AI()
{
	// 부품 생성
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	// 부품 초기설정

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI), E_FAIL);

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Pattern2", Make_BossPattern1_1(8.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Pattern1", Make_BossPattern1(4.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI(0.f, false)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_CutScene", Make_NubBossCutScene()), E_FAIL);
	
	return S_OK;
}

//Walker_Boss
HRESULT CMonster::Set_Boss2_AI()
{
	// 부품 생성
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	// 부품 초기설정

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI), E_FAIL);

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Pattern2", Make_BossPattern2(23.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Pattern1", Make_BossPattern1(7.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Pattern2_1", Make_BossPattern2_1(13.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_CutScene", Make_WalkerBossCutScene()), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI(0.f, false)), E_FAIL);

	return S_OK;
}

// Worm_Boss
HRESULT CMonster::Set_Boss3_AI()
{
	// 부품 생성
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	CLookAtTarget* pLook = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pLook, E_FAIL);

	// 부품 초기설정
	
	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI), E_FAIL);
	
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Pattern4", Make_BossPattern3_3(15.f/*15.f*/)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Pattern3", Make_BossPattern3_2(10.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Pattern2", Make_BossPattern3_1(6.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Pattern1", Make_BossPattern3(12.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Pattern4", Make_BossPattern3_4(13.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_CutScene", Make_WormBossCutScene()), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_PatternDefault", pLook), E_FAIL);
	
	return S_OK;
}

// Tree_Boss
HRESULT CMonster::Set_Boss4_AI()
{
	// 부품 생성
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	CLookAtTarget* pLook = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pLook, E_FAIL);
	// 부품 초기설정

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI), E_FAIL);

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SL_RootAI", Make_BossPattern4(10.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_CutScene", Make_TreeBossCutScene()), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_PatternDefault", pLook), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Init_AI_Behaviours()
{
	// 조립된 트리 전체 초기화
	FAILED_CHECK_RETURN(dynamic_cast<CRoot*>(m_pRoot)->Ready_Behavior(), E_FAIL);

	// 루트의 블랙보드에 자료형 채우기(공통 요소들은 여기에)
	FAILED_CHECK_RETURN(m_pRoot->m_pBlackBoard->Add_Type(L"fSpeed", m_fSpeed), E_FAIL);

	return S_OK;
}


