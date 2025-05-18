#pragma once

#include "Include.h"
#include "Creature.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CCollider;
class CRigidbody;
class CCamera;
class CLayer;
END



class CPlayer : public CCreature
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayer();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;
	

	virtual void OnCollisionEnter(const Collision* collsion) override;
	virtual void OnCollisionStay(const Collision* collision) override;
	virtual void OnCollisionExit(const Collision* collision) override;

	void			Jump(const _float& fTimeDelta);

	void			Change_Weapon(WEAPONTYPE eWeaponType);
	void			Next_Weapon();
	void			Prev_Weapon();
	void			Gain_Weapon(WEAPONTYPE eWeaponType);
	class CWeapon*	Get_CurWeapon() const { return m_pCurWeapon; }
	WEAPONTYPE		Get_CurWeaponType() const { return m_eCurWeaponType; }

	void			Gain_Coin(_int coin = 1) { m_iCoin += coin; }
	_int			Get_Coin() { return m_iCoin; }
	_bool			De_Coin(_int coin) 
	{ 
		if (m_iCoin - coin < 0) return false;
		m_iCoin -= coin; 
		return true;
	}
	_vec3			GetDeltaVec();
	void			Gain_Disc(_int disc = 1) { m_iDisc += disc; }
	void			Gain_Hp(_int Hp = 1) { m_iHp += Hp; }
	void			Gain_UltiGuage(_float fTimeDelta, _float guage = 1);
	_int			Get_Disc() { return m_iDisc; }
	_int			Get_UltiGuage() { return m_fUltimateGuage; }
	_int			Get_UltiMaxGuage() { return m_fUltimateMax; }

	void			Loss_UltiGuage(_float guage);

	void			AimHack();
	_bool			Get_bAimHack() { return m_bAimHack; }
	void			Set_bGravition(_bool state) { m_bGravition = state; }
	_bool			Get_bGravition() { return m_bGravition; }
	void			Fix_Aim(CCollider* pCollider);
	_vec3			Tactical_Bullet_Dir();
	_bool			Get_bJumped() { return m_bJumped; }

	bool IsObjectInFOV(_float fDistance, _float fRadius, _float fFov);
	void			IsOnIceTile(_bool _IsOnIceTile) {
		m_bIsOnIceTile = _IsOnIceTile;	}

	void			Set_FlyMode();


	virtual void Get_Damaged(_int Damage) override;
	void	    	Set_bDamaged(_bool state) { m_bDamaged = state; }
	_bool			Get_bDamaged() { return m_bDamaged; }

private:
	virtual HRESULT Add_Component() override;
	void		Key_Input(const _float& fTimeDelta);
	void		Mouse_Move(const _float& fTimeDelta);
	void		Fix_Mouse();
	void		InteractTile(_float fTimeDelta);

private:
	_bool					m_bFix;
	_bool					m_bFlyMode;

	_bool					Is_SlowTime = false;
	_bool					m_bDamaged = false;

	_bool					m_bGravition = false;
	_bool					m_bAimHack = false;
	_float					m_AimHackTime = 0.f;
	_bool					m_bTactic = false;
	_float					m_TacticTime = 0.f;

	_int					m_iCoin;
	_int					m_iDisc = 1;

	_float					m_fUltimateMax = 100.f;
	_float					m_fUltimateGuage = 100.f;
	_float					m_fUltimateGuageHealTime = 0.f;

	_bool					m_bInvicible;
	_bool					m_bColorInversion;

	_bool					m_bJumped;
	_float					m_fJumpTime;


	array<class CWeapon*, WEAPONEND>	m_MyWeaponList;
	class CWeapon*						m_pCurWeapon;
	WEAPONTYPE							m_eCurWeaponType;

	vector<CGameObject*>				m_vecMonster;
	list<_vec3>							m_PosList;

	_bool				m_bIsOnIceTile = false;


public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

};

