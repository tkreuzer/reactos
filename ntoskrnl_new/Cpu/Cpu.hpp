
#pragma once

#if defined(_M_AMD64)
#include "Cpu_amd64.hpp"
#elif defined(_M_IX86)
#include "Cpu_x86.hpp"
#else
#error Unsupported architecture
#endif // _M_AMD64
