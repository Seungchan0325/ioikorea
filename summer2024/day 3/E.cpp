#include <bits/stdc++.h>

using namespace std;

void hanoi(int n, int a, int b, int c)
{
    if(n == 1)
    {
        cout << a << " " << b << "\n";
        return;
    }
    hanoi(n-1, a, c, b);
    cout << a << " " << b << "\n";
    hanoi(n-1, c, b, a);
}

int main()
{
    int n;
    cin >> n;
    hanoi(n, 1, 3, 2);
}