#pragma once

#include "Typedef.h"

BEGIN(Engine)

typedef	 struct tagVertexColor
{
	_vec3			vPos;		// 위치
	_ulong			dwColor;	// 색상

}VTXCOL;

const	_ulong		FVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

typedef	 struct tagVertexTexture
{
	_vec3			vPos;		// 위치
	//_vec3			vNormal;	// 법선
	_vec2			vTexUV;		// 색상

}VTXTEX;

const	_ulong		FVF_TEX = D3DFVF_XYZ | D3DFVF_TEX1;

typedef	 struct tagVertexCube
{
	_vec3			vPos;		// 위치
	//_vec3			vNormal;
	_vec3			vTexUV;		// 색상

}VTXCUBE;

typedef	 struct tagVertexCubeNormal
{
	_vec3			vPos;		// 위치
	_vec3			vNormal;
	_vec3			vTexUV;		// 색상

}VTXCUBENORMAL;

const	_ulong		FVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

const	_ulong		FVF_CUBENORMAL = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0) | D3DFVF_NORMAL;


typedef VTXCOL PTCCOL;
typedef VTXTEX PTCTEX;

// D3DFVF_TEXCOORDSIZE3 : 텍스처의 UV값이 FLOAT형 3개의 크기 만큼이며 괄호 안 숫자의 의미는 본래 버텍스의 UV 값이 여러개 있을 수 잇는데 그 중 첫 번째 값을 사용하겠다는 의미

typedef	struct tagIndex16
{
	_ushort		_0;
	_ushort		_1;
	_ushort		_2;

}INDEX16;

typedef	struct tagIndex32
{
	_ulong		_0;
	_ulong		_1;
	_ulong		_2;

}INDEX32;

struct Particle
{
	_vec3	vPos;
	_vec2	vTexUV;
	_vec3	vVelocity;
	_vec3	vAccel;
	_float	fSpeed;
	_float	fRadius;
	_float	fAngle;
	_float	fLifeTime;
	_float	fAge;
	_ulong	dwColor;
	_ulong	dwColorFade;
	_bool	bIsAlive;
};

struct BoundingBox
{
	BoundingBox(const _vec3& offsetMin = { -1.f, -1.f, -1.f }, const _vec3& offsetMax = { 1.f, 1.f, 1.f })
	{
		_offsetMin = offsetMin;
		_offsetMax = offsetMax;
		_min = { 0.f,0.f,0.f };
		_max = { 0.f,0.f,0.f };
	}

	_vec3	Get_Center()
	{
		return (_max - _min) / 2 + _min;
	}

	_vec3	Get_Size()
	{
		return _offsetMax - _offsetMin;
	}

	// 지금은 큐브와 점의 충돌 검사
	virtual bool Intersect(const _vec3& point)
	{
		if (point.x >= _min.x && point.y >= _min.y && point.z >= _min.z &&
			point.x <= _max.x && point.y <= _max.y && point.z <= _max.z)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// 오리진 위치를 받아와서 offsetMin 이랑 offsetMax만큼 더해줌 그 이유는 게임오브젝트가 움직였을때 범위가 달라져야 하기때문.
	virtual void Offset(const _vec3& origin)
	{
		_min = origin + _offsetMin;
		_max = origin + _offsetMax;
	}

	// origin + 큐브의 크기 (큐브 월드 좌표)
	_vec3 _min;
	_vec3 _max;

	// 큐브의 크기 (큐브 로컬 좌표)
	_vec3 _offsetMin;
	_vec3 _offsetMax;
};

class Collision
{
public:
	Collision() : 
		CollisionDir(DIR_END),
		MyCollider(nullptr),
		OtherCollider(nullptr),
		OtherGameObject(nullptr),
		intersectBox(BoundingBox())
	{}
	
