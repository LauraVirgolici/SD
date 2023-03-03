/*VIRGOLICI LAURA ELENA GR 311CB*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*STRUCTURA UNEI CARTI*/
typedef struct
{
    char *nume;
    char *autor;
    int rating;
    int numar_de_pagini;
} TCarte;


/*STRUCTURA UNUI NOD DIN TRIE GENERIC*/
typedef struct nod
{
    char c;
    struct nod *first;
    struct nod *right;
    int isword;
    int afisat;
    void *point_carte; // utilizat doar pt capatul caii
} TNod, *Trie;


/*STRUCTURA TRIE.ULUI UNUI AUTOR*/
typedef struct autor
{
    char *name;
    Trie authors_trie;

}Trie_author_ob, *Trie_author;



/*STRUCTURA LISTA CARE TINE DENUMIRI DE CARTI SAU AUTORI */
typedef struct lista
{
    char *name;
    struct lista *urm;

}TCelula, *TLista;


TCarte * parse_and_create_book(char *line);
int pozitie(char c);
int cmp_names(char *name1, char *name2);