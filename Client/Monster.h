#pragma once

#include "Include.h"
#include "Creature.h"

BEGIN(Engine)
class CRoot;
class CTriCol;
class CTransform;
class CCollider;
class CSequence;
class CBlackBoard;
END

class CJump;
class CAttack;
class CBigJump;
class CLeapJump;
class CMonster : public CCreature
{
protected:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMonster();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void OnCollisionEnter(const class Collision* collsion);
	virtual void OnCollisionStay(const class Collision* collision);
	virtual void OnCollisionExit(const class Collision* collision);

	virtual void SetDead(_bool bDead = true) override;

	virtual void Get_Damaged(_int Damage) override;
	
private:
	virtual HRESULT Add_Component() override;

protected:
	Engine::CBlackBoard* Get_BlackBoard();

	HRESULT		Create_Root_AI();			// AI 생성 시 제일 먼저 실행 시켜야 함.
	HRESULT		Init_AI_Behaviours();		// AI작업 마지막에 무조건 실행 시켜야 함.

	CSequence*	Make_Patrol_AI(const _float& fWaitTime = 1.f, const _float& fMoveTime = 0.5f);
	CSequence*	Make_Follow_AI(const _float& fTimer = 100.f, _bool bIsRangeCheck = true);	// 디폴트값은 계속(이라고 하지만 아님) 쫒아옴
	CJump*	Make_JumpAI(const _float& fForce, const _float& fTimer = 0.f);
	CBigJump*	Make_BigJumpAI(const _float& fForce, const _float& fTimer = 0.f);
	CSequence*	Make_DBJumpAI(const _float& fForce, const _float& fTimer = 0.f);
	CSequence*	Make_DBBackJumpAI(const _float& fForce, const _float& fTimer = 0.f);
	CLeapJump*	Make_LeapJumpAI(const _float& fForce, const _float& fTimer = 0.f);
	CSequence*	Make_JumpToPlayer();
	CAttack*	Make_Attack(const _tchar* BulletKey, const _float& fSpeed, const _float& fCoolTime);
	CSequence*	Make_RushAI();
	CSequence*	Make_BossPattern1(const _float& fCoolTime = 6.f);
	CSequence*	Make_BossPattern1_1(const _float& fCoolTime = 18.f);
	CSequence*	Make_BossPattern2(const _float& fCoolTime = 12.f);
	CSequence*	Make_BossPattern2_1(const _float& fCoolTime = 12.f);
	CSequence*	Make_BossPattern2_2(const _float& fCoolTime = 0.f);
	CSequence*	Make_BossPattern3(const _float& fCoolTime = 12.f);
	CSequence*	Make_BossPattern3_1(const _float& fCoolTime = 12.f);
	CSequence*	Make_BossPattern3_2(const _float& fCoolTime = 12.f);
	CSequence*	Make_BossPattern3_3(const _float& fCoolTime = 12.f);
	CSequence*	Make_BossPattern3_4(const _float& fCoolTime = 12.f);
	CSequence*	Make_BossPattern4(const _float& fCoolTime = 12.f);
	CSequence*	Make_NubBossCutScene();
	CSequence*	Make_TreeBossCutScene();
	CSequence*	Make_WormBossCutScene();
	CSequence*	Make_WalkerBossCutScene();
	
	HRESULT		Set_AttackToPlayer(const _tchar* BulletKey, const _float& fSpeed, const _float& fCoolTime);
	HRESULT		Set_PatrolAndFollow_AI();
	HRESULT		Set_PAF_JumpAI();
	HRESULT		Set_PAF_DBJumpAI();
	HRESULT		Set_PAF_AttckAI(const _tchar* pBulletKey);
	HRESULT		Set_PAF_LeapJumpAI();
	HRESULT		Set_JumpFollowAI(const _float& fJumpTime, _bool bIsBoolCheck, const _tchar* pBindBoolTypename);
	HRESULT		Set_PAF_RushAI();
	HRESULT		Set_EvasionAndAttack();
	HRESULT		Set_JumpFollow(const _float& fJumpTime, _bool bIsBoolCheck, const _tchar* pBindBoolTypename);
	HRESULT		Set_TurretAI(const _float& fCoolTime, _bool bIsCheckPlayer = true);
	HRESULT		Set_Boss1_AI();
	HRESULT		Set_Boss2_AI();
	HRESULT		Set_Boss3_AI();
	HRESULT		Set_Boss4_AI();

private:
	CRoot*		m_pRoot;	// 모든 몬스터는 하나의 ai를 가지는걸로 가정.

protected:
	// 빨갛게 반짝이는 효과를 결정하는 변수들
	// m_fDuration로 효과의 지속시간을 결정함.
	bool m_redTexture;
	float m_fDuration = 0.05f;
	float m_fCurTime;
	float m_fPreTime;

public:
	static CMonster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void Free(void) override;
};