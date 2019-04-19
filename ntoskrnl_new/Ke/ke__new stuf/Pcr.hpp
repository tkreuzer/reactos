
#include _ARCH_RELATIVE_(XPcr.hpp)

namespace Ke {

class PCR : private XPCR, XPRCB
{

    friend class KERNEL;

private:
    VOID
    Initialize (
        VOID);

public:

    inline
    class THREAD*
    GetCurrentThread (
        VOID) const
    {
        return m_CurrentThread;
    }

    using XPCR::GetCurrentPrcb;

};

inline
PCR*
GetPcr (VOID)
{
    return XPCR::GetPcr();
}

} // namespace Ke

VOID
PCR::Initialze (
    VOID)
{
    Rtl::ZeroMemory(this, sizeof(*this));

    XPCR::Initialize();
}

