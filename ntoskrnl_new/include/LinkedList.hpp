
class CLIST_ENTRY
{
protected:
    LIST_ENTRY _ListEntry;

    CLIST_ENTRY (
        VOID)
    {
        _ListEntry.Blink = _ListEntry.Flink = &_ListEntry;
    }

    ~CLIST_ENTRY (
        VOID)
    {
        if ((_ListEntry.Flink != &_ListEntry) ||
            (_ListEntry.Blink != &_ListEntry))
        {
            FatalListEntryError(_ListEntry.Blink, &_ListEntry, _ListEntry.Flink);
        }
    }

};

class LIST_LINK : public CLIST_ENTRY
{
public:

    VOID
    RemoveFromList (
        VOID)
    {
        RemoveEntryList(&_ListEntry);
        _ListEntry.Blink = _ListEntry.Flink = &_ListEntry;
    }

};

class LINKED_LIST : public CLIST_ENTRY
{

public:

    bool
    IsEmpty (
        VOID)
    {
        return IsListEmpty(&_ListEntry);
    }

    PLIST_LINK
    GetHead (
        VOID)
    {
        PLIST_ENTRY ListEntry = _ListEntry.Flink;
        if (ListEntry == &_ListEntry)
        {
            return NULL;
        }
        return (PLIST_LINK)ListEntry;
    }

    PLIST_LINK
    GetTail (
        VOID)
    {
        PLIST_ENTRY ListEntry = _ListEntry.Blink;
        if (ListEntry == &_ListEntry)
        {
            return NULL;
        }
        return (PLIST_LINK)ListEntry;
    }

    PLIST_LINK
    GetNext (
        _In_ PLIST_LINK ListLink)
    {
        PLIST_ENTRY Flink = ListLink->_ListEntry.Flink;
        if (Flink == &_ListEntry)
        {
            return NULL;
        }
        return (PLIST_LINK)Flink;
    }

    PLIST_LINK
    RemoveHead (
        VOID)
    {
        if (IsListEmpty(&_ListEntry))
        {
            return NULL;
        }
        return (PLIST_LINK)RemoveHeadList(&_ListEntry);
    }

    PLIST_LINK
    RemoveTail (
        VOID)
    {
        if (IsListEmpty(&_ListEntry))
        {
            return NULL;
        }
        return RemoveTailList(&_ListEntry);
    }

    VOID
    InsertHead (
        _Out_ PLIST_LINK Link)
    {
        InsertHeadList(
    }

};

{
    while (!List->IsEmpty())
    {
        Link = List->RemoveHead();


    }

    for (Link = List->GetHead(); Link != NULL; List->GetNext(Link))
    {
    }

    for (auto entry : List)
    {
    }
}
