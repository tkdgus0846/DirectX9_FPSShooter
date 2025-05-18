#include "ImWindow.h"

#include "Export_Function.h"

CImWindow::CImWindow(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bEnable(true)
{
	m_pGraphicDev->AddRef();
}

CImWindow::~CImWindow()
{
}

HRESULT CImWindow::Ready_ImWindow()
{
	return S_OK;
}

void CImWindow::Free(void)
{
	Safe_Release(m_pGraphicDev);
}

void CImWindow::Toggle(bool & _bVariable)
{
	if (true == _bVariable)
		_bVariable = false;
	else
		_bVariable = true;
}