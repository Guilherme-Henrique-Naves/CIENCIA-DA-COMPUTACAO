#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSOS 100 //difinir o máximo de processos
#define MAX_BURSTS 20     // definir o máximo de Bursts

// Dados dos processos 
int prioridade[MAX_PROCESSOS];  
int chegada[MAX_PROCESSOS];

int burst[MAX_PROCESSOS][MAX_BURSTS];
int qtdBurst[MAX_PROCESSOS];

// Controle da simulação
int burstAtual[MAX_PROCESSOS];
int restante[MAX_PROCESSOS];

int terminou[MAX_PROCESSOS];
int esperandoIO[MAX_PROCESSOS];

int tempoEspera[MAX_PROCESSOS];
int turnaround[MAX_PROCESSOS];

// Quantidade de processos
int n = 0;

// Fila dos processos
int fila[MAX_PROCESSOS];
int inicio = 0;
int fim = 0;
int cpuOciosa = 0;

int executando = -1;      // Processo usando a CPU
int tempo = 0;            // Relógio da simulação
int finalizados = 0;      // Quantos processos terminaram

int tempoIO[MAX_PROCESSOS];

FILE *saida;

// Função para reinicar as vareaveis
void reiniciar(){
    tempo = 0;
    executando = -1;
    finalizados = 0;
    inicio = 0;
    fim = 0;
    cpuOciosa = 0;

    for(int i=0;i<n;i++){
        printf("AAA");
        burstAtual[i] = 0;
        restante[i] = burst[i][0];
        esperandoIO[i] = 0;
        terminou[i] = 0;
        tempoEspera[i] = 0;
        turnaround[i] = 0;
    }
}

// Função para inserir os processo na fila
void inserirFila(int p)
{
    fila[fim]=p;
    fim++;
}


//Procedimento para Remover o processo da fila
int removerFila()
{
    int p;
    
    p=fila[inicio];
    inicio++;
    
    return p;
}

// procedimento para verificar se a fila esta vazia
int filaVazia()
{
    return inicio==fim;
}



//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------



// Função do FCFS
void FCFS(){
    int primeiraExecucao = 1;
    fprintf(saida, "FCFS: ");

    while(finalizados < n){ // LOOP para executar todos os processos
        int indoParaIO = -1; // Rastreia se alguém entrou em I/O neste exato ciclo

        // Adiciona processos
        for(int i = 0; i < n; i++){
            if(chegada[i] == tempo){
                inserirFila(i); // insere na fila
            }
        }

       // Se a CPU estiver livre
        if(executando == -1 && !filaVazia()){
            // Se estava ociosa, fecha a impressão de ociosidade no tempo atual 
            if(cpuOciosa == 1){
                fprintf(saida, "*** %d|", tempo); // coloca "***" como significado de osiosa 
                cpuOciosa = 0; // não esta mais osiosa 
            }

            executando = removerFila(); // remove da fila

            // Se for o primeiro processo, abre o gráfico 
            if(primeiraExecucao){
                fprintf(saida, "%d[", tempo); // caso seja o primeiro processo imprima " [ "
                primeiraExecucao = 0; // apos a primeira execução, ela se torna falsa 
            }
        }

        //Se continuar livre e sem ninguém na fila, entra em ociosidade
        if(executando == -1 && filaVazia()){
            if(cpuOciosa == 0 && primeiraExecucao == 0){
                cpuOciosa = 1; // torna a osiosidade verdadeira
            }
        }

        // Atualiza tempo de espera de quem está na fila 
        for(int i = inicio; i < fim; i++){
            tempoEspera[fila[i]]++;
        }

        // Executa a CPU por  unidade de tempo 
        if(executando != -1){
            restante[executando]--;
            
            if(restante[executando] == 0){
                // O processo termina no próximo passo de tempo (tempo + 1)
                fprintf(saida, "P%d %d|", executando + 1, tempo + 1);

                burstAtual[executando]++; // Avança para o surto de I/O

                if(burstAtual[executando] >= qtdBurst[executando]){
                    terminou[executando] = 1;
                    turnaround[executando] = (tempo + 1) - chegada[executando];
                    finalizados++;
                } else {
                    /* Vai para E/S */
                    esperandoIO[executando] = burst[executando][burstAtual[executando]];
                    indoParaIO = executando; // Marca que entrou em I/O agora
                    burstAtual[executando]++; // Avança para o próximo surto de CPU
                }
                executando = -1; // Libera a CPU
            }
        }

        // Processa o I/O de quem está esperando
        for(int i = 0; i < n; i++){
            // Só decrementa se o processo já estava em I/O antes deste ciclo iniciar
            if(esperandoIO[i] > 0 && i != indoParaIO){
                esperandoIO[i]--;

                if(esperandoIO[i] == 0){
                    // Como burstAtual já foi incrementado duas vezes (CPU anterior + IO atual),
                    // o burstAtual[i] já aponta corretamente para o próximo surto de CPU.
                    restante[i] = burst[i][burstAtual[i]];
                    inserirFila(i);
                }
            }
        }

        // Avanço de tempo global e unificado 
        tempo++;
    }
    reiniciar(); // reinicia as vareavies para outros métodos
    
    fprintf(saida, "]\n\n"); // fim do processo
}

