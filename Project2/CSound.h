#pragma once
#include "CRes.h"
#include "CSoundMgr.h"

class CSound :
    public CRes
{
private:
    LPDIRECTSOUNDBUFFER     m_pSoundBuffer;
    DSBUFFERDESC            m_tBuffInfo;
    int                     m_iVolume;


public:
    int Load(const wstring& _strPath);

    // �Ϲ� ���
    void Play(bool _bLoop = false);

    // BGM���� ���
    void PlayToBGM(bool _bLoop = false);

    void Stop(bool _bReset = false);

    // ���� ���� (0~100)
    void SetVolume(float _fVolume);

    // �������� ��ġ ����
    void SetPosition(float _fPosition);

public:
    bool LoadWaveSound(const wstring& _strPath);
    // ����� ���� ������ ���ú��� ��������
    int GetDecibel(float _fVolume);


public:
    CSound();
    ~CSound();
};

