#pragma once

#include "Include.h"
#include "GameObject.h"
#include "Serializable.h"

class CMapObj :
	public CGameObject, public ISerializable
{
protected:
	explicit CMapObj(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMapObj();
	virtual void Render_GameObject(void) override;

	virtual void OnCollisionStay(const class Collision* collision);

	// ISerializable을(를) 통해 상속됨
	virtual void Serialization(HANDLE hFile, DWORD & dwByte) override;
	virtual void Deserialization(HANDLE hFile, DWORD & dwByte) override;
};