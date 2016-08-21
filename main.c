/* Mini-EP1 
   NUSP: 8987847
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* Para um inteiro, descarta o token que já foi lido e interpretado (para a leitura por extenso) e retorna o inteiro restante*/
/* Ex.: para x = 314, dado que o primeiro token já foi lido, 'trezentos', retorna o próximo inteiro para o qual deve-se fazer a leitura, ou seja, 14*/
int nextToken(int x){
	/*Valor de resposta*/
	int nt;
	/*Valor de x que será alterado*/
	int y = x;
	/*Representa a maior potência de 10 menor ou igual a x. Útil para se remover o algarismo mais significante de x*/
	int base = 1;
	/*No caso de 10 < x < 20, i.e, onze, doze, ..., dezenove; não haverá a busca pela unidade, logo não haverá um próximo token e a leitura por extenso terminará.*/ 
	if(10 < y && y < 20)
		nt = 0;
	else{
		while(y / 10){
			y /= 10;
			base *= 10;
		}
		nt = x - y*base;
	}
	return nt;
}

char *palavra(int *x){
	int a, b;
	int X = *x;
	int pivo = 0;
	char *conjuncao = "";
	char *grandeza = "";
	char *resp;
	char *palavra = "";
	char *numero[4][10] = {
		{"zero", "um", "dois", "três", "quatro", "cinco", "seis", "sete", "oito", "nove"},
		{"dez", "onze", "doze", "treze", "quatorze", "quinze", "dezesseis", "dezessete", "dezoito", "dezenove"},
		{"", "", "vinte", "trinta", "quarenta", "cinquenta", "sessenta", "setenta", "oitenta", "noventa"},
		{"cem", "cento", "duzentos", "trezentos", "quatrocentos", "quinhentos", "seiscentos", "setecentos", "oitocentos", "novecentos"},
	};
	
	while(X / 10){
		pivo++;
		X /= 10;
	}
	
	switch (pivo){
		case 1:
			if(nextToken(*x))
			conjuncao = " e";
			if(*x / 10 == 1)
				X = *x % 10;
			else
				pivo++;
			break;
		case 2:
			pivo++;
			if(nextToken(*x))
				conjuncao = " e";
			if((*x)/100 == 1 && !((*x)%100))
				X--;
			break;
		case 3:
			if(*x/1000 == 1){
				pivo--;
				X--;
			}
			else
				pivo = 0;
			grandeza = " mil";
			if(nextToken(*x))
				if((((*x % 1000)/100) && !((*x)%100)) || (!((*x % 1000)/100) && (*x)%100))
					conjuncao = " e";
			break;
	}
	
	palavra = (char *) malloc(2+strlen(numero[pivo][X]));
	strcpy(palavra, numero[pivo][X]);
	
	resp = (char *) malloc(1+strlen(palavra)+strlen(grandeza)+strlen(conjuncao));
	strcat(resp, palavra);strcat(resp, grandeza);strcat(resp, conjuncao); 
	
	return resp;	
}

char *leitura(int x){
	char *anterior = "";
	char *obtida = "";
	char *resp = "";
	do{
		anterior = malloc(1+strlen(resp));
		strcat(anterior, resp);
		obtida = palavra(&x);
		resp = (char *) malloc(2+strlen(anterior)+strlen(obtida));
		strcat(resp, anterior);
		strcat(resp, obtida);
		if(strlen(resp) > 0 && nextToken(x))
			strcat(resp, " ");
		x = nextToken(x);
	} while(x);
	return resp;
}

char gerador(char *texto, FILE *saida){
	char token[10];
	char *p, *q, *inteiro, *cent, *moeda, *centavos;
	char *teste = "RS";
	char i;
	int maior, decimalInt;
	p = texto;
	q = texto;
	
	while(*(p-1) != '$'){
		token[p-q] = *p;
		p++;
	}
	token[p - q] = '\0';
	if(!strcmp(token, "R$"))
		moeda = "reais";
	else if (!strcmp(token, "US$"))
		moeda = "dólares";
	else
		moeda = "erro";
	q = p;
	do{
		token[p-q] = *p;
		p++;
	} while(*p != ',');
	token[p-q] = '\0';
	maior = atoi(token);
	inteiro = leitura(maior);
	q = ++p;
	do{
		token[p-q] = *p;
		p++;
	} while(p - q < 2);
	token[p-q] = '\0';
	decimalInt = atoi(token);
	if(decimalInt > 1)
		centavos = "centavos";
	else if(decimalInt == 1)
		centavos = "centavo";
	else if(!decimalInt)
		centavos = "centavos";
	else
		centavos = "erro";
	cent = leitura(decimalInt);
	if(maior == 1 || !maior && (decimalInt == 1))
		if (moeda == "reais")
			moeda = "real";
		else if (moeda == "dólares")
			moeda = "dólar";
		else
			moeda = "erro na moeda";
	printf("maior %d\tcent%d\n", maior, decimalInt);
	if (!maior && decimalInt)
		fprintf(saida, "%s %s de %s\n", cent, centavos, moeda);	
	 else
		fprintf(saida, "%s %s e %s %s\n", inteiro, moeda, cent, centavos);
	//else fprintf(saida, "erro: %d\n", maior);
}

int main (int argc, char *argv[]) {
    FILE *entrada, *saida;
    /* Declaração de suas variáveis */
	char caso[500];
	
    /* Verifica se numero de argumentos de entrada é suficiente */
    if (argc < 3) {
        printf("Numero de parametros insuficiente:\n\tuse %s arquivo_entrada arquivo_saida\n", argv[0]);
    }
    /* Abre arquivo de entrada; termina programa em caso de falha */
    if (!(entrada = fopen(argv[1], "r"))) {
        printf("Nao foi possivel abir o arquivo %s para leitura. Abortando...\n", argv[1]);
        return 1;
    }
    /* Abre arquivo de saida; termina programa em caso de falha */
    if (!(saida = fopen(argv[2], "w"))) {
        printf("Nao foi possivel abir o arquivo %s para escrita. Abortando...\n", argv[2]);
        return 1;
    }
	
    /* Seu código */
	while(fscanf(entrada, "%s", caso) != EOF){
		//printf("%s\t", caso);
		gerador(caso, saida);
	}
	
	fclose(entrada);
	fclose(saida);
	
    return 0;
}