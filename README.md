
# Trabalho prático

## Simulador de Algoritmos de Escalonamento

__Alunos:__ Pedro Binelo e Kellven Dias 

Este projeto implementa diferentes algoritmos de escalonamento de processos em C. Os algoritmos disponíveis são:

- __First-Come, First-Served (FCFS)___
- __Shortest Job First (SJF) Preemptivo__
- __Shortest Job First (SJF) Não Preemptivo__
- __Priority Scheduling__
- __Round Robin (RR)__ 

### Funções

- __lerFCFS:__ Lê os dados dos processos para o algoritmo FCFS.
- __FCFS:__ Implementa o algoritmo First-Come, First-Served. 
- __lerSJFP:__ Lê os dados dos processos para o algoritmo SJF Preemptivo.
- __SJFpreemptive:__   Implementa o algoritmo Shortest Job First Preemptivo.
- __lerSJFNP:__ Lê os dados dos processos para o algoritmo SJF Não Preemptivo.
- __SJFNonPreemptive:__ Implementa o algoritmo Shortest Job First Não Preemptivo. 
- __lerPrioritySched:__ Lê os dados dos processos para o algoritmo Priority Scheduling.
- __PriorityScheduling:__ Implementa o algoritmo de escalonamento por prioridade.
- __lerRoundRobin:__ Lê os dados dos processos para o algoritmo Round Robin.
- __RoundRobin:__ Implementa o algoritmo Round Robin. 

### Função principal

A função `main` é responsável por apresentar o menu para o usuário e executar o algoritmo de escalonamento escolhido. Ela contém um loop que exibe as opções de algoritmo e chama a função correspondente conforme a escolha do usuário.



