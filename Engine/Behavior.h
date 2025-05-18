#pragma once
#include "Component.h"

/*
	Behavior트리의 구성요소는 다음과 같다.
	Root	-	ai 트리의 시작단계. 블랙보드를 가지고 있으며 모든 ai는 
				각자의 root를 가지고 있다.

	Selector-	ai의 세부 분리자 역할1. 연산자의 OR 연산과 비슷한 동작방식을
				가지고 있으며, 하나의 기능이라도 True를 반환할 경우 False를 반환한다.
				그리고 모든 기능을 순회 한 경우 True를 반환한다.

	Sequence-	ai의 세부 분리자 역할2. 연산자의 AND 연산과 비슷한 동작방식을
				가지고 있으며, 하나의 기능이라도 False를 반환할 경우 False를 반환한다.
				그리고 모든 기능을 순회 한 경우 True를 반환한다.

	Task	-	ai의 말단 기능부. ai의 기능을 담당하고 있으며, 프로그래머가
				필요한 경우 Behavior클래스를 상속받아서 기능을 구현하면 된다.
	
	이 중 프로그래머가 직접적으로 제작을 맡는 부분은 Task 부분이다.
*/

BEGIN(Engine)

class CBlackBoard;
class CBehavior : public CComposite
{
protected:
	explicit CBehavior(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBehavior(const CBehavior& rhs);
	virtual ~CBehavior();

public:
	virtual HRESULT Ready_Behavior();
	virtual _int	Update_Component(const _float& fTimeDelta);
	virtual void	LateUpdate_Component(void);
	virtual void	Render_Component(void);

	HRESULT			Add_Decorator(CComponent* pComponent);
	void			Set_Timer(const _float& fTime) { m_fTimer = fTime; }

protected:
	_int			update_Decorator(const _float& fTimeDelta);

protected:
	list<PRICOMP> m_DecoratorList;

	_float m_fCurTime;
	_float m_fPreTime;
	_float m_fTimer;

public:
	CBlackBoard* m_pBlackBoard;

protected:
	virtual CComponent * Clone(void) PURE;

protected:
	virtual void Free() override;
};

END