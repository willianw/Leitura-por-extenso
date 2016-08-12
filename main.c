/* Mini-EP1 
   NUSP: 8987847
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nextToken(int x){
	int nt;
	int y = x;
	int base = 1;
	if(10 < x && x < 20)
		nt = 0;
	else{
		while(x / 10){
			x /= 10;
			base *= 10;
		}
		nt = y - x*base;
	}
	//printf("NT(%d) = %d \n", y, nt);
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
		{"zero", "um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove"},
		{"dez", "onze", "doze", "treze", "quatorze", "quinze", "dezesseis", "dezessete", "dezoito", "dezenove"},
		{"", "", "vinte", "trinta", "quarenta", "cinquenta", "sessenta", "setenta", "oitenta", "noventa"},
		{"cem", "cento", "duzentos", "trezentos", "quatrocentos", "quinhentos", "seiscentos", "setecentos", "oitocentos", "novecentos"},
	};
	
	//printf("palavra x = %d\n", *x);
	while(X / 10){
		pivo++;
		X /= 10;
	}
	
	//printf("pivo = %d\n", pivo);
	
	switch (pivo){
		case 1:
			if(nextToken(*x))
			conjuncao = "e ";
			if(*x / 10 == 1)
				X = *x % 10;
			else
				pivo++;
			break;
		case 2:
			pivo++;
			if(nextToken(*x))
				conjuncao = "e ";
			printf("teste %d %d\npalavra %d, %d\n",  (*x)/100, (*x)%100, pivo, X);
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
			grandeza = "mil ";
			//a = (*x % 1000)/100;
			//b = (*x)%100;
			//printf("nt: %d\nnt/100: %d\nnt%%100: %d\n", nextToken(*x), a, b);
			if(nextToken(*x))
				if((((*x % 1000)/100) && !((*x)%100)) || (!((*x % 1000)/100) && (*x)%100))
					conjuncao = "e ";
			break;
	}		
	
	//printf("get numero(%d)(%d)\n", pivo, X);
	
	palavra = (char *) malloc(2+strlen(numero[pivo][X]));
	strcpy(palavra, numero[pivo][X]);
	strcat(palavra, " ");
	
	//printf("palavra resp: %s\n", palavra);
	//printf("gdz = %d\n", og);
	resp = (char *) malloc(1+strlen(palavra)+strlen(grandeza)+strlen(conjuncao));
	strcat(resp, palavra);strcat(resp, grandeza);strcat(resp, conjuncao); 
	
	//printf("palavra returns: %s\n", resp);
	
	return resp;	
}

char *leitura(int x){
	char *anterior = "";
	char *obtida = "";
	char *resp = "";
	do{
	//	printf("leitura x=%d\n", x);
		anterior = malloc(1+strlen(resp));
		strcat(anterior, resp);
		obtida = palavra(&x);
	//	printf("get palavra(%d) -> %s\n", x, obtida);
		resp = (char *) malloc(1+strlen(anterior)+strlen(obtida));
		strcat(resp, anterior);
		strcat(resp, obtida);
		x = nextToken(x);
		printf("resp = %s\n", resp);
	} while(x);
	return resp;
}

int main (int argc, char *argv[]) {
//    FILE *entrada, *saida;
//    /* Declara??o de suas vari?veis */
	
	
//    /* Verifica se numero de argumentos de entrada e' suficiente */
//    if (argc < 3) {
//        printf("Numero de parametros insuficiente:\n\tuse %s arquivo_entrada arquivo_saida\n", argv[0]);
//    }
    /* Abre arquivo de entrada; termina programa em caso de falha */
//    if (!(entrada = fopen(argv[1], "r"))) {
//        printf("Nao foi possivel abir o arquivo %s para leitura. Abortando...\n", argv[1]);
//        return 1;
//    }
    /* Abre arquivo de saida; termina programa em caso de falha */
//    if (!(saida = fopen(argv[2], "w"))) {
//        printf("Nao foi possivel abir o arquivo %s para escrita. Abortando...\n", argv[2]);
//        return 1;
//    }
    /* Seu c?digo */
    /* ... */
	//printf("%s\n", leitura(atoi(++*argv)));
	//printf("argv = %s, argv++ = %s\n", *argv, *(argv+1));
	leitura(atoi(*++argv));
	//printf("%d\n", removePivo(atoi(*++argv)));
    return 0;
}