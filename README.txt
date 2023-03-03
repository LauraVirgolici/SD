Descrierea structurii:

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

Pointerul first indica primul copil al unui nod, adica inceputul listei de copii.
Pointerul right indica fratele unui nod; fratii sunt legati intre ei prin right
iar parintele de copil prin first.

exemplu: Cuvinte(ALEX, DELIA, DENIS, DES)
/0 
|
A------D
|      |
L      E 
|      |
E      L--N--S
|      |  |
X      I  I
       |  |
       A  S
pt root: root->first=A
         root->right==NULL

pt A: A->first= L 
      A->right=D

pt L: L->first=I
      L->right=N

pt N: N->first=I
      N->right= S


functia citire_fisier ->parseaza linie cu linie si apeleaza functiile pt fiecare comanda
Functia add adauga un cuvant pe masura cel primeste.

Pt afisarea ordonata se parcurge trieul pana se gasesc toate celulele care au campul
isword setat 1 iar cuvintele se introduc intr-o lista folosind inserarea ordonata InsLG.


Search are doua functionalitati
pt 1 intoarce celula catre pointeaza(folosit la prefix)
pt 0 intoarce informatia continuta in celula


punctaj 110/135