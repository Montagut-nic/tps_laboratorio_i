#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this=(LinkedList*)malloc(sizeof(LinkedList));
    if(this!=NULL){
		this->pFirstNode=NULL;
		this->size=0;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int retorno = -1;
    if(this!=NULL){
    	retorno=this->size;
    }
    return retorno;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pNode=NULL;
	int indice=0;
	if(this!=NULL && nodeIndex>=0 && nodeIndex<ll_len(this) )
	{
		pNode=this->pFirstNode;
		for(;indice<ll_len(this);indice++){
			if(indice==nodeIndex){
				break;
			}
			pNode=pNode->pNextNode;
		}
	}
	return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int retorno = -1;
    Node* pNodoNuevo;
    Node* pNodoAnterior;
    if(this!=NULL && nodeIndex>=0 && nodeIndex<=ll_len(this))//si nodeIndex==ll_len enotnces se guarda en el utlimo
    {
    	pNodoNuevo = (Node*)malloc(sizeof(Node));
    	if(pNodoNuevo!=NULL) {
    		pNodoNuevo->pElement = pElement;
			if(nodeIndex==0)//primer nodo
			{
				pNodoNuevo->pNextNode=this->pFirstNode;
				this->pFirstNode=pNodoNuevo;
				this->size++;
				retorno=0;

			}else{
				pNodoAnterior = getNode(this,nodeIndex-1);
				if(pNodoAnterior!=NULL) {
					pNodoNuevo->pNextNode = pNodoAnterior->pNextNode;
					pNodoAnterior->pNextNode = pNodoNuevo;
					this->size++;
					retorno = 0;
				}else{
					free(pNodoNuevo);
				}
			}
    	}
    }
    return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int retorno = -1;
    if(this!=NULL && addNode(this,ll_len(this),pElement)==0 )
    {
    	retorno=0;
    }
    return retorno;
}

/** \brief Permite obtener el puntero a un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* pERetorno = NULL;
    Node* pNodo;
    if(this!=NULL && index>=0 && index<ll_len(this) )
    {
    	pNodo=getNode(this, index);
    	if(pNodo!=NULL){
    		pERetorno=pNodo->pElement;
    	}
    }
    return pERetorno;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int retorno=-1;
    Node*pNodo;
    if(this!=NULL && index>=0 && index<ll_len(this) ){
    	pNodo=getNode(this, index);
    	if(pNodo!=NULL){
    		pNodo->pElement=pElement;
    		retorno=0;
    	}
    }
    return retorno;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int retorno=-1;
    Node*pNodo;
    Node*pNodoAnterior;
    if(this!=NULL && index>=0 && index<ll_len(this) ) {
    	pNodo=getNode(this, index);
    	if(pNodo!=NULL){
    		if(index==0){
    			this->pFirstNode=pNodo->pNextNode;
    			free(pNodo);
				this->size--;
				retorno=0;
    		}else{
    			pNodoAnterior=getNode(this, index-1);
    			if(pNodoAnterior!=NULL){
    				pNodoAnterior->pNextNode=pNodo->pNextNode;
    				free(pNodo);
    				this->size--;
    				retorno=0;
    			}
    		}
    	}
    }
    return retorno;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int retorno=-1;
    int indice;
    int flagTerminado=0;
    if(this!=NULL){
    	do{
    		indice=ll_len(this);
    		indice--;
    		flagTerminado=ll_remove(this, indice);
    	}while(flagTerminado==0);
    	if(ll_len(this)==0){
    		retorno=0;
    	}
    }
    return retorno;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int retorno=-1;
    if(this!=NULL && !ll_clear(this)){
    	free(this);
    	retorno=0;
    }
    return retorno;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int retorno=-1;
    int indice=0;
    if(this!=NULL){
    	for(;indice<ll_len(this);indice++)
    	{
    		if( pElement==ll_get(this, indice) )
    		{
    			retorno=indice;
    			break;
    		}
    	}
    }
    return retorno;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int retorno=-1;
    if(this!=NULL){
    	retorno=0;
    	if(ll_len(this)==0){
    		retorno=1;
    	}
    }
    return retorno;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int retorno=-1;
    if(this!=NULL && index>=0 && index<=ll_len(this) &&
    	addNode(this,index,pElement)==0 )
    {
    	retorno=0;
    }
    return retorno;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* pERetorno=NULL;
    if(this!=NULL && index>=0 && index<ll_len(this)){
    	pERetorno=ll_get(this, index);
    	if(pERetorno!=NULL && ll_remove(this, index)!=0){
    		pERetorno=NULL;
    	}
    }
    return pERetorno;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int retorno = -1;
    if(this!=NULL){
    	retorno=0;
    	if(ll_indexOf(this, pElement)!=-1){
    		retorno=1;
    	}
    }
    return retorno;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int retorno=-1;
    int indice=0;
    if(this!=NULL && this2!=NULL){
    	retorno=1;
    	for(;indice<ll_len(this2);indice++)
    	{
    		if( ll_contains(this,ll_get(this2,indice))==0 )
    		{
    			retorno=0;
    			break;
    		}
    	}
    }
    return retorno;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int indice;
    if(this!=NULL && from>=0 && from<=ll_len(this) && from<to && to<=ll_len(this) )
    {
    	cloneArray=ll_newLinkedList();
    	if(cloneArray!=NULL){
    		for(indice=from;indice<to;indice++){
    			ll_add(cloneArray, ll_get(this, indice));
    		}
    	}
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    if(this!=NULL){
    	cloneArray=ll_subList(this,0,ll_len(this));
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int retorno=-1;
    int flagSwap;
    void*pEA;//primer elemento
    void*pEB;//elemento siguiente
    int comparacion;//comparacion 1=pEA>pEB -1=pEA<pEB
    if(this!=NULL && pFunc!=NULL && (order==1||!order) )
    {
    	do{
    		flagSwap=0;
    		for(int i=0;i<ll_len(this)-1;i++){
    			pEA=ll_get(this, i);
    			pEB=ll_get(this, i+1);
    			comparacion=pFunc(pEA,pEB);
    			if( (order==1 && comparacion==1) ||
    				(order==0 && comparacion==-1) )
    			{
    				ll_set(this, i, pEB);
    				ll_set(this, i+1, pEA);
    				flagSwap=1;
    			}
    		}
    	}while(flagSwap);
    	retorno=0;
    }
    return retorno;
}

