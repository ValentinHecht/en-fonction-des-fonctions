/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Brossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/

// Énumération des différents types de lexems existants
typedef enum{
    REEL,OPERATEUR,FONCTION,ERREUR,FIN,PAR_OUV,PAR_FERM,VARIABLE,BAR_OUV,BAR_FERM,ABSOLU
} typelexem;

// Énumération des différents types d'opérateur existants
typedef enum{
    PLUS,MOINS,FOIS,DIV,PUIS
} typeoperateur;

// Énumération des différents types de fonction existantes
typedef enum{
    ABS,SIN,SQRT,LOG,COS,TAN,EXP,ENTIER,VAL_NEG
} typefonction;

// Énumération des différentes erreurs possible (coté évaluateur)
typedef enum{
    DIV_ZERO, SQRT_NEG, PAR_NONFERM, PAR_NONOUVER, DOUBLE_OPE, ORTO_FONC, MAJ_FONC, VIRGULE
} typeerreur;

// Énumération des différents types de valeurs existantes
typedef union{
    float reel;
    typefonction fonction;
    typeoperateur operateur;
    typeerreur erreur;
} typejeton;

//Structure lexem
typedef struct Jeton {
    typelexem lexem;
    float reel;
    char var;
    typefonction fonction;
    typeoperateur operateur;
    typeerreur erreur;
} Jeton;

// Énumération des différents types de jetons existants
typedef struct Node{
    typejeton jeton;
    struct Node *pjetonpreced;
    struct Node *pjetonsuiv;
} Node;

typedef Node *Arbre;