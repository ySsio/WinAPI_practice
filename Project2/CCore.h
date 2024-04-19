#pragma once

// �̱��� ����
// 1. ��ü�� ������ 1���� ����.
// 2. ��𼭵� ���� �����ؾ� ��. 

//      => ������ �Ҹ��ڸ� private���� �����?  extern ���� �� �� ����. (2�� ����)
//		=> extern?  class�� extern���� �����Ѵٴ� �� ��ü�� ��ü�� ���� �� ���� �� �ִٴ� ��. (1�� ����)
// => Ư�� �Լ��� ���� �� �Լ��θ� ��ü�� ����?  �ٵ� ��ü�� �־�� ��� �Լ� ��밡��
// => static �Լ� : ��ü�� ��� ȣ���� �� ���� ��� �Լ�. ��ü�� ���� ȣ���ص� ��ü�� ����� ������ �� ����. this�� ����.




// �̱��� ����
// 1. class�� static ������ ���� (��ü�� heap��, �����ʹ� data ������ ����)
// 2. �������� Ȱ�� ? - ��ü�� ������ ������ �ø��� ���



// ���� 1.
//class CCore
//{
//public:
//	static CCore* g_pInst;	// ���� ��� (������ ����) - ��ü�� �����ص� ����(��������)/��(�����Ҵ�)�� �������� �ʰ� ������ ������ ��� �ϳ��θ� ������.
//							// Ŭ���� ���ο����� ���� ����
//
//							// GetInstance�� ���������� ����� Release �Լ����� GetInstance�� ȣ���ؼ� ���޸� ��� ���� �ִµ�, Release �ߴµ� ���߿� �ٽ� 
//							// ��ü�� ���� ����Ϸ��� �� �� �����ͺ����� �� ������ ���� ����Ű�� �ֱ� ������ nullptr�� �ƴ� ���� �߻�.
//							// �ᱹ ������ ������ nullptr�� �ٲ���� �Ǵµ�, ������ ������ GetInstance������ �����Ҽ� �����ϱ� �Ұ���.
//							// �ᱹ �� �Լ� �� ���� �� �� �ֵ��� Ŭ���� ���� ������ ��������.
//
// // ������, �Ҹ��� ����
//private:
//	CCore();
//	~CCore();
//
//public :
//	// ���� ��� �Լ�, ��ü ���� ȣ�� ����, this�� ���� (����� ���� �Ұ�) - static ����� ���� ����
//	static CCore* GetInstance()
//	{
//		// �Լ��� ���� ȣ�� �� ��� - ��ü ���� (���� �Ҵ�)
//		if (g_pInst == nullptr)
//		{
//			g_pInst = new CCore;
//		}
//		// => pCore��� ������ ���������� ������ ������, ���� CCore ��ü�� �� ������ �����.										
//
//		// 2�� �̻� ȣ�� �� ���
//		// �̹� ������� �ִ� �� ��ȯ
//
//		return g_pInst;
//	}
//
//	static void Release()
//	{
//		if (g_pInst == nullptr)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//		
//		return;
//	}
//
//};

class CTexture;

// ���� 2.
class CCore
{
	SINGLETON(CCore);

private:
	HWND		m_hWnd;			// ���� ������ �ڵ�
	POINT		m_ptResolution; // ���� ������ �ػ�
	HDC			m_hDC;			// ���� �����쿡 �׸� DC


	// ���� ���۸� - �纻�� DC
	//HBITMAP	m_hBit;
	//HDC		m_memDC;		// �纻 ��Ʈ�ʿ� �׸� DC
	CTexture*	m_pMemTex;		// ����� �ؽ���

	// ���� ����ϴ� GDI Object (Graphic Device Interface object)
	HBRUSH		m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN		m_arrPen[(UINT)PEN_TYPE::END];

	// �޴�
	HMENU		m_hMenu;

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockMenu();
	void SeparateMenu();
	void ChangeWindowSize(POINT _vResolution, bool _bMenu);

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};

// �Ŵ��� ���� �ֵ��� �̱��� �������� ���� ������ ������. => ��ũ�� �Լ��� ����� ����.