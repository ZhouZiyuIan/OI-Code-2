//
// Created by 118 on 25-7-26.
//
#include <stdio.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
#define _U 0x01
#define _L 0x02
#define _D 0x04
#define _C 0x08
#define _P 0x10
#define _S 0x20
#define _X 0x40
#define _SP 0x80
extern unsigned char _ctype[];
#define isdigit(c) ((_ctype+1)[c]&(_D))
unsigned char _ctype[]={0x00,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C|_S,_C|_S,_C|_S,_C|_S,_C|_S,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_S|_SP,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_P,_P,_P,_P,_P,_P,_P,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_P,_P,_P,_P,_P,_P,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_P,_P,_P,_P,_C,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int read(int *w) {
	int f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == 45) {
			f = -f;
		}
		else if (s == -1) {
			return -1;
		}
		s = getchar_unlocked();
	}
	do {
		x = (x << 1ll) + (x << 3ll) + (s ^ 48);
		s = getchar_unlocked();
	} while (isdigit(s));
	x *= f;
	*w = x;
	return 1;
}
void write(long long x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar_unlocked(x % 10 + 48);
}
int n, L, head = 1, tail = 1, q[50001], j;
double dp[50001], A[50001], B[50001], sum[50001];
double X(int x) {
	return B[x];
}
double Y(int x) {
	return dp[x] + B[x] * B[x];
}
double slope(int a, int b) {
	return (Y(a) - Y(b)) / (X(a) - X(b));
}
int main(){
	read(&n);
	read(&L);
	for (int i = 1; i <= n; ++i) {
		scanf("%lf", &sum[i]);
	}
	for (int i = 1; i <= n; ++i) {
		sum[i] += sum[i - 1];
		A[i] = sum[i] + i;
		B[i] = sum[i] + i + L + 1;
	}
	B[0] = L + 1;
	for (int i = 1; i <= n; ++i) {
		while (head < tail && slope(q[head], q[head + 1]) < 2 * A[i]) {
			++head;
		}
		dp[i] = dp[j = q[head]] + (A[i] - B[j]) * (A[i] - B[j]);
		while (head < tail && slope(i, q[tail - 1]) < slope(q[tail - 1], q[tail])) {
			--tail;
		}
		q[++tail] = i;
	}
	write(dp[n]);
	return 0;
}
