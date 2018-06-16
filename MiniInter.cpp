/** 
  * Mini Interpretador de um sistema operacional
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

/**
  * Metodo de criar um diretorio.
  */
void criarDiretorio() {
   
   printf("\nDigite o nome do diretório que será criado: ");
   char nomeDirAux [256];
   scanf("%s", nomeDirAux);
   const char * nomeDir = nomeDirAux;
   int flag = mkdir (nomeDir,0755);
   
   if(flag == 0){
      printf("Foi criada a pasta: %s\n", nomeDirAux);
   }
   else{
      printf("Não foi possivel criar a pasta: %s, pois ", nomeDirAux);
      
      switch(errno) {
         case EACCES:
            printf("o diretório não pode ser gravado aqui, pois não há permisão disponivel!\n");
            break;
         case EEXIST:
            printf("o diretório já existe neste local!\n");
            break;
         case ENOSPC:
            printf("o diretório não pode ser gravado aqui, pois não há espaço em disco!\n");
            break;
         default:
            printf("o diretório tem algum problema!\n");
            break;
      }
   }
}

/**
  * Metodo de deletar um diretorio.
  */
void deletarDiretorio() {
   
   printf("\nDigite o nome do diretório que será deletado: ");
   char nomeDirAux [256];
   scanf("%s", nomeDirAux);
   const char * nomeDir = nomeDirAux;
   int flag = rmdir (nomeDir);
   
   if(flag == 0) {
      printf("Foi deletada a pasta: %s\n", nomeDirAux);
   }
   else{
      printf("Não foi possivel deletar a pasta: %s, pois ", nomeDirAux);
      
      switch(errno) {
         case EACCES:
            printf("não há permisão disponivel!\n");
            break;
         case ENOENT:
            printf("o diretório não existe neste local!\n");
            break;
         case ENOTEMPTY:
            printf("o diretório está com arquivos dentro dele!\n");
            break;
         default:
            printf("o diretório tem algum problema!\n");
            break;
      }
   }
}		

/**
  * Metodo de mudar de diretorio.
  */
void mudarDiretorio() {
   printf("\nDigite o nome do diretório de destino(Caso queira voltar um diretório, escreva \"..\"): ");
   char nomeDirAux [256];
   scanf("%s", nomeDirAux);
   const char * nomeDir = nomeDirAux;
   int flag = chdir (nomeDir);
   
   if(flag == 0) {
      if(strcmp (nomeDirAux,"..") == 0) {
         printf("Você volto uma pasta!\n");
      }
      else{
         printf("Você esta trabalhando na pasta: %s, agora.\n", nomeDirAux);
      }	
   }
   else{
      printf("Não foi possivel entrar na pasta: %s, pois ", nomeDirAux);
      
      switch(errno) {
         case EACCES:
            printf("não há permisão disponivel!\n");
            break;
         case ENOTDIR:
            printf("o arquivo pode até existir,mas não é um diretório!\n");
            break;
         case ENOENT:
            printf("o diretório não existe neste local!\n");
            break;
         default:
            printf("o diretório tem algum problema!\n");
            break;
      }
   }
}
/**
  * Metodo de listar o diretorio.
  */
void listarDiretorio() {
  
   printf("\nArquivos encontrados:\n");
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
      perror ("Não é possivel listar este diretorio.");
  
   printf("\n");
}
/**
  * Metodo de criar um arquivo.
  */
