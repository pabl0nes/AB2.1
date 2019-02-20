# Identificação

* Página do repositório do trabalho ([link GitHub](TODO)) 

* Discente 1
	* Nome: Yago Taveiros Ferreira
	* Matrícula: 18211167
	* Distribuição da nota (%):33,3
* Discente 2
	* Nome: Ana Carolina Nesso Guedes
	* Matrícula:18211736
	* Distribuição da nota (%):33,3
* Discente 3
	* Nome: Pablo Vinicius de Araújo Gonçalves
	* Matrícula: 18211817
	* Distribuição da nota (%):33,3		
	
# Resultados

* TODO: Plotar um gráfico com os resultados das medições das seguintes métricas utilizadas para avaliar o comportamento do *processo filho*:
*  *UCP*:  
![grafico1](https://i.imgur.com/PlYTJqF.jpg)

O comportamento não foi o esperado, pois nota-se uma onda com vales e picos quando se executa só a ucp, o valor começa alto e decresce e em seguida volta a aumentar, porém esperávamos que ocorresse apenas um aumento progressivo, pois em tese ,devido ao loop ser ‘infinito”, era esperado um consumo crescente, como analisado no gráfico.
 
*  *UCP-MEM*:  
![grafico2](https://i.imgur.com/9CDLD3I.jpg)

Já quando observa-se o gráfico da ucp-mem, nota-se uma mudança brusca na utilização da ucp, comparando com os valores anteriormente recebidos, é notório uma redução na porcentagem de uso, como relata o gráfico:





# Discussão


Na int main, cria-se uma condicional para que ,se for digitado menos do que dois argumentos, emita uma mensagem de que seja inserido um ou mais argumentos.  
Após cria-se um inteiro que receberá o retorno da função fork(), se o inteiro tiver valor menor que zero exibe-se uma mensagem de “erro”, porque a função fork tem que retornar ou zero ou algum número.

int main(int argc, char **argv) 

    {
	
	if (argc<2)
	{
		printf("Por favor use ucp ou ucp-mem\n");
	}
	else 
	{
		int pid;
		pid=fork();

		if (pid<0)
		{
			printf("Erro\n");
			exit(-1);
    }


 Neste momento, ele cai para outra condicional, em que se seu valor for zero deduz-se que ele é o filho, nesse momento começa a executar as condicionais dedicadas ao “filho”, em que se o argv escrito for “ucp” ele executa um loop infinito, se o argv escrito for “ucp-mem” ele executa um loop infinito em ele dorme por 1 milésimo de segundo e executa o malloc que ocupa, em Bytes, a quantidade de memória digitada em seus parênteses. 

else if (pid==0)
		{
			
			if (strcmp(argv[1], "ucp")==0)
			{
				for (;;){}
			}
			else if (strcmp(argv[1], "ucp-mem")==0){
				for(;;)
				{
					usleep(1);
					malloc(sizeof(10000));
				}
			}

Quando esse inteiro receber um valor que for diferente de zero, deduzimos que ele entrou no processo pai, em que esse inteiro executará o monitoramento  do trabalho desempenhado pelo filho tanto na cpu, quanto na memória.

else 
		{

			if (strcmp(argv[1], "ucp")==0)
			{
				for (int i = 0; i < 10; ++i)
				{
					sleep(1);
					monitorar_ucp(pid);
				}
			}
			else if(strcmp(argv[1], "ucp-mem")==0)
			{
				for (int i = 0; i < 10; ++i)
				{
					sleep(1);
					monitorar_ucp(pid);
					monitorar_mem(pid);
				}
			}

			matar_meu_filho(pid);
		}
	}


    void monitorar_ucp(int pid)
    {
	char bash_cmd[256];
	sprintf(bash_cmd, "ps u %d | awk '{print $3}' | grep -v CPU", pid);
	char buffer[1000];
	FILE *pipe;
	int len; 
	pipe = popen(bash_cmd, "r");

	if (NULL == pipe) {
		perror("pipe");
		exit(1);
    } 
	
	char* cpu_usage = fgets(buffer, sizeof(buffer), pipe);
	len = strlen(bash_cmd);
	bash_cmd[len-1] = '\0'; 
	pclose(pipe);

	printf("cpu_usage == %s", cpu_usage);
     }


    void monitorar_mem(int pid)
    {
	char bash_cmd[256];
	sprintf(bash_cmd, "ps u %d | awk '{print $5}' | grep -v VSZ", pid);
	char buffer[1000];
	FILE *pipe;
	int len; 
	pipe = popen(bash_cmd, "r");

	if (NULL == pipe) {
		perror("pipe");
		exit(1);
    } 
	
	char* mem_usage = fgets(buffer, sizeof(buffer), pipe);
	len = strlen(bash_cmd);
	bash_cmd[len-1] = '\0'; 
	pclose(pipe);

	printf("mem_usage == %s\n", mem_usage);
}

Em seguida, chama-se uma função para encerrar o processo filho.

    void matar_meu_filho(int pid)
     {
	char bash_cmd[256] = "kill -TERM 0";
	sprintf(bash_cmd, "kill -TERM %d",pid);
	char buffer[1000];
	FILE *pipe;
	int len; 
	pipe = popen(bash_cmd, "r");

	if (NULL == pipe) {
		perror("pipe");
		exit(1);
     } 
	
	char* mem_usage = fgets(buffer, sizeof(buffer), pipe);
	len = strlen(bash_cmd);
	bash_cmd[len-1] = '\0'; 
	pclose(pipe);

}


Tal função foi adaptada do trecho de código disponibilizado.








