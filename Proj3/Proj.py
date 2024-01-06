from pulp import *
from time import *

def resolver_e_escrever_output(input_filename, output_filename):
    # Create problem
    prob = LpProblem("toyFactory", LpMaximize)
    
    with open(input_filename, 'r') as file:
        # Read input from file
        t, p, max = map(int, file.readline().split())
        time_1 = time()
        # Initialize lists for data
        ls, cs, x = [0], [0], [None]
        sets = [[i] for i in range(t + 1)]
        multipliers = [1] * (t + 1) + [3] * p
        # Individual toys
        for n in range(t):
            l, c = map(int, file.readline().split())
            ls.append(l)
            cs.append(c)
            x += [LpVariable(f"x{n + 1}", 0, c, LpInteger)]
        # Toy sets
        for m in range(p):
            i, j, k, l = map(int, file.readline().split())
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
    prob.solve(GLPK(msg=0))
    time_2 = time()
    # Write output to file
    with open(output_filename, 'w') as output_file:
        if LpStatus[prob.status] != "Optimal":
            output_file.write("Infeasible")
        else:
            output_file.write("Time: " + str(time_2 - time_1) + "\n")
            output_file.write(str(value(prob.objective)))

def main():
    # Número total de testes
    num_testes = 15

    # Executa para cada teste
    for i in range(1, num_testes + 1):
        input_filename = f'teste_{i}.txt'
        output_filename = f'resultado_{i}.txt'
        resolver_e_escrever_output(input_filename, output_filename)

if __name__ == "__main__":
    import os
    script_dir = os.path.dirname(os.path.abspath(__file__))
    os.chdir(script_dir)
    main()
