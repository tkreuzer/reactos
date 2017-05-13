/*
 *  ReactOS RosPerf - ReactOS GUI performance test program
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <windows.h>
#include "rosperf.h"

void
HeapProc(void *Context, PPERF_INFO PerfInfo, unsigned Reps)
{
  unsigned Rep;
  HANDLE hHeap;
  LPVOID lpMem;

  for (Rep = 0; Rep < Reps; Rep++)
  {
    hHeap = HeapCreate(0, 100, 100000);
    lpMem = HeapAlloc(hHeap, 0, 10000);
    HeapFree(hHeap, 0, lpMem);
    HeapDestroy(hHeap);
  }
}


/* EOF */
