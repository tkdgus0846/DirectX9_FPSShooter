#pragma once
#include "Monster.h"
#include "Serializable.h"

class CEnemy :
	public CMonster, public ISerializable
{
protected:
	explicit CEnemy(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CEnemy();

public:
	virtual void Serialization(HANDLE hFile, DWORD & dwByte) override;
	virtual void Deserialization(HANDLE hFile, DWORD & dwByte) override;
};

