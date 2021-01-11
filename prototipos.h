/* ***********************************************
         prototipos.h
   *********************************************** */

int Anadir_arista(struct nodo_v *ady,int v1,int v2,double c);
int Anadir_arco(struct nodo_v *ady, int v1,int v2,double c);
int Anadir_vertice(struct nodo_v **ady,int v1);

int Eliminar_arco(NODO_V **ady, int v1, int v2 );
int Eliminar_arista(struct nodo_v **ady,int v1,int v2);
int Eliminar_vertice( NODO_V **ADY, int VI);
void Eliminar_todos(NODO_V *p,int v1);
void Eliminar(NODO_L **INICIO,NODO_L *P);

int Existe_arista(NODO_V *ADY, int V1, int V2);
int Existe_arco (NODO_V *ADY, int V1, int V2 );
int Existe_vertice(NODO_V* ADY, int VI);

NODO_V * Buscar_vertice(NODO_V *p, int v);

void Borrar_listas_adyacencia(struct nodo_v **ADY);
void Vaciar_lista(NODO_L **INICIO);
