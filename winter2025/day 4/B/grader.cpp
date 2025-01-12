#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "kong.h"
using namespace std;

void my_assert(bool e, const char* s = ""){
    if(!e){
        puts(s);
        exit(42);
    }
}

static int a[2222], n;
static int call_count;
int compare(int i, int j){
    ++call_count;
    my_assert(1 <= i && i <= n && 1 <= j && j <= n && i != j, "Wrong Answer : compare() got an invalid call");
    my_assert(2222 * n >= call_count, "Wrong Answer : compare() got too many calls");
    return a[i-1] < a[j-1] ? -1 : 1;
}

int main(){
    my_assert(scanf("%d",&n) == 1, "Invalid input");
    my_assert(2 <= n && n <= 2222, "Invalid input");
    for(int i = 0; i < n; i++) my_assert(scanf("%d",&a[i]) == 1, "Invalid input");
    vector<int> v(a,a+n);
    sort(v.begin(),v.end());
    v.resize(unique(v.begin(),v.end()) - v.begin());
    my_assert(v.size() == n, "Invalid input");


    int user = kong(n);
    vector<int> id(n);
    for(int i=0;i<n;i++)
        id[i]=i+1;
    sort(id.begin(),id.end(),[](int i, int j){return a[i-1] > a[j-1];});
    my_assert(id[1] == user, "Wrong Answer");


    int lg = 0;
    for(;(1 << lg) < n; lg++);
    if(call_count <= n + lg - 2){
        puts("Correct : Subtask 3");
        return 0;
    }
    if(call_count <= 2 * n){
        puts("Correct : Subtask 2");
        return 0;
    }
    if(call_count <= 2222 * n){
        puts("Correct : Subtask 1");
        return 0;
    }
    return 0;
}
