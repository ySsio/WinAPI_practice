#pragma once

// ��ũ�� ����

// ��ũ�� �Լ�
// �������� ���̸� �̾���.

#define SINGLETON(type)	public:									\
							static type* GetInst()				\
							{									\
								static type mgr;				\
								return &mgr;					\
							}									\
						private:								\
							type();								\
							~type();							\

// �Լ� �� ���������� ���� - ������ ���� ���. ���� 1ȸ�� �����.
// ������ ������ ����ϹǷ� �޸� ���� �Ű� �Ƚᵵ ��. ��� ���� ���� ����.