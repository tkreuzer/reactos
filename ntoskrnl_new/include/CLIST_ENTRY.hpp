#define NO_KERNEL_LIST_ENTRY_CHECKS 1
#include "brush.hpp"

#ifdef _MSC_VER
#pragma optimize( "g", on )
#endif

DBG_DEFAULT_CHANNEL(GdiBrush);

class CLIST_ENTRY
{
protected:
    LIST_ENTRY _ListEntry;

    inline
    VOID
    CheckListEntry (
        VOID)
    {
#ifndef NO_KERNEL_LIST_ENTRY_CHECKS
        if (((_ListEntry.Flink->Blink) != &_ListEntry) ||
            ((_ListEntry.Blink->Flink) != &_ListEntry))
        {
            FatalListEntryError((PVOID)&_ListEntry,
                                (PVOID)_ListEntry.Flink->Blink,
                                (PVOID)_ListEntry.Blink->Flink);
        }
#endif
    }

    //__attribute__((returns_nonnull))
    inline
    LIST_ENTRY&
    GetFlink (
        VOID) const
    {
        return *_ListEntry.Flink;
    }

public:

    inline
    CLIST_ENTRY (
        VOID)
    {
        _ListEntry.Blink = _ListEntry.Flink = &_ListEntry;
    }

    inline
    ~CLIST_ENTRY (
        VOID)
    {
#ifndef NO_KERNEL_LIST_ENTRY_CHECKS
        if ((_ListEntry.Flink != &_ListEntry) ||
            (_ListEntry.Blink != &_ListEntry))
        {
            FatalListEntryError((PVOID)&_ListEntry,
                                (PVOID)_ListEntry.Flink,
                                (PVOID)_ListEntry.Blink);
        }
#endif
    }


};

class LIST_LINK : public CLIST_ENTRY
{
    friend class LINKED_LIST;

public:

    inline
    VOID
    RemoveFromList (
        VOID)
    {
        CheckListEntry();
        RemoveEntryList(&_ListEntry);
        _ListEntry.Blink = _ListEntry.Flink = &_ListEntry;
    }

};
typedef class LIST_LINK *PLIST_LINK;

//#define NULLCHECK

class LINKED_LIST : public CLIST_ENTRY
{
public:

    inline
    bool
    IsEmpty (
        VOID) const
    {
        //return IsListEmpty(&_ListEntry);
        return (_ListEntry.Flink == &_ListEntry);
    }

    inline
    bool
    IsListHead (
        const LIST_LINK *Link) const
    {
#ifdef NULLCHECK
        return (Link == NULL);
#else
        return (&Link->_ListEntry == &_ListEntry);
#endif
    }

    inline
    PLIST_LINK
    GetHead (
        VOID) const
    {
        LIST_ENTRY &ListEntry = GetFlink();
#ifdef NULLCHECK
        return (&ListEntry != &_ListEntry) ? (PLIST_LINK)&ListEntry : nullptr;
        //__assume(ListEntry != NULL);
        //if (ListEntry == NULL) __builtin_unreachable();
        if (&ListEntry == &_ListEntry)
        {
            return NULL;
        }
#endif
        return (PLIST_LINK)&ListEntry;
    }

    inline
    PLIST_LINK
    GetTail (
        VOID) const
    {
        PLIST_ENTRY ListEntry = _ListEntry.Blink;
#ifdef NULLCHECK
        return (ListEntry != &_ListEntry) ? (PLIST_LINK)ListEntry : nullptr;
        //__assume(ListEntry != NULL);
        if (ListEntry == &_ListEntry)
        {
            return NULL;
        }
#endif
        return (PLIST_LINK)ListEntry;
    }

    inline
    PLIST_LINK
    GetNext (
        _In_ const LIST_LINK *ListLink) const
    {
        LIST_ENTRY &Flink = ListLink->GetFlink();
#ifdef NULLCHECK
        return (&Flink != &_ListEntry) ? (PLIST_LINK)&Flink : nullptr;
#endif
        return (PLIST_LINK)&Flink;
    }

