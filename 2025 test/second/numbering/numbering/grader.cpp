#include <iostream>
#include <vector>

using namespace std;
 
extern long long max_diversity(
int N, int M, vector<int> U, vector<int> V);


int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    int N, M;
    cin >> N >> M;
    
    std::vector<int> U(M), V(M);
    for (int i=0;i<M;i++){
        cin >> U[i] >> V[i];
    }
    
    long long S = max_diversity(N, M, U, V);
    cout << S << "\n";
}
