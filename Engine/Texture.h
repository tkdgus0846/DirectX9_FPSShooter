#pragma once

#include "Base.h"
#include "Component.h"

BEGIN(Engine)

class  CTexture : public CComponent
{
private:
	explicit CTexture(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTexture(const CTexture& rhs);
	virtual ~CTexture();

public:
	HRESULT			Ready_Texture(TEXTYPE eTextype, const _tchar* pPath, const _uint& iCnt = 1);
	// 쌤은 옛날에 바로 Set_Texture로 디바이스에 넣었으나, 우리는 m_TextureNum에 저장해놨다가 Render_Component() 타이밍에 디바이스에 넣는다.
	void			Set_Texture_Num(const _uint& iIndex = 0)
	{
		m_TextureNum = iIndex;
	}
	_int			Get_Size() const { return m_vecTexture.size(); }

	// 바로 그려주는 함수도 있다.
	void Render_Texture(const _uint& iIndex = 0);
	void Render_Texture_Num();
	virtual void Render_Component() override;

	// 에디터에서만 사용하세요.
	const IDirect3DBaseTexture9* Get_TextureCom() const { return m_vecTexture[0]; }
private:
	vector<IDirect3DBaseTexture9*>		m_vecTexture;
	_uint								m_TextureNum;

public:
	static CTexture*		Create(LPDIRECT3DDEVICE9 pGraphicDev, TEXTYPE eTextype, const _tchar* pPath, const _uint& iCnt = 1);
	virtual CComponent*		Clone(void);

private:
	virtual void Free(void);
};

END