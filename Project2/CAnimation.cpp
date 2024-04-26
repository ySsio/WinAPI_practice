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
	fprintf(pFile, "[Animation Name]\n");
	//SaveWString(m_strName, pFile);
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// m_pTex
	// 텍스쳐는 리소스 매니저 쪽에서 load 할 거고, animation은 텍스쳐의 키값만 저장해 두면 됨.
	//SaveWString(m_pTex->GetKey(), pFile);
	// 추가로, 찾고자 하는 텍스처가 없을 경우 로드를 해야하기 때문에 사용하는 텍스처의 상대경로도 저장해둠
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
	// 모든 프레임 정보를 저장. 벡터이므로 먼저 몇 프레임인지를 맨 앞에 저장해야 함.
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

	// m_strName
	// 문자열 로드 (맨 앞에 글자 수 읽고, 그 글자 수 만큼 읽어서 로드)
	LoadWString(m_strName, pFile);

	// m_pTex
	wstring strTexKey, strTexPath;
	LoadWString(strTexKey, pFile);
	LoadWString(strTexPath, pFile);
	// LoadTexture에서 먼저 key 값으로 find를 한 다음 있으면 그걸 리턴하고 없으면 텍스처를 등록하고 리턴해줌
	m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strTexPath);
	
	// m_vecFrm
	// 맨 앞에서 총 몇 프레임인지부터 읽음
	size_t iFrameCount = 0;
	fread(&iFrameCount, sizeof(size_t), 1, pFile);

	// 모든 프레임 정보 배열이므로 한번에 쭉 저장
	// 벡터 공간을 미리 확보해 두고 메모리를 한 번에 덮어 씀
	m_vecFrm.resize(iFrameCount); // resize : count를 미리 확보. vs reserve : capacity를 미리 확보
	fread(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);


	fclose(pFile);
}
