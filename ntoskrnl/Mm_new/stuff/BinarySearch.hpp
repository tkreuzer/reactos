
#pragma once
#define _BINARY_SEARCH_HPP_

#include <sal.h>

template<typename _DataType, int _CompareFunc(void*, _DataType*)>
inline
_DataType*
BinarySearch (
    _In_ _DataType DataArray[],
    _In_ unsigned NumberOfElements,
    _In_ void* Key)
{
    unsigned IndexLow, IndexMid, IndexHigh;
    int Result;

    IndexLow = 0;
    IndexHigh = NumberOfElements;
    while (IndexHigh > IndexLow)
    {
        IndexMid = (IndexLow + IndexHigh) / 2;

        Result = _CompareFunc(Key, &DataArray[IndexMid]);
        if (Result < 0)
        {
            /* Continue search in lower half */
            IndexHigh = IndexMid;
        }
        else if (Result > 0)
        {
            /* Continue search in higher half */
            IndexLow = IndexMid + 1;
        }
        else
        {
            /* Found the entry */
            return IndexMid;
        }
    }

    return -1;
}

