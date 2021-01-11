/* ***********************************************
         tipos.h
   *********************************************** */


struct nodo_l  //NODO_L
{
    int ID_VERTICE;
    double COSTE;
    struct nodo_l *ENLACE;
};

struct nodo_v  //NODO_V
{
    int ID_VERTICE;
    struct nodo_l *P_LISTA;
    struct nodo_v *ENLACE;
};

typedef struct nodo_v NODO_V;
typedef struct nodo_l NODO_L;
