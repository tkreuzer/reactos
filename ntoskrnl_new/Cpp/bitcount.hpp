
#pragma once

namespace Cpp {

template<unsigned long long N>
struct bit_count
{
    enum { val = bit_count<(N>>1)>::val + (N & 1) };
};

template<>
struct bit_count<0>
{
    enum { val = 0 };
};


template<unsigned long long N>
struct lowest_bit
{
    enum { val = (N & 1) ? 0 : lowest_bit<(N>>1)>::val + 1 };
};

template<>
struct lowest_bit<1>
{
    enum { val = 0 };
};

/// Test!
const unsigned Mylowest_bit = lowest_bit<2343791094>::val;

template<unsigned long long N>
struct value_info
{
    enum { bit_count = bit_count<N>::val };
    enum { lowest_bit = lowest_bit<N>::val };
};

/// Test!
const unsigned Mybit_count2 = value_info<2343791094>::bit_count;
const unsigned Mylowest_bit2 = value_info<2343791094>::lowest_bit;

union random_u
{
    struct
    {
        unsigned pad : 3;
        unsigned bit : 1;
    };
    unsigned x;
};

struct random_s
{
    unsigned pad : 3;
    unsigned bit : 1;
};

static const random_u myvalue = {{0,1}};

const unsigned Mylowest_bit3 = value_info<sizeof(myvalue.x)>::lowest_bit;


struct bitfield1
{
    char bits1 : 4;
};

struct bitfield2 : public bitfield1
{
    char bits2 : 3;
};

static_assert(sizeof(bitfield2) == 2, "");

}; // namespace Cpp

#define bitcount(Value) (::Cpp::bit_count<Value>::val)

unsigned
Testxx()
{
    //return BitCount<2343791094>();
    //return ::Cpp::bit_count<2343791094>::val;
    //return ::Cpp::lowest_bit<2343791094>::val;
    return ::Cpp::lowest_bit<1>::val;
}

