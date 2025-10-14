def main():
    import sys
    input = sys.stdin.read().split()
    ptr = 0

    n = int(input[ptr])
    m = int(input[ptr+1])
    H = int(input[ptr+2])
    c = int(input[ptr+3])
    ptr +=4

    tasks = []
    for _ in range(n):
        h_i = int(input[ptr])
        p_i = int(input[ptr+1])
        g_i = int(input[ptr+2])
        e_i = int(input[ptr+3])
        tasks.append((h_i, p_i, g_i, e_i))
        ptr +=4

    min_p = -10
    max_p = 10
    if max_p < 0:
        max_p = 0

    # 定义生成函数的方法
    def generate_func(task):
        h_start, h_end = task['h']
        p_list = task['p']
        g = task['g']
        e_list = task['e']
        
        matrix = []
        for h in range(h_start, h_end + 1):
            new_p_vals = []
            for pp in p_list:
                new_p_val = pp - H
                if pp > max_p:
                    continue
                # 创建影响矩阵
                matrix.append({h: [new_p_val] + list(range(min_p, max_p+1))})
        
        return matrix

    tasks_list = []
    for task in tasks:
        h_i, p_i, g_i, e_i = task
        if min(p_i, max(p_i)) < -10 or max(p_i) > 10:
            continue
        tasks_list.append(generate_func({'h': [h_i], 'p': [p_i], 'g': [g_i], 'e': e_i}))
    
    # 处理生成函数后的结果
    import itertools

    total = {}
    for task in tasks_list:
        new_dp = defaultdict(int)
        for (f, g_list) in task:
            for h in range(H+1):
                dp_current = {h: -float('inf')}
                if dp_current[h] == -float('inf'):
                    continue
                # 转换为列表形式
                for pp in g_list:
                    new_p_val = pp - H
                    if pp > max_p:
                        continue
                    total[(f, h)][pp] += dp_current[h]
    
    result = 0
    print(result)

if __name__ == '__main__':
    main()
