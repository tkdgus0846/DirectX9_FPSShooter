#pragma once

#include "Typedef.h"

template <typename T>			// 클래스 포인터들을 해제
DWORD Safe_Release(T& pointer)
{
	DWORD	dwRefCnt = 0;

	if (nullptr != pointer)
	{
		dwRefCnt = pointer->Release();

		if (dwRefCnt == 0)
			pointer = nullptr;
	}
	return dwRefCnt;
}

template <typename T>
void Safe_Single_Destory(T& pointer)
{
	if (NULL != pointer)
	{
		pointer->DestroyInstance();
		pointer = NULL;
	}
}

template <typename T>			// 원시 자료형, 구조체 포인터 해제
void Safe_Delete(T& pointer)
{
	if (NULL != pointer)
	{
		delete pointer;
		pointer = NULL;
	}
}

template <typename T>			// 동적 배열을 삭제하는 용도
void Safe_Delete_Array(T& pointer)
{
	if (NULL != pointer)
	{
		delete[] pointer;
		pointer = NULL;
	}
}

/* Float 에서 DWORD로 변환 */
static DWORD FtoDw(float f)
{
	return *((DWORD*)&f);
}

/* lowBound 에서 highBound로 변환 */
static float GetRandomFloat(float lowBound, float highBound)
{
	if (lowBound >= highBound)
		return lowBound;

	float f = (rand() % 10000) * 0.0001f;

	return (f * (highBound - lowBound)) + lowBound;
}

/* min 벡터와 max 벡터사이의 랜덤 벡터 구해줌 */
static void GetRandomVector(
	D3DXVECTOR3* out,
	D3DXVECTOR3* min,
	D3DXVECTOR3* max)
{
	out->x = GetRandomFloat(min->x, max->x);
	out->y = GetRandomFloat(min->y, max->y);
	out->z = GetRandomFloat(min->z, max->z);
}

/* 특정 반지름을 가진 원의 벡터를 랜덤 반환 */
static void GetRandomVectorIncircle(D3DXVECTOR3* out, _float radius)
{
	_float randNum = (rand() % 10000) * 0.0001f;
	*out = D3DXVECTOR3(randNum, 1 - randNum, 0.f);
	D3DXVec3Normalize(out, out);
	*out = *out * radius;
	switch (rand() % 4)
	{
	case 0:
		// 1사분면
		break;
	case 1:
		// 2사분면
		out->x *= -1;
		break;
	case 2:
		// 3사분면
		out->x *= -1;
		out->y *= -1;
		break;
	case 3:
		// 4사분면
		out->y *= -1;
		break;
	}
}
//////////////////////////////////////////////////////////////////
/////////////////////////////////Functor 함수객체//////////////////////////

class CTag_Finder
{
public:
	explicit CTag_Finder(const _tchar* pTag)
		: m_pTargetTag(pTag)
	{
	}
	~CTag_Finder() {		}
public:
	template<typename T>
	bool operator()(const T& pair)
	{
		if (0 == lstrcmpW(m_pTargetTag, pair.first))
		{
			return true;
		}

		return false;
	}

private:
	const _tchar*		m_pTargetTag = nullptr;
};

class CDeleteObj
{
public:
	explicit CDeleteObj(void) {}
	~CDeleteObj(void) {}
public: // operator
	template <typename T>
	void operator () (T& pInstance)
	{
		_ulong dwRefCnt = 0;

		dwRefCnt = pInstance->Release();

		if (0 == dwRefCnt)
			pInstance = nullptr;
	}
};

// 연관컨테이너 삭제용
class CDeleteMap
{
public:
	explicit CDeleteMap(void) {}
	~CDeleteMap(void) {}
public: // operator	
	template <typename T>
	void operator () (T& Pair)
	{
		_ulong dwRefCnt = 0;

		dwRefCnt = Pair.second->Release();

		if (0 == dwRefCnt)
			Pair.second = NULL;
	}
};