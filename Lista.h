#include <iostream>

using namespace std;

// Definici�n de la plantilla de la clase NodoLista y de la clase Lista

/* Prototipo de la plantilla de la clase Lista. As�, en la clase NodoLista se
   podr� hacer referencia a ella. */
template <class T>
class Lista;

template <class T>
class NodoLista
{
  public:
     NodoLista<T> * Liga;
     T Info;
  public:
     NodoLista();
     T RegresaInfo();
     friend class Lista<T>;
};
/* Constructor por omisi�n. Inicializa con el valor NULL al apuntador al
   siguiente nodo. */
template <class T>
NodoLista<T>::NodoLista()
{
   Liga = NULL;
}

/* M�todo que permite, a los usuarios ajenos a la clase, conocer el valor del
   atributo Info. */
template <class T>
T NodoLista<T>::RegresaInfo()
{
   return Info;
}

// Definici�n de la clase Lista
template <class T>
class Lista
{
  private:
     NodoLista<T> * Primero;
  public:
     Lista();
     NodoLista<T> * RegresaPrimero();
     void CreaInicio();
     void CreaFinal();
     void ImprimeIterativo();
     void ImprimeRecursivo(NodoLista<T> * );
     void ImprimeUnNodo(NodoLista<T> * );
     void InsertaInicio(T);
     void InsertaFinal(T);
     void InsertaOrdenCrec(T);
     int InsertaAntes(T, T);
     int InsertaDespues(T, T);
     int EliminaPrimero();
     int EliminaUltimo();
     int EliminaUnNodo(T);
     int EliminaAnterior(T);
     int EliminaDespues(T);
     NodoLista<T> * BuscaDesordenada(T);
     NodoLista<T> * BuscaOrdenada(T);
     NodoLista<T> * BuscaRecursivo(T, NodoLista<T> *);
};

/* M�todo constructor. Inicializa el apuntador al primer nodo de la lista con
   el valor NULL: indica lista vac�a. */
template <class T>
Lista<T>::Lista()
{
   Primero = NULL;
}

/* M�todo que regresa la direcci�n del primer nodo de la lista. */
template <class T>
NodoLista<T> * Lista<T>::RegresaPrimero()
{
   return Primero;
}

/* M�todo que crea una lista agregando el nuevo nodo al inicio de la misma. */
template <class T>
void Lista<T>::CreaInicio()
{
   NodoLista<T> * P;
   T Dato;
   char Resp;
   Primero = new NodoLista<T>();
   cout << "Ingresa la informacion a almacenar: \n";
   cin >> Dato;
   Primero->Info = Dato;
   cout<< "\nDeseas ingresar otro elemento (S/N)? ";
   cin>>Resp;
   while (Resp == 'S' || Resp == 's')
   {
      cout<< "Ingresa la informacion: \n";
      cin>> Dato;
      P = new NodoLista<T>();
      P->Info = Dato;
      P->Liga = Primero;
      Primero = P;
      cout<< "\nDeseas ingresar otro elemento (S/N)? ";
      cin>>Resp;
   }
}

/* M�todo que crea una lista agregando el nuevo nodo al final de la misma. */
template <class T>
void Lista<T>::CreaFinal()
{
   NodoLista<T> * P, *Ultimo;
   T Dato;
   char Resp;
   Primero = new NodoLista<T>();
   cout<<"Ingresa la informacion a almacenar: \n";
   cin>>Dato;
   Primero->Info = Dato;
   /* Se mantiene un apuntador al �ltimo nodo agregado a la lista para evitar
      tener que recorrerla con cada nuevo nodo. */
   Ultimo = Primero;
   cout<<"\nDeseas ingresar otro elemento (S/N)? ";
   cin>>Resp;
   while (Resp == 'S' || Resp == 's')
   {
      cout<< "\nIngresa la informacion \n";
      cin>>Dato;
      P = new NodoLista<T>();
      P->Info = Dato;
      Ultimo->Liga = P;
      Ultimo = P;
      cout<< "\nDeseas ingresar otro elemento (S/N)? ";
      cin>>Resp;
   }
}

/* M�todo que despliega el contenido de la lista iterativamente. */
template <class T>
void Lista<T>::ImprimeIterativo()
{
   NodoLista<T> * P;
   P = Primero;
   while (P)
   {
      cout<< "\nInformacion: "<< P->Info;
      P = P->Liga;
   }
   cout<< '\n';
}

/* M�todo que despliega el contenido de la lista recursivamente. Recibe como
   par�metro el nodo cuya informaci�n se va a imprimir. */
template <class T>
void Lista<T>::ImprimeRecursivo(NodoLista<T> * P)
{
   if (P)
   {
      cout<<"\nInformacion: "<< P->Info;
      ImprimeRecursivo(P->Liga);
   }
   cout<<'\n';
}

