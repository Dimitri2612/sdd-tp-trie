#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct snode Tnode;
typedef Tnode *TTrie;

struct snode {
    char val;  // caractère pour représenter la lettre du noeud
    bool m;  // boléen qui vaut vrai si le caractère du noeud est la dernière lettre d'un mot, false sinon
    TTrie fi;  // pointeur sur un noeud fils
    TTrie fr;  // pointeur sur un noeud frère
};


/* La fonction creer_noeud prend en argument un caractère et renvoie un pointeur sur un noeud qui contient ce caractère. */
TTrie creer_noeud(char carac) {
    TTrie nouveau_noeud = (TTrie)malloc(sizeof(Tnode));
    if (nouveau_noeud != NULL) {
        nouveau_noeud->val = carac;
        nouveau_noeud->m = false;
        nouveau_noeud->fi = NULL;
        nouveau_noeud->fr = NULL;
    }
    return nouveau_noeud;
}


/* La fonction trie_vide initialise un nouveau trie en renvoyant un pointeur null. */
TTrie trie_vide() {
    return NULL;
}


/* La procédure ajout_mot prend en argument un pointeur sur TTrie et une chaîne de caractère pour le mot à ajouter. Elle ajoute le mot dans le trie. */
void ajout_mot(TTrie *ptrie, char mot[]) {

    if (strlen(mot) == 0) {
        printf("Erreur : saisir un mot d'au moins un caractère.\n");
        return;
    }

    char carac = mot[0];  // on s'intéresse à la première lettre du mot

    if (*ptrie == NULL) {
        TTrie nouveau_noeud = creer_noeud(carac);
        *ptrie = nouveau_noeud;
        TTrie courant = *ptrie;
        for (int i = 1; mot[i] != '\0'; i++) {
            courant->fi = creer_noeud(mot[i]);
            courant = courant->fi;
        }
        courant->m = true;
        return;
    }

    while ((*ptrie)->val != carac && (*ptrie)->fr != NULL) {  // parcourir tous les noeuds "frères". Si l'un d'eux à la caractère recherché alors on continue l'ajout dans le fils, sinon on ajoute la caractère dans un nouveau frère
        ptrie = &((*ptrie)->fr);
    }

    if ((*ptrie)->val == carac) {
        if (strlen(mot) == 1) {
            (*ptrie)->m = true;
        } else {
            ajout_mot(&((*ptrie)->fi), mot + 1);  // mot + 1 permet de considérer la chaîne de caractère sans son premier caractère
        }
    } else {
        TTrie nouveau_noeud = creer_noeud(carac);
        (*ptrie)->fr = nouveau_noeud;
        TTrie courant = (*ptrie)->fr;
        for (int i = 1; mot[i] != '\0'; i++) {
            courant->fi = creer_noeud(mot[i]);
            courant = courant->fi;
        }
        courant->m = true;
    }
}


/* La fonction recherche prend en argument un élément TTrie et une chaîne de caractère. Elle renvoie le boléen true si le mot se trouve bien dans le trie, false sinon. */
bool recherche(TTrie trie, char mot[]) {

    if (trie == NULL) {
        return false;
    }

    char carac = mot[0];

    while (trie->val != carac && trie->fr != NULL) {
        trie = trie->fr;
    }

    if (trie->val == carac) {
        if (strlen(mot) == 1) {
            return trie->m;
        } else if (trie->fi != NULL) {
            return recherche(trie->fi, mot + 1);
        } else {
            return false;
        }
    } else {
        return false;
    }
}

/* La procédure affichage prend en argument un élément TTrie. Elle permet d'afficher l'ensemble des lettres contenues dans le trie en précisant quand l'une d'elles termmine un mot. */
void affichage(TTrie trie) {
    if (trie != NULL) {
        printf("%c", trie->val);
        if (trie->m) {
            printf(" (mot)\n");
        } else {
            printf("\n");
        }
        affichage(trie->fi);
        affichage(trie->fr);
    }
}


int main() {

    TTrie trie = trie_vide();

    char mot1[] = "la";
    char mot2[] = "ma";
    char mot3[] = "me";
    char mot4[] = "mai";
    char mot5[] = "male";
    char mot6[] = "mat";
    char mot7[] = "mais";
    char mot8[] = "main";
    char mot9[] = "chariot";
    char mot10[] = "mal";
    char mot11[] = "metier";

    ajout_mot(&trie, mot1);
    ajout_mot(&trie, mot2);
    ajout_mot(&trie, mot3);
    ajout_mot(&trie, mot4);
    ajout_mot(&trie, mot5);
    ajout_mot(&trie, mot6);
    ajout_mot(&trie, mot7);
    ajout_mot(&trie, mot8);

    printf("Affichage du trie :\n");
    affichage(trie);

    printf("\nRésultats de recherche :\n");
    printf("Mot \"%s\" présent dans le trie : %s\n", mot1, recherche(trie, mot1) ? "oui" : "non");  // résultat attendu : oui
    printf("Mot \"%s\" présent dans le trie : %s\n", mot2, recherche(trie, mot2) ? "oui" : "non");  // résultat attendu : oui
    printf("Mot \"%s\" présent dans le trie : %s\n", mot3, recherche(trie, mot3) ? "oui" : "non");  // résultat attendu : oui
    printf("Mot \"%s\" présent dans le trie : %s\n", mot4, recherche(trie, mot4) ? "oui" : "non");  // résultat attendu : oui
    printf("Mot \"%s\" présent dans le trie : %s\n", mot5, recherche(trie, mot5) ? "oui" : "non");  // résultat attendu : oui
    printf("Mot \"%s\" présent dans le trie : %s\n", mot6, recherche(trie, mot6) ? "oui" : "non");  // résultat attendu : oui
    printf("Mot \"%s\" présent dans le trie : %s\n", mot7, recherche(trie, mot7) ? "oui" : "non");  // résultat attendu : oui
    printf("Mot \"%s\" présent dans le trie : %s\n", mot8, recherche(trie, mot8) ? "oui" : "non");  // résultat attendu : oui
    printf("Mot \"%s\" présent dans le trie : %s\n", mot9, recherche(trie, mot9) ? "oui" : "non");  // résultat attendu : non
    printf("Mot \"%s\" présent dans le trie : %s\n", mot10, recherche(trie, mot10) ? "oui" : "non");  // résultat attendu : non
    printf("Mot \"%s\" présent dans le trie : %s\n", mot11, recherche(trie, mot11) ? "oui" : "non");  // résultat attendu : non

    return 0;
}

