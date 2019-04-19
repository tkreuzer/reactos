


class TIMER : public DISPATCHER_OBJECT
{
    union CONTROL_FLAGS
    {
        UCHAR Value;
        struct
        {
            UCHAR Absolute : 1;
            UCHAR Wake : 1;
            UCHAR EncodedTolerableDelay : 6;
        };
    };

    union MISC_FLAGS
    {
        UCHAR Value;
        struct
        {
#ifdef _M_AMD64
            UCHAR Index : TIMER_EXPIRED_INDEX_BITS;
#else
            UCHAR Index : 1;
            UCHAR Processor : TIMER_PROCESSOR_INDEX_BITS;
#endif
            UCHAR Inserted : 1;
            volatile UCHAR Expired : 1;
        };
    };

    /* "Rename" some members */
    CONTROL_FLAGS &ControlFlags = _Extra1;
    UCHAR &Hand = _Extra2;
    MISC_FLAGS &MiscFlags = _Extra3;

};

