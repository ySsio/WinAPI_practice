#include "global.h"
#include "func.h"
#include "CEventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;
	
	// 이벤트 매니저에게 전달
	// # ㅅㅂ 뭐지 진짜 여기 때문에 계속 링킹에러 뜨고 주석 처리했다가 해제하면 오류 없어짐;
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
		char c = (char)getc(_pFile); // 문자 하나를 읽음
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
	// 데이터 직렬화 serialization ? 내가 파일로 저장하고자 하는 데이터 중 포인터가 있음
	// 그 주소를 저장하면 안되니까 그 포인터를 참조해서 순수 필요한 데이터를 일렬로 나열
	// 실질적인 데이터를 얻어내는 과정
	const wchar_t* pStrName = _str.c_str(); // wstring 타입을 wchar_t*로 실제 문자열이 저장된 주소를 반환함.
	size_t iLen = _str.length();

	// 문자열 길이를 가장 앞에 저장해서 로드할 때 앞으로 몇 글자를 읽어야 되는 지 알 수 있도록 함.
	fwrite(&iLen, sizeof(size_t), 1, _pFile);

	// 실제 문자열 저장
	fwrite(pStrName, sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
	// 맨 앞에 몇 글자 저장되어 있는 지에 대한 정보를 먼저 읽는다.
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, _pFile);

	// 버퍼를 준비해서 그 안에 저장된 글자 수 만큼 읽음.
	wchar_t szBuff[256] = {};
	fread(szBuff, sizeof(wchar_t), iLen, _pFile);

	// 받아온 _str에 넣어줌
	_str = szBuff;
}

