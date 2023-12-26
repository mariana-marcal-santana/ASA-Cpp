from pulp import *

prob = LpProblem("question 1", LpMaximize)

x = [None] + [LpVariable(f"x{i+1}", 0, None, LpInteger) for i in range(4)]

l = [1.5, 2.5, 3, 4.5]
a = [2, 4, 3, 7]
po = [3, 2, ]

#Add goal
prob += lpSum([x[i] * l[i] for i in range(1, len(x))]), "objective function"
prob# += 1.5 * x[1] + 2.5 * x[2] + 3 * x[3] + 4.5 * x[4], "objective function"

prob += 2 * x[1] + 4 * x[2] + 3 * x[3] + 7 * x[4] <= 100000, "assembly restriction"

prob += 3 * x[1] + 4 * x[2] + 3 * x[3] + 4 * x[4] <= 50000, "polish restriction"

prob += 2 * x[1] + 3 * x[2] + 2 * x[3] + 5 * x[4] <= 60000, "packaging restriction"

print(prob)

prob.solve(GLPK(msg=0))

if LpStatus[prob.status] != "Optimal":
    print("Infeasible")
else:
    print(value(prob.objective))
for v in prob.variables():
    print(v.name, "=", v.varValue)

