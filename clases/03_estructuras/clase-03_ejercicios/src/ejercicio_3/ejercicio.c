#include <stdlib.h>

struct nodo{
	int dato;
	struct nodo *prox;
};
struct lista{
	struct nodo *primero;
};

void borrarUltimo(struct lista *l) {
	// Voy hasta el último y lo borro
	struct nodo** next = &(l->primero);
	struct nodo** prev = next;
	// Me muevo hasta que next es null, i.e llegué al último nodo,
	// el que tengo que borrar
	while(*next) {
		prev = next;
		next = &((*next)->prox);
	}

	// Borro el último nodo
	free(*prev);
	*prev = NULL;
}

void agregarPrimero(struct lista* l, int unInt) {
	// Creo el nuevo nodo
	struct nodo* n = malloc(sizeof(struct nodo));
	n->dato = unInt;
	n -> prox = l->primero;
	l->primero = n;
}