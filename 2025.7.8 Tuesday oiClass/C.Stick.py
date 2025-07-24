MOD = 10**9 + 7

def main():
    x = int(input())
    
    if x >= 4:
        print(2 % MOD)
        return

    # 第一次变换生成new_x
    first = [x, x+1]
    for i in range(x+1, min(4*x, 10**6)+1):
        new_x = i
        first.append(new_x)
    
    second = []
    for i in range(len(first)):
        for j in range(i+1, len(first)):
            if first[j] < 4 * first[i]:
                second.append((first[i], first[j]))
    
    # 统计满足条件的情况数目
    total = 0
    for a, b in second:
        if (a + b) > max(a, b):
            total +=1

    print(total % MOD)

if __name__ == "__main__":
    main()
