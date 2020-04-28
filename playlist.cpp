#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct 
{
	int codigo;
	char nome[50];
} ARTISTA;

typedef struct
{
	char exc;
	char titulo[50];
	int cod_artista;
	char estilo[50];
} MUSICA;

ARTISTA a;
MUSICA music;
FILE *fp, *fp2, *novo;

void cadastroartista ()
{
	ARTISTA b;
	achou = 1;
	fp = fopen("artista.dat", "ab");
	printf ("\n Cadastro do Artista\n\nCodigo -> ");
	scanf ("%d ", &a.codigo);
	while ((fread (&b, sizeof(b), 1, fp))==1)
	{
		if (a.codigo == b.codigo)
		{
			printf ("Codigo ja cadastrado ");
			achou = 0;
		    break;
		}
    }
    
	if (achou)
	{
		printf ("Nome do artista -> ");
	  	gets (a.nome);
    	fwrite (&a, sizeof(a), 1, fp);
    }
	fclose(fp);
}

void listarartista ()
{	
	if ((fp = fopen("artista.dat", "rb")) == NULL )
    puts ("Artista nao cadastrado ");
	else
	{
		while ((fread(&a, sizeof(a), 1, &fp)) == 1)
		{
			printf ("Artista........ %s \n", a.nome);
			printf ("Artista........ %d \n ", a.codigo);
	    }
	}
	fclose(fp);
}

void consultaartista ()
{
	achou = 0;
	ARTISTA c;
	puts ("Nome do artista -> ");
	fflush(stdin);
	gets (a.nome);
	if ((fp = fopen ("artista.dat", "rb")) == NULL)
	puts ("Artista nao encontrado ");
	else
	{
		while ((fread(&a, sizeof(ARTISTA), 1, &fp))==1)
		{
			if (strcmp (a.nome, c.nome == 0))
			{
				strcpy(a.nome, c.nome);
				c.codigo = a.codigo;
				achou = 1;
				break;
			}		
		}
	}
	fclose(fp);
}

void alterarArtista (char *titulo)
{
	long int pos;
	int achou = 0 ;
	char resp;
	
	fp = fopen ("artista.dat", "rb+");
	while (fread (&a, sizeof(ARTISTA), 1, fp) == 1)
	{
		if (strcmp (titulo, a.nome) == 0)
		{
			achou = 1;
			break;
		}
	}
	if (achou)
	{
		printf ("Titulo...... %s\n ", a.nome);
		printf ("Deseja alterar? s para sim ou n para nao ");
		fflush (stdin);
		resp = getchar();
		if (resp == 's')
		{
			pos = ftell(fp);
			pos -= sizeof (ARTISTA);
			fseek (fp, pos, SEEK_SET);
			char novonome[50];
			printf ("Digite o novo artista ");
			fflush (stdin);
			gets (a.nome);
			fwrite (&a, sizeof(ARTISTA), 1, fp);
		}	
	fclose(fp);	
	}
}

void cadastroMusica()
{
	MUSICA c;
	fp2 = fopen("Musicas.dat", "ab+");	
	printf("\n\t\t*CADASTRANDO MUSICA*\n\nCodigo do Artista -> ");
	fflush(stdin);
	scanf("%d", &music.cod_artista);
	while((fread(&a, sizeof(a), 1, fp))==1)
	{
		if(a.codigo == music.cod_artista)
		{
			printf("\n\t\t*CADASTRANDO MUSICA*\n\nArtista -> %s\n", a.nome);
			printf("Estilo -> ");
			fflush(stdin);
			gets(music.estilo);
			printf("Titulo -> ");
			fflush(stdin);
			gets(music.titulo);
			fflush(stdin);
			while((fread(&c, sizeof(c), 1, fp2))==1)
			{
				if((strcmp(c.titulo, music.titulo))==0) 
				{
					printf("Musica com este titulo ja cadastrada!");
					fflush(stdin);
				}
			}
		}
	}
	fclose(fp2);	
}

void listarMusica ()
{	
	if ((fp = fopen("Musicas.dat", "rb")) == NULL )
    puts ("Musica nao cadastrada ");
	else
	{
		while ((fread(&music, sizeof(music), 1, &fp2)) == 1)
		{
			printf ("Musica........ %s \n", music.titulo);
			printf ("Musica........ %s \n ", music.estilo);
	    }
	}
	fclose(fp2);
}
void remover(char *musica)
{
	long int pos;
	int achou = 0 ;
	char resp;
	
	fp = fopen ("Musicas.dat", "rb+");
	while (fread (&music, sizeof(music), 1, fp2) == 1)
	{
		if (strcmp (musica, music.titulo) == 0)
		{
			achou = 1;
			break;
		}
	}
	if (achou)
	{
		printf ("Musica...... %s\n ", music.titulo);
		printf ("Deseja remover a musica ? s para sim ou n para nao ");
		fflush (stdin);
		resp = getchar();
		if (resp == 's')
		{
			pos = ftell(fp2);
			pos -= sizeof (music);
			fseek (fp2, pos, SEEK_SET);
			music.exc = '*';
			fwrite (&music, sizeof(music), 1, fp2);
		}	
	fclose(fp2);	
	}
}