	// 충돌한 방향
	COL_DIR				CollisionDir;
	// 내 콜라이더
	class CCollider*	MyCollider; 
	// 상대 콜라이더
	class CCollider*    OtherCollider;
	// 상대 게임오브젝트
	class CGameObject*	OtherGameObject; 
	// 충돌한 지점
	BoundingBox			intersectBox;
	// 얼마나 충돌했는지에 대한 벡터 (x만큼 겹침, y만큼 겹침, z만큼 겹침)
	_vec3				amountVec;
};

typedef struct tagViewParams
{
	_vec3 vEye;
	_vec3 vAt;
	_vec3 vUp;

	tagViewParams()
	{
		ZeroMemory(this, sizeof(tagViewParams));
	}
	tagViewParams(const _vec3& vEye, const _vec3& vAt, const _vec3& vUp)
	{
		this->vEye = vEye;
		this->vAt = vAt;
		this->vUp = vUp;
	}
	tagViewParams(const tagViewParams& rhs)
	{
		this->vEye = rhs.vEye;
		this->vAt = rhs.vAt;
		this->vUp = rhs.vUp;
	}
	D3DXMATRIX* LookAtLH(D3DXMATRIX* pMatView)
	{
		return D3DXMatrixLookAtLH(pMatView, &vEye, &vAt, &vUp);
	}
}VIEWPARAMS;

typedef struct tagProjParams
{
	_float fFov;
	_float fAspect;
	_float fNear;
	_float fFar;

	tagProjParams()
	{
		ZeroMemory(this, sizeof(tagProjParams));
	}
	tagProjParams(const _float& fFov, const _float& fAspect, const _float& fNear, const _float& fFar)
	{
		this->fFov = fFov;
		this->fAspect = fAspect;
		this->fNear = fNear;
		this->fFar = fFar;
	}
	tagProjParams(const tagProjParams& rhs)
	{
		this->fFov = rhs.fFov;
		this->fAspect = rhs.fAspect;
		this->fNear = rhs.fNear;
		this->fFar = rhs.fFar;
	}
	D3DXMATRIX* PerspectiveLH(D3DXMATRIX* pMatProj)
	{
		return D3DXMatrixPerspectiveFovLH(pMatProj, fFov, fAspect, fNear, fFar);
	}
}PROJPARAMS;

typedef struct tagRay
{
	_vec3 vOrigin;
	_vec3 vDirection;
}Ray;

struct BoundingSphere
{
	_vec3 vCenter;
	float fRadius;

	BoundingSphere(float _fRadius)
		: fRadius(_fRadius) {};

	virtual void Offset(const _vec3& origin)
	{
		vCenter = origin + vCenter;
	}
};

struct Triangle
{
	_vec3 Normal()
	{
		_vec3 v0 = v[1] - v[0];
		_vec3 _v1 = v[2] - v[0];
		_vec3 cross = v0.Cross(_v1);
		cross.Normalize();
		return cross;
	}
	_vec3 v[3];
};

struct Vertex4
{
	_vec3 _v1, _v2, _v3, _v4;

	float triangle_area(const D3DXVECTOR3& a, const D3DXVECTOR3& b, const D3DXVECTOR3& c) {
		D3DXVECTOR3 ab, ac, cross_product;
		D3DXVec3Subtract(&ab, &b, &a);
		D3DXVec3Subtract(&ac, &c, &a);
		D3DXVec3Cross(&cross_product, &ab, &ac);
		return 0.5f * D3DXVec3Length(&cross_product);
	}

	bool is_upper_left_triangle(const D3DXVECTOR3& point) {
		float triangle1_area = triangle_area(_v1, _v2, point);
		float triangle2_area = triangle_area(_v2, _v3, point);
		float triangle3_area = triangle_area(_v3, _v4, point);
		float triangle4_area = triangle_area(_v4, _v1, point);

		float total_area = triangle_area(_v1, _v2, _v3) + triangle_area(_v1, _v3, _v4);
		float sum_of_triangle_areas = triangle1_area + triangle2_area + triangle3_area + triangle4_area;

		// 주어진 점이 삼각형 내부에 있을 때, 삼각형들의 합이 정사각형의 넓이와 일치함
		const float epsilon = 1e-6f;
		if (fabs(total_area - sum_of_triangle_areas) < epsilon) {
			// 주어진 점이 왼쪽 위 삼각형 내부에 있는지 판단
			if (triangle1_area > epsilon && triangle2_area < epsilon) {
				return true;
			}
		}
		return false;
	}
};

typedef struct tagInteractInfo
{
	class CGameObject* pGameObject;
	_float _fTimeDelta;
}InteractInfo;

END