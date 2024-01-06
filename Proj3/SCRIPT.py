import subprocess
from time import time

def run_program(input_data):
   
    # Use subprocess.run para simplificar a execução
    result = subprocess.run(['python3', 'Proj.py'], input=input_data, text=True, capture_output=True)

    return result.stdout
def main():
    input_filename = 'input.txt'
    output_filename = 'output.txt'

    with open(input_filename, 'r') as file:
        input_data = file.read().strip().split('\n')  # Separa instâncias pelo padrão \n\n

    with open(output_filename, 'w') as file:
        for instance_data in input_data:
            result = run_program(instance_data)
            file.write(result)
            file.write('\n\n')

if __name__ == "__main__":
    main()
