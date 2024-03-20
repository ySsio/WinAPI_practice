#pragma once

class CObject;
enum class GROUP_TYPE;

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);

void DeleteObject(CObject* _pObj);

void ChangeScene(SCENE_TYPE _eNext);

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