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
    # Initialize lists for data
    ls = [0] * (t + p + 1)
    cs = [0] * (t + 1)
    # Create list of LP variables
    x = [None] + [LpVariable(f"x{i + 1}", 0, None, LpInteger) for i in range(t + p)]
    # Individual toys
    for n in range(t):
        l, c = map(int, input().split())
        ls[n + 1] = l
        cs[n + 1] = c
        # Individual production constraint
        prob += x[n + 1] <= c, f"constraint {n + 1}"
    # Toy sets
    for m in range(p):
        i, j, k, l = map(int, input().split())
        ls[m + t + 1] = l
    # Max production constraint
    prob += lpSum([x[i] for i in range(1, len(x))]) <= max, "constraint max"
    # Set objective function
    prob += lpSum([x[i] for i in range(1, len(x))]), "objective function"
    prob += lpSum([x[i] * l[i] for i in range(1, len(x))]), "objective function"

    print(ls)
    print(cs)

    prob.solve(GLPK(msg = 0))

    if LpStatus[prob.status] != "Optimal":
        print("Infeasible")
    else:
        print(value(prob.objective))
        for v in prob.variables():
            print(v.name, "=", v.varValue)

main()