//--------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------


// Procedimento para remover da fila no método SJF
int removerFilaSJF()
{
    int menor = inicio;

    // Procura o processo com menor burst de CPU
    for(int i = inicio + 1; i < fim; i++)
    {
        if(restante[fila[i]] < restante[fila[menor]])
        {
            menor = i;
        }
    }

    // Processo escolhido
    int processo = fila[menor];

    // Remove da fila deslocando os demais
    for(int i = menor; i < fim - 1; i++)
    {
        fila[i] = fila[i + 1];
    }

    fim--;

    return processo;
}


// Função do SJF
void SJF(){
    int primeiraExecucao = 1;
    fprintf(saida, "SJF: ");

    while(finalizados < n){
        int indoParaIO = -1; // Rastreia se alguém entrou em I/O neste exato ciclo

        //Adiciona processos 
        for(int i = 0; i < n; i++){
            if(chegada[i] == tempo){
                inserirFila(i); // Insere na fila
            }
        }

        // Se a CPU estiver livre, tenta pegar um processo
        if(executando == -1 && !filaVazia()){
            //Se estava ociosa, fecha a impressão de ociosidade no tempo atual
            if(cpuOciosa == 1){
                fprintf(saida, "*** %d|", tempo); // coloca "***" como significado de osiosidade
                cpuOciosa = 0; // não esta mais osiosa 
            }

            executando = removerFilaSJF(); // Remove da fila

            /* Se for o primeiro processo, abre o gráfico */
            if(primeiraExecucao){
                fprintf(saida, "%d[", tempo); // Imprime " [ " caso seja o primeiro processo
                primeiraExecucao = 0; // torna o primeiro processo falso
            }
        }

        //Se continuar livre e sem ninguém na fila, entra em ociosidade 
        if(executando == -1 && filaVazia()){
            if(cpuOciosa == 0 && primeiraExecucao == 0){
                cpuOciosa = 1; // ociosidade Verdadeira
            }
        }

        // Atualiza tempo de espera de quem está na fila 
        for(int i = inicio; i < fim; i++){
            tempoEspera[fila[i]]++;
        }

        // Executa a CPU por 1 unidade de tempo 
        if(executando != -1){
            restante[executando]--;
            
            if(restante[executando] == 0){
                // O processo termina no próximo passo de tempo (tempo + 1)
                fprintf(saida, "P%d %d|", executando + 1, tempo + 1);

                burstAtual[executando]++; // Avança para o surto de I/O

                if(burstAtual[executando] >= qtdBurst[executando]){
                    terminou[executando] = 1;
                    turnaround[executando] = (tempo + 1) - chegada[executando];
                    finalizados++;
                } else {
                    /* Vai para E/S */
                    esperandoIO[executando] = burst[executando][burstAtual[executando]];
                    indoParaIO = executando; // Marca que entrou em I/O agora
                    burstAtual[executando]++; // Avança para o próximo surto de CPU
                }
                executando = -1; // Libera a CPU
            }
        }

        // Processa o I/O de quem está esperando 
        for(int i = 0; i < n; i++){
            // Só decrementa se o processo já estava em I/O antes deste ciclo iniciar
            if(esperandoIO[i] > 0 && i != indoParaIO){
                esperandoIO[i]--;

                if(esperandoIO[i] == 0){
                    // Como burstAtual já foi incrementado duas vezes (CPU anterior + IO atual),
                    // o burstAtual[i] já aponta corretamente para o próximo surto de CPU.
                    restante[i] = burst[i][burstAtual[i]];
                    inserirFila(i);
                }
            }
        }

        //Avanço de tempo global e unificado 
        tempo++;
    }
    reiniciar();
    
    fprintf(saida, "]\n\n"); // fim do processo
}







