#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"


// ���� 1.
// Ŭ�������� ������ ���� ����� �ۿ��� �ݵ�� �ʱ�ȭ ����� �Ѵ�. ���ϸ� ��ũ���� ��
// CCore* CCore::g_pInst = nullptr;



// ���� 2.
CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)

{

}

CCore::~CCore()
{
	// DC�� �޸𸮿��� ����.
	ReleaseDC(m_hWnd, m_hDC);

	// �纻 DC�� ����. ���� ������ DC�� �ٸ��� DeleteDC�� ����ؾ� �Ѵ�.
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����
	// �츮�� ���ϴ� �ػ󵵷� �簢�� ��ǥ ����
	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };

	// AdjustWindowRect : �츮�� �����Ϸ��� �ػ󵵸� �Ѱ��ָ� Ÿ��Ʋ, �޴���, �׵θ� ���� ��������� �����ؼ� SetWindowPos�� �־�� �� ������ ������ ��. (���ϰ� x)
	// ���� ���ϰ��� �ʹ� ũ�� (�������Ϳ� ��Ҵٰ� �޸𸮿� �����ϱ� ��ȿ������ ���) ���� ���ڿ� �ٽ� ������� �������ִ� ����� ä����.
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);	// 3��° ���ڴ� �޴��� ����ؾ� �ϴ��� ����

	// SetWindowPos : Ÿ��Ʋ â, �޴� ��, ������ �׵θ��� ������ ũ�⸦ ������
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	// Device Context Ŀ�� ������Ʈ -> �׸��� ���� �ʿ�
	// �޼��� ����� BeginPaint/EndPaint�� DC�� �����ϰ� release �ߴµ�,
	// �޼��� ��� �Ȼ���ϸ� GetDC�� DC�� ������ �����, �׸� �� �׸��� ���� release�� �ʿ䵵 ���� ���α׷� ������ �� �������ָ� ��. (�Ҹ��ڿ� ����)
	m_hDC = GetDC(m_hWnd);



	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC ����
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	// �̷��� ���� ������൵ ���� ���� ����. DC�� Bitmap�� ��������� ��. => SelectObject() 
	// => ���� ��Ʈ���� ��ȯ��. DC ������ �� �⺻������ �������� �ʿ��ϹǷ� 1��Ʈ ¥�� bitmap�� ��ϵǾ� ����. �̰� ��ȯ�޾Ƽ� ������.
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);



	// Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();


	
	return S_OK;
}

#include <iostream>

void CCore::progress()
{
	// Manager update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();
	
	// =========
	// Rendering
	// =========
	
	// ȭ�� û��
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	// ��Ʈ�ʿ��� ������ ���� (BitBlt = Bit-Block transfer).. ������ �����������..!!
	// ��û�� �ݺ�ó�� (�ܼ��۾�������) .. CPU Ȥ��
	// => �׷���ī��. Direct X�� �׷���ī�带 �ٷ�� �Լ� ���.
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);

	//CTimeMgr::GetInst()->render();
}

void CCore::update()
{
	// ��ü�� �������� üũ.

	// �񵿱� Ű ����� �Լ�
	// ��� â�� ��Ŀ�� �Ǿ����� ���� �� ���� ��׶��忡 �־ �׻� �����
	// GetAsyncKeyState : ���ϰ����� Ű�� ���ȴ��� �ô��� �̷� ���°��� ��Ʈǥ������ �ִµ�, Ű ���� ���¸� Ȯ���Ϸ��� 0x8000 �ڸ� Ȯ���ϸ� �ȴ�. �� ���ڸ�?

	// ��ǻ�� ó���ӵ��� �ʹ� ���� Ű ������ �� �ȼ� ������ �����ϸ� � �ȼ��� �� ������ �ѹ���
	// �׷��ٰ� �ܼ��� �Ǽ��� ��ȯ�ؼ� �����ص� ��ǻ�� ���ɿ� ���� �̵��� �޶��� �� ����. 
	// => �ð� ����ȭ. ��ǻ�Ͱ� �ƹ��� ���� �����ص� ���� �ð��� ��Ī�� �Ǿ�� �Ѵ�. �� �����Ӹ��� �����̴� ���� ���� ���̸� �� ��.
	// ��ǻ�� �ӵ��� ���� ���������� 1�ʸ� ����� ��. (��ǻ�Ͱ� ������ ������Ʈ���� ���� �����̰� �������� ������Ʈ���� ���� �����̰�)


	// �̷��� �����ϸ� 1�����ӿ� ���ÿ� ���� �ϵ��� �۾��ϴµ�, �۾� �߰��� Ű ���°� �ٲ������� 1������ �ȿ��� �ٸ� Ű�� ���� ������ �����ϴ� ��찡 �߻��� �� ����.
	// KeyMgr => 1. ������ ����ȭ. �� �����ӿ��� �߻��� �ϵ��� ������ Ű �Է¿� ���� �߻��ؾ� �Ѵ�.
	//			 2. ������ ���Ƿδ� �����ִ� ���¸� Ȯ���� �� �ִµ�, �����δ� Ű�ٿ�, Ű��, ŰȦ�� ���� ������ �����ؼ� ������ �ʿ伺 ����.
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	//	vPos.x -= 400.f * fDT;
	// # �ٵ� ã�� ���ϱ� 0, 0x8000, 1, 0x8001�� NONE, TAP, AWAY, HOLD ó�� �����ϴ°� ������ �ƴѰ�?

}

void CCore::render()
{
	
	
}
