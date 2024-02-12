
## Documentação da biblioteca

#### Estruturas úteis

```c
router
```

| Atributos   | Tipo       | Descrição                           |
| :---------- | :--------- | :---------------------------------- |
| `first` | `struct screen` | **Obrigatório**. Aponta para a primeira tela |
| `start` | `ponteiro para método` | Inicia o roteador, desta forma, gerenciando qual opção está sendo selecionada, desenhando |
| `listen` | `ponteiro para método` | Adiciona uma tela a lista |

```c
screen
```

| Atributos   | Tipo       | Descrição                           |
| :---------- | :--------- | :---------------------------------- |
| `id` | `int` | Id automático, auto incremet |
| `optionsQuantity` | `int` | Possuí a quantidade de opções disponíveis na tela|
| `handler` | `addressa` | Armazena a função que gerencia a tela |
| `next` | `struct screen` | Ponteiro para a próxima tela |
| `options` | `char [][]` | Ponteiro para as opções |
| `title` | `char` | Ponteiro para o título da tela |

```c
input
```

| Atributos   | Tipo       | Descrição                           |
| :---------- | :--------- | :---------------------------------- |
| `state` | `int` | Estado, possuí o id da tela que deve ser exibida |
| `position` | `int` | Posição da opção que estara selecionada |

Em construção...
