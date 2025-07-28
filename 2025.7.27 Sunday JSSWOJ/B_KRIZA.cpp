//
// Created by 118 on 25-7-27.
//
#include <stdio.h>
#include <ctype.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
typedef long long ll;
void readInt(int* w) {
	int f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == 45) f = -f;
		s = getchar_unlocked();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	} while (isdigit(s));
	*w = x * f;
}
void readLL(ll* w) {
	int f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == 45) f = -f;
		s = getchar_unlocked();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	} while (isdigit(s));
	*w = x * f;
}
void writeLL(ll x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) writeLL(x / 10);
	putchar_unlocked(x % 10 + 48);
}
int n, v[100001], pos[100001], diff, cyclestat, diffCycle;
ll k, C, totErr, times, cycleErr;
typedef struct {
	int first;
	long long second;
}pair1;
pair1 simulate(int s, int R) {
	long long err = 0;
	int cur = s;
	for (int d = 1; d <= R; d++){
		int diff = pos[d] - cur;
		if(diff < 0) diff += n;
		err += diff;
		cur = pos[d];
	}
	return {cur, err};
};
int main() {
	readInt(&n);
	readLL(&k);
	for (int i = 0; i < n; ++i) {
		readInt(&v[i]);
		pos[v[i]] = i;
	}
	for (int d = 2; d <= n; ++d) {
		diff = pos[d] - pos[d - 1];
		if (diff < 0) {
			diff += n;
		}
		C += diff;
	}
	if(k < n){
		totErr = simulate(0, (int)k).second;
	}
	else{
		times = k / n;
		diff = pos[1];
		if (diff < 0) {
			diff += n;
		}
		totErr += diff + C;
		cyclestat = pos[n];
		if(times > 1) {
			diffCycle = pos[1] - cyclestat;
			if (diffCycle < 0) {
				diffCycle += n;
			}
			cycleErr = diffCycle + C;
			totErr += (times - 1) * cycleErr;
		}
		if(k % n > 0){
			totErr += simulate(cyclestat, k % n).second;
		}
	}
	writeLL(totErr);
}