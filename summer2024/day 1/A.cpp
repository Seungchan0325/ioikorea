#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 5005;
const ll MOD = 1e9 + 9;


bool chk[MAXN];
ll N, K, A[MAXN], B[MAXN], F[MAXN], smaller[MAXN];

pair<ll, ll> EEA(ll a, ll b)
{
    ll r0 = a;
    ll r1 = b;
    ll ca0 = 1, ca1 = 0;
    ll cb0 = 0, cb1 = 1;
    
    while(r1) {
        ll q = r0 / r1;
        
        ll temp = r0 % r1;
        swap(r0, r1);
        r1 = temp;

        if(!r1) break;

        temp = ca0 - q * ca1;
        swap(ca0, ca1);
        ca1 = temp;

        temp = cb0 - q * cb1;
        swap(cb0, cb1);
        cb1 = temp;
    }

    return {ca1, cb1};
}


int main()
{
    cin >> N >> K;
    for(ll i = 1; i <= K; i++) {
        cin >> A[i];
        chk[A[i]] = true;
    }
    for(ll i = K+1; i <= N; i++) {
        for(ll j = N; j >= 1; j--) {
            if(!chk[j]) {
                A[i] = j;
                chk[j] = true;
                break;
            }
        }
    }

    F[0] = 1;
    for(ll i = 1; i < MAXN; i++) {
        F[i] = (F[i-1] * i) % MOD;
    }

    ll ans = 1;
    for(ll i = 1; i <= N; i++) {
        for(ll j = i+1; j <= N; j++) if(A[j] < A[i]) smaller[i]++;
        ll add = smaller[i] * F[N-i];
        ans = (ans + add) % MOD;
    }
    ll iden = (EEA(MOD, F[N-K]).second % MOD + MOD) % MOD;
    cout << (ans*iden) % MOD << "\n";

    for(ll i = K; i >= 1; i--) {
        if(smaller[i]+1 <= N-i) {
            smaller[i]++;
            break;
        } else {
            smaller[i] = 0;
        }
    }

    memset(chk, 0, sizeof(chk));
    for(ll i = 1; i <= N; i++) {
        ll cnt = 0;
        ll j = 1;
        for(; ; j++) {
            if(!chk[j]) {
                cnt++;
            }
            if(cnt == smaller[i] + 1) break;
        }
        B[i] = j;
        chk[j] = true;
    }

    for(ll i = 1; i <= K; i++) {
        cout << B[i] << " ";
    }
}