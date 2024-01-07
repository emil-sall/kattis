"""
Problem: Bing It On - https://open.kattis.com/problems/bing
Author: Emil Säll
"""

f = {'W': int(input())}
for i in range(f['W']):
    w = f
    value = 0
    for j in input():
        if j not in w:
            w[j] = {'W' : 1}
        w = w[j]
        w['W'] += 1
        value = w['W']
    print(value - 2)