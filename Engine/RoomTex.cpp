#include "stdafx.h"
#include "RoomTex.h"


CRoomTex::CRoomTex(LPDIRECT3DDEVICE9 pGraphicDev) :
	CVIBuffer(pGraphicDev)
{
}

CRoomTex::CRoomTex(const CRoomTex & rhs) :
	CVIBuffer(rhs)
{
}

CRoomTex::~CRoomTex()
{
}

HRESULT CRoomTex::Ready_Buffer(void)
{
	m_dwFVF = FVF_CUBE;
	m_dwVtxSize = sizeof(VTXCUBE);
	m_dwVtxCnt = 8;
	m_dwTriCnt = 10;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(__super::Ready_Buffer(), E_FAIL);

	VTXCUBE*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	// 버텍스 버퍼 메모리 공간의 접근을 막는 행위, 3번 인자는 버텍스 버퍼에 저장된 버텍스들 중 첫 번째 버텍스의 주소를 반환한다.

	pVertex[0].vPos = { -1.f, 1.f, -1.f };
	pVertex[0].vTexUV = pVertex[0].vPos ;

	pVertex[1].vPos = { 1.f, 1.f, -1.f };
	pVertex[1].vTexUV = pVertex[1].vPos ;

	pVertex[2].vPos = { 1.f, -1.f, -1.f };
	pVertex[2].vTexUV = pVertex[2].vPos;

	pVertex[3].vPos = { -1.f, -1.f, -1.f };
	pVertex[3].vTexUV = pVertex[3].vPos;


	// 큐브맵에서 타일처럼 여러장 깔려면 어떻게 해야됨? 2배한다고 되는게아닌거같은데
	pVertex[4].vPos = { -1.f, 1.f, 1.f };
	pVertex[4].vTexUV = pVertex[4].vPos;

	pVertex[5].vPos = { 1.f, 1.f, 1.f };
	pVertex[5].vTexUV = pVertex[5].vPos;

	pVertex[6].vPos = { 1.f, -1.f, 1.f };
	pVertex[6].vTexUV = pVertex[6].vPos;

	pVertex[7].vPos = { -1.f, -1.f, 1.f };
	pVertex[7].vTexUV = pVertex[7].vPos;


	m_pVB->Unlock();

	INDEX32*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// x+
	pIndex[0]._0 = 1;
	pIndex[0]._1 = 5;
	pIndex[0]._2 = 6;

	pIndex[1]._0 = 1;
	pIndex[1]._1 = 6;
	pIndex[1]._2 = 2;

	// x-
	pIndex[2]._0 = 4;
	pIndex[2]._1 = 0;
	pIndex[2]._2 = 3;

	pIndex[3]._0 = 4;
	pIndex[3]._1 = 3;
	pIndex[3]._2 = 7;


	// y+
	/*pIndex[4]._0 = 4;
	pIndex[4]._1 = 5;
	pIndex[4]._2 = 1;

	pIndex[5]._0 = 4;
	pIndex[5]._1 = 1;
	pIndex[5]._2 = 0;*/

	// y-
	pIndex[4]._0 = 3;
	pIndex[4]._1 = 2;
	pIndex[4]._2 = 6;

	pIndex[5]._0 = 3;
	pIndex[5]._1 = 6;
	pIndex[5]._2 = 7;

	// z+
	pIndex[6]._0 = 7;
	pIndex[6]._1 = 6;
	pIndex[6]._2 = 5;

	pIndex[7]._0 = 7;
	pIndex[7]._1 = 5;
	pIndex[7]._2 = 4;

	// z-
	pIndex[8]._0 = 0;
	pIndex[8]._1 = 1;
	pIndex[8]._2 = 2;

	pIndex[9]._0 = 0;
	pIndex[9]._1 = 2;
	pIndex[9]._2 = 3;

	m_pIB->Unlock();

	return S_OK;
}

CRoomTex * CRoomTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRoomTex *	pInstance = new CRoomTex(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CRoomTex::Clone(void)
{
	return new CRoomTex(*this);
}

void CRoomTex::Free(void)
{
	__super::Free();
}