void criarArquivo() {
   printf("\nDigite o nome do arquivo que será criado: ");
   int opcao;
   string linha;
   char nomeArqAux [256];
   scanf("%s", nomeArqAux);
   const char * nomeArq = nomeArqAux;
   mode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH;
   int flag = creat(nomeArq,mode);
   if(flag != -1) {
      printf("Foi criado o arquivo: %s\n", nomeArq);
      printf("Arquivo criado, deseja escrever algo nele?\n1 - Sim.\n2 - Não.\nOpção:");	
      cin >> opcao;
      if(opcao == 1) {
         printf("Digite o que você quiser, para parar digite \"parar\":\n");
         cin >> linha;
         linha += "\n";		
         flag = open(nomeArq,O_CREAT|O_WRONLY,0600);
         while(linha.compare("parar\n") != 0) {
            const char * linhaAux = linha.c_str(); 
            write(flag,linhaAux,linha.length());
            cin >> linha;
            linha += "\n";
         }			
         close(flag);
      }
      else if(opcao != 1){
         printf("Arquivo foi somente criado!\n");
      }
   	
   }
   else{
      printf("Não foi possivel criar o arquivo: %s, pois ", nomeArqAux);
      
      switch(errno) {
         case EACCES:
            printf("não há permisão disponivel!\n");
            break;
         case ENOSPC:
            printf("não há espaço em disco!\n");
            break;
         case EMFILE:
            printf("já tem muito arquivos criados para este processo!\n");
            break;
         case EROFS:
            printf("o arquivo/diretório só tem permissao de ler!\n");
            break;
         default:
            printf("o arquivo tem algum problema!\n");
            break;
      }
   }
}

/**
  * Metodo de deletar um arquivo.
  */
void deletarArquivo() {
	
   printf("\nDigite o nome do arquivo ou link de um arquivo que será deletado: ");
   char nomeArqAux [256];
   scanf("%s", nomeArqAux);
   const char * nomeArq = nomeArqAux;
   int flag = unlink (nomeArq);
   
   if(flag != -1){
      printf("Foi delatado o arquivo/link: %s\n", nomeArqAux);
   }
   else{
      printf("Não foi possivel deletar o arquivo/link: %s, pois ", nomeArqAux);
      
      switch(errno) {
         case EACCES:
            printf("não há permisão disponivel!\n");
            break;
         case EROFS:
            printf("o arquivo/diretório só tem permissao de ler!\n");
            break;
         case ENOENT:
            printf("o arquivo/link não existe neste local!\n");
            break;
         default:
            printf("o arquivo/link tem algum problema!\n");
            break;
      }
   }
}
/**
  * Metodo de criar um link de arquivo.
  */
void criarLinkArquivo() {
   printf("\nDigite o nome do arquivo que será linkado: ");
   char linkArqAux [256];
   char nomeArqAux [256];
   scanf("%s", nomeArqAux);  
   printf("Digite o nome do link do arquivo: ");
   scanf("%s", linkArqAux);
   const char * linkArq = linkArqAux;
   const char * nomeArq = nomeArqAux;
   int flag = symlink (nomeArq,linkArq);
   
   if(flag != -1){
      printf("Foi linkado o arquivo: %s, usado o link: %s\n", nomeArqAux,linkArqAux);
   }
   else{
      printf("Não foi possivel criar um link de arquivo: %s, pois", nomeArqAux);
      
      switch(errno) {
         case EACCES:
            printf("não há permisão disponivel!\n");
            break;
         case EROFS:
            printf("nome do link já esta sendo usado!\n");
            break;
         case ENOSPC:
            printf("não há espaço em disco!\n");
            break;
         case EEXIST:
            printf("o nome do link de arquivo já existe!\n");
            break;
         case EMFILE:
            printf("já tem muito links de arquivos criados para este processo!\n");
            break;
         default:
            printf("o link de arquivo tem algum problema!\n");
            break;
      }
   }
}
/**
  * Metodo de mostrar todo o conteudo de um arquivo.
  */
void mostrarArquivo() {
   printf("\nDigite o nome do arquivo que será mostrado: ");
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
   }
   else{
      printf("Não foi possivel mostrar o arquivo: %s, pois ", nomeArqAux);
      
      switch(errno) {
         case EACCES:
            printf("não há permisão disponivel!\n");
            break;
         case ENOENT:
            printf("o arquivo não existe neste local!\n");
            break;
         default:
            printf("o arquivo tem algum problema!\n");
            break;
      }
   }
}
/**
  * Metodo de criar um arquivo temporario.
  */
