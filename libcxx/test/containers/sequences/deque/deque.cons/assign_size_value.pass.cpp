//===----------------------------------------------------------------------===//
//
// ΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚΚThe LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <deque>

// void assign(size_type n, const value_type& v);

#include <deque>
#include <cassert>

#include "../../../iterators.h"

std::deque<int>
make(int size, int start = 0 )
{
    const int b = 4096 / sizeof(int);
    int init = 0;
    if (start > 0)
    {
        init = (start+1) / b + ((start+1) % b != 0);
        init *= b;
        --init;
    }
    std::deque<int> c(init, 0);
    for (int i = 0; i < init-start; ++i)
        c.pop_back();
    for (int i = 0; i < size; ++i)
        c.push_back(i);
    for (int i = 0; i < start; ++i)
        c.pop_front();
    return c;
};

void
test(std::deque<int>& c1, int size, int v)
{
    typedef std::deque<int> C;
    typedef C::const_iterator CI;
    std::size_t c1_osize = c1.size();
    c1.assign(size, v);
    assert(c1.size() == size);
    assert(distance(c1.begin(), c1.end()) == c1.size());
    for (CI i = c1.begin(); i != c1.end(); ++i)
        assert(*i == v);
}

void
testN(int start, int N, int M)
{
    typedef std::deque<int> C;
    typedef C::iterator I;
    typedef C::const_iterator CI;
    C c1 = make(N, start);
    test(c1, M, -10);
}

int main()
{
    int rng[] = {0, 1, 2, 3, 1023, 1024, 1025, 2047, 2048, 2049};
    const int N = sizeof(rng)/sizeof(rng[0]);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                testN(rng[i], rng[j], rng[k]);
}
