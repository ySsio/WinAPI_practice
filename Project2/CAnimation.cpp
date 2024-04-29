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
	

	vPos += m_vecFrm[m_iCurFrm].vOffset;	// offset 만큼 추가 이동

	// 렌더링 좌표로 변환
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
	// Animation의 이름을 저장한다. (문자열 저장) - 데이터 직렬화
	fprintf(pFile, "[Animation_Name]\n");
	//SaveWString(m_strName, pFile);
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// m_pTex
	// 텍스쳐는 리소스 매니저 쪽에서 load 할 거고, animation은 텍스쳐의 키값만 저장해 두면 됨.
	//SaveWString(m_pTex->GetKey(), pFile);
	// 추가로, 찾고자 하는 텍스처가 없을 경우 로드를 해야하기 때문에 사용하는 텍스처의 상대경로도 저장해둠
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
	// 모든 프레임 정보를 저장. 벡터이므로 먼저 몇 프레임인지를 맨 앞에 저장해야 함.
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

	// 모든 프레임 정보 배열이므로 한번에 쭉 저장
	// vector data() 함수 
	// : wstring의 c_str()처럼 vector가 내부적으로 사용하는 데이터 저장 공간의 직접적인 주소 리턴
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

	// 한 줄씩 읽어올 버퍼
	char szBuff[256] = {};
	//fscanf_s(pFile, "%s", szBuff, 256); // 공백문자 / 개행문자 만날때 까지 읽음
	// fscanf_s는 공백문자 만나면 끊기므로 getc()로 한 글자씩 읽어서 개행문자 만날 떄 끊어줄 거임
	// 개행문자 만날때만 끊기도록 함수 만들었음.
	//FScanf(szBuff, pFile);

	// wstring으로 바꾸기 위한 임시 저장 (1byte 가변)
	string str = "";


	//// m_strName
	//// 문자열 로드 (맨 앞에 글자 수 읽고, 그 글자 수 만큼 읽어서 로드)
	//LoadWString(m_strName, pFile);
	FScanf(szBuff, pFile);	// [Animation_Name]
	FScanf(szBuff, pFile);
	str = szBuff;

	m_strName = wstring(str.begin(), str.end());

	//// m_pTex
	//wstring strTexKey, strTexPath;
	//LoadWString(strTexKey, pFile);
	//LoadWString(strTexPath, pFile);
	//// LoadTexture에서 먼저 key 값으로 find를 한 다음 있으면 그걸 리턴하고 없으면 텍스처를 등록하고 리턴해줌
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
	//// 맨 앞에서 총 몇 프레임인지부터 읽음
	//size_t iFrameCount = 0;
	//fread(&iFrameCount, sizeof(size_t), 1, pFile);

	FScanf(szBuff, pFile);	// [Frame_Count]
	int iFrameCount = 0;
	fscanf_s(pFile, "%d\n", &iFrameCount);	// 문자열을 정수 포맷으로 변환해서 읽음

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