    inline
    PLIST_LINK
    RemoveHead (
        VOID)
    {
    #if 0
        PLIST_ENTRY ListEntry;
#ifdef NULLCHECK
        if (IsListEmpty(&_ListEntry))
        {
            return NULL;
        }
#endif
        ListEntry = RemoveHeadList(&_ListEntry);
        ListEntry->Blink = ListEntry->Flink = ListEntry;
        return (PLIST_LINK)ListEntry;
///
#endif
        PLIST_ENTRY ListEntry, Flink;

        ListEntry = _ListEntry.Flink;
#ifdef NULLCHECK
        if (ListEntry == &_ListEntry) return NULL;
        //__assume(ListEntry != NULL);
#endif
        Flink = ListEntry->Flink;
        _ListEntry.Flink = Flink;
        Flink->Blink = &_ListEntry;
        return (PLIST_LINK)ListEntry;
    }

    inline
    PLIST_LINK
    RemoveTail (
        VOID)
    {
#ifdef NULLCHECK
        if (IsListEmpty(&_ListEntry))
        {
            return NULL;
        }
#endif
        return (PLIST_LINK)RemoveTailList(&_ListEntry);
    }

    inline
    VOID
    InsertHead (
        _Out_ PLIST_LINK Link)
    {
        InsertHeadList(&_ListEntry, &Link->_ListEntry);
    }

    inline
    VOID
    InsertTail (
        _Out_ PLIST_LINK Link)
    {
        InsertTailList(&_ListEntry, &Link->_ListEntry);
    }

};

typedef class LINKED_LIST *PLINKED_LIST;

ULONG
TestListC_Count(PLIST_ENTRY ListHead)
{
    PLIST_ENTRY ListEntry;
    ULONG Count = 0;

    ListEntry = ListHead->Flink;
    while (ListEntry != ListHead)
    {
        ListEntry = ListEntry->Flink;
        Count++;
    }
    return Count;
}

ULONG
TestListCpp_Count(PLINKED_LIST LinkedList)
{
    PLIST_LINK ListLink;
    ULONG Count = 0;

    ListLink = LinkedList->GetHead();
    while (!LinkedList->IsListHead(ListLink))
    {
        ListLink = LinkedList->GetNext(ListLink);
        Count++;
    }
    return Count;
}

class TEST
{
protected:
    int _i{3};
};

class TEST2 : public TEST
{
public :
    int& _Value = _i;

};

//C_ASSERT(sizeof(TEST2) == sizeof(TEST));

int TestInit()
{
    TEST2 t;

    return t._Value;
}

#if 0
template<class _Type, _Type _Get(void), _Type _Set(_Type)>
class _TGETSET
{
    _Type _Value;

    _Type
    operator= (_Type NewValue)
    {
        return _Set(NewValue);
    }

    operator _Type()
    {
        return _Get
    }
}
#endif // 0

#undef PCR

class PCR
{
protected:
    class PCR *_Self;
    void *_CurrentThread;

    int _Value1;

};

class CURRENT_PCR : public PCR
{

public:

    const int &_Value1 = PCR::_Value1;

    static class CURRENT_PCR * GetSelf(void)
    {
        return (class CURRENT_PCR *)__readfsdword(FIELD_OFFSET(CURRENT_PCR, _Self));
    }

    static void* GetCurrentThread(void)
    {
        return (void*)__readfsdword(FIELD_OFFSET(CURRENT_PCR, _CurrentThread));
    }
};

class CURRENT_PCR_REF
{
public:

    CURRENT_PCR * operator ->()
    {
        return CURRENT_PCR::GetSelf();
    }
};

CURRENT_PCR_REF CurrentPcr;

//CURRENT_PCR& CurrentPcr2 = *CURRENT_PCR::GetSelf();

#define CurrentPcr (*CURRENT_PCR::GetSelf())

void* TestPcr()
{
    return CurrentPcr.GetCurrentThread();
}

