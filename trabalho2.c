//Pedro Renato Binelo Briltes e Kellven Dias
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <limits.h>

#define MAX_PROC 100

//processo preemptivo
typedef struct{
    int pid;
    int bt;//burst time
    int arrival_time;
    int remaining_time;
    int finish_time;
    int wt;//waiting time
    int tat;//turnaround time 
    int completed;
    int priority;
} Process;



void lerFCFS(int **proc, int **burst_time, int *n);
void FCFS(int proc[], int n, int burst_time[]);
void lerSJFP(Process proc[], int tamanho);
void lerSJFNP(Process proc[], int tamanho);
int findShortestRemainingTime(Process proc[], int tamanho, int current_time);
void SJFpreemptive(Process proc[], int tamanho);
int findShortestJob(Process proc[], int tamanho, int current_time);
void SJFNonPreemptive(Process proc[], int tamanho);
void lerPrioritySched(Process proc[], int tamanho);
void PriorityScheduling(Process proc[], int tamanho);
void lerRoundRobin(Process proc[], int tamanho);
void RoundRobin(Process proc[], int tamanho, int quantum);

int main(){
    setlocale(LC_ALL, "Portuguese");
    int op, tamanho, quantum;
    int *proc = NULL;
    int n;
    int *burst_time = NULL;

    do{
        printf("\n\nEscolha algum algoritmo de escalonamento: \n\n");
        printf("\t1 - FCFS\n");
        printf("\t2 - SJF preemptivo\n");
        printf("\t3 - SJF não preemptivo\n");
        printf("\t4 - Priority Scheduling\n");
        printf("\t5 - Round Robin\n\n");
        printf("\tDigite qualquer outro valor para encerrar o programa.\n\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &op);
        system("clear");

        if(op == 1){
            //FCFS
            lerFCFS(&proc, &burst_time, &n);
            FCFS(proc, n, burst_time);

            //liberar memória alocada
            free(proc);
            free(burst_time);
        }
        else if(op == 2){ //SJF preemptivo
                do{
                    printf("Digite o número de processos: ");
                    scanf("%d", &tamanho);
                    system("clear");
                    if(tamanho<2){
                        printf("\tValor inválido.\n\n");
                    }
                }while(tamanho<2);

                Process *proc = (Process *)malloc(tamanho * sizeof(Process));

                if(proc == NULL){
                    printf("Erro de alocação de memória.\n");
                    exit(1);
                }

                lerSJFP(proc, tamanho);
                SJFpreemptive(proc, tamanho);
                free(proc);
        }
        else if(op == 3){
                    //SJF não preemptivo
                    do{
                        printf("Digite o número de processos: ");
                        scanf("%d", &tamanho);
                        system("clear");
                        if(tamanho<2){
                            printf("\tValor inválido.\n\n");
                        }
                    }while(tamanho<2);

                    Process *proc = (Process *)malloc(tamanho * sizeof(Process));

                    if(proc == NULL){
                        printf("Erro de alocação de memória.\n");
                        exit(1);
                    }

                    lerSJFNP(proc, tamanho);
                    SJFNonPreemptive(proc, tamanho);
                    free(proc);
        }
        else if(op == 4){

            do{
                printf("Digite o número de processos: ");
                scanf("%d", &tamanho);
                system("clear");
                if(tamanho<2){printf("\tValor inválido. \n\n");}
            }while(tamanho<2);

            Process *proc = (Process *)malloc(tamanho * sizeof(Process));

            if(proc==NULL){
                printf("Erro de alocação de memória. \n");
                exit(1);
            }

            lerPrioritySched(proc, tamanho);
            PriorityScheduling(proc, tamanho);
            free(proc);


        }
        else if(op == 5){ //Round Robin

            do{
                printf("Digite o número de processos: ");
                scanf("%d", &tamanho);
                system("clear");
                if(tamanho<2){printf("\tValor inválido. \n\n");}
            }while(tamanho<2);

            printf("Digite o valor do quantum: ");
            scanf("%d", &quantum);

            Process *proc = (Process *)malloc(tamanho * sizeof(Process));

            if(proc==NULL){
                printf("Erro de alocação de memória. \n");
                exit(1);
            }

            lerRoundRobin(proc, tamanho);
            RoundRobin(proc, tamanho, quantum);
            free(proc);

        }
        else if(op>5 || op<=0){
                                printf("\n\tFim do programa.\n\n");
                            }
    }while(op>0 && op<6);
    
    return 0;
}

void lerFCFS(int **proc, int **burst_time, int *n){
    do{
        printf("Digite o número de processos: ");
        scanf("%d", n);
        system("clear");
        if(*n<2){
            printf("\tValor inválido.\n\n");
        }
    }while(*n<2);

//alocação de memória para numero de processos e burst time
    *proc = (int*) malloc(*n * sizeof(int));
    *burst_time = (int*) malloc(*n * sizeof(int));

    if(*proc == NULL || *burst_time == NULL){
        printf("Erro de alocação de memória.");
        exit(1);
    }
    if(*proc!=NULL && *burst_time!=NULL){
        for(int i=0; i<*n; i++){
            (*proc)[i] = i+1;
            printf("Digite o burst time do processo %d: ", (*proc)[i]);
            scanf("%d", &(*burst_time)[i]);
            system("clear");
        }
    }

}
void FCFS(int proc[],int n,int burst_time[]){
    int i, wait_time[n], sum_wt=0;

    //Find the waiting time for processes
    wait_time[0]=0; //Because waiting time for 1° process is zero
    //Calculating waiting time
    i=1;
    while(i<n){
        wait_time[i] = burst_time[i-1] + wait_time[i-1];
        i++;
    }
    printf("\tProcessos\tBurst\tEspera\n\n");

    for(int i = 0; i<n; i++){
        sum_wt += wait_time[i];
        printf("\t%d\t\t%d\t%d\n\n", (i+1), burst_time[i], wait_time[i]);
    }

    float avgwt = (float)sum_wt/n;
    printf("Tempo médio de espera: %.2f\n", avgwt);
}
void lerSJFP(Process proc[], int tamanho){
    for(int i = 0; i<tamanho; i++){
        proc[i].pid = i+1;
        printf("Digite o tempo de chegada do processo %d: ", proc[i].pid);
        scanf("%d", &proc[i].arrival_time);
        system("clear");
        printf("Digite o burst time do processo %d: ", proc[i].pid);
        scanf("%d", &proc[i].bt);
        system("clear");
    }
}
int findShortestRemainingTime(Process proc[], int tamanho, int current_time){
    int min_index = -1;
    int min_time = INT_MAX;

    for(int i = 0; i<tamanho; i++){
        if(proc[i].arrival_time <= current_time && proc[i].remaining_time > 0 && proc[i].remaining_time < min_time){
            min_time = proc[i].remaining_time;
            min_index = i;
        }
    }

    return min_index; //indice do processo com menor tempo restante
}
void SJFpreemptive(Process proc[], int tamanho){
    int current_time = 0;
    int completed = 0;

    for(int i = 0; i<tamanho; i++){
        proc[i].remaining_time = proc[i].bt;
    }

    while(completed < tamanho){
        int shortest = findShortestRemainingTime(proc, tamanho, current_time);

        //verificação se há processos prontos no momento
        if(shortest == -1){
            current_time++;
            continue;
        }

        proc[shortest].remaining_time--;
        current_time++;

        //calculo turnaround time e waiting time
        if(proc[shortest].remaining_time == 0){
            completed++;
            proc[shortest].finish_time = current_time;
            proc[shortest].tat = proc[shortest].finish_time - proc[shortest].arrival_time;
            proc[shortest].wt = proc[shortest].tat - proc[shortest].bt;
        }
    }
    // Calcular tempo médio de espera e tempo mÃ©dio de turnaround
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    printf("PID\tChegada\tBurst\tTérmino\tTurnaround\tEspera\n");

    for (int i = 0; i < tamanho; i++) {
        total_waiting_time += proc[i].wt;
        total_turnaround_time += proc[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].bt, proc[i].finish_time, proc[i].tat, proc[i].wt);
    }

    printf("\n\nTempo médio de espera: %.2f\n", total_waiting_time / tamanho);
    printf("Tempo médio de turnaround: %.2f\n", total_turnaround_time / tamanho);
}
int findShortestJob(Process proc[], int tamanho, int current_time){
    int min_index = -1;
    int min_time = INT_MAX;

    for (int i = 0; i < tamanho; i++) {
        if (proc[i].arrival_time <= current_time && !proc[i].completed && proc[i].bt < min_time) {
            min_time = proc[i].bt;
            min_index = i;
        }
    }

    return min_index;
}
void SJFNonPreemptive(Process proc[], int tamanho) {
    int current_time = 0;
    int completed = 0;

    while (completed < tamanho) {
        int shortest = findShortestJob(proc, tamanho, current_time);

        if (shortest == -1) {
            current_time++;
            continue;
        }

        current_time += proc[shortest].bt;
        proc[shortest].finish_time = current_time;
        proc[shortest].tat = proc[shortest].finish_time - proc[shortest].arrival_time;
        proc[shortest].wt = proc[shortest].tat - proc[shortest].bt;
        proc[shortest].completed = 1;
        completed++;
    }

    // Calcular tempo médio de espera e tempo médio de turnaround
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    printf("PID\tChegada\tBurst\tTérmino\tTurnaround\tEspera\n");

    for (int i = 0; i < tamanho; i++) {
        total_waiting_time += proc[i].wt;
        total_turnaround_time += proc[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].bt, proc[i].finish_time, proc[i].tat, proc[i].wt);
    }

    printf("\n\nTempo médio de espera: %.2f\n", total_waiting_time / tamanho);
    printf("Tempo médio de turnaround: %.2f\n", total_turnaround_time / tamanho);
}
void lerSJFNP(Process proc[], int tamanho){
    for(int i = 0; i<tamanho; i++){
        proc[i].pid = i+1;
        printf("Digite o tempo de chegada do processo %d: ", proc[i].pid);
        scanf("%d", &proc[i].arrival_time);
        system("clear");
        printf("Digite o burst time do processo %d: ", proc[i].pid);
        scanf("%d", &proc[i].bt);
        system("clear");
        proc[i].completed = 0;
    }
}
void lerPrioritySched(Process proc[], int tamanho){


    for(int i=0; i<tamanho; i++){
        proc[i].pid = i+1;
        printf("Digite o tempo de chegada do processo %d: ", proc[i].pid);
        scanf("%d", &proc[i].arrival_time);
        system("clear");
        printf("Digite o burst time do processo %d: ", proc[i].pid);
        scanf("%d", &proc[i].bt);
        system("clear");
        printf("Digite a prioridade do processo %d: ", proc[i].pid);
        scanf("%d", &proc[i].priority);
        system("clear");
    }

}
void PriorityScheduling(Process proc[], int tamanho){

    int current_time = 0;
    int completed = 0;
    
    for(int i=0; i<tamanho; i++){
        proc[i].remaining_time = proc[i].bt;
    }

    //calcular a maior prioridade cada processo
    while (completed < tamanho){
        int max_priority_index = -1;
        int max_priority = INT_MAX;

        //processo de maior prioridade é definido como o processo de menor valor numérico, isto é, se proc1.priority = 1 e proc2.priority = 2, proc1 tem maior prioridade que proc2
        //Encontrar processo com maior prioridade
        for(int i=0; i<tamanho; i++){
            if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0 && proc[i].priority < max_priority){
                max_priority_index = i;
                max_priority = proc[i].priority;
            }
        }

        if(max_priority_index == -1){
            current_time++;
            continue;
        }

        //execução do processo com maior prioridade
        int shortest = max_priority_index;
        proc[shortest].remaining_time--;
        current_time++;

        //conclusão do processo
        if(proc[shortest].remaining_time == 0){
            completed++;
            proc[shortest].finish_time = current_time;
            proc[shortest].tat = proc[shortest].finish_time - proc[shortest].arrival_time;
            proc[shortest].wt = proc[shortest].tat - proc[shortest].bt;
        }
        
    }
       // Calcular tempo médio de espera e tempo médio de turnaround
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    printf("PID\tChegada\tBurst\tPrioridade\tTérmino\tTurnaround\tEspera\n");

    for (int i = 0; i < tamanho; i++) {
        total_waiting_time += proc[i].wt;
        total_turnaround_time += proc[i].tat;
        printf("%-4d\t%-7d\t%-6d\t%-15d\t%-11d\t%-11d\t%-2d\n", proc[i].pid, proc[i].arrival_time, proc[i].bt, proc[i].priority, proc[i].finish_time, proc[i].tat, proc[i].wt);
    }

    printf("\n\nTempo médio de espera: %.2f\n", total_waiting_time / tamanho);
    printf("Tempo médio de turnaround: %.2f\n", total_turnaround_time / tamanho);
}
void lerRoundRobin(Process proc[], int tamanho){

    for(int i=0; i<tamanho; i++){
        proc[i].pid = i+1;
        printf("Digite o tempo de chegada do processo %d: ", proc[i].pid);
        scanf("%d", &proc[i].arrival_time);
        system("clear");
        printf("Digite o burst time do processo %d: ", proc[i].pid);
        scanf("%d", &proc[i].bt);
        system("clear");

    }
}
void RoundRobin(Process proc[], int tamanho, int quantum){
    
    //inicializando processos
    for(int i=0; i<tamanho; i++){
        proc[i].remaining_time = proc[i].bt;
        proc[i].completed = 0;
        proc[i].wt = 0;
        proc[i].tat = 0;
        proc[i].finish_time = 0;
    }

    int time = 0;
    int completed_proc = 0;
    int queue[MAX_PROC];
    int front = 0, rear = 0;

    //iniciar lista com processos que chegaram primeiro
    for(int i=0; i<tamanho; i++){
        if(proc[i].arrival_time <= time){
            queue[rear++] = i;
        }
    }

    while(completed_proc < tamanho){

        if(front != rear){
            int current_proc_index = queue[front++];
            Process *current_proc = &proc[current_proc_index];

            if(current_proc->remaining_time>quantum){
                time += quantum;
                current_proc->remaining_time -= quantum;
            } else{
                time += current_proc->remaining_time;
                current_proc->remaining_time = 0;
                current_proc->completed = 1;
                current_proc->finish_time = time;
                current_proc->tat = current_proc->finish_time - current_proc->arrival_time;
                current_proc->wt = current_proc->tat - current_proc->bt;
                completed_proc++;
            }

            for(int i=0; i<tamanho; i++){
                if(proc[i].arrival_time <= time && proc[i].completed == 0 && i != current_proc_index){
                    bool already_in_queue = false;
                    for(int j = front; j<rear; j++){
                        if(queue[j] == i){
                            already_in_queue = true;
                            break;
                        }
                    }
                    if(!already_in_queue){
                        queue[rear++] = i;
                    }

                }
            }

            if(current_proc->remaining_time > 0){
                queue[rear++] = current_proc_index;
            }
        }else{

            int min_arrival_time = INT_MAX;
            for(int i=0; i<tamanho; i++){
                if(proc[i].completed == 0 && proc[i].arrival_time < min_arrival_time){
                    min_arrival_time = proc[i].arrival_time;
                }
            }
            if(min_arrival_time != INT_MAX){
                time = min_arrival_time;
                for(int i=0; i<tamanho; i++){
                    if(proc[i].arrival_time <= time && proc[i].completed == 0){
                        queue[rear++] = i;
                    }
                }
            }
        }
    }
    
    printf("PID\tChegada\tBurst\tFinish\tEspera\tTurnaround\n");
    for(int i=0; i<tamanho; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].bt, proc[i].finish_time, proc[i].wt, proc[i].tat);
    }   
}
