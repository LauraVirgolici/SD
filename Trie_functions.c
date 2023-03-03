/*VIRGOLICI LAURA ELENA GR 311CB*/
#include "Utils.h"
#include "Trie_functions.h"
#include <strings.h>
#define MAX_TITLE 50
#define ALPHABET_SIZE 73

Trie Init_Trie()
{
    Trie root = (Trie)calloc(1, sizeof(TNod));

    root->first = NULL;
    root->right = NULL;
    root->point_carte = NULL;
    root->isword = 0;
    root->afisat=0;

    return root;
}


TNod *Create_nod(char c)
{
    TNod *nod = (TNod *)calloc(1, sizeof(TNod));

    nod->first = NULL;
    nod->right = NULL;
    nod->point_carte = NULL;
    nod->isword = 0;
    nod->c = c;

    return nod;
}

/*pt search*/
int check_if_found(TNod *p, char *name, char *word)
{
    if (strcmp(word, name) == 0 && p->isword == 1) // daca s-a terminat numele si este considerat nume valid
        return 1;
    else
        return 0;
}

/*pt add*/
int check_if_done(TNod *p, void *info, char *word, char *name_to_add)
{
    if (strcmp(word, name_to_add) == 0)
    {
        p->point_carte = info;
        p->isword = 1;
        return 1;
    }
    else
        return 0;
}

TNod *cauta_dreapta(TNod *p, char caracter, int *gasit)
{
    *gasit = 0;
    if (p->right == NULL)
        return NULL;

    while (p->right && p->c != caracter)
        p = p->right;

    if (p->c == caracter)
    {
        *gasit = 1;
        return p; // va fi pointer spre caracter
    }
    else
    {
        *gasit = 0;
        return p; // pointer catre sfarsit
    }
}


int Add_to_Trie_generic(char *name_to_add, Trie root, void *info)
{
    TNod *p = root;
    TNod *p_dreapta = root;
    int done = 0, i = 0;
    char *word = calloc(MAX_TITLE, sizeof(char));

    while (done == 0)
    {
        int gasit = 0;
        if (p->first == NULL)
        {
            p->first = Create_nod(name_to_add[i]);
            strncat(word, &name_to_add[i], 1);
            p = p->first;
            i++;
            done = check_if_done(p, info, word, name_to_add);
            continue;
        }

        if (p->first->c == name_to_add[i]) // merg pe caracterul care exista deja in jos (daca exista)
        {
            strncat(word, &name_to_add[i], 1);
            p = p->first;
            i++;
            done = check_if_done(p, info, word, name_to_add);
            continue;
        }

        p_dreapta = cauta_dreapta(p->first, name_to_add[i], &gasit);

        if (gasit == 1) // merg pe caracterul din dreapta care exista deja in jos (daca exista)
        {
            strncat(word, &name_to_add[i], 1);
            p = p_dreapta; // ma mut pe caracterul respectiv
            i++;
            done = check_if_done(p, info, word, name_to_add);
            continue;
        }

        if (p_dreapta == NULL)
        {
            strncat(word, &name_to_add[i], 1);
            p->first->right = Create_nod(name_to_add[i]);
            p = p->first->right;
            i++;
            done = check_if_done(p, info, word, name_to_add);
            continue;
        }

        if (gasit == 0) // daca sunt la sfarsitul listei
        {
            strncat(word, &name_to_add[i], 1);
            p_dreapta->right = Create_nod(name_to_add[i]);
            p = p_dreapta->right;
            i++;
            done = check_if_done(p, info, word, name_to_add);
            continue;
        }
    }
    return 0;
}



