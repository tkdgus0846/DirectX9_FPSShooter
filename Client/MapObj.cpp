#include "MapObj.h"
#include "Export_Function.h"

CMapObj::CMapObj(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_TRIGGER);
}

CMapObj::~CMapObj()
{
}

void CMapObj::Render_GameObject(void)
{
	//m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();
}

void CMapObj::OnCollisionStay(const Collision * collision)
{

}

void CMapObj::Serialization(HANDLE hFile, DWORD & dwByte)
{
	_tchar tmp[32];

	lstrcpy(tmp, m_ObjInfo.pObjTag);
	WriteFile(hFile, tmp, sizeof(_tchar) * 32, &dwByte, nullptr);

	m_pTransform->WriteTransformFile(hFile, dwByte);
}

void CMapObj::Deserialization(HANDLE hFile, DWORD & dwByte)
{
	m_pTransform->ReadTransformFile(hFile, dwByte);

	// 생명체들끼리 밀어내는 코드.
	if (Get_WorldTime() < 3.f)
		return;

}