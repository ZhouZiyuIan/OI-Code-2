import sys
import math
from collections import defaultdict

def sieve(limit):
    sieve = [True] * (limit + 1)
    sieve[0] = sieve[1] = False
    for i in range(2, int(math.sqrt(limit)) + 1):
        if sieve[i]:
            for j in range(i*i, limit+1, i):
                sieve[j] = False
    primes = [p for p, is_prime in enumerate(sieve) if is_prime]
    return primes

# 预生成所有质数 p <= 1000
primes = sieve(1000)
m = len(primes)

def factorize(n, primes):
    factors = defaultdict(int)
    while n != 1:
        for p in primes:
            if p * p > n:
                break
            if n % p == 0:
                count = 0
                while n % p == 0:
                    count += 1
                    n //= p
                factors[p] += count
            else:
                continue
        # 如果剩下的是一个质数，直接处理
        if n > 1:
            factors[n] += 1
    return factors

def build_matrix(primes, a):
    matrix = []
    for num in a:
        factors = factorize(num, primes)
        row = [0] * len(matrix)
        for i, p in enumerate(factors.keys()):
            row[i] = factors[p] % 2
        matrix.append(row)
    return matrix

def compute_rank(matrix):
    # 进行高斯消元法计算秩
    n = len(matrix[0])
    rank = 0
    m = len(matrix)
    for col in range(n):
        # 极大值
        max_row = -1
        for row in range(rank, m):
            if matrix[row][col] == 0:
                continue
            if matrix[row][col] > max_row[0]:
                max_row = row
        if max_row == -1:
            rank += 1
            continue

        # 交换行
        if max_row != rank:
            matrix[rank], matrix[max_row] = matrix[max_row], matrix[rank]
            rank += 1

        pivot_val = matrix[rank][col]
        for row in range(m):
            if row != rank and matrix[row][col] != 0:
                factor = matrix[row][col] // pivot_val
                matrix[row] = [matrix[row][i] - factor * matrix[rank][i] for i in range(col, n)]

    return rank

def main():
    # 输入数组 a
    a = list(map(int, sys.stdin.read().split()))
    if not a:
        print(0)
        return

    # 建立矩阵 A
    A = build_matrix(primes, a)
    
    # 计算矩阵的秩
    rank = compute_rank(A)
    
    # 如果所有元素都是奇数，输出 1
    if rank == m * n:
        print(1)
    else:
        print(rank)

if __name__ == "__main__":
    main()
