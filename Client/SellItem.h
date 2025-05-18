#pragma once
#include "GameObject.h"


BEGIN(Engine)

class CTexture;
class CRcTex;
class CCollider;

END

enum SellType
{
	SELL_WEAPON, SELL_BOOTS, SELL_END
};

class CSellItem : public CGameObject
{
private:
	CSellItem(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSellItem();

public:
	virtual HRESULT Add_Component();
	virtual HRESULT Ready_GameObject(_vec3 vPos, SellType eID, _int iPrice, WEAPONTYPE weaponType = WEAPONEND);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;
	virtual void OnCollisionEnter(const class Collision* collsion) final;
	virtual void OnCollisionStay(const class Collision* collision) final;
	
	static CSellItem*	Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos, SellType eID, _int iPrice, WEAPONTYPE weaponType = WEAPONEND);
	static CGameObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	void Set_Price(_int iPrice) { m_Price = iPrice; }
	
private:
	class CItem*	m_SellItem;
	_int			m_Price;

	CTexture*		m_NumTexture;
	CTexture*		m_CoinTexture;
	vector<CRcTex*> m_RcVec;
	CRcTex*			m_CoinRc;

	string			m_strNum;

protected:
	virtual void Free(void) override;

};

