
VOID
NTAPI
KiUserApcDispatcher(
    IN PVOID NormalRoutine,
    IN PVOID NormalContext,
    IN PVOID SystemArgument1,
    IN PVOID SystemArgument2)
{

    /* Setup SEH stack */
    SehRecord.Next = __readfsdword(FIELD_OFFSET(TEB, ExceptionList));
    SehRecord.Handler = KiUserApcExceptionHandler;

    /* Enable SEH */
    _writefsdword(FIELD_OFFSET(TEB, ExceptionList), &SehRecord);

    /* Put the Context in EDI */
    pop eax

    Context = &[esp+12]

    /* Call the APC Routine */
    call eax

    /* Restore exception list */
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
