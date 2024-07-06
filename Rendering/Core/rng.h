#ifndef RNG_H
#define RNG_H

// A fast pseudo-random number generator with period of 131072
// TODO: This is NOT thread-safe!!!
struct RNG
{
    unsigned int seed;
    const unsigned int mask = 524287;
    const float fmask = mask;

    RNG(unsigned int _seed = 123457) : seed(_seed)
    { }

    inline float operator()()
    {
        seed = (seed * seed + seed) & mask;
        return seed / fmask;
    }
};



#endif // RNG_H
