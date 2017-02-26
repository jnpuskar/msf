//
// (C) Copyright by Victor Derks
//
// See README.TXT for the details of the software licence.
//

#include "stdafx.h"

#include "vvvfile.h"
#include "resource.h"
#include <msf.h>


class ATL_NO_VTABLE __declspec(uuid("EDD37CEF-F1E0-42bb-9AEF-177E0306AA71")) InfoTip :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<InfoTip, &__uuidof(InfoTip)>,
    public InfoTipImpl<InfoTip>
{
public:
    BEGIN_COM_MAP(InfoTip)
        COM_INTERFACE_ENTRY(IQueryInfo)
        COM_INTERFACE_ENTRY(IInitializeWithFile)
    END_COM_MAP()

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    static HRESULT WINAPI UpdateRegistry(BOOL bRegister) noexcept
    {
        return InfoTipImpl<InfoTip>::UpdateRegistry(bRegister, IDR_INFOTIP,
            L"VVV Sample InfoTip ShellExtension", wszVVVFileRootExt);
    }

    void InitializeImpl(const wchar_t* szFilename, DWORD /*dwMode*/)
    {
        VVVFile vvvfile(szFilename);

        _strLabel = vvvfile.GetLabel();
        _strFileCount = MSF::ToString(vvvfile.GetFileCount());
    }

    // Purpose: called by the shell/MSF when it needs the text for the infotip.
    //          The string is used for the tooltip and the text in the status bar.
    CString GetInfoTip(DWORD /* dwFlags */) const
    {
        return LoadString(IDS_SHELLEXT_LABEL) + L": " + _strLabel + L"\n" +
               LoadString(IDS_SHELLEXT_FILECOUNT) + L": " + _strFileCount;
    }

private:
    CString _strLabel;
    CString _strFileCount;
};

OBJECT_ENTRY_AUTO(__uuidof(InfoTip), InfoTip)
