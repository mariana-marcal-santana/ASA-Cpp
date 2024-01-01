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
    sets = [[i] for i in range(t + 1)]
    multipliers = [1] * (t + 1) + [3] * p
    # Create list of LP variables
    x = [None] + [LpVariable(f"x{i + 1}", 0, None, LpInteger) for i in range(t + p)]
    # Individual toys
    for n in range(t):
        l, c = map(int, input().split())
        ls[n + 1] = l
        cs[n + 1] = c
    # Toy sets
    for m in range(p):
        i, j, k, l = map(int, input().split())
        ls[m + t + 1] = l
        sets[i].append(m + t + 1)
        sets[j].append(m + t + 1)
        sets[k].append(m + t + 1)
    #print(sets)
    # Max production constraint
    prob += lpSum([x[i] * multipliers[i] for i in range(1, len(x))]) <= max, "constraint max"
    # Toy sets constraint
    for i in range(1, len(sets)):
        prob += lpSum([x[j] for j in sets[i]]) <= cs[i], f"constraint set {i}"
    # Set objective function
    prob += lpSum([x[i] * ls[i] for i in range(1, len(x))]), "objective function"

    #print(ls)
    #print(cs)

    prob.solve(GLPK(msg = 0))

    if LpStatus[prob.status] != "Optimal":
        print("Infeasible")
    else:
        print(value(prob.objective))
        #for v in prob.variables():
            #print(v.name, "=", v.varValue)

main()