void buscarMusica(char *p)
{
	char nome[50], resp;
	int achou=0;
	do
	{
		printf("\n\t\tCADASTRANDO MUSICAS NA PLAYLIST\n\nDigite o titulo da musica -> ");		
		fflush(stdin);
		gets(nome);
		if((fp = fopen("artista.dat", "rb"))==NULL || (fp2 = fopen("Musicas.dat", "rb"))==NULL)
		printf("\nErro ao abrir o arquivo!");
		else
		{
			novo = fopen(p, "a");
			while((fread(&music, sizeof(music), 1, fp2))==1)
			{
				if(((strcmp(nome, music.titulo))==0) && (music.exc!='*'))
				{
					achou=1;
					while((fread(&a, sizeof(a), 1, fp))==1)
					{
						if(music.cod_artista==a.codigo)
						{
							printf("\n\t\t*MUSICA ENCONTRADA*\n\nNome do artista -> %s\nEstilo -> %s\nTitulo -> %s\n\n", a.nome, music.estilo, music.titulo);
							fprintf(novo, "Nome do artista -> %s\tTitulo da musica -> %s\n", a.nome, music.titulo);
							fflush(stdin);
							printf("\nDeseja encerrar a playlist? (S ou N) -> ");
							fflush(stdin);
							scanf("%c", &resp);
							resp = toupper(resp);
						}
					}
				}
			}
			if(!achou)
			{
			printf("\nMusica nao cadastrada!");
			printf("\nDeseja encerrar a playlist? (S ou N) -> ");
			fflush(stdin);
			scanf("%c", &resp);
			resp = toupper(resp);
			}
		}
	fclose(fp);
	fclose(fp2);
	fclose(novo);
	}while(resp!='S');
}

void buscarArtista(char *p)
{
	int achou=0;
	char nome[50];
	printf("\n\t\tCADASTRANDO PLAYLIST POR ARTISTA\n\nNome do artista -> ");
	fflush(stdin);
	gets(nome);
	if((fp = fopen("artista.dat", "rb"))==NULL || (fp2 = fopen("Musicas.dat", "rb"))==NULL)
	printf("Erro ao abrir o arquivo!");
	else
	{
		novo = fopen(p, "w");
		while((fread(&a, sizeof(a), 1, fp))==1)
		{
			if((strcmp(nome, a.nome))==0)
			{
				achou=1;
				while((fread(&music, sizeof(music), 1, fp2))==1)
				{
					if(a.codigo == music.cod_artista)
					fprintf(novo, "Nome do artista -> %s\tTitulo da musica -> %s\n", a.nome, music.titulo);
				}
			}
		}
		if(!achou)
			printf("Não foi encontrado registro desse artista!");
		else
		printf("\nPlaylist criada com sucesso!");
		
		fclose(fp);
		fclose(fp2);
		fclose(novo);
}

void verPlaylist(*p)
{
	char letra;
	if((novo = fopen(p, "r"))==NULL)
	{
		printf("Erro ao abrir o arquivo!");
		fflush(stdin);
		getch();
	}
	else
	{
		printf("\n\t\tPLAYLIST %s\n\n", p);
		while((letra=fgetc(novo))!=EOF)
		printf("%c", letra);
		fflush(stdin);
		getch();
		fclose(fp);
	}
}

main()
{
	int resp, resp2;
	char p[30];
	do
	{
		printf("\n\t\t*PLAYLIST*\n\n 1 - Artista\n2 - Musica\n 3 - Playlist\n 4 - Sair\n Resposta -> ");
		scanf("%d", &resp);
		switch(resp)
		{
			case 1:
			system("cls");
			printf("\n\t\tARTISTA\n\n 1 - Cadastrar artista\n 2 - Listar artistas\n 3 - Consultar por nome\n 4 - Alterar nome do artista\n 5 - Voltar\nResposta -> ");
			scanf("%d", &resp2);
			switch(resp2)
			{
				case 1:
				cadastroartista();
				break;
				case 2:
				listarartista();
				break;
				case 3:
				consultaartista();
				break;
				case 4:
				alterarArtista();
				break;
				case 5:
				break;
			}
			break;
			case 2:
			printf("\n\t\t*MUSICA*\n\n 1 - Cadastrar musica\n 2 - Listar musicas\n 3 - Consultar por nome\n 4 - Remover musica\n 5 - Voltar\nResposta -> ");
			scanf("%d", &resp2);
			switch(resp2)
			{
				case 1:
				cadastroMusica();
				break;
				case 2:
				listarMusica();
				break;
				case 3:
				consultaMusica();
				break;
				case 4:
				remover();
				break
			}
			break;
			case 3:
			printf("\n\t\tPLAYLIST\n\n1 - Escolher musicas\n 2 - Escolher artista\n 3 - Ver playlist\n 4 - Voltar\nResposta -> ");
			scanf("%d", &resp2);
			switch(resp2)
			{
				case 1:
				printf("\nDigite o nome da playlist a ser criada -> ");
				fflush(stdin);
				gets(p);
				buscarMusica(p);
				break;
				case 2:
				printf("\nDigite o nome da playlist a ser criada -> ");
				fflush(stdin);
				gets(p);
				buscarArtista(p);
				break;
				case 3:
				printf("\nDigite o nome da playlist que deseja abrir -> ");
				fflush(stdin);
				gets(p);
				verPlaylist(p);
				break;
				case 4:
				break;
			}
		break;	
		}
	}while(resp!=4);
}


