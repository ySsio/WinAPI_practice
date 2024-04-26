#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CCamera.h"
#include "CPathMgr.h"
#include "CResMgr.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}


void CAnimation::update()
{
	if (m_bFinish) return;

	m_fAccTime += fDT;

	if (m_fAccTime >= m_vecFrm[m_iCurFrm].fDuration)
	{
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;

		if (m_iCurFrm == m_vecFrm.size() - 1)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
		}
		else	
			++m_iCurFrm;
	}
	
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish) return;

	CObject* pObj = m_pAnimator->GetOwner();
	Vec2 vPos = pObj->GetPos();
	

	vPos += m_vecFrm[m_iCurFrm].vOffset;	// offset ��ŭ �߰� �̵�

	// ������ ��ǥ�� ��ȯ
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
		, m_pTex->GetDC()
		, (int)(m_vecFrm[m_iCurFrm].vLT.x)
		, (int)(m_vecFrm[m_iCurFrm].vLT.y)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
			, RGB(255, 0, 255));

}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;
	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.vLT = _vLT + _vStep * i;
		frm.vSlice = _vSliceSize;
		frm.fDuration = _fDuration;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	assert(pFile);

	// m_strName
	// Animation�� �̸��� �����Ѵ�. (���ڿ� ����) - ������ ����ȭ
	fprintf(pFile, "[Animation Name]\n");
	//SaveWString(m_strName, pFile);
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// m_pTex
	// �ؽ��Ĵ� ���ҽ� �Ŵ��� �ʿ��� load �� �Ű�, animation�� �ؽ����� Ű���� ������ �θ� ��.
	//SaveWString(m_pTex->GetKey(), pFile);
	// �߰���, ã���� �ϴ� �ؽ�ó�� ���� ��� �ε带 �ؾ��ϱ� ������ ����ϴ� �ؽ�ó�� ����ε� �����ص�
	//SaveWString(m_pTex->GetRelativePath(), pFile);
	fprintf(pFile, "[Texture Name]\n");
	strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture Path]\n");
	strName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// m_vecFrm
	// ��� ������ ������ ����. �����̹Ƿ� ���� �� ������������ �� �տ� �����ؾ� ��.
	//size_t iFrameCount = m_vecFrm.size();
	//fwrite(&iFrameCount, sizeof(size_t), 1, pFile);
	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d\n", (int)m_vecFrm.size());

	
	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fprintf(pFile, "[Frame Index]\n");
		fprintf(pFile, "%d\n", (int)i);

		fprintf(pFile, "[Left Top]\n");
		fprintf(pFile, "%d, %d\n", (int)m_vecFrm[i].vLT.x, (int)m_vecFrm[i].vLT.y);

		fprintf(pFile, "[Slice Size]\n");
		fprintf(pFile, "%d, %d\n", (int)m_vecFrm[i].vSlice.x, (int)m_vecFrm[i].vSlice.y);

		fprintf(pFile, "[Offset]\n");
		fprintf(pFile, "%d, %d\n", (int)m_vecFrm[i].vOffset.x, (int)m_vecFrm[i].vOffset.y);

		fprintf(pFile, "[Duration]\n");
		fprintf(pFile, "%f\n", m_vecFrm[i].fDuration);

		fprintf(pFile, "\n\n");
	}

	// ��� ������ ���� �迭�̹Ƿ� �ѹ��� �� ����
	// vector data() �Լ� 
	// : wstring�� c_str()ó�� vector�� ���������� ����ϴ� ������ ���� ������ �������� �ּ� ����
	//fwrite(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);



	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	// m_strName
	// ���ڿ� �ε� (�� �տ� ���� �� �а�, �� ���� �� ��ŭ �о �ε�)
	LoadWString(m_strName, pFile);

	// m_pTex
	wstring strTexKey, strTexPath;
	LoadWString(strTexKey, pFile);
	LoadWString(strTexPath, pFile);
	// LoadTexture���� ���� key ������ find�� �� ���� ������ �װ� �����ϰ� ������ �ؽ�ó�� ����ϰ� ��������
	m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strTexPath);
	
	// m_vecFrm
	// �� �տ��� �� �� �������������� ����
	size_t iFrameCount = 0;
	fread(&iFrameCount, sizeof(size_t), 1, pFile);

	// ��� ������ ���� �迭�̹Ƿ� �ѹ��� �� ����
	// ���� ������ �̸� Ȯ���� �ΰ� �޸𸮸� �� ���� ���� ��
	m_vecFrm.resize(iFrameCount); // resize : count�� �̸� Ȯ��. vs reserve : capacity�� �̸� Ȯ��
	fread(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);


	fclose(pFile);
}
