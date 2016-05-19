#include <stdio.h>
#include <stdlib.h>
#include <String.h>

void PegaEmail(FILE *fileR, char linha[], char *email);
int PegaDiasOnline(char linha[]);
int PegaPaginas(char linha[]);
int PegaVBID(char linha[], char *ant);

int main()
{
    FILE *fileR, *fileW;
	fileR = fopen("ufsm2016.txt", "r");
	fileW = fopen("dados.arff", "w");

	char email[60], linha [300], emailAnt[60], antLivro[20] = " ";
	int x = 0, diasOn = 0, nextDiasOn = 0, paginas = 0, nextPages = 0, qtdLivros = 0, nextQtdLivros = 0;

	fprintf(fileW, "@RELATION MinhaBiblioteca \n\n");
	fprintf(fileW, "@ATTRIBUTE email	            CARACTER \n");
	fprintf(fileW, "@ATTRIBUTE diasOnline	        NUMERIC \n");
	fprintf(fileW, "@ATTRIBUTE quantidadePaginas	NUMERIC \n");
	fprintf(fileW, "@ATTRIBUTE diasAcessoLivro	    NUMERIC \n");
	fprintf(fileW, "@ATTRIBUTE numeroLivros	        NUMERIC \n");
	fprintf(fileW, "\n\n");
    fclose(fileW);

    fgets(linha, 300, fileR);

    fgets(linha, 300, fileR);
    PegaEmail(fileR, linha, email);
    strcpy(emailAnt, email);
    diasOn = (int) PegaDiasOnline(linha);
    paginas = (int) PegaPaginas(linha);
    qtdLivros = (int) PegaVBID(linha, antLivro);

	while(! feof(fileR))
	{
	    strcpy(emailAnt, email);
		fgets(linha, 300, fileR);
		PegaEmail(fileR, linha, email);

		if( (strcmp(email, emailAnt) == 0) )
        {
            diasOn = (int) PegaDiasOnline(linha) + diasOn;
            paginas = (int) PegaPaginas(linha) + paginas;
            qtdLivros = (int) PegaVBID(linha, antLivro) + qtdLivros;
        }
        else
        {
            nextDiasOn = (int) PegaDiasOnline(linha);
            nextPages = (int) PegaPaginas(linha);
            nextQtdLivros = (int) PegaVBID(linha, antLivro);
        }

        if( strcmp(email, emailAnt) )
        {
            fileW = fopen("dados.arff", "a");
            //printf("DADOS:  %s, %d, %d, %d, %d \n", emailAnt, diasOn, paginas, 0, qtdLivros);
            fprintf(fileW, "%s, %d, %d, %d, %d", emailAnt, diasOn, paginas, 0, qtdLivros);
            fprintf(fileW, " \n");
            diasOn = nextDiasOn;
            paginas = nextPages;
            qtdLivros = nextQtdLivros;
            fclose(fileW);
        }
	}

	fclose(fileR);
	fclose(fileW);

    return 0;
}

void PegaEmail(FILE *fileR, char linha[], char *email)
{
    int x;
    for(x = 0; x < 60; x++)
    {
        if(linha[x] == '\t')
        {
           email[x] = '\0';
           break;
        }
        else
        {
            email[x] = linha[x];
        }
    }
}

int PegaDiasOnline(char linha[])
{
    int x, acum = 0, n;
    char lin[4];
    for(x = 0; x < 300; x++)
    {
        if(linha[x] == '\t')
            acum++;

        if(acum == 8)
        {
            int y = x + 1, c = 0;
            while(linha[y] != '\t')
            {
               lin[c] = linha[y];
               y++;
               c++;
            }

            lin[c] = '\0';
            n = atoi(lin);
            return n;
        }
    }
}

int PegaPaginas(char linha[])
{
    int x, acum = 0, n;
    char lin[4];
    for(x = 0; x < 300; x++)
    {
        if(linha[x] == '\t')
            acum++;

        if(acum == 9)
        {
            int y = x + 1, c = 0;
            while(linha[y] != '\t')
            {
               lin[c] = linha[y];
               y++;
               c++;
            }

            lin[c] = '\0';
            n = atoi(lin);
            return n;
        }
    }
}

int PegaVBID(char linha[], char *ant)
{
    int x, acum = 0;
    char lin[20] = " ";
    for(x = 0; x < 300; x++)
    {
        if(linha[x] == '\t')
            acum++;

        if(acum == 2)
        {
            int y = x + 1, c = 0;
            while(linha[y] != '\t')
            {
               lin[c] = linha[y];
               y++;
               c++;
            }

            lin[c] = '\0';

            if( strcmp(lin, ant) == 0 )
            {
                strcpy(ant, lin);
                return 0;
                break;
            }
            else
            {
                strcpy(ant, lin);
                return 1;
                break;
            }
        }
    }
}
