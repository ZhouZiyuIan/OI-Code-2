import sys

def main():
    def solve():
        n, k = map(int, sys.stdin.readline().split())
        a = list(map(int, sys.stdin.readline().split()))
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + a[i]

        max_avg = 0.0
        for length in range(k, n + 1):
            for i in range(n - length + 1):
                total = prefix[i + length] - prefix[i]
                avg = total / length
                if avg > max_avg:
                    max_avg = avg
        print("%.6f" % max_avg)

if __name__ == "__main__":
    main()
