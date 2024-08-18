#include "timecard.h"

static int N;

void init(int n) {
    N = n;
}

std::string convert(std::string s) {
    for(auto& c : s) c |= 32;
    return s;
}
