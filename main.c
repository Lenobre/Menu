#include <stdio.h>

// Incluindo lib para menu
#include "menu.h"

input homeHandler(int index)
{
  input Out;

  // Se selecionada a opcao do indice 0 da pagina principal, ele entao retorna um input para o gerenciador e telas
  if (index == 0)
  {
    Out.state = 2;   // Id da tela, o id e gerado automaticamente
    Out.postion = 0; // É possível deixar pre-selecionado uma opção, coloque o indice da opcao
    return Out;      // Ao fazer isso oo gerenciador sabera se e necessario desenhar outra tela
  }
  else
  {
    exit(0);
  }
}

input pageHandler(int index)
{
  input Out;

  // Se selecionada a opcao do indice 0 da pagina principal, ele entao retorna um input para o gerenciador e telas
  if (index == 0)
  {
    Out.state = 2;   // Id da tela, o id e gerado automaticamente
    Out.postion = 0; // É possível deixar pre-selecionado uma opção, coloque o indice da opcao
    return Out;
  }
  else
  {
    Out.state = 1;   // Id da tela, o id e gerado automaticamente
    Out.postion = 0; // É possível deixar pre-selecionado uma opção, coloque o indice da opcao
    return Out;
  }
}

int main(void)
{
  // Inicia o roteador, responsavel por chamar as telas
  router *Router = initRouter();

  // Criacao de duas telas, os ids possuem auto incremento
  screen *Home = setupScreen("Pagina principal", (char *[]){"Pagina 1", "Sair", NULL}, homeHandler); // id 1
  screen *PG1 = setupScreen("PG1", (char *[]){"opcao 1", "Voltar", NULL}, pageHandler);              // id 2

  // Adiciona as telas ao roteador
  Router->listen(Router, Home);
  Router->listen(Router, PG1);

  // Inicia o roteador e entra em um loop
  Router->start(Router, 0);

  return 0;
}