FILE * criarArqTemp(FILE * file) {
  
   if(file == NULL) {
      printf("\nCriando arquivo temporario!\n");
      file = tmpfile();
      
      if(file != NULL) {
         printf("Foi criado um arquivo temporario.\n");
      }
      else{
         printf("Error ao criar arquivo temporario.\n");
      }
   }
   else{
      printf("Arquivo temporario já foi criando antes, deseja exclui-lo?\n1 - Sim.\n2 - Nao\nOpcao: ");
      int opcao;
      cin >> opcao;
      if(opcao == 1) {
         fclose(file);
         file = NULL;
         printf("Arquivo temporario excluido!\n");
      }
   }
   return file;
}
/**
  * Metodo main.
  */
int main() {
   
   FILE * file = NULL;
   int flag = -1;
   int opcao;
   printf("----TRABALHO DE SISTEMA OPERACIONAIS----\nMini interpretador de comandos em C++\nAbaixo estão todos os comandos:\n");
   printf("\nPrograma possui as seguintes opções:");
   printf("\n 1 - Criar e apagar um diretório;");
   printf("\n 2 - Mudar de diretório;");
   printf("\n 3 - Listar o conteúdo de um diretório;");
   printf("\n 4 - Criar e a apagar arquivos;");
   printf("\n 5 - Criar e apagar links para arquivos;");
   printf("\n 6 - Ler e mostrar conteúdo de arquivos texto;");
   printf("\n 7 - Criar arquivos texto temporários, que serão apagados ao fim da execução;");
   printf("\n 8 - Mostrar todas as opções do programa.\n");
   do{
      printf("\nEscolha a opção que desejar:");
      cin >> flag;
      switch(flag) {
         case 0:
            printf("\nPrograma está encerrando...\n");
            break;
         case 1:
            printf("\nVocê escolheu a opção 1 - Criar um diretório.");
            printf("\n1 - Deseja criar um diretório;");
            printf("\n2 - Deseja apagar um diretório(Ele precisa está vazio!!!).");
            printf("\nOpção:");
            cin >> opcao;
            if( opcao == 1 ) {
               criarDiretorio();
            }
            else if ( opcao == 2 ){
               deletarDiretorio();
            }
            break;
         case 2:
            printf("\nVocê escolheu a opção 2 - Mudar de diretório.");
            mudarDiretorio();
            break;
         case 3:
            printf("\nVocê escolheu a opção 3 - Listar o conteúdo de um diretório.");
            listarDiretorio();
            break;
         case 4:
            printf("\nVocê escolheu a opção 4 - Criar e a pagar arquivos.\nEscolha a opção:");
            printf("\n1 - Deseja criar um arquivo;");
            printf("\n2 - Deseja apagar um arquivo.");
            printf("\nOpção:");
            cin >> opcao;
            if( opcao == 1 ) {
               criarArquivo();
            }
            else if( opcao == 2 ){
               deletarArquivo();
            }
            break;
         case 5:
            printf("\nVocê escolheu a opção 5 - Criar e apagar links para arquivos.");
            printf("\n1 - Deseja criar um link para arquivo;");
            printf("\n2 - Deseja apagar um link para arquivo.");
            printf("\nOpção:");
            cin >> opcao;
            if( opcao == 1 ) {
               criarLinkArquivo();
            }
            else if( opcao == 2 ){
               deletarArquivo();
            }           
            break;
         case 6:
            printf("\nVocê escolheu a opção 6 - Ler e mostrar conteúdo de arquivos texto.");
            mostrarArquivo();
            break;
         case 7:
            printf("\nVocê escolheu a opção 7 - Criar arquivos texto temporários.");
            file = criarArqTemp(file);
            break;
         case 8:
            printf("\nPrograma possui as seguintes opções:");
            printf("\n 1 - Criar e apagar um diretório;");
            printf("\n 2 - Mudar de diretório;");
            printf("\n 3 - Listar o conteúdo de um diretório;");
            printf("\n 4 - Criar e a apagar arquivos;");
            printf("\n 5 - Criar e apagar links para arquivos;");
            printf("\n 6 - Ler e mostrar conteúdo de arquivos texto;");
            printf("\n 7 - Criar arquivos texto temporários, que serão apagados ao fim da execução.");
            printf("\n 8 - Mostrar todas as opções do programa.\n");
            break;
         default:
            printf("Opção não existe.");  
            break;
      
      }
   }while(flag != 0);

   return 0;
}
