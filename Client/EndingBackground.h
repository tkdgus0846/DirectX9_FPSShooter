#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CRcTex;
class CTexture;
END

class CEndingBackground : public CGameObject
{
private:
	explicit CEndingBackground(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CEndingBackground();

public:
	static CEndingBackground*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual HRESULT Add_Component() override;


	virtual void Render_GameObject(void) override;

	void Make_Logo_Text(string msg, const _vec3& startPoint, const _float& seq);

protected:
	CTexture*			m_LogoTextTexture;
	vector<CRcTex*>		m_LogoTextBufferVec;
	vector<_vec3>		m_LogoTextPosVec;
	vector<_uint>		m_LogoTextNumVec;
	vector<_int>		m_TextSeperator;
	_int				m_iSeperator;
	_int				m_CurSeperatorIndex;

	virtual void Free(void) override;
};

