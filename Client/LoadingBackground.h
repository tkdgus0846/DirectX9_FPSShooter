#pragma once
#include "UI.h"

BEGIN(Engine)
class CRcTex;
class CTexture;
END

class CLoadingBackground : public CUI
{
private:
	explicit CLoadingBackground(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLoadingBackground();

public:
	static CLoadingBackground*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual HRESULT Add_Component() override;


	virtual void Render_GameObject(void) override;

	void Make_Logo_Text(string msg, const _vec3& startPoint, const _float& seq);

	void Loading_Next_Text()
	{
		m_CurSeperatorIndex++;
		if (m_CurSeperatorIndex > 3)
			m_CurSeperatorIndex = 1;
	}
	void Loading_Complete_Text()
	{
		m_CurSeperatorIndex = 4;
	}

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

