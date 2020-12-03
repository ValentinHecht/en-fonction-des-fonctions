/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Brossard

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/


// Énumération des différents types de lexems existants

typedef enum{
    REEL = 0, OPERATEUR = 1, FONCTION = 2, ABSOLU = 3, 
    ERREUR = 4, FIN = 5, PAR_OUV = 6, PAR_FERM = 7, 
    VARIABLE = 8, BARRE = 9
} typelexem;

// Énumération des différents types d'opérateur existants
typedef enum{
    PLUS = 10, MOINS = 11, FOIS = 12, DIV = 13, PUIS = 14
} typeoperateur;

// Énumération des différents types de fonction existantes
typedef enum{
    ABS = 15, SIN = 16, SQRT = 17, LOG = 18, COS = 19, 
    TAN = 20, EXP = 21, ENTIER = 22, VAL_NEG = 23, SINC = 24
} typefonction;

// Énumération des différentes erreurs possible (coté évaluateur)
typedef enum{
    DIV_ZERO, DOUBLE_OPE, SQRT_NEG, PAR_NONFERM, PAR_NONOUVER, ORTO_FONC, MAJ_FONC, BAR_NONFERME, OPE_PAR, BAR_ABS
}typeerreur;


// Énumération des différents types de valeurs existantes
typedef union{
    float reel;
    typefonction fonction;
    typeoperateur operateur;
    typeerreur erreur;
}typevaleur;


// Énumération des différents types de jetons existants
typedef struct{
    typelexem lexem;
    typevaleur valeur;
} typejeton;

//Structure lexem Node
typedef struct Node{
    typejeton jeton;
    struct Node *pjetonpreced;
    struct Node *pjetonsuiv;
    struct Node *pjetonparent;
    int colonne;
    int couche;
} Node;

//Structure lexem
typedef struct Jeton {
    typelexem lexem;
    float reel;
    typefonction fonction;
    typeoperateur operateur;
    typeerreur erreur;
} Jeton;

typedef Node *Arbre;
