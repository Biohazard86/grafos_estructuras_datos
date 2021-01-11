 /* *******************************************************************
 * Programa principal para el ejercicio de grafos, para las personas que
 * han trabajado en el desarrollo colaborativo del sofware 
 * 
 * COMPILAR
 *  gcc ej_grafos_colab_esqueleto.c grafos_colaborativo.o  
 *
 ******************************************************************* */


 /* *******************************************************************
 * 		GRUPO 2
 *	  David Barrios     davidbarrios@usal.es
 *
 *	gcc -no-pie ej_grafos_colab_esqueleto.c grafos_colaborativo.o
 *      ./a.out 
 * 
 *     *Es necesario usar -no-pie por la version de GCC*
 ******************************************************************* */




// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Librerias usadas
#include <stdio.h>
#include <stdlib.h>

//#include "prototipos.h"
#include "tipo.h"

// Definiciones
#ifndef Verdadero
#define Verdadero 1						// TRUE o VERDADERO
#define Falso     0						// FALSE o FALSO
#endif
#define NIGL 6

// Nodo COLA
struct NODO_COLA
{
	int dato;							// dato de tipo entero
	struct NODO_COLA *enlace;			
};typedef struct NODO_COLA nodo_cola;
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//Prototipos usados:
int cola_vacia(nodo_cola *ptro_cola) ;
void encolar(int elemento,nodo_cola **entrada,nodo_cola **salida) ;
int desencolar(int *elemento,nodo_cola **entrada,nodo_cola **salida);
void recorridoAnchura(NODO_V *ady, int v0, int n,char values[][100]);
NODO_V * Buscar_vertice(NODO_V *p, int v); 
int Anadir_arista(struct nodo_v *ady,int v1,int v2,double c);
int Anadir_vertice(struct nodo_v **ady,int v1);
int Eliminar_arista(struct nodo_v **ady,int v1,int v2);
int Existe_arista(NODO_V *ADY, int V1, int V2);
int Existe_vertice(NODO_V* ADY, int VI);
void Borrar_listas_adyacencia(struct nodo_v **ADY);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::



//===================================================================================================================================
// Funcion que sirve para presentar el programa. No tiene ninguna utilidad.
void presentacion (){
    // Funcion para presentar el programa.
    printf("\n\t-------------------------------------------");
    printf("\n\t          Grafos colaborativo");
    printf("\n\t   David Barrios davidbarrios@usal.es");
    printf("\n\t-------------------------------------------\n\n\n");
}
//===================================================================================================================================

