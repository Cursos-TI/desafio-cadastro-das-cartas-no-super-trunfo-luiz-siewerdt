#include <stdio.h>
#include <string.h>

typedef struct {
  char estado;
  char codigoCarta[4];
  char cidade[256];
  int populacao;
  float area;
  float pib;
  int pontosTuristicos;
} Carta;

void getInput(char *input, int inputSize) {
  if (fgets(input, inputSize, stdin)) {
    size_t strSize = strlen(input);
    if (input[strSize - 1] == '\n' && strSize <= inputSize) {
      input[strSize - 1] = '\0';
    } else {
      int ch;
      while ((ch = getchar()) != '\n' && ch != EOF)
        ;
    }
  }
}

int isCharValid(char *ch, int min, int max, int haveUpercase) {
  int chASCII = (int)*ch;
  if (haveUpercase) {
    return chASCII >= min && chASCII <= max ||
           chASCII >= min + 32 && chASCII <= max + 32;
  } else {
    return chASCII >= min && chASCII <= max;
  }
}

Carta novaCarta(int numero) {
  printf("\n Formulário Carta %i:", numero);
  Carta c;
  int isValidEstado = 0;
  int isValidCodigo = 0;

  do {
    char input[10];
    printf("\n Digite o Estado: ");
    getInput(input, sizeof(input));

    if (isCharValid(input, 65, 72, 1)) {
      isValidEstado = 1;
      c.estado = input[0];
    }
  } while (!isValidEstado);

  do {
    char input[10];
    printf("\n Digite o código: ");
    getInput(input, sizeof(input));

    if (isCharValid(&input[0], 65, 72, 1) && input[1] == '0' &&
        isCharValid(&input[2], 49, 52, 0)) {
      isValidCodigo = 1;
      c.estado = input[0];
    }
  } while (!isValidCodigo);

  printf("\n Digite o nome da cidade: ");
  getInput(c.cidade, sizeof(c.cidade));

  printf("\n Digite o número de população: ");
  scanf("%i", &c.populacao);

  printf("\n Digite a área da cidade (em km²): ");
  scanf("%f", &c.area);

  printf("\n Digite o PIB ");
  scanf("%f", &c.pib);

  printf("\n Digite o número de pontos turísticos: ");
  scanf("%i", &c.pontosTuristicos);

  getchar();

  return c;
}

void exibirCarta(Carta *c, int numeroCarta) {
  printf("\n --- Carta %i --- \n\n", numeroCarta);
  printf("Estado: %c\n", c->estado);
  printf("Codigo da Carta: %s\n", c->codigoCarta);
  printf("Cidade: %s\n", c->cidade);
  printf("População: %d\n", c->populacao);
  printf("Área: %.2f km²\n", c->area);
  printf("PIB: %.2f bilhões\n", c->pib);
  printf("Pontos Turísticos: %d\n", c->pontosTuristicos);
}


int main() {
  Carta carta = novaCarta(1);
  Carta carta2 = novaCarta(2);

  exibirCarta(&carta, 1);
  exibirCarta(&carta2, 2);

  return 0;
}
