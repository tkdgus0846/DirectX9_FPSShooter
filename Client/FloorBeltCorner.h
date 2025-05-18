#pragma once
#include "FloorTile.h"
class CFloorBeltCorner :
	public CFloorTile
{
private:
	CFloorBeltCorner(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CFloorBeltCorner();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorBeltCorner"; }

public:
	virtual void InteractGameObject(const InteractInfo* tInteractInfo);

	_float linearInterpolation(const _vec3& p1, const _vec3& p2, float x) {
		_float slope = (p2.z - p1.z) / (p2.x - p1.x);
		_float z_intercept = p1.z - slope * p1.x;

		return slope * x + z_intercept;
	}

	float triangle_area(const _vec3& p1, const _vec3& p2, const _vec3& p3)
	{
		_vec3 A = { p2.x - p1.x, p2.y - p1.y, p2.z - p1.z };
		_vec3 B = { p3.x - p1.x, p3.y - p1.y, p3.z - p1.z };
		_vec3 C = { A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x };
		float area = 0.5f * std::sqrt(C.x * C.x + C.y * C.y + C.z * C.z);
		return area;
	}

	bool isPointInUpperLeftTriangle(const _vec3& point, const _vec3& v1, const _vec3& v2, const _vec3& v3)
	{
		float mainTriangleArea = triangle_area(v1, v2, v3);
		float triangleArea1 = triangle_area(point, v1, v2);
		float triangleArea2 = triangle_area(point, v1, v3);
		float triangleArea3 = triangle_area(point, v2, v3);

		return (std::fabs(triangleArea1 + triangleArea2 + triangleArea3 - mainTriangleArea) < 0.01f);
	}

	bool isPointInUpperLeftTriangleRegardlessRotation(const _vec3& point, const Vertex4& vertex)
	{
		const _vec3& v1 = vertex._v1;
		const _vec3& v2 = vertex._v2;
		const _vec3& v3 = vertex._v3;
		const _vec3& v4 = vertex._v4;

		// 원래 순서: v1, v2, v3
		if (isPointInUpperLeftTriangle(point, v1, v2, v3)) return true;

		// 반시계 방향으로 90도 회전한 경우: v3, v1, v4
		if (isPointInUpperLeftTriangle(point, v3, v1, v4)) return true;

		// 반시계 방향으로 180도 회전한 경우: v4, v3, v2
		if (isPointInUpperLeftTriangle(point, v4, v3, v2)) return true;

		// 반시계 방향으로 270도 회전한 경우: v2, v4, v1
		if (isPointInUpperLeftTriangle(point, v2, v4, v1)) return true;

		return false;
	}

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

