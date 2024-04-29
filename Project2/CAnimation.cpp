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
	fprintf(pFile, "[Animation_Name]\n");
	//SaveWString(m_strName, pFile);
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// m_pTex
	// �ؽ��Ĵ� ���ҽ� �Ŵ��� �ʿ��� load �� �Ű�, animation�� �ؽ����� Ű���� ������ �θ� ��.
	//SaveWString(m_pTex->GetKey(), pFile);
	// �߰���, ã���� �ϴ� �ؽ�ó�� ���� ��� �ε带 �ؾ��ϱ� ������ ����ϴ� �ؽ�ó�� ����ε� �����ص�
	//SaveWString(m_pTex->GetRelativePath(), pFile);
	fprintf(pFile, "[Texture_Name]\n");
	strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture_Path]\n");
	strName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// m_vecFrm
	// ��� ������ ������ ����. �����̹Ƿ� ���� �� ������������ �� �տ� �����ؾ� ��.
	//size_t iFrameCount = m_vecFrm.size();
	//fwrite(&iFrameCount, sizeof(size_t), 1, pFile);
	fprintf(pFile, "[Frame_Count]\n");
	fprintf(pFile, "%d\n", (int)m_vecFrm.size());

	
	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fprintf(pFile, "\n");

		fprintf(pFile, "[Frame_Index]\n");
		fprintf(pFile, "%d\n", (int)i);

		fprintf(pFile, "[Left_Top]\n");
		fprintf(pFile, "%d, %d\n", (int)m_vecFrm[i].vLT.x, (int)m_vecFrm[i].vLT.y);

		fprintf(pFile, "[Slice_Size]\n");
		fprintf(pFile, "%d, %d\n", (int)m_vecFrm[i].vSlice.x, (int)m_vecFrm[i].vSlice.y);

		fprintf(pFile, "[Offset]\n");
		fprintf(pFile, "%d, %d\n", (int)m_vecFrm[i].vOffset.x, (int)m_vecFrm[i].vOffset.y);

		fprintf(pFile, "[Duration]\n");
		fprintf(pFile, "%f\n", m_vecFrm[i].fDuration);
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

	// �� �پ� �о�� ����
	char szBuff[256] = {};
	//fscanf_s(pFile, "%s", szBuff, 256); // ���鹮�� / ���๮�� ������ ���� ����
	// fscanf_s�� ���鹮�� ������ ����Ƿ� getc()�� �� ���ھ� �о ���๮�� ���� �� ������ ����
	// ���๮�� �������� ���⵵�� �Լ� �������.
	//FScanf(szBuff, pFile);

	// wstring���� �ٲٱ� ���� �ӽ� ���� (1byte ����)
	string str = "";


	//// m_strName
	//// ���ڿ� �ε� (�� �տ� ���� �� �а�, �� ���� �� ��ŭ �о �ε�)
	//LoadWString(m_strName, pFile);
	FScanf(szBuff, pFile);	// [Animation_Name]
	FScanf(szBuff, pFile);
	str = szBuff;

	m_strName = wstring(str.begin(), str.end());

	//// m_pTex
	//wstring strTexKey, strTexPath;
	//LoadWString(strTexKey, pFile);
	//LoadWString(strTexPath, pFile);
	//// LoadTexture���� ���� key ������ find�� �� ���� ������ �װ� �����ϰ� ������ �ؽ�ó�� ����ϰ� ��������
	//m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strTexPath);
	FScanf(szBuff, pFile);	// [Texture_Name]
	FScanf(szBuff, pFile);
	str = szBuff;

	wstring strTexKey = wstring(str.begin(), str.end());


	FScanf(szBuff, pFile);	// [Texture_Path]
	FScanf(szBuff, pFile);
	str = szBuff;

	wstring strTexPath = wstring(str.begin(), str.end());

	m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strTexPath);


	//// m_vecFrm
	//// �� �տ��� �� �� �������������� ����
	//size_t iFrameCount = 0;
	//fread(&iFrameCount, sizeof(size_t), 1, pFile);

	FScanf(szBuff, pFile);	// [Frame_Count]
	int iFrameCount = 0;
	fscanf_s(pFile, "%d\n", &iFrameCount);	// ���ڿ��� ���� �������� ��ȯ�ؼ� ����

	//m_vecFrm.reserve(iFrameCount);
	for (int i = 0; i < iFrameCount; ++i)
	{
		fscanf_s(pFile, "\n");

		tAnimFrm newFrm = {};

		int iData = 0;
		FScanf(szBuff, pFile);	// [Frame_Index]
		fscanf_s(pFile, "%d\n", &iData);

		int x = 0; int y = 0;

		FScanf(szBuff, pFile);	// [Left Top]
		fscanf_s(pFile, "%d, %d\n", &x, &y);
		newFrm.vLT = Vec2{ x,y };

		FScanf(szBuff, pFile);	// [Slice Size]
		fscanf_s(pFile, "%d, %d\n", &x, &y);
		newFrm.vSlice = Vec2{ x,y };

		FScanf(szBuff, pFile);	// [Offset]
		fscanf_s(pFile, "%d, %d\n", &x, &y);
		newFrm.vOffset = Vec2{ x,y };

		float fData = 0.f;

		FScanf(szBuff, pFile);	// [Duration]
		fscanf_s(pFile, "%f\n", &fData);
		newFrm.fDuration = fData;

		m_vecFrm.push_back(newFrm);
	}


	fclose(pFile);
}
