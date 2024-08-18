#include "password.h"
#include "password.cpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

static std::string s;
static int N, T;
static int questions; // Number of questions asked

void WA(std::string s) {
	std::cout << "Wrong Answer, " << s << std::endl;
	exit(0);
}

bool ask_question(std::string p) {
	questions++;
	if (p.size() > s.size()) WA("Wrong5 query size");
	if (p.empty()) WA("Wrong query size");
	for (int i = 0; i < p.size(); i++) {
		if (p[i] != '0' && p[i] != '1') {
			WA("String is not a binary string");
		}
	}
	if(questions > T) {
		WA("Too many queries");
	}
	std::string ss = p + "#" + s;
	std::vector<int> pr(ss.size() + 1);
	pr[0] = -1;
	bool answer = false;
	for (int i = 1; i <= ss.size(); i++) {
		int k = pr[i - 1];
		while (k >= 0 && ss[k] != ss[i - 1])
			k = pr[k];
		pr[i] = k + 1;
		if (pr[i] == p.size()) {
			answer = true;
			break;
		}
	} 
	return answer;
}

int main() {
    std::cin >> N >> T;
	std::cin >> s;
	if(s.size() != N) {
		std::cout << "Input Error: size of s is not N" << std::endl;
		return 0;
	}
    std::string ans = solve(s.size(), T);
	std::cout << questions << std::endl << ans << std::endl;
    return 0;
}
