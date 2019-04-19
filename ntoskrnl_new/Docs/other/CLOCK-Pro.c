
ULONG NumberOfNonResidentPages = 0;

AskHandHotForAction
{
    Done = 0;

    do
    {
        Current = HandHot;

        if (Current->Status == Hot)
        {
            if (Done) return;

            if (Current->Pte->Accessed)
            {
                Current->Pte->Accessed = 0;
            }
            else
            {
                Current->Status = Cold;
                Done = 1;
            }
        }
        else
        {
            Current->TestPeriod = 0;
            if (!Current->Resident)
            {
                RemovefromList(Current);
            }
        }

        HandHot = HandHot->Next;
    }
}


EvictPage()
{
    FoundPage = 0;

    do
    {
        Current = HandCold;
        ASSERT(Current->Resident);

        // what to do with hot pages or non resident?
        if (Current->Status == Hot)
        {
            // ????
            continue; ???
        }

        if (FoundPage) return FoundPage;

        if (Current->Pte->Accessed)
        {
            if (Current->TestPeriod)
            {
                Current->Status = Hot;

                AskHandHotForAction()
            }
            Current->Pte->Accessed = 0;
            MoveToListHead(Current);
        }
        else
        {
            Unmap(Current->Pte);
            if (!Current->TestPeriod)
            {
                RemoveFromList(Current);
                FoundPage = Current->Page;
            }

        }

        HandCold = HandCold->Next;
    }
}


RestoredPage(Page)
{
    ASSERT(Page->Status == Cold);

    if (!InList(Page))
    {
        InsertHeadList(Page);
    }
    else
    {
        Page->Status = Hot;
        MoveToListHead(Page);
    }

    Page->TestPeriod = 1;

}