/* M�todo que imprime la informaci�n de un nodo dado como dato. */
template <class T>
void Lista<T>::ImprimeUnNodo(NodoLista<T> * P)
{
   if (P)
      cout<< P->Info;
}

/* M�todo que inserta un nodo al inicio de la lista. El m�todo es v�lido tanto
   para listas ya creadas como para listas vac�as. */
template <class T>
void Lista<T>::InsertaInicio(T Dato)
{
  NodoLista<T> * P;
  P = new NodoLista<T>();
  P->Info = Dato;
  P->Liga = Primero;
  Primero = P;
}

/* M�todo que inserta un nodo al final de la lista. El m�todo es v�lido tanto
   para listas ya creadas como para listas vac�as. */
template <class T>
void Lista<T>::InsertaFinal(T Dato)
{
  NodoLista<T> * P, *Ultimo;
  P = new NodoLista<T>();
  P->Info = Dato;
  if (Primero)
  {
     /* Si la lista tiene al menos un elemento, entonces se debe recorrer hasta
        llegar al �ltimo nodo. */
     Ultimo = Primero;
     while (Ultimo->Liga)
        Ultimo = Ultimo->Liga;
     // El �ltimo nodo de la lista apunta al nuevo nodo, cuya direcci�n est� en P
     Ultimo->Liga = P;
  }
  else
     /* Si la lista no tiene elementos, entonces el nuevo elemento ser� el
        primero de la misma. */
     Primero = P;
}

/* M�todo que inserta un nodo en orden creciente. Luego de varias inserciones,
  usando este m�todo, se habr� generado una lista ordenada de menor a mayor. */
template <class T>
void Lista<T>::InsertaOrdenCrec(T Dato)
{
   NodoLista<T> * P, *Q, *Ant;
   if (!Primero || Primero->Info > Dato)
      InsertaInicio(Dato);
   else
   {
      Q = Primero;
      while (Q && Q->Info < Dato)
      {
         Ant= Q;
         Q = Q->Liga;
      }
      P = new NodoLista<T>();
      P->Info = Dato;
      Ant->Liga = P;
      P->Liga = Q;
   }
}

/* M�todo que inserta un nodo antes de un nodo dado como referencia. Recibe como
   par�metros la informaci�n a insertar y un dato dado como referencia. Regresa
   1 si se pudo insertar, 0 si no se encontr� la referencia y �1 si la lista
   est� vac�a. */
template <class T>
int Lista<T>::InsertaAntes(T Dato, T Ref)
{
   NodoLista<T> * P, *Ant, *Q;
   int Resp = 1;
   if (Primero)
   {
      Q = Primero;
      while ((Q != NULL ) && (Q->Info != Ref))
      {
         Ant = Q;
         Q = Q->Liga;
      }
      if (Q != NULL )
      {
         P = new NodoLista<T>();
         P->Info = Dato;
         // El dato de referencia es el primero de la lista.
         if (Primero == Q)
         {
            P->Liga = Primero;
            Primero = P;
         }
         else
         {
            Ant->Liga = P;
            P->Liga = Q;
         }
      }
      else
         // No se encontr� el dato dado como referencia
         Resp = 0;
   }
   else
      // La lista est� vac�a
      Resp = -1;
   return Resp;
}

/* M�todo que inserta un nodo despu�s de uno dado como referencia. Recibe como
   par�metros la informaci�n a insertar y la referencia. Regresa 1 si se pudo
   insertar, 0 si no se encontr� el dato dado y �1 si la lista est� vac�a. */
template <class T>
int Lista<T>::InsertaDespues(T Dato, T Ref)
{
   NodoLista<T> * Q, *P;
   int Resp = 1;
   if (Primero)
   {
      Q = Primero;
      while ((Q != NULL ) && (Q->Info != Ref))
         Q = Q->Liga;
      if ( Q != NULL )
      {
         P = new NodoLista<T>();
         P->Info = Dato;
         P->Liga = Q->Liga;
         Q->Liga = P;
      }
      else
         // No se encontr� la referencia
         Resp = 0;
   }
   else
      // La lista est� vac�a
      Resp = -1;
   return Resp;
}

/* M�todo que elimina el primer elemento de la lista. El m�todo redefine el
  apuntador al inicio de la lista y libera el espacio de memoria del nodo
  eliminado. Regresa 1 si se pudo llevar a cabo la operaci�n y 0 en caso
  contrario. */
template <class T>
int Lista<T>::EliminaPrimero()
{
   NodoLista<T> * P;
   int Resp = 1;
   if (Primero)
   {
      P = Primero;
      Primero = P->Liga;
      delete (P);
   }
   else
      // La lista est� vac�a
      Resp = 0;
   return Resp;
}

/* M�todo que elimina el �ltimo elemento de una lista. Primero lo localiza,
  guardando la direcci�n del nodo que le precede. Posteriormente redefine la
  liga de �ste con el valor de NULL para indicar que ahora �ste es el �ltimo y
  libera el espacio de memoria. Regresa 1 si se pudo llevar a cabo la eliminaci�n
  y 0 en caso contrario. */
