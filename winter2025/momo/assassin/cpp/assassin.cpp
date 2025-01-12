#include <vector>
#include <bits/stdc++.h>

using namespace std;

int N;
int A, B;

std::vector<std::vector<int> > set_tasks(int n){
    N = n;
    std::vector<std::vector<int> > S;
    vector<bitset<2048>> bits;
    int step = 1;
    while(true) {
        if(step >= N) break;
        bitset<2048> bit;
        vector<int> v;
        for(int i = 1; i <= N; i+=2*step) {
            for(int j = 0; j < step && i+j <= N; j++) {
                v.push_back(i+j);
                bit.set(i+j);
            }
        }
        S.push_back(v);
        bits.push_back(bit);
        A++;
        step *= 2;
    }
    step = 1;
    reverse(S.begin(), S.end());
    reverse(bits.begin(), bits.end());
    while(true) {
        if(step >= A) break;
        bitset<2048> bit;
        for(int i = 0; i < A; i+=2*step) {
            for(int j = 0; j < step && i+j < A; j++) {
                bit ^= bits[i+j];
            }
        }
        vector<int> v;
        for(int i = 1; i <= N; i++) {
            if(bit.test(i)) v.push_back(i);
        }
        S.push_back(v);
        B++;
        step *= 2;
    }
    reverse(S.begin()+A, S.end());
    vector<int> v1, v2;
    bitset<2048> bit;
    for(int i = 0; i < A; i++) {
        bit ^= bits[i];
    }
    for(int i = 1; i <= N; i++) {
        if(bit.test(i)) v1.push_back(i);
        else v2.push_back(i);
    }
    S.push_back(v1);
    S.push_back(v2);
    return S;
}

std::vector<int> find_location(std::vector<std::vector<int> > R){
    int T = R.size();
    vector<int> ret;
    for(int i = 0; i < T; i++) {
        vector<int> a(R[i].begin(), R[i].begin()+A);
        vector<int> b(R[i].begin()+A, R[i].begin()+A+B);
        int even = R[i].end()[-2];
        int odd = R[i].end()[-1];

        int sum1 = 0;
        for(auto i : a) sum1 += i;
        if((sum1 + even) % 2 != 0 && (sum1 + odd) % 2 != 1) {
            int step = 1;
            while(2*step < A) step *= 2;
            int idx = 0;
            for(int i : b) {
                int s = 0;
                for(int j = 0; j < A; j+=2*step) {
                    for(int k = 0; k < step && j + k < A; k++) {
                        s += a[j+k];
                    }
                }
                if((i+s)%2==0) idx += step;
                step /= 2;
            }
            a[idx] = 1 - a[idx];
        }

        int step = 1;
        while(2*step < N) step *= 2;
        int idx = 1;
        for(auto i : a) {
            if(i==0) idx += step;
            step /= 2;
        }
        ret.push_back(idx);
    }
    return ret;
}