//--------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------


// função para escolher qual processo deve executar na CPU
int escolherSRTF(){
    int escolhido = -1;

    for(int i = 0; i < n; i++){
        if(!terminou[i] &&
           esperandoIO[i] == 0 &&
           chegada[i] <= tempo &&
           restante[i] > 0)
        {
            if(escolhido == -1 || restante[i] < restante[escolhido])
            {
                escolhido = i;
            }
        }
    }

    return escolhido;
}


// Função SRTF
void SRTF(){
    int primeiraExecucao = 1;
    int ultimo_executando = -1; // Rastreia quem estava na CPU na iteração anterior
    fprintf(saida, "SRTF: ");

    while(finalizados < n){
        int indoParaIO = -1; // Rastreia se alguém entrou em I/O neste exato ciclo

        // Adiciona processos 
        for(int i = 0; i < n; i++){
            if(chegada[i] == tempo){
                inserirFila(i); // inseri na fila
            }
        }

        executando = escolherSRTF(); //Escolhe o processo com MENOR tempo restante atualizado 


        if(ultimo_executando != -1 && executando != ultimo_executando && restante[ultimo_executando] > 0){
   
            fprintf(saida, "P%d %d|", ultimo_executando + 1, tempo);   // Imprime no gráfico que o processo anterior foi interrompido no tempo atual
            
            // O processo que sofreu preempção deve voltar para a fila de prontos
            inserirFila(ultimo_executando);
        }


        if(executando != -1){
            if(cpuOciosa == 1){  // verifica se está ociosa 
                fprintf(saida, "*** %d|", tempo); // imprime " *** " , caso esteja ociosa 
                cpuOciosa = 0; // retorna a ociosidade falsa 
            }

            //caso seja a primeira execução
            if(primeiraExecucao){
                fprintf(saida, "%d[", tempo); // imprime " [ " caso seja a primeira execução
                primeiraExecucao = 0; // primeira execução falsa
            }
        }

        // Se continuar livre e sem ninguém na fila, entra em ociosidade
        if(executando == -1){
            if(cpuOciosa == 0 && primeiraExecucao == 0){
                cpuOciosa = 1;
            }
        }

        //Atualiza tempo de espera de quem está mofando na fila 
        for(int i = inicio; i < fim; i++){
            tempoEspera[fila[i]]++;
        }

        ultimo_executando = executando;

        // Executa a CPU por 1 unidade de tempo 
        if(executando != -1){
            restante[executando]--;
            
            if(restante[executando] == 0){
                // O processo termina e sai da CPU com sucesso no tempo + 1
                fprintf(saida, "P%d %d|", executando + 1, tempo + 1);

                burstAtual[executando]++; // Avança para o surto de I/O

                if(burstAtual[executando] >= qtdBurst[executando]){
                    terminou[executando] = 1;
                    turnaround[executando] = (tempo + 1) - chegada[executando];
                    finalizados++;
                } else {
                    /* Vai para E/S */
                    esperandoIO[executando] = burst[executando][burstAtual[executando]];
                    indoParaIO = executando; // Marca que entrou em I/O agora
                    burstAtual[executando]++; // Avança para o próximo surto de CPU
                }
                executando = -1; 
                ultimo_executando = -1; // Limpa para não disparar falsa preempção
            }
        }

        //Processa o I/O de quem está esperando 
        for(int i = 0; i < n; i++){
            if(esperandoIO[i] > 0 && i != indoParaIO){
                esperandoIO[i]--;

                if(esperandoIO[i] == 0){
                    restante[i] = burst[i][burstAtual[i]];
                    inserirFila(i);
                }
            }
        }

        // 7. Avanço de tempo global e unificado 
        tempo++;
    }
    
    reiniciar();
    fprintf(saida, "]\n\n"); // fim do processo
}


//--------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------


