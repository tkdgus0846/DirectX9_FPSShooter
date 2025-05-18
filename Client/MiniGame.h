#pragma once
#include "Scene.h"

BEGIN(Engine)

class CTexture;
class CRcTex;

END

class CMiniGame : public CScene
{
public:
	explicit CMiniGame(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMiniGame();

	virtual _int Update_Scene(const _float& fTimeDelta) override;
	virtual void LateUpdate_Scene(void) override;
};

