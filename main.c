/*VIRGOLICI LAURA ELENA GR 311CB*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "Utils.h"
#include "Trie_functions.h"
#define MAX_TITLE 50
#define MAX_INT 2147483647

void clean_line(char *line)
{
    int len = 0;
    len = strlen(line);
    if (line[len - 1] == '\n')
    {
        line[len - 1] = '\0';
        if (line[len - 2] == '\r')
            line[len - 2] = '\0';
    }
}

int citestefisier(char *numeFisier_in, char *numeFisier_out)
{
    FILE *f = NULL;
    char *line = calloc(255, sizeof(char));
    size_t len = 0;

    f = fopen(numeFisier_in, "rt");
    if (f == NULL)
        return -1;

    FILE *f_out = fopen(numeFisier_out, "w+");

    Trie Trie_Books = Init_Trie();
    Trie Trie_Authors = Init_Trie();

    while (getline(&line, &len, f) != -1 && line[0] != '\0' && line[0] != '\n')
    {
        char *comanda = strtok(line, " ");
        int comanda_prefix = 0;

        if (strcmp(comanda, "add_book") == 0)
            clean_line(line);

        char *name;
        char *name_book;
        if (strcmp(comanda, "list_author") == 0 || strcmp(comanda, "search_book") == 0)
        {
            name = strtok(NULL, "\r\n");
            if (name[strlen(name) - 1] == '~')
                comanda_prefix = 1;
        }

        int case_full_full = 0;
        int case_pre = 0;
        int case_full_pre = 0;

        if (strcmp(comanda, "search_by_author") == 0)
        {
            name = strtok(NULL, ":");
            name_book = strtok(NULL, "\r\n");

            if (name_book == NULL)
                case_pre = 1;
            else
            {
                if (name_book[strlen(name_book) - 1] == '~')
                    case_full_pre = 1;
                else
                    case_full_full = 1;
            }
        }

        if (strcmp(comanda, "add_book") == 0)
        {
            // adaug cartea in T1
            TCarte *carte = parse_and_create_book(line);
            TCarte *exista = (TCarte *)Search_Trie(carte->nume, Trie_Books, 0);
            if (exista == NULL)
                Add_to_Trie_generic(carte->nume, Trie_Books, carte); // o adaug in trieul de carti

            // pt autor
            Trie_author trieul_autorului = (Trie_author)Search_Trie(carte->autor, Trie_Authors, 0); // va returna trieul de carti al autorului

            if (trieul_autorului == NULL) // inseamna ca trebuie adaugat in T2
            {
                Trie_author new_authors_trie = (Trie_author)calloc(1, sizeof(Trie_author_ob));
                new_authors_trie->authors_trie = Init_Trie();

                new_authors_trie->name = calloc((strlen(carte->autor) + 1), sizeof(char));
                strcpy(new_authors_trie->name, carte->autor); // trieul sau de carti

                Add_to_Trie_generic(carte->nume, new_authors_trie->authors_trie, carte); // adaug noua carte in trieul lui
                Add_to_Trie_generic(carte->autor, Trie_Authors, new_authors_trie);       // adaug numele autorului in trieul de autori
            }
            else                                                                         // eu am deja autorul in T2 deci el deja are trie de carti
                Add_to_Trie_generic(carte->nume, trieul_autorului->authors_trie, carte); // adaug noua carte in trieul lui
        }



        if (strcmp(comanda, "search_book") == 0 && comanda_prefix == 0)
        {
            TCarte *carte = (TCarte *)Search_Trie(name, Trie_Books, 0);

            if (carte == NULL)
                fprintf(f_out, "Cartea %s nu exista in recomandarile tale.\n", name);
            else
                fprintf(f_out, "Informatii recomandare: %s, %s, %d, %d\n", carte->nume, carte->autor, carte->rating, carte->numar_de_pagini);
        }



        if (strcmp(comanda, "list_author") == 0 && comanda_prefix == 0)
        {
            Trie_author trieul_autorului = (Trie_author)Search_Trie(name, Trie_Authors, 0);

            TLista lista_de_carti = NULL;

            if (trieul_autorului == NULL)
                fprintf(f_out, "Autorul %s nu face parte din recomandarile tale.\n", name);
            else
            {
                Scan_tree_authors(trieul_autorului->authors_trie, &lista_de_carti, cmp_names);
                Afisare(lista_de_carti, f_out, MAX_INT);
                Reset_afisare(trieul_autorului->authors_trie);
            }
        }


        if (strcmp(comanda, "list_author") == 0 && comanda_prefix == 1)
        {
            name[strlen(name) - 1] = '\0'; // sterg ~
            TLista lista_de_autori = NULL;
            int exista = pozitionare_pointer(Trie_Authors, name, &lista_de_autori, cmp_names);

            if (exista == -1)
                fprintf(f_out, "Niciun autor gasit.\n");
            else
            {
                Afisare(lista_de_autori, f_out, 3);
                Reset_afisare(Trie_Authors);
            }
        }



        if (strcmp(comanda, "search_by_author") == 0 && case_full_full == 1)
        {
            Trie_author trieul_autorului = (Trie_author)Search_Trie(name, Trie_Authors, 0);

            if (trieul_autorului == NULL)
                fprintf(f_out, "Autorul %s nu face parte din recomandarile tale.\n", name);
            else
            {
                TCarte *carte = (TCarte *)Search_Trie(name_book, trieul_autorului->authors_trie, 0);
                if (carte == NULL)
                    fprintf(f_out, "Cartea %s nu exista in recomandarile tale.\n", name_book);
                else
                    fprintf(f_out, "Informatii recomandare: %s, %s, %d, %d\n", carte->nume, carte->autor, carte->rating, carte->numar_de_pagini);
            }
        }


        if (strcmp(comanda, "search_book") == 0 && comanda_prefix == 1)
        {
            name[strlen(name) - 1] = '\0'; // sterg ~
            TLista lista_carti = NULL;
            int exista = pozitionare_pointer(Trie_Books, name, &lista_carti, cmp_names);

            if (exista == -1)
                fprintf(f_out, "Nicio carte gasita.\n");
            else
            {
                Afisare(lista_carti, f_out, 3);
                Reset_afisare(Trie_Books);
            }
        }


        if (strcmp(comanda, "search_by_author") == 0 && case_full_pre == 1)
        {

            name_book[strlen(name_book) - 1] = '\0';
            Trie_author trieul_autorului = (Trie_author)Search_Trie(name, Trie_Authors, 0);

            if (trieul_autorului == NULL)
                fprintf(f_out, "Autorul %s nu face parte din recomandarile tale.\n", name);
            else
            {
                TLista lista_carti = NULL;
                int exista = pozitionare_pointer(trieul_autorului->authors_trie, name_book, &lista_carti, cmp_names);

                if (exista == -1)
                    fprintf(f_out, "Nicio carte gasita.\n");
                else
                {
                    Afisare(lista_carti, f_out, 3);
                    Reset_afisare(trieul_autorului->authors_trie);
                }
            }
        }

        if (strcmp(comanda, "search_by_author") == 0 && case_pre == 1)
        {
            clean_line(name);
            name[strlen(name) - 1] = '\0'; // sterg ~
            TLista lista_de_autori = NULL;
            int exista = pozitionare_pointer(Trie_Authors, name, &lista_de_autori, cmp_names);

            if (exista == -1)
                fprintf(f_out, "Niciun autor gasit.\n");
            else
            {
                Afisare(lista_de_autori, f_out, 3);
                Reset_afisare(Trie_Authors);
            }
        }
    }

    fclose(f);
    fclose(f_out);

    return 0;
}

int main(int argc, char *argv[])
{
    char *fisier_in = calloc(100, sizeof(char));
    char *fisier_out = calloc(100, sizeof(char));

    strcpy(fisier_in, argv[1]);
    strcpy(fisier_out, argv[2]);
    citestefisier(fisier_in, fisier_out);

    free(fisier_in);
    free(fisier_out);
}