// função para escolher a propriedade
int escolherPrioridade(){
    int escolhido = -1;

    for(int i = 0; i < n; i++){
        if(!terminou[i] &&
           chegada[i] <= tempo &&
           esperandoIO[i] == 0 &&
           restante[i] > 0)
        {
            if(escolhido == -1){
                escolhido = i;
            }
            else if(prioridade[i] > prioridade[escolhido]){
                escolhido = i;
            }
            else if(prioridade[i] == prioridade[escolhido]){
                /* Empate: quem chegou primeiro */
                if(chegada[i] < chegada[escolhido])
                    escolhido = i;
            }
        }
    }

    return escolhido;
}


// função Propriedade Preemptivo
void Prioridade_Preemptivo(){
    int primeiraExecucao = 1;
    int ultimo_executando = -1; // Rastreia quem estava na CPU na iteração anterior
    fprintf(saida, "Prioridade Preemptivo: ");

    while(finalizados < n){
        int indoParaIO = -1; // Rastreia se alguém entrou em I/O neste exato ciclo

        // Adiciona processos  
        for(int i = 0; i < n; i++){
            if(chegada[i] == tempo){
                inserirFila(i);
            }
        }

        //Escolhe o processo com MENOR tempo restante atualizado 
         executando = escolherPrioridade();

        if(ultimo_executando != -1 && executando != ultimo_executando && restante[ultimo_executando] > 0){
            // Imprime no gráfico que o processo anterior foi interrompido no tempo atual
            fprintf(saida, "P%d %d|", ultimo_executando + 1, tempo);
            
        }

        /* Configuração de saída do Gráfico */
        if(executando != -1){
            if(cpuOciosa == 1){
                fprintf(saida, "*** %d|", tempo);
                cpuOciosa = 0;
            }

            // Verifica se é o primeiro processo
            if(primeiraExecucao){
                fprintf(saida, "%d[", tempo); // imprime " [ " caso seja o primeiro processo
                primeiraExecucao = 0; // torna o primeiro processo falso
            }
        }

        // Se continuar livre e sem ninguém na fila, entra em ociosidade 
        if(executando == -1){
            if(cpuOciosa == 0 && primeiraExecucao == 0){
                cpuOciosa = 1;
            }
        }

        // Atualiza tempo de espera de quem está mofando na fila 
        for(int i = inicio; i < fim; i++){
            tempoEspera[fila[i]]++;
        }

        //Rastreia quem operou este ciclo antes de gastar o tempo 
        ultimo_executando = executando;

        //5. Executa a CPU por 1 unidade de tempo 
        if(executando != -1){
            restante[executando]--;
            
            if(restante[executando] == 0){
                fprintf(saida, "P%d %d|", executando + 1, tempo + 1);

                burstAtual[executando]++; // Avança para o surto de I/O

                if(burstAtual[executando] >= qtdBurst[executando]){
                    terminou[executando] = 1;
                    turnaround[executando] = (tempo + 1) - chegada[executando];
                    finalizados++;
                } else {
                    /* Vai para E/S */
                    esperandoIO[executando] = burst[executando][burstAtual[executando]];
                    indoParaIO = executando; // Marca que entrou em I/O agora
                    burstAtual[executando]++; // Avança para o próximo surto de CPU
                }
                executando = -1; 
                ultimo_executando = -1; 
            }
        }

        // Processa o I/O de quem está esperando 
        for(int i = 0; i < n; i++){
            if(esperandoIO[i] > 0 && i != indoParaIO){
                esperandoIO[i]--;

                if(esperandoIO[i] == 0){
                    restante[i] = burst[i][burstAtual[i]];
                    inserirFila(i);
                }
            }
        }

        tempo++;
    }
    reiniciar();
    
    fprintf(saida, "]\n\n"); // fim dos processos
}



//--------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------


