

#include "CExplorerBand.h"

void *operator new(size_t size)
{
    return malloc(size);
}

void operator delete(void *ptr)
{
}

extern "C" void __cxa_pure_virtual(void)
{
    __debugbreak();
}

void* p1 = (void*)CExplorerBand::UpdateRegistry;
void* p2 = (void*)CExplorerBand::_ClassFactoryCreatorClass::CreateInstance;
