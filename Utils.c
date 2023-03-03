/*VIRGOLICI LAURA ELENA GR 311CB*/
#include "Utils.h"
#include <strings.h>
#define MAX_TITLE 50
#define MAX_AUTHOR 50


TCarte *parse_and_create_book(char *line)
{
    char *name = strtok(NULL, ":");
    char *autor = strtok(NULL, ":");
    int rating = atoi(strtok(NULL, ":"));
    int numar_pag = atoi(strtok(NULL, ":"));

    //aloc pointerul catre o carte
    TCarte *point_carte = (TCarte *)calloc(1, sizeof(TCarte));

    //alocari pt siruri de caractere
    point_carte->nume = calloc(MAX_TITLE, sizeof(char));
    point_carte->autor = calloc(MAX_AUTHOR, sizeof(char));

    strcpy(point_carte->nume, name);
    strcpy(point_carte->autor, autor);
    point_carte->rating = rating;
    point_carte->numar_de_pagini = numar_pag;

    return point_carte;
}


int pozitie(char c)
{
    char alfabet[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
    int nr = 0;
    for (int i = 0; i < strlen(alfabet); i++)
    {
        if (c == alfabet[i])
            return i;
        else
            nr++;
    }
    return 0;
}

int cmp_names(char *name1, char *name2)
{
    int i = 0;
    while (name1[i] == name2[i])
        i++;

    return  pozitie(name1[i])-pozitie(name2[i]);
}
