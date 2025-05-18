#include "UI.h"
#include "Export_Function.h"

CUI::CUI(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_UI);
}

CUI::~CUI()
{
}

void CUI::Set_ViewMatrix_UI()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	D3DXMATRIX translationMat;
	D3DXMatrixScaling(&matView, m_vScale.x, m_vScale.y, 1.f);
	D3DXMatrixTranslation(&translationMat, m_vPos.x, m_vPos.y, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &translationMat);


	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

void CUI::Set_ViewMatrix_UI(_float posX, _float posY)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	D3DXMatrixScaling(&matView, m_vScale.x, m_vScale.y, 0.f);
	matTrans.Translation(posX, posY, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

void CUI::Set_ViewMatrix_UI(_float posX, _float posY, _float scaleX, _float scaleY)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	D3DXMatrixScaling(&matView, scaleX, scaleY, 0.f);
	matTrans.Translation(posX, posY, 0.1f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}