// função Round Robin
void RoundRobin(int quantum){
    int quantumAtual = 0;
    int primeiraExecucao = 1;
    fprintf(saida, "RoundRobin( %d ms): ",quantum);

    while(finalizados < n){
        int indoParaIO = -1; // Rastreia se alguém entrou em I/O neste exato ciclo

        // Adiciona processos na fila 
        for(int i = 0; i < n; i++){
            if(chegada[i] == tempo){
                inserirFila(i);
            }
        }

        // Se a CPU estiver livre, tenta pegar um processo 
        if(executando == -1 && !filaVazia()){
            //Se estava ociosa, fecha a impressão de ociosidade no tempo atual
            if(cpuOciosa == 1){
                fprintf(saida, "*** %d|", tempo);
                cpuOciosa = 0;
            }

            executando = removerFila();
            quantumAtual = 0;

            //Se for o primeiro processo, abre o gráfico
            if(primeiraExecucao){
                fprintf(saida, "%d[", tempo);
                primeiraExecucao = 0;
            }
        }


        // Se continuar livre e sem ninguém na fila, entra em ociosidade 
        if(executando == -1 && filaVazia()){
            if(cpuOciosa == 0 && primeiraExecucao == 0){
                cpuOciosa = 1;
            }
        }

        // Atualiza tempo de espera de quem está na fila 
        for(int i = inicio; i < fim; i++){
            tempoEspera[fila[i]]++;
        }

        // Executa a CPU por 1 unidade de tempo 
        if(executando != -1){
            restante[executando]--;
            quantumAtual++;
            
            if(restante[executando] == 0){
                fprintf(saida, "P%d %d|", executando + 1, tempo + 1);

                burstAtual[executando]++; // Avança para o surto de I/O

                if(burstAtual[executando] >= qtdBurst[executando]){
                    terminou[executando] = 1;
                    turnaround[executando] = (tempo + 1) - chegada[executando];
                    finalizados++;
                } else {
                    /* Vai para E/S */
                    esperandoIO[executando] = burst[executando][burstAtual[executando]];
                    indoParaIO = executando; // Marca que entrou em I/O agora
                    burstAtual[executando]++; // Avança para o próximo surto de CPU
                }
                executando = -1; // Libera a CPU
            }else if(quantumAtual == quantum){

            
                  fprintf(saida, "P%d %d|", executando + 1, tempo + 1);
                inserirFila(executando);

                executando = -1;
            }
        }

        //Processa o I/O de quem está esperando 
        for(int i = 0; i < n; i++){
            // Só decrementa se o processo já estava em I/O antes deste ciclo iniciar
            if(esperandoIO[i] > 0 && i != indoParaIO){
                esperandoIO[i]--;

                if(esperandoIO[i] == 0){
                    restante[i] = burst[i][burstAtual[i]];
                    inserirFila(i);
                }
            }
        }
        tempo++;
    }
  
    
    fprintf(saida, "]\n\n");
}



//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------




// Função para ler o arquivo e guardar nos vetores
void lerArquivo(char nome[]){
    FILE *arq;
    char linha[300];
    char *token;

    arq = fopen(nome, "r");

    if(arq == NULL){
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }


    while(fgets(linha,sizeof(linha),arq)){

        token = strtok(linha," ");
        prioridade[n] = atoi(token);

        token = strtok(NULL," ");
        chegada[n] = atoi(token);

        qtdBurst[n] = 0;

        while((token = strtok(NULL," \n")) != NULL){
            burst[n][qtdBurst[n]] = atoi(token);
            qtdBurst[n]++;
        }
        burstAtual[n]=0;
        restante[n]=burst[n][0];

        terminou[n]=0;
        tempoIO[n]=0;

        tempoEspera[n]=0;
        turnaround[n]=0;

        n++;
    }
    fclose(arq);
}


int main(int argc, char *argv[]){
    
    char nomeSaida[100];
     int quantum;

    // Verificar se a entrada esta correta

    if(argc < 3){
        printf("Uso: %s arquivo.txt quantum\n", argv[0]);
        return 1;
    }


    // Ler o arquivo
    lerArquivo(argv[1]);

    sprintf(nomeSaida,"%s.out",argv[1]);
    saida = fopen(nomeSaida,"w");

    if(saida==NULL){
        printf("Erro ao criar arquivo.\n");
        return 1;
    }

    

    FCFS();
    SJF();
    SRTF();
    Prioridade_Preemptivo();

    quantum = atoi(argv[2]);
    RoundRobin(quantum);

    fclose(saida);


    printf("Quantidade de processos: %d\n\n", n);

    //Saída da leitura do arquivo
    for (int i = 0; i < n; i++){
        printf("P%d\n", i + 1);

        printf("Prioridade= %d\n", prioridade[i]);
        printf("Chegada= %d\n", chegada[i]);

        printf("Bursts: ");

        for (int j = 0; j < qtdBurst[i]; j++){
            printf("%d", burst[i][j]);

            if (j < qtdBurst[i] - 1)
                printf(" ");
        }
          printf("\n\n");
    }

    return 0;
}


