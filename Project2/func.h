#pragma once

class CObject;
class AI;
enum class GROUP_TYPE;

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(CObject* _pObj);
void ChangeScene(SCENE_TYPE _eNext);
void ChangeAIState(AI* _pAI, MON_STATE _eNextState);

template <typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (_vec[i] != nullptr)
			delete _vec[i];
	}
	_vec.clear();
}

template <typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	// template���� inner class �� ����Ϸ��� typename�� �տ� �ٿ���� �Ѵ�.
	typename map<T1, T2>::iterator iter = _map.begin();
	for (; iter != _map.end(); ++iter)
	{
		if (iter->second != nullptr)
		{
			delete iter->second;
		}
	}
	_map.clear();
}

void FScanf(char* _pOutBuff, FILE* _pFile);

void SaveWString(const wstring& _str, FILE* _pFile); // _str�� ������ ���Ͽ� ����
void LoadWString(wstring& _str, FILE* _pFile); // _str�� ���Ͽ��� �ҷ��� ������ ����