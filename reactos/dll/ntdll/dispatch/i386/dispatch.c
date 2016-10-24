
VOID
NTAPI
KiUserApcDispatcher(
    IN PVOID NormalRoutine,
    IN PVOID NormalContext,
    IN PVOID SystemArgument1,
    IN PVOID SystemArgument2)
{

    /* Setup SEH stack */
    //lea eax, [esp+CONTEXT_ALIGNED_SIZE+16]
    //mov ecx, fs:[TEB_EXCEPTION_LIST]
    //mov [eax], ecx
    SehRecord.Next = __readfsdword(FIELD_OFFSET(TEB, ExceptionList));

    //mov edx, offset _KiUserApcExceptionHandler
    //mov [eax+4], edx
    SehRecord.Handler = KiUserApcExceptionHandler;

    /* Enable SEH */
    //mov fs:[TEB_EXCEPTION_LIST], eax
    _writefsdword(FIELD_OFFSET(TEB, ExceptionList), &SehRecord);

    /* Put the Context in EDI */
    //pop eax
    //lea Context, [esp+12]
    Context = &[esp+12]

    /* Call the APC Routine */
    call eax

    /* Restore exception list */
    //mov ecx, [Context+CONTEXT_ALIGNED_SIZE]
    //mov fs:[TEB_EXCEPTION_LIST], ecx
    _writefsdword(FIELD_OFFSET(TEB, ExceptionList), SehRecord.Next);

    /* Switch back to the context */
    Status = ZwContinue(Context, 1);

    /* Raise status */
StatusRaiseApc:
    RtlRaiseStatus(Status);
    goto StatusRaiseApc;
}


KiRaiseUserExceptionDispatcher
{
    EXCEPTION_RECORD ExceptionRecord;



}
