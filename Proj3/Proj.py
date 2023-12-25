"""
Project 1 ASA - 2023/2024
Project made by:
    Mariana Santana (106992)
    João Rodrigues (106221)
"""

from pulp import *

def main():
    # Create problem
    prob = LpProblem("toyFactory", LpMaximize)
    # Initialize lists for data
    ls = []
    cs = []
    # Read input
    count = 0
    user_input = input("write input: ")
    t, p, max = map(int, user_input.split())
    print("T:", t)
    print("P:", p)
    print("Max:", max)

    x = [None] + [LpVariable(f"x{i+1}", 0, None, LpInteger) for i in range(t + p)]

    for i in range(t):
        l, c = map(int, input().split())
        ls.append(l)
        cs.append(c)
        prob += x[i + 1] <= c, f"constraint {i + 1}"
        count += 1
     
    for j in range(p):
        i, j, k, l = map(int, input().split())
        ls.append(l)

    prob += lpSum([x[i] * l[i] for i in range(1, len(x))]), "objective function"

main()