﻿//
// (C) Copyright by Victor Derks
//
// See README.TXT for the details of the software licence.
//
#pragma once

#include "util.h"

namespace msf {

/// <summary>Base class for the Clipboard format handlers.</summary>
class ClipboardFormatHandler
{
public:
    ClipboardFormatHandler(const ClipboardFormatHandler&) = delete;
    ClipboardFormatHandler(ClipboardFormatHandler&&) = delete;
    virtual ~ClipboardFormatHandler() = default;
    ClipboardFormatHandler& operator=(const ClipboardFormatHandler&) = delete;
    ClipboardFormatHandler& operator=(ClipboardFormatHandler&&) = delete;

    CLIPFORMAT GetClipFormat() const noexcept
    {
        return m_clipformat;
    }

    bool CanGetData() const noexcept
    {
        return m_bCanGetData;
    }

    bool CanSetData() const noexcept
    {
        return m_bCanSetData;
    }

    virtual HRESULT Validate(const FORMATETC& formatetc) const noexcept
    {
        if (formatetc.dwAspect != DVASPECT_CONTENT)
            return DV_E_DVASPECT;

        if (!IsBitSet(formatetc.tymed, TYMED_HGLOBAL))
            return DV_E_TYMED;

        if (formatetc.lindex != -1)
            return DV_E_LINDEX;

        return S_OK;
    }

    virtual void GetData(const FORMATETC&, STGMEDIUM&) const
    {
    }

    virtual void SetData(const FORMATETC&, STGMEDIUM&, bool /*bRelease*/)
    {
    }

    bool IsValid(const FORMATETC& formatetc, const STGMEDIUM& stgmedium) const noexcept
    {
        return SUCCEEDED(Validate(formatetc)) && formatetc.tymed == stgmedium.tymed;
    }

protected:
    ClipboardFormatHandler(CLIPFORMAT clipformat, bool bCanGetData, bool bCanSetData) noexcept :
        m_clipformat(clipformat),
        m_bCanGetData(bCanGetData),
        m_bCanSetData(bCanSetData)
    {
    }

    ClipboardFormatHandler(PCWSTR lpszFormat, bool bCanGetData, bool bCanSetData) :
        m_clipformat(Win32::RegisterClipboardFormat(lpszFormat)),
        m_bCanGetData(bCanGetData),
        m_bCanSetData(bCanSetData)
    {
    }

private:
    CLIPFORMAT m_clipformat;
    bool       m_bCanGetData;
    bool       m_bCanSetData;
};

}
