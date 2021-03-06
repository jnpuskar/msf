﻿//
// (C) Copyright by Victor Derks
//
// See README.TXT for the details of the software licence.
//
#pragma once


#include "msfbase.h"


namespace msf
{

class IEnumFORMATETCPtr : public ::IEnumFORMATETCPtr
{
public:
    IEnumFORMATETCPtr() noexcept : ::IEnumFORMATETCPtr()
    {
    }

    bool Next(FORMATETC& formatetc)
    {
        return Next(1, &formatetc, nullptr);
    }

    bool Next(ULONG celt, FORMATETC* rgelt, ULONG* pceltFetched)
    {
        const HRESULT hr = GetInterfacePtr()->Next(celt, rgelt, pceltFetched);
        RaiseExceptionIfFailed(hr);

        return hr == S_OK;
    }
};


} // end msf namespace
