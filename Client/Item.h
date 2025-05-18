#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CAnimation;
class CTexture;

END

class CPlayer;
class CItem : public CGameObject
{
	friend class CItemPool;
protected:
	explicit CItem(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CItem();

public:
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void OnCollisionEnter(const class Collision* collsion) override;
	virtual void OnCollisionStay(const class Collision* collision) override;

	void		Set_Loot(_bool state = true) { m_bCanLoot = state; }
	_bool		Get_Loot() const { return m_bCanLoot; }

	void		SetAge(_float age = 0.f) { m_fAge = age; }

public:
	class CAnimation* m_pAniCom;
	class CTexture*   m_pTextureCom;
	
protected:
	_bool					m_bDrop;
	_bool					m_bBill;
	_float					m_fY;
	_float					m_fSpeed;
	_float					m_fMaxY;
	_float					m_fMinY;
	_bool					m_bCanLoot;

	// 살아있을 수 있는 시간
	_float		m_fLifeSpan;
	// 살고 있는 시간
	_float		m_fAge;

protected:
	virtual void		ItemPatrol(const _float& fTimeDelta);
	virtual void		ItemMagnetic(CPlayer* pPlayer);
	virtual void		ItemDrop(const _float & fTimeDelta);

	void			Aging(_float fTimeDelta)
	{
		m_fAge += fTimeDelta;
		if (m_fAge >= m_fLifeSpan)
		{
			SetDead();
		}
	}

private:
	_float m_fTime;
	_float m_randNum;

protected:
	virtual void Free() override;
};