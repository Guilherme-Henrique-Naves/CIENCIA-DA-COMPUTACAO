import os
import platform


def turing(estado_atual, estados_finais, estados_rejeicao, tabela_transicoes, fita, i, caminho=[]):

    caminho.append((estado_atual, "".join(fita), i))

    if estado_atual in estados_finais:
        print("Máquina aceita a entrada!\n")
        print("Passos:\n")
        for passo, (estado, fita_atual, posicao) in enumerate(caminho):
            print(f"Passo {passo}: Estado {estado}, Fita: {fita_atual}, Cabeça na posição {posicao}")
        return

    if estado_atual in estados_rejeicao:
        print("Máquina rejeita a entrada!\n")
        print("Passos:\n")
        for passo, (estado, fita_atual, posicao) in enumerate(caminho):
            print(f"Passo {passo}: Estado {estado}, Fita: {fita_atual}, Cabeça na posição {posicao}")
        return

    if i < 0 or i >= len(fita):
        print("Erro: Saiu da fita!")
        return

    chave = f'{estado_atual}-{fita[i]}'
    if chave not in tabela_transicoes:
        print(f"Erro: Transição indefinida para {chave}")
        print("Passos:")
        for passo, (estado, fita_atual, posicao) in enumerate(caminho):
            print(f"Passo {passo}: Estado {estado}, Fita: {fita_atual}, Cabeça na posição {posicao}")
        return

    prox_estado, novo_simbolo, direcao = tabela_transicoes[chave]

    if prox_estado == '-' or novo_simbolo == '-' or direcao == '-':
        print("Transição '-,-,-' encontrada. Automato encerrado.\n")
        print("Passos:\n")
        for passo, (estado, fita_atual, posicao) in enumerate(caminho):
            print(f"Passo {passo}: Estado {estado}, Fita: {fita_atual}, Cabeça na posição {posicao}")
        return


    
    fita[i] = novo_simbolo

    if direcao == 'D':
        i += 1
    elif direcao == 'E':
        i -= 1
    else:
        print(f"Erro: Direção '{direcao}' inválida!")
        return

    turing(prox_estado, estados_finais, estados_rejeicao, tabela_transicoes, fita, i, caminho)


print("\n === Maquina de Turing ===\n")

print(" === 1. Observações ===\n")

print(" Q  – conjunto de estados internos")
print(" Σ  – conjunto do alfabeto de entrada")
print(" Γ  – conjunto finito de símbolos, chamado de alfabeto da fita")
print(" q0 – estado inicial ( q0 ∈ Q )")
print(" F  – conjunto de estados finais/aceitação ( F ∈ Q )")
print(" R  – conjunto de estados de rejeição (caso tenha) (R ∈ Q)\n")

print(" δ  – função de transição, definida por δ: Q x Γ → Q x Γ x {D, E}\n")

print(" *Importante!! Para os conjuntos, separar os itens por virgula.*\n")


estados = set(input("  1. Q : ").strip().split(","))
alfabeto_sigma = set(input("  2. Σ : ").strip().split(","))
alfabeto_gamma = set(input("  3. Γ : ").strip().split(","))
estado_inicial = input("  4. q0: ")
estados_finais = input("  5. F : ").strip().split(",")
estados_rejeicao = input("  6. R : ").strip().split(",")

print("\n")

os.system("clear")

tabela_transicoes = {}

print(" === Tabela de Transições (δ) ===\n")
print(" === 2. Observações ===\n")

print(" 1. O input será solicitado no seguinte formato:\n")
print("    δ(estado,alfabeto) = \n")
print("   Você deve informar a transição no formato:")
print("       'estado', 'símbolo', 'direção'\n")
print(" 2. Detalhes sobre os parâmetros:\n")
print("   - 'estado': Deve ser um estado pertencente ao conjunto de estados lidos.")
print("       Exceção: Use '-' para indicar que a transição não existe.\n")
print("   - 'símbolo': Deve ser um símbolo que pertence ao alfabeto lido.\n")
print("       Exceção: Use '_' para indicar caracter branco.\n")
print("   - 'direção': Indique o movimento da cabeça de leitura com:")
print("       'D' para mover à direita ou 'E' para mover à esquerda.\n")
print(" 3. Exemplos de entradas:\n")
print("    δ(q1,b) = q1,a,D")
print("    δ(q1,a) = q2,_,E")
print("    δ(q1,b) = -,-,-   *Significa que essa transição não está definida para esta maquina*")

print("\n")

contador = 0

print(" === Entre com as Transições ===\n")

alfabeto = alfabeto_gamma | alfabeto_sigma

for estado in sorted(estados):
    if estado in estados_finais or estado in estados_rejeicao:
        break
    for simbolo in sorted(alfabeto):
        contador = contador + 1
        tabela_transicoes[f'{estado}-{simbolo}'] = list(input(f'{contador}º - δ({estado}, {simbolo}) = ').strip().split(","))

continuar = "sim"

while (continuar == "sim"):

    fita = list(input("Entre com uma palavra na fita: ")) + ["_"] * 5
    caminho = []
    turing(estado_inicial, estados_finais, estados_rejeicao, tabela_transicoes, fita, 0, caminho)

    continuar = input("Deseja testar outra palavra? (sim) ou (nao): ")
    print("\n")
