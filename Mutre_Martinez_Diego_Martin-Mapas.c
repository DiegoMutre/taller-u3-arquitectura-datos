#include <stdio.h>
#include <stdlib.h>

typedef struct tiponodo
{

  int clave;
  double valor;
  int peso;
  struct tiponodo *s;
  struct tiponodo *a;

} NODO;

typedef struct mapa
{
  int nelementos;
  NODO *dato;
} Mapa;

NODO *agregar(NODO *lista, int clave, double valor)
{
  NODO *p;

  if (lista == NULL)
  {
    p = (NODO *)malloc(sizeof(NODO));
    p->clave = clave;
    p->valor = valor;
    p->peso = 0;
    p->s = NULL;
    p->a = NULL;
    return p;
  }
  else
  {
    if (lista->clave < clave)
    {
      lista->s = agregar(lista->s, clave, valor);
      lista->s->a = lista;
      lista->peso = lista->s->peso + 1;
    }
    else if (lista->clave > clave)
    {
      p = (NODO *)malloc(sizeof(NODO));
      p->clave = clave;
      p->valor = valor;
      p->peso = lista->peso + 1;
      p->s = lista;
      p->a = lista->a;
      lista->a = p;
      lista = p;
    }
    else
    {
      // Clave existente, actualiza el valor
      lista->valor = valor;
    }
  }

  return lista;
}

void agregarElemento(Mapa *m, int clave, double valor)
{
  if (m != NULL)
  {
    m->dato = agregar(m->dato, clave, valor);
    m->nelementos = m->dato->peso + 1;
  }
}

NODO *eliminar(NODO *lista, int clave)
{
  NODO *p;

  if (lista != NULL)
  {
    if (lista->clave == clave)
    {
      p = lista->s;
      free(lista);
      lista = p;
    }
    else
    {
      lista->s = eliminar(lista->s, clave);

      if (lista->s == NULL)
      {
        lista->peso = 0;
      }
      else
      {
        lista->peso = lista->s->peso + 1;
      }
    }
  }

  return lista;
}

Mapa *eliminarElemento(Mapa *m, int clave)
{
  if (m != NULL)
  {
    if (m->dato != NULL)
    {
      m->dato = eliminar(m->dato, clave);

      if (m->dato != NULL)
      {
        m->nelementos = m->dato->peso + 1;
      }
      else
      {
        m->nelementos = 0;
      }
    }
  }

  return m;
}

void imprimirMapa(Mapa *m)
{
  if (m == NULL || m->dato == NULL)
  {
    printf("El mapa está vacío.\n");
    return;
  }

  NODO *p = m->dato;
  printf("Mapa:\n");
  while (p != NULL)
  {
    printf("Clave: %d, Valor: %.1f, Peso: %d\n", p->clave, p->valor, p->peso);
    p = p->s;
  }
}

Mapa *inicializarMapa()
{
  Mapa *m = (Mapa *)malloc(sizeof(Mapa));
  m->nelementos = 0;
  m->dato = NULL;

  return m;
}

int main()
{

  Mapa *m = inicializarMapa();
  int datos_claves[] = {22, 2, 47, 72, 88, 35};
  double datos_valores[] = {1.2, 3.5, 6.5, 8.9, 9.4, 3.7};

  size_t datos_length = sizeof(datos_claves) / sizeof(datos_claves[0]);

  printf("====================Agregar Elementos al Mapa====================\n\n");

  for (int i = 0; i < datos_length; i++)
  {
    printf("Agregar elemento %.1f con clave %d\n", datos_valores[i], datos_claves[i]);
    agregarElemento(m, datos_claves[i], datos_valores[i]);
    imprimirMapa(m);
    printf("\n\n"); // Doble salto de linea para que se vea mejor
  }

  printf("====================Eliminar Elementos del Mapa====================\n\n");

  for (int i = 0; i < datos_length; i++)
  {
    printf("Eliminar elemento con clave: %d\n", datos_claves[i]);
    eliminarElemento(m, datos_claves[i]);
    imprimirMapa(m);
    printf("\n\n");
  }

  return 0;
}