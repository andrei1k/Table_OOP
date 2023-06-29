#ifndef PAIR_H
#define PAIR_H

struct Pair {
    
    Pair() : fst(0), snd(0) {}
    Pair(int fst, int snd) : fst(fst), snd(snd) {}
    Pair(const Pair& copy) = default;
    Pair& operator=(const Pair& copy) = default;
    int fst, snd;
};

#endif // !PAIR_H 