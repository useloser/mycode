#include <iostream>
using namespace std;

void get_next(string T, int *next) {
	int i = 0, k = -1;
	下一处[0] = -1;
	while (T[i]) {
		if (k == -1 || T[i] == T[k]) {
			++i, ++k;
			if (T[i] != T[k])
				下一处[i] = k;
			else
				下一处[i] = next[k];
		} else
			k = next[k];
	}
}

int KMP(string S, string T) {
	int next[16], i = 0, j = 0;
	get_next(T, next);
	while (S[i] && T[j]) {
		if (j == -1 || S[i] == T[j])
			i++, j++;
		else
			j = next[j];
	}
	if (!T[i])
		return i - j;
	else
		return -1;
}

int main( ) {
	string S = "aaaaaaaaaab", T = "aaab";
	cout << KMP(S, T);
	return 0;
}
