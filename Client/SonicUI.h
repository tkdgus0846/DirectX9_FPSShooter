#pragma once
#include "UI.h"

BEGIN(Engine)
class CRcTex;
class CTexture;
END

class CSonicUI : public CUI
{
private:
	explicit CSonicUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSonicUI();

public:
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual HRESULT Add_Component() override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	void		Start_Game();
	void		End_Game();

	void		Add_Score(_int iScore = 1) { m_Score += iScore; }

	static CSonicUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	vector<CRcTex*>		m_ScoreBufferVec; // 流立 昏力秦拎具窃.
	CRcTex*				m_GameOverBuffer;
	CTexture*			m_ScoreTexture;
	CTexture*			m_GameOverTexture;

	_bool				m_bRenderScore;
	_int				m_Score;

protected:
	virtual void Free(void) override;

};

