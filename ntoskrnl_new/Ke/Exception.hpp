
#pragma once

#include "Kep.hpp"


class EXCEPTION : EXCEPTION_RECORD, EXCEPTION_FRAME, TRAP_FRAME
{

    VOID
        GetContext(
            _Out_ PCONTEXT OutContext);

    VOID
        Dispatch(
            VOID);



};
