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
  float densidade;
  float pibPerCapita;
  float superPoder;
} Carta;

void getInput(char *input, size_t inputSize) {
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
    printf("\n Digite o código: ");
    getInput(c.codigoCarta, sizeof(c.codigoCarta));
    printf("\n%s", c.codigoCarta);
    if (isCharValid(&c.codigoCarta[0], 65, 72, 1) && c.codigoCarta[1] == '0' &&
        isCharValid(&c.codigoCarta[2], 49, 52, 0)) {
      isValidCodigo = 1;
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

void calcularDensidade(Carta *c) {
  c->densidade = (float)c->populacao / c->area;
}

void calcularPipPerCapita(Carta *c) {
  c->pibPerCapita = c->pib / (float)c->populacao;
}

void exibirCarta(Carta *c, int numeroCarta) {
  printf("\n --- Carta %i --- \n", numeroCarta);
  printf("Estado: %c\n", c->estado);
  printf("Codigo da Carta: %s\n", c->codigoCarta);
  printf("Cidade: %s\n", c->cidade);
  printf("População: %d\n", c->populacao);
  printf("Área: %.2f km²\n", c->area);
  printf("PIB: %.2f bilhões\n", c->pib);
  printf("Pontos Turísticos: %d\n", c->pontosTuristicos);
  printf("Densidade: %.2f habitantes por km²\n", c->densidade);
  printf("PIB per Capita: %.2f\n\n", c->pibPerCapita);
}

void calcularSuperPoder(Carta *c) {
  c->superPoder = (c->populacao + c->area + c->pib + c->pontosTuristicos +
                   c->pibPerCapita) -
                  c->densidade;
}

int compararRetorno(void *value1, void *value2) {
  if (*(int *)value1 > *(int *)value2)
    return 1; // Carta 1 ganha
  if (*(int *)value1 < *(int *)value2)
    return 2; // Carta 2 ganha
  return 3;   // Empate
}

void compararCartas(Carta *c1, Carta *c2) {
  int resultado;

  printf("\n--- Comparação de Cartas ---\n");

  resultado = compararRetorno(&c1->populacao, &c2->populacao);
  printf("População: ");
  if (resultado == 1)
    printf("Carta 1 ganhou!\n");
  else if (resultado == 2)
    printf("Carta 2 ganhou!\n");
  else
    printf("Empate!\n");

  resultado = compararRetorno(&c1->area, &c2->area);
  printf("Área: ");
  if (resultado == 1)
    printf("Carta 1 ganhou!\n");
  else if (resultado == 2)
    printf("Carta 2 ganhou!\n");
  else
    printf("Empate!\n");

  resultado = compararRetorno(&c1->pib, &c2->pib);
  printf("PIB: ");
  if (resultado == 1)
    printf("Carta 1 ganhou!\n");
  else if (resultado == 2)
    printf("Carta 2 ganhou!\n");
  else
    printf("Empate!\n");

  resultado = compararRetorno(&c1->pontosTuristicos, &c2->pontosTuristicos);
  printf("Pontos Turísticos: ");
  if (resultado == 1)
    printf("Carta 1 ganhou!\n");
  else if (resultado == 2)
    printf("Carta 2 ganhou!\n");
  else
    printf("Empate!\n");

  resultado = compararRetorno(&c1->densidade, &c2->densidade);
  printf("Densidade: ");
  if (resultado == 1)
    printf("Carta 1 ganhou!\n");
  else if (resultado == 2)
    printf("Carta 2 ganhou!\n");
  else
    printf("Empate!\n");

  resultado = compararRetorno(&c1->pibPerCapita, &c2->pibPerCapita);
  printf("PIB per capita: ");
  if (resultado == 1)
    printf("Carta 1 ganhou!\n");
  else if (resultado == 2)
    printf("Carta 2 ganhou!\n");
  else
    printf("Empate!\n");

  resultado = compararRetorno(&c1->superPoder, &c2->superPoder);
  printf("Super Poder: ");
  if (resultado == 1)
    printf("Carta 1 ganhou!\n");
  else if (resultado == 2)
    printf("Carta 2 ganhou!\n");
  else
    printf("Empate!\n");
}



int main() {
  Carta carta = novaCarta(1);
  Carta carta2 = novaCarta(2);

  calcularDensidade(&carta);
  calcularDensidade(&carta2);

  calcularPipPerCapita(&carta);
  calcularPipPerCapita(&carta2);

  calcularSuperPoder(&carta);
  calcularSuperPoder(&carta2);

  exibirCarta(&carta, 1);
  exibirCarta(&carta2, 2);

  compararCartas(&carta, &carta2);

  return 0;
}
