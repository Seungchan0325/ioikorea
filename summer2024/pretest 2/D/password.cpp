#include "password.h"

#include <string>
#include <vector>
using namespace std;

std::string solve(int N, int T) {
    int lo = 0;
    int hi = N+1;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(ask_question(string(mid, '1'))) lo = mid;
        else hi = mid;
    }
    int maxone = lo;

    string s = string(maxone, '1');
    int ones = 0;
    while(true) {
        string nxt = s + string(ones, '1') + '0';
        if(nxt.size() <= N && ask_question(nxt)) {
            s = nxt;
            ones = 0;
        } else {
            ones++;
            if(ones > maxone) {
                lo = 0;
                hi = min(maxone + 1, N - (int)s.size() + 1);
                while(lo + 1 < hi) {
                    int mid = (lo + hi) / 2;
                    string ss = s + string(mid, '1');
                    if(ss.size() <= N && ask_question(ss)) lo = mid;
                    else hi = mid;
                }
                s += string(lo, '1');
                break;
            }
        }
    }

    while(s.size() < N) {
        if(ask_question("0" + s)) s = "0" + s;
        else s = "1" + s;
    }
    return s;
}