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
    # Read input
    t, p, max = map(int, input().split())
    ntp = t + p

    x = [None] + [LpVariable(f"x{i+1}", 0, None, LpInteger) for i in range(ntp)]

    for i in range(t):
        l, c = map(int, input().split())
    for j in range(p):
        i, j, k, l = map(int, input().split())