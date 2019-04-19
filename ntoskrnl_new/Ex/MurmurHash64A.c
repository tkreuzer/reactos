ULONG_PTR
MurmurHash64A (ULONG_PTR OldHash, ULONG_PTR Value)
{
#ifdef _WIN64
	const ULONG64 Magic = 0xc6a4a7935bd1e995LLU;
	const ULONG Shift = 47;
#else
#endif
    ULONG_PTR Temp, Hash;

    Temp = Value * Magic;
    Temp ^= Temp >> Shift;
    Temp *= Magic;

    Hash = OldHash ^ (sizeof(OldHash) * Magic);
    Hash ^= Temp;
    Hash *= Magic;

	Hash ^= Hash >> Shift;
	Hash *= Magic;
	Hash ^= Hash >> Shift;

	return Hash;
}


uint32_t MurmurHash2 ( const void * key, int len, uint32_t seed )
{
  // 'm' and 'r' are mixing constants generated offline.
  // They're not really 'magic', they just happen to work well.

  const uint32_t m = 0x5bd1e995;
  const int r = 24;

  // Initialize the hash to a 'random' value

  uint32_t h = seed ^ len;

  // Mix 4 bytes at a time into the hash

  const unsigned char * data = (const unsigned char *)key;

  while(len >= 4)
  {
    uint32_t k = *(uint32_t*)data;

    k *= m;
    k ^= k >> r;
    k *= m;

    h *= m;
    h ^= k;

    data += 4;
    len -= 4;
  }

  // Handle the last few bytes of the input array

  switch(len)
  {
  case 3: h ^= data[2] << 16;
  case 2: h ^= data[1] << 8;
  case 1: h ^= data[0];
      h *= m;
  };

  // Do a few final mixes of the hash to ensure the last few
  // bytes are well-incorporated.

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}
