# Nome do arquivo de entrada
nome_arquivo_entrada = 'output.txt'

# Lê o conteúdo do arquivo
with open(nome_arquivo_entrada, 'r') as file:
    conteudo = file.read()

# Separa os testes com base em duas quebras de linha (\n\n)
testes = conteudo.strip().split('\n\n')

# Para cada teste, cria um arquivo .txt e escreve o conteúdo nele
for i, teste in enumerate(testes):
    # Ignora testes vazios
    if not teste.strip():
        continue
    
    # Cria um novo arquivo com o nome teste_{i+1}.txt
    nome_arquivo_saida = f'teste_{i+1}.txt'
    
    # Escreve o conteúdo do teste no novo arquivo
    with open(nome_arquivo_saida, 'w') as file:
        file.write(teste)
    
    print(f'Arquivo {nome_arquivo_saida} criado com sucesso.')
