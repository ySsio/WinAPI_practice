#pragma once

// ��ũ�� ����

// ��ũ�� �Լ�
// �������� ���̸� �̾���.

#define SINGLETON(type)		public:								\
							static type* GetInst()				\
							{									\
								static type mgr;				\
								return &mgr;					\
							}									\

// �Լ� �� ���������� ���� - ������ ���� ���. ���� 1ȸ�� �����.
// ������ ������ ����ϹǷ� �޸� ���� �Ű� �Ƚᵵ ��. ��� ���� ���� ����.