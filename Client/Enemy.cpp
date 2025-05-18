#include "Enemy.h"

#include "Export_Function.h"

CEnemy::CEnemy(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
}

CEnemy::~CEnemy()
{
}

void CEnemy::Serialization(HANDLE hFile, DWORD & dwByte)
{
	_tchar tmp[32];

	lstrcpy(tmp, m_ObjInfo.pObjTag);
	WriteFile(hFile, tmp, sizeof(_tchar) * 32, &dwByte, nullptr);

	m_pTransform->WriteTransformFileForMonster(hFile, dwByte);
}

void CEnemy::Deserialization(HANDLE hFile, DWORD & dwByte)
{
	m_pTransform->ReadTransformFileForMonster(hFile, dwByte);
}
