#pragma once
#include "Tile.h"
class CWallTile :
	public CTile
{
protected:
	explicit CWallTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWallTile();
};

