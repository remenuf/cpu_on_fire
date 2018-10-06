#include <stdio.h> /* Usada com a função "snprintf". */
#include <stdlib.h> /* Usada com as funções "system" e "malloc". */
#include <string.h> /* Usada com a função "strcmp". */
#include <unistd.h> /* Usada com as funções "fork" e "sleep". */
#include <time.h> /* Usada com as funções "time" e "difftime". */

int main(int argc, char *argv[]) /* O "argv" será usado para especificar qual função o programa irá executar, bastando escrever o comando após o comando de execução do programa. */
{
  char cmd_cpu[256]; /* String utilizada para armazenar o comando bash de leitura do uso de CPU. */
  char cmd_mem[256]; /* String utilizada para armazenar o comando bash de leitura do uso de Memória. */
  int pid = fork(); /* Cria um processo filho identico ao original ao mesmo tempo em que retorna o ID do processo */

  time_t last, now; /* Cria duas variáveis que serão utilizadas para armazenar o tempo de execução do processo e posteriormente serão comparadas. */
last = time(NULL); /* Definição da variável com a função "time", que retorna o valor de segundos passados desde o início do processo. */

  snprintf (cmd_cpu, 256, "ps -p %d -o %%cpu | grep -v %%CPU", pid); /* Função utilizada para introduzir uma variável dentro de uma string, neste caso o PID (ID do processo), que será utilizado para especificar qual processo terá sua CPU analisada. PEsquise sobre comandos Bash no Linus para uma melhor compreensão.*/
  snprintf (cmd_mem, 256, "pmap %d | grep -i total | awk '{print$2}'", pid);


  if (pid > 0) /* Condição ativa caso o processo em questão seja o processo pai. */
  {
    int i = 0; /* Variável criada como índice para a repetição. */
    while (i < 10) /* Condição para repetir o que estiver na função por 10 vezes. */
    {
      system(cmd_cpu); /* Envia uma String como comando para o sistema, no caso que antes fora armazenado o comando para leitura de CPU. */
      system(cmd_mem); /* Envia para o sistema o comando de leitura de uso de memória. */
      i ++; /* Acrescenta-se + 1 na variável "i" para que eventualmente a condição (i < 10) deixe de ser verdadeira. */
      sleep (1); /* Para a execução da funçao por 1 segundo, assim o programa durará os 10 segundos requisitados. */
    }
    char kill[256]; /* String criada para o comando Bash que encerrará o processo filho (responsável pelo uso de CPU e Memória). */
    snprintf (kill, 256, "kill %d", pid); /* Definindo o PID do processo filho como o parâmetro do comando "Kill", que encerra um processo. */
    system(kill); /* Envia o comando para matar o processo filho. */
  }
  else /* Caso contrário se trata do processo filho. */
  {
    if (strcmp(argv[1], "cpu") == 0) /* Se a String definida no argv[1] (entrada após o "./main") for igual a "cpu": Execute o que estiver contido. */
    {
      for(;;){} /* Laço infinito que implica no intenso uso da UCP. */
    }
    if (strcmp(argv[1], "cpu-mem") == 0) /*Se a String definida no aergv[1] for igual a "cou-mem": Execute o que estiver contido. */
    {
      int i; /* Índice. */
      for (;;) /* Laço infinito que resulta no alto uso da UCP. */
      {
        now = time(NULL); /* Outra utilização de "time" para definir quantos segundos se passaram desde o início do processo. "now" representará o tempo atual (para o processo). */
        if (difftime(now, last) >= 0.5) /* Se "now" e "last" tiverem uma diferença de tempo maior do que meio segundo: Execute o que estiver contido. */
        {
          for (i = 0; i < 10000; i++) /* Execute o que estiver contido 10000 vezes, garantia de que o processo utilizará a memória intensamente. */
          {
            malloc(3000*sizeof(int)); /* Aloque "x" bits para serem utilizados neste processo. */
          }
          last = time(NULL); /* Definição através de "time". "last" será usado como referência para comparar com "now". */
        }
      }
    }
  }

}
