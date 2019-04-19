
namespace Kex {

class XPCR
{
    //
    friend class PCR;

private:

    VOID
    Initialize (
        VOID);

};

XPCR*
GetPcr (VOID) const
{
    __readfsqword(FIELD_OFFSET(...));
}


} // namespace Ke

