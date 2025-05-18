#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CAnimation;
END

class CEffect : public CGameObject
{
	friend class CEffectManager;
	friend class CEffectPool;

protected:
	explicit CEffect(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CEffect();

public:
	virtual HRESULT Add_Component() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void Render_GameObject(void) override;

protected:
	_float	m_fAge;
	_float	m_fLifeSpan;
	_float  m_fAnimationTime;
	_bool	m_bEndByTime;
	const _tchar* m_TextureName;

	CAnimation* m_pAnimation;

private:
	void			Aging(_float fTimeDelta)
	{
		m_fAge += fTimeDelta;
		if (m_fAge >= m_fLifeSpan)
		{
			SetDead();
		}
	}
	virtual void	SetDead(_bool bDead = true) override;

private:
	static CEffect* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* name, _float fAnimationTime = 0.1f, _bool bEndByTime = FALSE, _float fLifeSpan = 1.0f);

	virtual void Free(void) override;

};

