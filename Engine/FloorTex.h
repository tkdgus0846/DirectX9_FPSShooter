#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

struct VertexPoints
{
	_vec3 p1;
	_vec3 p2;
	_vec3 p3;
};

class  CFloorTex : public CVIBuffer
{
private:
	explicit CFloorTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFloorTex(const CFloorTex& rhs);
	virtual ~CFloorTex();

public:
	const _vec3*		Get_VtxPos(void) { return m_pPos; }

public:
	HRESULT		Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv );

	bool IsInPlane(const _vec3& playerPos, const int& iIndex);

	vector<D3DXPLANE>	m_PlaneVec;
	vector<VertexPoints> m_VertexPoints;

private:
	HANDLE				m_hFile;
	BITMAPFILEHEADER	m_fH;
	BITMAPINFOHEADER	m_iH;
	_vec3*				m_pPos;

public:
	static CFloorTex*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX = VTXCNTX, const _ulong& dwCntZ = VTXCNTZ, const _ulong& dwVtxItv = VTXITV);
	virtual CComponent*	Clone(void);
private:
	virtual void Free(void);

};

END