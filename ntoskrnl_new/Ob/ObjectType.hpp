
namespace Ob {

typedef class OBJECT_TYPE *POBJECT_TYPE;

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
        POBJECT_TYPE_INITIALIZER TypeInitializer);

    ~OBJECT_TYPE (
        VOID);

    NTSTATUS
    InsertObject (
        _In_ POBJECT Object);

    VOID
    RemoveObject (
        _In_ POBJECT Object);

};


}; // namespace Ob