//===================================================================================================================================
// Este modulo comprueba si la cola esta vacia o no
//recibe el puntero de acceso a la cola
int cola_vacia(nodo_cola *ptro_cola)
{
	if(ptro_cola==NULL)	//comprueba si el puntero es nulo
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//===================================================================================================================================


//===================================================================================================================================
//Funcion para encolar.
void encolar(int elemento,nodo_cola **entrada,nodo_cola **salida)
{
	nodo_cola *nuevo;	//puntero auxiliar
	//nuevo=(nodo_cola *)calloc(1,sizeof(nodo_cola));	
	nuevo=(nodo_cola *)malloc(sizeof(nodo_cola));	
	if(nuevo==NULL)	//si nuevo es nulo
	{
		printf("ERROR. No hay memoria suficiente\n");	//Mensaje de control en el caso de que no haya memoria
	}
	else
	{
		nuevo->dato=elemento;	
		nuevo->enlace=NULL;								// Dejamos el enlace a nulo (NULL)

		if(cola_vacia(*salida)==1)						//Comprobamos si la lista esta vacia
		{
			*salida=nuevo;	
		}
		else
		{
			(*entrada)->enlace=nuevo;					//Insertamos el nuevo elemento
		}
		*entrada=nuevo;									//Apuntamos el puntero de entrada al elemento nuevo
	}
}
//===================================================================================================================================


//===================================================================================================================================
//Funcion para desencolar
int desencolar(int *elemento,nodo_cola **entrada,nodo_cola **salida)
{
	nodo_cola *p;									//Puntero aux

	if(cola_vacia(*entrada)==1)						//Comprobamos si la cola esta vacia
	{
		printf("ERROR. La cola esta vacia\n");		//En caso de estarlo, mostramos el mensaje de ERROR
		return 0;									// Retornamos 0 si esto pasa
	}
	else											//si no
	{
		*elemento=(*salida)->dato;					//se guarda el dato
		p=*salida;					
		*salida=(*salida)->enlace;					//se apunta el puntero de salida al siguiente que deberia salir

		if(*salida==NULL)							//si el puntero de salida es nulo
		{
			*entrada=NULL;	
		}
		free(p);									// Procedemos a liberar la memoria
		return 1;									// Retornamos 1 si ha salido bien
	}
}
//===================================================================================================================================


//===================================================================================================================================
//Funcion recorrido en anchura
void recorridoAnchura(NODO_V *ady, int v0, int n,char values[][100]){
													//Creamos los punteros auxiliares
	NODO_L *p;	
	NODO_V *p_v;	
													//Creamos las variables necesarias
	int v1,v2, elemento;
	//int *visitado = (int*) calloc (n,sizeof(int));	//Con esto indicamos si se visita
	int *visitado = (int*) malloc (sizeof(int));	//Con esto indicamos si se visita
													//Iniciamos la cola
	nodo_cola *entrada;	nodo_cola *salida;	
													//Ponemos los punteros a nulo (NULL)
	entrada=NULL;
	salida=NULL;
													// Encolamos el primer vertice
	encolar(v0,&entrada,&salida);
	visitado[v0]=1;

													//Hacemos esto mientras la cola no este vacia
	while(cola_vacia(entrada)==0)
	{
													// Desencolamos el vertice
		desencolar(&v1,&entrada,&salida);
		printf("%s\t",values[v1]);
		p_v=Buscar_vertice(ady,v1);
													//para todos los vertices con los que tenga enlace
		for(p=p_v->P_LISTA;p!=NULL;p=p->ENLACE)
		{
													//si no se han visitado
			if(visitado[p->ID_VERTICE]==0)
			{
				encolar(p->ID_VERTICE,&entrada,&salida); //encolamos
				visitado[p->ID_VERTICE]=1;
			}
		}
	}
}
//===================================================================================================================================


//===================================================================================================================================
// Funcion MAIN
void main()
{
    // Iglesias / Lugares
	char iglesias[NIGL][100]={ "SAN ILDEFONSO", 
	"SAN JUAN", 
	"CATEDRAL", 
	"SAN VICENTE", 
	"SANTIAGO DEL BURGO", 
	"SAN TORCUATO"
	};

	// Matriz de adyacencia
	int adyacencia[NIGL][NIGL]=
	{
		0,1,1,0,0,0,
		1,0,1,1,1,1,
		1,1,0,1,0,0,
		0,1,1,0,0,1,
		0,1,0,0,0,1,
		0,1,0,1,1,0

	};

	// Matriz de costes
	int costes[NIGL][NIGL]=
	{
		1000,   5,   6,1000,1000,1000,
		   5,1000,  13,   1,   5,   3,
		   6,  13,1000,  15,1000,1000,
		1000,   1,  15,1000,1000,   2,
		1000,   5,1000,1000,1000,   1,
		1000,   3,1000,   2,   1,1000

	};


	//VARIABLES
	int i,j;						//Variables que usamos de contador
	int opcion ;					//Variable que almacena la ipcion elegida por el usuario, de que lugar comenzar
	int arista ;					//Variable para ver si hay aristas
	struct nodo_v *grafo;  			//Grafo entero
	struct nodo_v *p;				//Apuntador aux para borrar


	// =================================================================================================================================================================


															// Funcion para la presentacion del programa
	presentacion();
	// Vamos a seguir el enunciado de la tarea de Studium >>
	/* 1- CREAR EL GRAFO, UTILIZANDO LISTAS DE ADYACENCIA, QUE CORRESPONDE A LOS 
	    DATOS QUE APARECEN MÁS ARRIBA */
	for(i=0;i<NIGL;i++)
	{
		Anadir_vertice(&grafo,i);							//Aniadimos vertice
	}

	for(i=0;i<NIGL;i++)										// Recorremos con un for
	{
		for(j=0;j<NIGL;j++)
		{
			if(adyacencia[i][j])
			{
				Anadir_arista(grafo,i,j,costes[i][j]);		// aniadimos la arista
			}
		}
	}

	/*2- RECORRER EL GRAFO, PARTIENDO DEL VÉRTICE QUE INDIQUE EL USUARIO
	  grupo 1 -> recorrido en profundidad, con el módulo que usa una pila
	  grupo 2 -> recorrido en anchura */

	//Mostramos las opciones
	printf("\n  /// LUGARES  \\\\\\");
	printf("\n  1 SAN IDELFONSO ");
	printf("\n  2 SAN JUAN ");
	printf("\n  3 CATEDRAL ");
	printf("\n  4 SAN VICENTE ");
	printf("\n  5 SANTIAGO DEL BURGO ");
	printf("\n  6 SAN TORCUATO ");
	printf("\nIntroduzca el numero deseado >> ");
	scanf("%d", &opcion) ;								// Leemos la opcion seleccionada

	
	if ((opcion >= 1) && (opcion <= 6))					// Si la opcion es correcta, leemos el grafo en anchura
	{
		printf("\n -> El grafo es recorrido por anchura. \n\n");
		recorridoAnchura(grafo,(opcion-1),NIGL,iglesias);

	}
	else{
		printf("\n\n ERROR. Opcion NO valida\n\t SALIENDO\n\n ");	// Si el usuario introduce un numero no valido
		exit (1);													// Acabamos el programa
	} 

	/* 3- LIBERAR LA MEMORIA QUE OCUPA EL GRAFO */

	//Borrar_listas_adyacencia(&grafo); //  ERROR

	
	for(i=0;i<NIGL;i++)								// Recorremos con el for
	{
		for(j=0;j<NIGL;j++)
		{
			if(adyacencia[i][j])
			{
				Eliminar_arista(&grafo,i,j);		// Eliminamos la arista
			}	
			
		}
	}
	
	for(i=0;i<NIGL;i++)								// Recorremos con el for
	{
		for(j=0;j<NIGL;j++)
		{
			if(Existe_arista(grafo, i, j))
			{
				arista = 1;
			}
		}
	}
	if(arista == 1)
	{
		printf("\n\n\nERROR al eliminar las aristas");			// Si se produce un error al eliminar una arista
	} else
	{
		printf("\n\n\nAristas eliminadas correctamente\n\n");				// Si conseguimos eliminar todas las aristas 
	}
	
	/*	
	for(i=0;i<NIGL;i++)
	{	
		Eliminar_vertice(&grafo,i);		// ERROR AL USAR ESTA FUNCION!!!
	}
	*/
	


	// DESCOMENTANDO ESTAS LINEAS, NOS SALE UN ERROR CON free()!!!
	/*
	while(grafo->ENLACE!=NULL) 
	{
		p=grafo;	
		grafo=grafo->ENLACE;		
		free(p);	//libera la memoria del vertice
	}
	*/

	grafo=NULL;


	for(i=0;i<NIGL;i++)
	{	
		if(Existe_vertice(grafo,i))
		{
			printf("\nError al elimina el vertices %d", i);
		}
	}

}



