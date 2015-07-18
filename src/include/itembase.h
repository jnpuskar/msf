//
// (C) Copyright by Victor Derks
//
// See README.TXT for the details of the software licence.
//
#pragma once


namespace MSF
{

// Purpose: base class for items contained in a shellfolder.
//          The itembase doesn't own the actual item.
class CItemBase
{
public:
    CItemBase(LPCITEMIDLIST pidl) throw() :
        m_pidl(pidl)
    {
    }


    USHORT GetDataSize() const throw()
    {
        return m_pidl->mkid.cb - sizeof(short);
    }


    const BYTE* GetData() const throw()
    {
        return m_pidl->mkid.abID;
    }


    LPCITEMIDLIST GetItemIdList() const
    {
        return m_pidl;
    }

private:

    LPCITEMIDLIST m_pidl;
};

} // end MSF namespace