template <class T>
int Lista<T>::EliminaUltimo()
{
   NodoLista<T> * Ant, *P;
   int Resp = 1;
   if (Primero)
   {
      /* Verifica si la lista est� formada por un �nico elemento, en tal caso
         redefine el puntero al inicio con el valor de NULL, indicando lista vac�a. */
      if (!Primero->Liga)
      {
         delete (Primero);
         Primero = NULL;
      }
      else
      {
         P = Primero;
         while (P->Liga)
         {
            Ant = P;
            P = P->Liga;
         }
         Ant->Liga = NULL;
         delete (P);
      }
   }
   else
      // La lista est� vac�a
      Resp = 0;
   return Resp;
}

/* M�todo que elimina un nodo que almacena cierta informaci�n. Recibe como
   par�metro el dato a eliminar y regresa como resultado 1 si lo elimina, 0 si
   no lo encuentra y �1 si la lista est� vac�a. */
template <class T>
int Lista<T>::EliminaUnNodo(T Ref)
{
   NodoLista<T> * P, *Ant;
   int Resp = 1;
   if (Primero)
   {
      P = Primero;
      while ((P->Liga) && (P->Info != Ref))
      {
         Ant = P;
         P = P->Liga;
      }
      if (P->Info != Ref)
         // El elemento no fue encontrado
         Resp = 0;
      else
      {
         if (Primero == P)
            Primero = P->Liga;
         else
            Ant->Liga = P->Liga;
         delete (P);
      }
   }
   else
      Resp = -1;
   return Resp;
}

/* M�todo que elimina el nodo anterior al nodo que almacena un dato dado como
   referencia. Regresa 1 si el nodo fue eliminado, 2 si la referencia es el
   primero, 3 si no fue encontrado y 4 si la lista est� vac�a. */
template <class T>
int Lista<T>::EliminaAnterior(T Ref)
{
   NodoLista<T> * Q, *Ant, *P;
   int Resp= 1;
   if (Primero)
   {
      if (Primero->Info == Ref)
      // No hay nodo que preceda al dado como referencia.
      Resp= 2;
   else
   {
      Q = Primero;
      Ant = Primero;
      /* Ciclo que permite encontrar la informaci�n dada como referencia,
         guardando la direcci�n del nodo que le precede (nodo que se eliminar�)
         y del anterior a �ste para establecer las ligas correspondientes. */
      while ((Q->Info != Ref) && (Q->Liga))
      {
         P = Ant;
         Ant = Q;
         Q = Q->Liga;
      }
      if (Q->Info != Ref)
      // El elemento dado como referencia no est� en la lista.
         Resp = 3;
      else
         if (Primero->Liga == Q)
         {
            delete (Primero);
            Primero = Q;
         }
         else
         {
            P->Liga = Q;
            delete (Ant);
         }
      }
   }
   else
   // La lista est� vac�a
      Resp = 4;
   return Resp;
}

/* M�todo que busca un elemento dado referencia en una lista desordenada. Regresa
   la direcci�n del nodo si lo encuentra y NULL en caso contrario. */
template <class T>
NodoLista<T> * Lista<T>::BuscaDesordenada(T Ref)
{
   NodoLista<T> * Q, *Resp= NULL;
   if (Primero)
   {
      Q = Primero;
      while ((Q->Info != Ref) && (Q->Liga))
         Q = Q->Liga;
      // Se verifica si el elemento dado como referencia fue encontrado en la lista
      if (Q->Info == Ref)
         Resp = Q;
   }
   return Resp;
}

/* M�todo que busca un elemento dado como referencia, en una lista ordenada de
   menor a mayor. Regresa la direcci�n del nodo si lo encuentra y NULL en caso
   contrario. */
template <class T>
NodoLista<T> * Lista<T>::BuscaOrdenada(T Ref)
{
   NodoLista<T> * Q, *Resp= NULL;
   if (Primero)
   {
      Q = Primero;
      while ((Q->Info < Ref) && (Q->Liga))
         Q = Q->Liga;
      // Se verifica si el elemento dado como referencia fue encontrado en la lista
      if (Q->Info == Ref)
         Resp = Q;
   }
   return Resp;
}

/* M�todo que busca un dato en la lista. La operaci�n se realiza recursivamente.
   El m�todo recibe como par�metro el elemento a buscar ( Dato) y una variable
   ( Q) que almacena la direcci�n de un nodo (la primera vez es la direcci�n del
   primero). Regresa como resultado la direcci�n del nodo si lo encuentra y NULL
   en caso contrario. */
template <class T>
NodoLista<T> * Lista<T>::BuscaRecursivo(T Dato, NodoLista<T> * Q)
{
   if (Q)
      if (Q->Info == Dato)
         return Q;
      else
         return BuscaRecursivo(Dato, Q->Liga);
   else
      return NULL;
}

