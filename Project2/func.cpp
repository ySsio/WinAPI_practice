#include "global.h"
#include "func.h"
#include "CEventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;
	
	// �̺�Ʈ �Ŵ������� ����
	// # ���� ���� ��¥ ���� ������ ��� ��ŷ���� �߰� �ּ� ó���ߴٰ� �����ϸ� ���� ������;
	CEventMgr::GetInst()->AddEvent(evn);
}

void DeleteObject(CObject* _pObj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeAIState(AI* _pAI, MON_STATE _eNextState)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::AI_STATE_CHANGE;
	evn.lParam = (DWORD_PTR)_pAI;
	evn.wParam = (DWORD_PTR)_eNextState;

	CEventMgr::GetInst()->AddEvent(evn);
	
}

void FScanf(char* _pOutBuff, FILE* _pFile)
{
	int i = 0;
	while (true)
	{
		char c = (char)getc(_pFile); // ���� �ϳ��� ����
		if (c == '\n')
		{
			_pOutBuff[i++] = '\0';
			break;
		}

		_pOutBuff[i++] = c;
	}
}

void SaveWString(const wstring& _str, FILE* _pFile)
{
	// ������ ����ȭ serialization ? ���� ���Ϸ� �����ϰ��� �ϴ� ������ �� �����Ͱ� ����
	// �� �ּҸ� �����ϸ� �ȵǴϱ� �� �����͸� �����ؼ� ���� �ʿ��� �����͸� �Ϸķ� ����
	// �������� �����͸� ���� ����
	const wchar_t* pStrName = _str.c_str(); // wstring Ÿ���� wchar_t*�� ���� ���ڿ��� ����� �ּҸ� ��ȯ��.
	size_t iLen = _str.length();

	// ���ڿ� ���̸� ���� �տ� �����ؼ� �ε��� �� ������ �� ���ڸ� �о�� �Ǵ� �� �� �� �ֵ��� ��.
	fwrite(&iLen, sizeof(size_t), 1, _pFile);

	// ���� ���ڿ� ����
	fwrite(pStrName, sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
	// �� �տ� �� ���� ����Ǿ� �ִ� ���� ���� ������ ���� �д´�.
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, _pFile);

	// ���۸� �غ��ؼ� �� �ȿ� ����� ���� �� ��ŭ ����.
	wchar_t szBuff[256] = {};
	fread(szBuff, sizeof(wchar_t), iLen, _pFile);

	// �޾ƿ� _str�� �־���
	_str = szBuff;
}