/*flag:pozitionare_pe_prefix
-->pt 1 nu verifica daca este cuvant, returneaza pointer la celula unde se termina prefixul
-->pt 0 returneaza direct pointer catre informatie, daca gaseste 
*/
void *Search_Trie(char *name_to_find, Trie root, int pozitionare_pe_prefix)
{
    TNod *p = root;
    TNod *p_dreapta = root;
    int done = 0, i = 0;
    char *word = calloc(MAX_TITLE, sizeof(char));

    while (done == 0)
    {
        int gasit = 0;

        if (p->first == NULL)
            return NULL;

        if (p->first->c == name_to_find[i]) // merg pe caracterul care exista deja in jos (daca exista)
        {
            strncat(word, &name_to_find[i], 1);
            p = p->first;
            i++;
            done = check_if_found(p, name_to_find, word);

            if (pozitionare_pe_prefix == 1)
            {
                if (strcmp(name_to_find, word) == 0)
                    return p;
            }
            else
            {
                if (done == 1)
                    return p->point_carte;
            }
            continue;
        }

        p_dreapta = cauta_dreapta(p->first, name_to_find[i], &gasit);

        if (gasit == 1) // merg pe caracterul din dreapta care exista deja in jos (daca exista)
        {
            strncat(word, &name_to_find[i], 1);
            p = p_dreapta; // ma mut pe caracterul respectiv
            i++;

            done = check_if_found(p, name_to_find, word);

            if (pozitionare_pe_prefix == 1)
            {
                if (strcmp(name_to_find, word) == 0)
                    return p;
            }
            else
            {
                if (done == 1)
                    return p->point_carte;
            }
            continue;
        }

        if (gasit == 0 || p_dreapta == NULL) // daca sunt la sfarsitul listei sau nu exista lista
            return NULL;
    }
    return 0;
}


/*inserare ordonata intr-o lista*/
void InsLG(TLista *aL, char *ae, TF_cmp f_cmp)
{
    TLista aux = calloc(1, sizeof(TCelula));
    if (!aux)
        return;

    aux->name = calloc(MAX_TITLE, sizeof(char));
    strcpy(aux->name, ae);

    TLista p, ant;

    if (*aL == NULL)
    {
        aux->urm = *aL;
        *aL = aux;
        (*aL)->urm = NULL;
        return;
    }
    else
    {
        for (p = *aL, ant = NULL; p != NULL; ant = p, p = p->urm)
        {
            int cmpValue = f_cmp(p->name, ae);
            if (cmpValue < 0)
                continue;

            if (cmpValue > 0)
            {
                if (ant == NULL)
                {
                    aux->urm = p;
                    *aL = aux;
                    return;
                }
                else
                {
                    aux->urm = p;
                    ant->urm = aux;
                    return;
                }
            }
        }
    }
    ant->urm = aux;
    return;
}

void Afisare(TLista aL, FILE *f_out, int nr_afisari)
{
    for (TLista p = aL; p != NULL && nr_afisari != 0; p = p->urm)
    {
        fprintf(f_out, "%s\n", p->name);
        nr_afisari--;
    }
}


/*cand gaseste un cuvant il insereaza in lista*/
void Scan_tree_authors(Trie root, TLista *lista_carti, TF_cmp functie_cmp)
{
    TNod *p = root;

    if (p->isword == 1 && p->afisat!=1)
    {
        TCarte *carte = (TCarte *)p->point_carte;
        p->afisat=1;
        InsLG(lista_carti, carte->nume, functie_cmp);
    }

    if (p->first != NULL)
    {
        p = p->first;
        Scan_tree_authors(p, lista_carti, functie_cmp);
    }

    while (p->right != NULL)
    {
        p = p->right;
        Scan_tree_authors(p, lista_carti, functie_cmp);
    }

}


int pozitionare_pointer(Trie root, char *name_to_find, TLista *lista, TF_cmp functie_cmp)
{
    TNod *p = Search_Trie(name_to_find, root, 1); // ma pozitionez cu pointerul p unde se termina prefixul

    if(p==NULL)
        return -1; // nu exista
    else 
    Scan_tree_authors(p, lista, functie_cmp); // incep de la pozitia lui p

    return 0;
}

/*reseteaza campul afisat*/
void Reset_afisare(Trie root)
{
    TNod *p = root;

    if (p->isword == 1 )
        p->afisat=0;

    if (p->first != NULL)
    {
        p = p->first;
        Reset_afisare(p);
    }

    while (p->right != NULL)
    {
        p = p->right;
        Reset_afisare(p);
    }

}
