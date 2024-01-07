"""
Project 1 ASA - 2023/2024
Project made by:
    Mariana Santana (106992)
    João Rodrigues (106221)
"""

from pulp import *
from time import *

def main():
    # Create problem
    prob = LpProblem("toyFactory", LpMaximize)
    # Read input
    t, p, max = map(int, input().split())
    time_1=time()
    # Initialize lists for data
    ls, cs, x = [0], [0], [None]
    sets = [[i] for i in range(t + 1)]
    multipliers = [1] * (t + 1) + [3] * p
    # Individual toys
    for n in range(t):
        l, c = map(int, input().split())
        ls.append(l)
        cs.append(c)
        x += [LpVariable(f"x{n + 1}", 0, c, LpInteger)]
    # Toy sets
    for m in range(p):
        i, j, k, l = map(int, input().split())
        ls.append(l)
        sets[i].append(m + t + 1)
        sets[j].append(m + t + 1)
        sets[k].append(m + t + 1)
        x += [LpVariable(f"x{m + t + 1}", 0, min(cs[i], cs[j], cs[k]), LpInteger)]
    # Max production constraint
    prob += lpSum([x[i] * multipliers[i] for i in range(1, len(x))]) <= max, "constraint max"
    # Toy sets constraints
    for i in range(1, len(sets)):
        prob += lpSum([x[j] for j in sets[i]]) <= cs[i], f"constraint set {i}"
    # Set objective function
    prob += lpSum([x[i] * ls[i] for i in range(1, len(x))]), "objective function"
    # Solve problem
    prob.solve(GLPK(msg = 0))
    time_2=time()
    # Print solution
    print(f"{time_2-time_1:.4f}")
    if LpStatus[prob.status] != "Optimal":
        print("Infeasible")
    else:
        print(value(prob.objective))

main()
