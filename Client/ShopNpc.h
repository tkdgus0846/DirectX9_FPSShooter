#pragma once
#include "Enemy.h"

BEGIN(Engine)

class CAnimation;

END

class CSellItem;

class CShopNpc : public CMonster
{
public:
	CShopNpc(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CShopNpc();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int	Update_GameObject(const _float& fTimeDelta) override;
	virtual void	LateUpdate_GameObject(void) override;
	virtual void	Render_GameObject(void) override;

	virtual void	Get_Damaged(_int Damage) override;

	void			Add_SellItem_Stage1();
	void			Add_SellItem_Stage2();
	void			Add_SellItem_Stage3();
	void			Add_SellItem_Stage4();

private:
	D3DXMATRIX  matWorld, matView;
	virtual void OnCollisionEnter(const class Collision* collsion) final;
	virtual void OnCollisionStay(const class Collision* collision) final;

	CAnimation* Ani;

	_int				m_SellNum;
	_float				m_fPlayBGMTime;

public:
	static CGameObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"ShopNpc"; }

private:
	virtual void Free(void) override;
};

