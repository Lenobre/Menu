#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

struct input
{
  int state;
  int postion;
};

typedef struct input input;

struct screen
{
  int id;
  int optionsQuantity;

  input (*handler)(int index);
  struct screen *next;
  char **options;
  char *title;
};

typedef struct screen screen;

struct router
{
  screen *first;
  int (*start)(struct router *Router, int position);
  int (*listen)(struct router *Router, screen *pageInstance);
};

typedef struct router router;

int idCount = 0;

/// @brief Inicia uma tela
/// @param title Titulo da tela
/// @param options Opcoes disponiveis na tela
/// @param handler Funcao para controlar as acoes
/// @return Retorna uma instância da estrutura "screen"
screen *setupScreen(char title[], char *options[], input (*handler)(int index))
{
  screen *Screen = malloc(sizeof(screen));

  if (Screen != NULL)
  {
    idCount++;

    Screen->id = 0;
    Screen->id = idCount;
    Screen->next = NULL;

    // Alocando espaço para o titulo e movendo uma string para ele
    Screen->title = malloc((strlen(title) + 1) * sizeof(char));

    if (Screen->title != NULL)
    {
      strcpy(Screen->title, title);
    }

    Screen->optionsQuantity = 0;

    // Varre as opções para descobrir quantas existem
    for (int i = 0; options[i] != NULL; i++)
    {
      Screen->optionsQuantity++;
    }

    // Alocando espaço para opções
    Screen->options = malloc(Screen->optionsQuantity * sizeof(char *));

    // Alocando espaço para os textos das opções
    for (int i = 0; i < Screen->optionsQuantity; i++)
    {
      Screen->options[i] = malloc(strlen(options[i]) * sizeof(char));

      if (Screen->options[i] != NULL)
        strcpy(Screen->options[i], options[i]);
    }

    Screen->handler = handler;
  }

  // Devolve a instância
  return Screen;
}

int listen(router *Router, screen *pageInstance)
{
  if (Router == NULL || pageInstance == NULL)
    return 0;

  if (Router->first == NULL && pageInstance != NULL)
  {
    Router->first = pageInstance;
    return 1;
  }

  screen *prevScreen = Router->first;
  while (prevScreen->next != NULL)
  {
    prevScreen = prevScreen->next;
  }

  prevScreen->next = pageInstance;

  return 1;
}

screen *getScreenDetails(router *Router, int id)
{
  if (Router->first != NULL)
  {

    if (Router->first->id == id)
      return Router->first;

    screen *prevScreen = Router->first->next;
    while (prevScreen->next != NULL && prevScreen->next->id != id)
    {
      prevScreen = prevScreen->next;
    }

    return prevScreen;
  }
}

input drawMenu(screen *Screen, input Input)
{
  system("cls");
  printf("%s\n", Screen->title);

  for (int i = 0; i < Screen->optionsQuantity; i++)
  {
    if (i == Input.postion)
    {
      printf("[X] %s \n", Screen->options[i]);
    }
    else
    {
      printf("[ ] %s \n", Screen->options[i]);
    }
  }

  int ch = _getch();

  switch (ch)
  {
  case 72:
    Input.postion = (Input.postion <= Screen->optionsQuantity && (Input.postion - 1 >= 0)) ? Input.postion - 1 : Input.postion;
    break;
  case 80:
    Input.postion = (Input.postion == Screen->optionsQuantity - 1) ? Screen->optionsQuantity - 1 : Input.postion + 1;
    break;
  case 13:
    Input = Screen->handler(Input.postion);
    break;
  }

  return Input;
}

void start(router *Router, int position)
{
  input Input;
  Input.state = 1;
  Input.postion = position;

  while (1)
  {
    Input = drawMenu(getScreenDetails(Router, Input.state), Input);
  }
}

router *initRouter()
{
  router *Router = malloc(sizeof(router));

  if (Router != NULL)
  {
    Router->first = NULL;
    Router->listen = listen;
    Router->start = start;
  }

  return Router;
}
