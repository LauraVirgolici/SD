/*VIRGOLICI LAURA ELENA GR 311CB*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef int (*TF_cmp)(char *, char *);
Trie Init_Trie();
TNod *Create_nod(char c);
int check_if_found(TNod *p, char *name, char *word);
int check_if_done(TNod *p, void *info, char *word, char *name_to_add);

TNod *cauta_dreapta(TNod *p, char caracter, int *gasit);
void *Search_Trie(char *name_to_find, Trie root, int pozitionare_pe_prefix);
int Add_to_Trie_generic(char *name_to_add, Trie root, void *info);
void Print_trie_lexicografic(Trie root, FILE *f_out);
void Scan_tree_authors(Trie root, TLista *lista_carti, TF_cmp functie_cmp);
void Afisare(TLista aL, FILE *f_out, int nr_afisari);
int pozitionare_pointer(Trie root, char *name_to_find, TLista *lista, TF_cmp functie_cmp);
void Reset_afisare(Trie root);