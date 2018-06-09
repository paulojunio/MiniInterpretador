/** 
  *
  *
  */
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string>

using namespace std;

void criarDiretorio() {
   
   printf("\nDigite o nome do diretório: ");
   char nomeDirAux [256];
   scanf("%s", nomeDirAux);
   const char * nomeDir = nomeDirAux;
   //int flag = mkdir (nomeDir,nomeDir);

}

void mudarDiretorio() {

}
void listarDiretorio() {

}
void criarArquivo() {

}
void deletarArquivo() {

}
void criarLinkArquivo() {

}
void deletarLinkArquivo() {

}
void mostrarArquivo() {

}
void criarArqTemp() {

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
      printf("\n 1- Criar um diretório;");
      printf("\n 2- Mudar de diretório;");
      printf("\n 3- Listar o conteúdo de um diretório;");
      printf("\n 4- Criar e a pagar arquivos;");
      printf("\n 5- Criar e apagar links para arquivos;");
      printf("\n 6- Ler e mostrar conteúdo de arquivos texto;");
      printf("\n 7- Criar arquivos texto temporários, que serão apagados ao fim da execução.");
      printf("\nOpção:");
      cin >> flag;
      switch(flag) {
         case 0:
            printf("Programa está encerrando...");
            break;
         case 1:
            printf("Você escolheu a opção 1 - Criar um diretório.");
            criarDiretorio();
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
