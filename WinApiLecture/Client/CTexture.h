#pragma once
#include "CRes.h"
class CTexture :
    public CRes
{

private:
    HDC         m_dc;
    HBITMAP     m_hBit;
    BITMAP      m_bitInfo;

public:
    void Load(const wstring& _strFilePath);

    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDC() { return m_dc; }

    // ���ҽ� �Ŵ��� �̿ܿ� �ؽ�ó�� �����Ҵ� �� �� ������ private����, friend class ���
private:
    CTexture();
    ~CTexture();

    friend class CResMgr;
};

