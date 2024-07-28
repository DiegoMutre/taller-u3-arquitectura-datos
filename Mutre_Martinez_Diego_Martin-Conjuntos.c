#include <stdio.h>
#include <stdlib.h>

typedef struct tiponodo
{
  int peso;
  int valor;
  struct tiponodo *s;
  struct tiponodo *a;
} NODO;

typedef struct tipoconjunto
{
  int nelementos;
  NODO *dato;
} Conjunto;

NODO *agregar(NODO *lista, int valor)
{
  NODO *p;

  if (lista != NULL)
  {
    if (lista->valor < valor)
    {
      lista->s = agregar(lista->s, valor);
      lista->peso++;
    }
    else if (lista->valor > valor)
    {
      p = (NODO *)malloc(sizeof(NODO));
      p->s = lista;
      p->a = lista->a;
      if (lista->a != NULL)
      {
        lista->a->s = p;
      }
      p->valor = valor;
      p->peso = lista->peso + 1;
      lista->a = p;
      lista = p;
    }
  }
  else
  {
    p = (NODO *)malloc(sizeof(NODO));
    p->s = NULL;
    p->a = NULL;
    p->valor = valor;
    p->peso = 0;
    lista = p;
  }

  return lista;
}

void agregarElemento(Conjunto *c, int valor)
{
  if (c != NULL)
  {
    c->dato = agregar(c->dato, valor);
    c->nelementos = c->dato->peso + 1;
  }
}

NODO *imprimir(NODO *lista, int modo)
{

  if (lista != NULL)
  {
    if (modo == 0)
      printf("%d ", lista->valor);

    imprimir(lista->s, modo);

    if (modo == 1)
      printf("%d ", lista->valor);
  }

  return lista;
}

void imprimirConjunto(Conjunto *c, int modo)
{
  printf("Conjunto: (%d) [ ", c->nelementos);
  imprimir(c->dato, modo);
  printf("]\n");
}

NODO *eliminar(NODO *lista, int valor)
{
  NODO *p;

  if (lista != NULL)
  {
    if (lista->valor == valor)
    {
      p = lista->s;
      if (p != NULL)
      {
        p->a = lista->a;
      }
      free(lista);
      lista = p;
    }
    else
    {
      lista->s = eliminar(lista->s, valor);
      if (lista->s != NULL)
      {
        lista->peso = lista->s->peso + 1;
      }
      else
      {
        lista->peso = 0;
      }
    }
  }

  return lista;
}

Conjunto *eliminarElemento(Conjunto *c, int valor)
{
  if (c != NULL)
  {
    if (c->dato != NULL)
    {
      c->dato = eliminar(c->dato, valor);
      if (c->dato != NULL)
      {
        c->nelementos = c->dato->peso + 1;
      }
      else
      {
        c->nelementos = 0;
      }
    }
  }

  return c;
}

Conjunto *inicializarConjunto()
{
  Conjunto *c = (Conjunto *)malloc(sizeof(Conjunto));
  c->dato = NULL;
  c->nelementos = 0;

  return c;
}

int main()
{
  Conjunto *c = inicializarConjunto();
  int datos[] = {22, 2, 47, 72, 88, 35};

  size_t datos_length = sizeof(datos) / sizeof(datos[0]);

  printf("====================Agregar Elementos al Conjunto====================\n");

  // Agregar los datos al conjunto
  for (int i = 0; i < datos_length; i++)
  {
    printf("Agregar dato: %d\n", datos[i]);
    agregarElemento(c, datos[i]);
    imprimirConjunto(c, 1);
  }

  printf("\n\n====================Eliminar Elementos del Conjunto====================\n");

  // Eliminar los datos del conjunto
  for (int i = 0; i < datos_length; i++)
  {
    printf("Eliminar dato: %d\n", datos[i]);
    eliminarElemento(c, datos[i]);
    imprimirConjunto(c, 1);
  }

  return 0;
}