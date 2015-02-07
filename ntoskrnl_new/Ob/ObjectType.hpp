
namespace Ob {

typedef class OBJECT_TYPE *POBJECT_TYPE;
extern "C" POBJECT_TYPE ObpTypeObjectType;

class OBJECT_TYPE : public OBJECT
{
private:
    LIST_ENTRY _TypeList;
    UNICODE_STRING _Name;
    PVOID _DefaultObject;
    UCHAR _Index;
    ULONG _TotalNumberOfObjects;
    ULONG _TotalNumberOfHandles;
    ULONG _HighWaterNumberOfObjects;
    ULONG _HighWaterNumberOfHandles;
    OBJECT_TYPE_INITIALIZER _TypeInfo;
    EX_PUSH_LOCK _TypeLock;
    ULONG _Key;
    LIST_ENTRY _CallbackList;

    static const UCHAR TypeObjectTypeIndex = 0;
    static const ULONG MAX_OBJECT_TYPES = 255;
    static POBJECT_TYPE ObjectTypeTable[MAX_OBJECT_TYPES];
    static LONG NextObjectIndex;


public:

    static
    VOID
    InitializeClass (
        VOID);

    void*
    operator new (
        _In_ size_t Size) throw();

    OBJECT_TYPE (
        _In_ PCUNICODE_STRING TypeName,
        _In_ POBJECT_TYPE_INITIALIZER TypeInitializer);

    ~OBJECT_TYPE (
        VOID);

    NTSTATUS
    CreateObject (
        _Out_ PVOID *Object,
        _In_ SIZE_T ObjectSize,
        _In_ POBJECT_ATTRIBUTES ObjectAttributes,
        _In_opt_ SIZE_T PagedPoolCharge,
        _In_opt_ SIZE_T NonPagedPoolCharge);

    VOID
    InsertObject (
        _In_ POBJECT Object);

    VOID
    RemoveObject (
        _In_ POBJECT Object);

    inline
    UCHAR
    GetIndex (
        VOID)
    {
        return _Index;
    }

    inline
    POBJECT_TYPE
    GetObjectType (
        VOID)
    {
        return ObjectTypeTable[_Index];
    }

};


}; // namespace Ob
