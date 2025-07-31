#include <stdio.h>
#include <ctype.h>
#ifdef _WIN64
#define putchar_unlocked _putchar_nolock
#endif
#define rd read()
#define gc pa == pb && (pb = (pa = buf) + fread(buf, 1, 100000, stdin), pa == pb) ? EOF : *pa++
static char buf[100000], *pa(buf), *pb(buf);
void read(int *w) {
	int x = 0, s = gc;
	while (!isdigit(s))s = gc;
	while (isdigit(s))x = (x << 1) + (x << 3) + (s ^ 48), s = gc;
	*w=x;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9ll) {
		write(x / 10);
	}
	putchar_unlocked(x % 10 + 48);
}
typedef struct {
	int x, id;
}node;
int n, m;

int main() {
	read(&n);
	read(&m);
}