/** 
  * Mini Inter de um sistema operaciona
  * @actor Paulo Junio 
  * @actor Joao Paulo 
  * Professor Caram
  */
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

using namespace std;

void criarDiretorio() {
   
   printf("\n\nDigite o nome do diretório: ");
   char nomeDirAux [256];
   scanf("%s", nomeDirAux);
   const char * nomeDir = nomeDirAux;
   int flag = mkdir (nomeDir,0755);
   
   if(flag == 0){
		printf("\nFoi criada a pasta: %s\n", nomeDirAux);
   }else{
		printf("\nNão foi possivel criar a pasta: %s, pois ", nomeDirAux);
      
      switch(errno) {
         case EACCES:
            printf("o diretório não pode ser gravado aqui, pois não permisão disponivel!");
            break;
         case EEXIST:
            printf("o diretório já existe neste local!");
            break;
         case ENOSPC:
            printf("o diretório não pode ser gravado aqui, pois não há espaço em disco!");
            break;
         default:
            printf(" o diretório tem algum problema!");
            break;
      }
   }
}

void deletarDiretorio() {
   
   printf("\n\nDigite o nome do diretório: ");
   char nomeDirAux [256];
   scanf("%s", nomeDirAux);
   const char * nomeDir = nomeDirAux;
   int flag = rmdir (nomeDir);
   
   if(flag == 0) {
		printf("\nFoi deletada a pasta: %s\n", nomeDirAux);
	}else{
		printf("\nNão foi possivel deletar a pasta: %s\n", nomeDirAux);
	}
}		

