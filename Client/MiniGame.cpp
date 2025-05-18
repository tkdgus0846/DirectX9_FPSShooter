#include "MiniGame.h"
#include "Layer.h"

#include "Export_Function.h"


CMiniGame::CMiniGame(LPDIRECT3DDEVICE9 pGraphicDev) :
	CScene(pGraphicDev)
{
}

CMiniGame::~CMiniGame()
{
}

_int CMiniGame::Update_Scene(const _float& fTimeDelta)
{
	_int iResult = 0;

	for (int i = LAYER_STATIC_END + 1; i < LAYER_DYNAMIC_END; i++)
	{
		CLayer* curLayer = Get_Layer((LAYERID)i);
		if (curLayer == nullptr) continue;

		iResult = curLayer->Update_Layer(fTimeDelta);

		if (iResult & 0x80000000)
			return iResult;
	}

	return iResult;
}

void CMiniGame::LateUpdate_Scene(void)
{
	for (int i = LAYER_STATIC_END + 1; i < LAYER_DYNAMIC_END; i++)
	{
		CLayer* curLayer = Get_Layer((LAYERID)i);
		if (curLayer == nullptr) continue;

		curLayer->LateUpdate_Layer();
	}
}


