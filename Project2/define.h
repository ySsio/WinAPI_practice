#pragma once

// 매크로 정의

// 매크로 함수
// 마지막에 붙이면 이어짐.

#define SINGLETON(type)	public:									\
							static type* GetInst()				\
							{									\
								static type mgr;				\
								return &mgr;					\
							}									\
						private:								\
							type();								\
							~type();							\

// 함수 내 정적변수로 선언 - 데이터 영역 사용. 최초 1회만 실행됨.
// 데이터 영역을 사용하므로 메모리 해제 신경 안써도 됨. 대신 지울 수도 없음.