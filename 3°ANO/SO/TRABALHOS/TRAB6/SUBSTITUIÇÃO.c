
#include <stdio.h>
#include <stdlib.h>

void simular(int *enderecos, int total, int quadros, int tamanho_pagina, FILE *saida, int algoritmo) {

    int *memoria = malloc(quadros * sizeof(int));
    int *ultimo_uso = malloc(quadros * sizeof(int));
    int quantidade = 0;
    int proximo = 0;
    int erros = 0;
    char *nome;

    if (algoritmo == 0)
        nome = "FIFO";
    else if (algoritmo == 1)
        nome = "OPT";
    else
        nome = "LRU";

    fprintf(saida, "\n%s: \n", nome);

    for (int i = 0; i < total; i++) {

        int endereco = enderecos[i];
        int pagina = endereco / tamanho_pagina;

        int encontrou = 0;
        int posicao = -1;

        for (int j = 0; j < quantidade; j++) {
            if (memoria[j] == pagina) {
                encontrou = 1;
                posicao = j;
                break;
            }
        }
        if (encontrou) {
            if (algoritmo == 2) {
                ultimo_uso[posicao] = i;
            }
            continue;
        }

        erros++;

        fprintf(saida,"Erro de pagina no endereco %d, pagina %d\n",endereco, pagina);

        if (quantidade < quadros) {

            memoria[quantidade] = pagina;
            ultimo_uso[quantidade] = i;
            quantidade++;
        } else {
            int substituir = 0;

            if (algoritmo == 0) {
                substituir = proximo;
                proximo = (proximo + 1) % quadros;
            }
            else if (algoritmo == 1) {
                int maior_distancia = -1;

                for (int j = 0; j < quadros; j++) {
                    int proximo_uso = -1;

                    for (int k = i + 1; k < total; k++) {

                        int proxima_pagina = enderecos[k] / tamanho_pagina;
                        if (proxima_pagina == memoria[j]) {
                            proximo_uso = k;
                            break;
                        }
                    }

                    if (proximo_uso == -1) {
                        substituir = j;
                        maior_distancia = total + 1;
                        break;
                    }
                    if (proximo_uso > maior_distancia) {
                        maior_distancia = proximo_uso;
                        substituir = j;
                    }
                }
            }
            else if (algoritmo == 2) {

                int menor_uso = ultimo_uso[0];
                for (int j = 1; j < quadros; j++) {
                    if (ultimo_uso[j] < menor_uso) {
                        menor_uso = ultimo_uso[j];
                        substituir = j;
                    }
                }
            }

            memoria[substituir] = pagina;
            ultimo_uso[substituir] = i;
        }
    }
    float percentual = 0;
    if (total > 0) {
        percentual = (float) erros / total * 100;
    }

    printf("\n===== RESULTADO %s =====\n", nome);
    printf("Quantidade de acessos: %d\n", total);
    printf("Quantidade de erros: %d\n", erros);
    printf("Percentual de erros: %.2f%%\n",(int)(percentual * 100) / 100.0);

    fprintf(saida, "Total de erros: %d\n", erros);
    fprintf(saida, "Percentual de erros: %.2f%%\n",(int)(percentual * 100) / 100.0);

    free(memoria);
    free(ultimo_uso);
}

int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Uso: %s <tamanho_pagina> <tamanho_memoria> <arquivo>\n",
               argv[0]);
        return 1;
    }

    int tamanho_pagina = atoi(argv[1]);
    int tamanho_memoria = atoi(argv[2]);

    if (tamanho_pagina <= 0 || tamanho_memoria <= 0) {
        printf("Erro: tamanhos invalidos.\n");
        return 1;
    }

    int quadros = tamanho_memoria / tamanho_pagina;

    if (quadros == 0) {
        printf("Erro: memoria insuficiente.\n");
        return 1;
    }

    FILE *arquivo = fopen(argv[3], "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int capacidade = 100;
    int total = 0;
    int endereco;

    int *enderecos = malloc(capacidade * sizeof(int));

    if (enderecos == NULL) {
        printf("Erro de memoria.\n");
        fclose(arquivo);
        return 1;
    }
    while (fscanf(arquivo, "%d", &endereco) == 1) {

        if (endereco < 0 || endereco > 65535) {
            printf("Endereco invalido: %d\n", endereco);
            free(enderecos);
            fclose(arquivo);
            return 1;
        }

        if (total == capacidade) {

            capacidade *= 2;

            int *temp = realloc(enderecos,capacidade * sizeof(int));

            if (temp == NULL) {
                printf("Erro ao aumentar memoria.\n");
                free(enderecos);
                fclose(arquivo);
                return 1;
            }
            enderecos = temp;
        }
        enderecos[total] = endereco;
        total++;
    }
    fclose(arquivo);
    FILE *saida = fopen("erros.out", "w");
    if (saida == NULL) {
        printf("Erro ao criar erros.out.\n");
        free(enderecos);
        return 1;
    }
    printf("Tamanho da pagina: %d bytes\n", tamanho_pagina);
    printf("Tamanho da memoria: %d bytes\n", tamanho_memoria);
    printf("Quantidade de quadros: %d\n", quadros);

    simular(enderecos, total, quadros, tamanho_pagina, saida, 0);
    simular(enderecos, total, quadros, tamanho_pagina, saida, 1);
    simular(enderecos, total, quadros, tamanho_pagina, saida, 2);
    printf("\nArquivo erros.out gerado com sucesso!\n");
    fclose(saida);
    free(enderecos);
    return 0;
}
