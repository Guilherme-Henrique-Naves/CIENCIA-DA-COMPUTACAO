#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <ctype.h>

#define MAX 1000

// ---------- ARVORE DE PROCESSOS ----------
 //verificar e imprimir os processos ativos 
void print_tree(int pid, int level) {
    DIR *dir = opendir("/proc"); // ABRIR A PASTA "PROC"
    struct dirent *entry;

    //VERIFICA SE CONSEGUIU ABIR
    if (!dir) {
        perror("opendir");
        return; // retuna caso não tenha conseguido 
    }

    // PERCORRER TODO OS ARQUIVOS DA PASTA "PROC"
    while ((entry = readdir(dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            char path[256];
            // MONTA O CAMINHO PARA: /proc/PID/stat
            sprintf(path, "/proc/%s/stat", entry->d_name);

            FILE *fp = fopen(path, "r");
            if (!fp) continue;  // SE NÃO CONSEGUIR ABRIR IGNORA
//---------------------------------------------------------------------------


            // lê informações do arquivo stat
            // formato: PID (nome) estado PPID
            int child_pid, ppid;
            char name[256], state;

            fscanf(fp, "%d (%[^)]) %c %d", &child_pid, name, &state, &ppid);
            fclose(fp);

             // verifica se esse processo é filho do PID informado
            if (ppid == pid) {
                
                for (int i = 0; i < level; i++)
                    printf("  "); //imprime identação (nível da árvore)

                printf("|- %s (%d)\n", name, child_pid);  // imprime nome e PID do processo
                print_tree(child_pid, level + 1); // chamada recursiva para verificar se há filhos
            }
        }
    }

    closedir(dir); // // fecha a pasta
}


// // Função que separa a linha digitada em argumentos
void quebrar(char *linha, char **args) {
    int i = 0;
    args[i] = strtok(linha, " \n");

    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " \n");
    }
}

int main() {
    char comando[MAX]; // vareavel para o comando digitado
    char *args[MAX];  // vetor de argumentos
    
    printf("  -----* INTERPRETADOR DE COMANDOS *-------\n");
    
    // loop infinito para não encerrar o terminal
    while (1) {
        printf("Terminal de comando> ");
        fflush(stdout);

        if (!fgets(comando, MAX, stdin))  // lê entrada do usuário
            break;

    
        comando[strcspn(comando, "\n")] = 0;  // remove o \n da string

        int background = 0; // vareavel para conseguir digitar outros comandos ao mesmo tempo

        // verifica se o comando termina com "&""
        int len = strlen(comando);
        if (len > 0 && comando[len - 1] == '&') {
            background = 1;   // execução em background
            comando[len - 1] = '\0'; //   // remove o '&
        }

     // separa comando em argumentos
        quebrar(comando, args);

        if (args[0] == NULL)    // se não digitou nada
            continue;
            
        // implementa echo $$ 
        if (strcmp(args[0], "echo") == 0 && args[1] != NULL) {
            if (strcmp(args[1], "$$") == 0) {
                printf("%d\n", getpid()); // // imprime PID
                continue;
            }
        }

        // EXIT -------------------------------------------------
        if (strcmp(args[0], "exit") == 0) {
            break;     // encerra o terminal
        }


        // CD ----------------------------------------------------
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                printf("Uso: cd PATH\n");  // muda diretório
            } else {
                if (chdir(args[1]) != 0)
                    perror("cd");  // // erro ao mudar diretório
            }
            continue;
        }
        

        // TREE  ---------------------------------------------------
        if (strcmp(args[0], "tree") == 0) {
            if (args[1] == NULL) {
                printf("Uso: tree PID\n");
            } else {
                int pid = atoi(args[1]);
                printf("%d\n", pid);      // imprime árvore de processos
                print_tree(pid, 1);   // chama função recursiva
            }
            continue;
        }
        

        // PROCESSO -----------------------------------------------
        pid_t pid = fork(); // // cria processo filho

        if (pid == 0) {
             // processo filho executa o comando
            execvp(args[0], args);
            perror("Erro ao executar"); // se execvp falhar
            exit(1);
        } else if (pid > 0) {
            if (!background) {
                wait(NULL);  // espera o filho terminar
            } else {
                printf("[Processo %d executando em background]\n", pid); // imprime o pid do processo em execução
            }
        } else {
            perror("fork");   // erro no fork
        }
    }

    return 0;
}