void mudarDiretorio() {
   printf("\n\nDigite o nome do diretório de destino: ");
	char nomeDirAux[256];
   scanf("%s", nomeDirAux);
   const char * nomeDir = nomeDirAux;
   int flag = chdir (nomeDir);
   
   if(flag == 0) {
		printf("\nFoi desta trabalhando na pasta: %s, agora.\n", nomeDirAux);
	}else{
		printf("\nNão foi possivel entrar na pasta: %s, pois\n", nomeDirAux);
	}
}
void listarDiretorio() {
  
  printf("\n\nArquivos encontrados:\n");
  DIR *dp;
  struct dirent *ep;

  printf("\n");
  dp = opendir ("./");
  if (dp != NULL)
    {
      while (ep = readdir (dp))
        puts (ep->d_name);
      (void) closedir (dp);
    }
  else
    perror ("\nNão é possivel listar este diretorio.");
  
  printf("\n");
}
void criarArquivo() {
   printf("\n\nDigite o nome do arquivo que será criado: ");
   int opcao;
   string linha;
   char nomeArqAux [256];
   scanf("%s", nomeArqAux);
   const char * nomeArq = nomeArqAux;
   mode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH;
   int flag = creat (nomeArq,mode);
   if(flag > 0) {
		printf("\nFoi criado o arquivo: %s\n", nomeArq);
		printf("Arquivo criado, deseja escrever algo nele?\n1 - Sim.\n2 - Não.\nOpção:");	
		cin >> opcao;
		if(opcao == 1) {
			printf("\nDigite o que você quiser, para parar digite \"parar\":\n");
			cin >> linha;
         linha += "\n";		
			flag = open(nomeArq,O_CREAT|O_WRONLY,0600);
			while(linha.compare("parar\n") != 0) {
            const char * linhaAux = linha.c_str(); 
            write(flag,linhaAux,linha.length());
				cin >> linha;
            linha += "\n";
			}			
		}else if(opcao != 1){
			printf("\nArquivo foi somente criado!\n");
		}
		
   }else{
		printf("Não foi possivel criar o arquivo: %s\n", nomeArqAux);
   }
}
void deletarArquivo() {
	
   printf("\n\nDigite o nome do arquivo que será deletado: ");
   char nomeArqAux [256];
   scanf("%s", nomeArqAux);
   const char * nomeArq = nomeArqAux;
   int flag = unlink (nomeArq);
   
   if(flag != -1){
		printf("\nFoi delatado o arquivo: %s\n", nomeArqAux);
   }else{
		printf("\nNão foi possivel deletar o arquivo: %s\n", nomeArqAux);
   }
}
void criarLinkArquivo() {

}
void deletarLinkArquivo() {

}
void mostrarArquivo() {
   printf("\n\nDigite o nome do arquivo que será mostrado: ");
   char nomeArqAux [256];
   scanf("%s", nomeArqAux);
   const char * nomeArq = nomeArqAux;
   int flag = open (nomeArq, O_RDONLY);
   char * linha = (char*) calloc(1000,sizeof(char));
   if(flag != -1){
      printf("Mostrando o que foi encontrado no arquivo:\n");
		while(read (flag, linha,1000) > 0) {
         printf("%s",linha);    
		}
		close(flag);
   }else{
		printf("\nNão foi possivel deletar o arquivo: %s\n", nomeArqAux);
   }
}
void criarArqTemp() {
  char buffer [256] = "teste";
  FILE * tmp;
  tmp = tmpfile();
  
  if(tmp == NULL) {
    printf("Arquivo não criado, ative a permissão");
  }else{
    
    printf("\nArquivo temporario criado\n");
    do {
      //printf("aa");
      if (!fgets(buffer,256,stdin)) 
         break;
       //printf("aa");
       fputs ("BALEIA",tmp);
    } while (strlen(buffer) > 1);
   
    rewind(tmp);
   
    while (!feof(tmp)) {
      if (fgets (buffer,256,tmp) == NULL) break;
      fputs (buffer,stdout);
    }
   
	//fclose(tmp);
  }
}
int main() {
   
   int flag = -1;
   int opcao;
   printf("--TRABALHO DE SISTEMA OPERACIONAIS--\nMini interpretador de comandos em C++\nAbaixo esta todos os comandos:\n");
   /*printf("\n 1- Criar um diretório");
   printf("\n 2- Mudar de diretório");
   printf("\n 3- Listar o conteúdo de um diretório");
   printf("\n 4- Criar e a pagar arquivos");
   printf("\n 5- Criar e apagar links para arquivos");
   printf("\n 6- Ler e mostrar conteúdo de arquivos texto");
   printf("\n 7- Criar arquivos texto temporários, que serão apagados ao fim da execução");*/
   
   do{
      printf("\nEscolha uma das opções:");
      printf("\n 1- Criar e apagar um diretório;");
      printf("\n 2- Mudar de diretório;");
      printf("\n 3- Listar o conteúdo de um diretório;");
      printf("\n 4- Criar e a apagar arquivos;");
      printf("\n 5- Criar e apagar links para arquivos;");
      printf("\n 6- Ler e mostrar conteúdo de arquivos texto;");
      printf("\n 7- Criar arquivos texto temporários, que serão apagados ao fim da execução.");
      printf("\nOpção:");
      cin >> flag;
      switch(flag) {
         case 0:
            printf("Programa está encerrando...\n");
            break;
         case 1:
            printf("Você escolheu a opção 1 - Criar um diretório.");
			printf("\n1 - Deseja criar um diretório;");
            printf("\n2 - Deseja apagar um diretório(Ele precisa está vazio!!!).");
            printf("\nOpção:");
            cin >> opcao;
            if( opcao == 1 ) {
               criarDiretorio();
            }else{
               deletarDiretorio();
            }
            break;
         case 2:
            printf("Você escolheu a opção 2 - Mudar de diretório.");
            mudarDiretorio();
            break;
         case 3:
            printf("Você escolheu a opção 3 - Listar o conteúdo de um diretório.");
            listarDiretorio();
            break;
         case 4:
            printf("Você escolheu a opção 4 - Criar e a pagar arquivos.\nEscolha a opção:");
            printf("\n1 - Deseja criar um arquivo;");
            printf("\n2 - Deseja apagar um arquivo.");
            printf("\nOpção:");
            cin >> opcao;
            if( opcao == 1 ) {
               criarArquivo();
            }else{
               deletarArquivo();
            }
            break;
         case 5:
            printf("Você escolheu a opção 5 - Criar e apagar links para arquivos.");
            printf("\n1 - Deseja criar um link para arquivo;");
            printf("\n2 - Deseja apagar um link para arquivo.");
            printf("\nOpção:");
            cin >> opcao;
            if( opcao == 1 ) {
               criarLinkArquivo();
            }else{
               deletarLinkArquivo();
            }           
            break;
         case 6:
            printf("Você escolheu a opção 6 - Ler e mostrar conteúdo de arquivos texto.");
            mostrarArquivo();
            break;
         case 7:
            printf("Você escolheu a opção 7 - Criar arquivos texto temporários.");
            criarArqTemp();
            break;
         default:
            printf("Opção não existe.");  
            break;
      
      }
   }while(flag != 0);

   return 0;
}
