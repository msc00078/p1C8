/**
 * @file ListaEnlazada.h
 * @author Asistente de Calidad (assistant@domain.com)
 * @brief Declaración e implementación de una Lista Enlazada Simple genérica.
 * @version 0.1
 * @date 2026-03-09
 * * @copyright Copyright (c) 2026
 */
#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

using namespace std;
#include <iostream>

/**
 * @class NodoL
 * @brief Representa un nodo para la clase ListaEnlazada.
 * Almacena el dato genérico y un puntero al siguiente elemento.
 */
template<class T>
class NodoL {

public:
    T dato;       ///< Información almacenada en el nodo.
    NodoL *sig;   ///< Puntero al siguiente nodo de la lista.

    /**
     * @brief Constructor del nodo de la lista.
     * @param aDato Dato a almacenar.
     * @param aSig Puntero al siguiente nodo.
     */
    NodoL(const T &aDato, NodoL *aSig = 0):dato(aDato), sig(aSig) {}

    /**
     * @brief Destructor del nodo de la lista.
     */
    ~NodoL() {}
};

/**
 * @class ListaEnlazada
 * @brief Estructura de datos dinámica tipo Lista Simplemente Enlazada.
 * Permite insertar, borrar y recorrer elementos secuencialmente mediante un iterador.
 */
template<class T>
class ListaEnlazada {

//declaracion del Nodo local

    NodoL<T> *cabecera;  ///< Puntero al primer elemento de la lista.
    NodoL<T> *cola;      ///< Puntero al último elemento de la lista.
    unsigned tama;       ///< Número de elementos actualmente en la lista.

public:

    /**
     * @class Iterador
     * @brief Permite recorrer los nodos de la ListaEnlazada secuencialmente.
     */
    template <class U>
    class Iterador {
        NodoL<U> *nodo; ///< Puntero al nodo actual en la iteración.
    public:
        friend class ListaEnlazada<U>;

        /**
         * @brief Constructor del iterador.
         * @param aNodo Nodo inicial.
         */
        Iterador(NodoL<U> *aNodo=0) : nodo(aNodo) {}

        /**
         * @brief Verifica si se ha alcanzado el final de la lista.
         * @return bool True si ha terminado, False si hay más elementos.
         */
        bool fin() { return nodo == 0; }

        /**
         * @brief Avanza el iterador al siguiente nodo.
         */
        void siguiente() {
            nodo = nodo->sig;
        }
        // Nodo<T> *vernodo() { return nodo; }

        /**
         * @brief Obtiene el dato almacenado en el nodo actual del iterador.
         * @return T& Referencia al dato.
         */
        T &dato() { return nodo->dato; }

        /**
         * @brief Destructor del iterador.
         */
        ~Iterador() {}
    };

    /**
     * @brief Constructor por defecto de la lista enlazada.
     */
    ListaEnlazada() : cabecera(0), cola(0), tama(0) {}

    /**
     * @brief Destructor de la lista enlazada.
     */
    ~ListaEnlazada();

    /**
     * @brief Constructor de copia.
     * @param l Lista original a copiar.
     */
    ListaEnlazada(const ListaEnlazada<T> &l);

    /**
     * @brief Sobrecarga del operador de asignación.
     * @param l Lista a asignar.
     * @return ListaEnlazada& Referencia a la lista actual.
     */
    ListaEnlazada &operator=(const ListaEnlazada<T> &l);

    /**
     * @brief Devuelve un iterador apuntando al inicio de la lista.
     * @return Iterador<T> Iterador inicializado en la cabecera.
     */
    Iterador<T> iterador() const;

    /**
     * @brief Inserta un dato al principio de la lista.
     * @param dato Dato a insertar.
     */
    void insertarInicio(const T &dato);

    /**
     * @brief Inserta un dato al final de la lista.
     * @param dato Dato a insertar.
     */
    void insertarFin(const T &dato);

    /**
     * @brief Inserta un dato justo delante del nodo apuntado por el iterador.
     * @param p Iterador indicando la posición.
     * @param dato Dato a insertar.
     */
    void insertaDelante(Iterador<T> &p, const T &dato);

    /**
     * @brief Inserta un dato justo detrás del nodo apuntado por el iterador.
     * @param p Iterador indicando la posición.
     * @param dato Dato a insertar.
     */
    void insertaDetras( Iterador<T> &p, const T &dato);

    /**
     * @brief Borra el primer elemento de la lista.
     */
    void borrarInicio();

    /**
     * @brief Borra el último elemento de la lista.
     */
    void borrarFinal();

    /**
     * @brief Borra el nodo apuntado por el iterador.
     * @param i Iterador apuntando al nodo a borrar.
     */
    void borra(Iterador<T> &i);

    /**
     * @brief Devuelve el número de elementos de la lista.
     * @return int Tamaño actual.
     */
    int tam(){ return tama;}

    /**
     * @brief Elimina todos los elementos de la lista liberando su memoria.
     */
    void destruyeLista();  //puede/debe ir en private

    /**
     * @brief Concatena otra lista al final de la actual devolviendo una nueva lista.
     * @param l Lista a concatenar.
     * @return ListaEnlazada<T> Nueva lista resultante.
     */
    ListaEnlazada<T> concatena(const ListaEnlazada<T> &l);

    /**
     * @brief Sobrecarga del operador suma para concatenar listas.
     * @param l Lista a concatenar.
     * @return ListaEnlazada<T> Nueva lista resultante.
     */
    ListaEnlazada<T> operator+(const ListaEnlazada<T> &l);

    /**
     * @brief Obtiene una referencia al dato del primer nodo.
     * @return T& Referencia al primer dato.
     */
    T &inicio(){
        if (!cabecera)
            throw std::invalid_argument("No existe ese elemento");
        return cabecera->dato;
    };

    /**
     * @brief Obtiene una referencia al dato del último nodo.
     * @return T& Referencia al último dato.
     */
    T &fin(){
        if (!cola)
            throw std::invalid_argument("No existe ese elemento");
        return cola->dato;
    };
};

template<class T>
typename ListaEnlazada<T>::template Iterador<T> ListaEnlazada<T>::iterador() const{
    return Iterador<T> (cabecera);
}

//CONSTRUCTOR DE COPIA
template<class T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada<T> &l){
    NodoL<T> *i= l.cabecera;
    cabecera=0;
    cola=0;
    tama=l.tama;

    while (i){
         NodoL<T> *nuevo;
         nuevo = new NodoL<T>(i->dato, 0);
         if (cola != 0)
             cola->sig = nuevo;
         // Caso especial: si la lista estaba vac a, poner la cabecera apuntando al nodo
         if (cabecera == 0)
             cabecera = nuevo;
         cola = nuevo;
         i=i->sig;
    }
}

// DESTRUCTOR
template<class T>
ListaEnlazada<T>::~ListaEnlazada(){
    destruyeLista();
}

//OPERADOR DE ASIGNACION
template<class T>
ListaEnlazada<T> &ListaEnlazada<T>::operator=(const ListaEnlazada<T> &l){

    if (this!=&l){
        if (cabecera) {
              NodoL<T> *borra= cabecera;
              while ( borra ){
                  cabecera= cabecera->sig;
                  delete borra;
                  borra=cabecera;
              }
              cola = 0;
        }
        NodoL<T> *i= l.cabecera;
        cabecera=0;
        cola=0;
        tama=l.tama;

        while (i){
             NodoL<T> *nuevo;
             nuevo = new NodoL<T>(i->dato, 0);
             if (cola != 0)
                 cola->sig = nuevo;
             // Caso especial: si la lista estaba vac a, poner la cabecera apuntando al nodo
             if (cabecera == 0)
                 cabecera = nuevo;
             cola = nuevo;
             i=i->sig;
        }
    }
    return (*this);

}

template<class T>
void ListaEnlazada<T>::insertarInicio(const T &dato){
    NodoL<T> *nuevo;
    nuevo = new NodoL<T>(dato, cabecera);
    // Caso especial: si la lista estaba vac a poner la cola apuntando al nodo
    if (cola == 0)
        cola = nuevo;

    cabecera = nuevo;
    ++tama;
};

template<class T>
void ListaEnlazada<T>::insertarFin(const T &dato){
    NodoL<T> *nuevo;
    nuevo = new NodoL<T>(dato, 0);

    if (cola != 0)
        cola->sig = nuevo;
    // Caso especial: si la lista estaba vac a, poner la cabecera apuntando al nodo
    if (cabecera == 0)
        cabecera = nuevo;
    cola = nuevo;
    ++tama;
}

template<class T>
void ListaEnlazada<T>::insertaDelante(Iterador<T> &p, const T &dato){
    if (p.fin()) {
        insertarFin(dato);
    }else{

        if (p.nodo==cabecera){
            insertarInicio(dato);
            return;
        }

        ++tama;
        NodoL<T> *anterior = 0;

        anterior = cabecera;
        while (anterior->sig != p.nodo)
            anterior = anterior->sig;

        NodoL<T> *nuevo;
        nuevo = new NodoL<T>(dato, p.nodo);
        anterior->sig = nuevo;
    }
}

template<class T>
void ListaEnlazada<T>::insertaDetras( Iterador<T> &p,const T &dato){
    if (!p.fin()){
        ++tama;
        NodoL<T> *nuevo;
        nuevo = new NodoL<T>(dato, p.nodo->sig);
        p.nodo->sig = nuevo;
        if (p.nodo == cola)
            cola= nuevo;
    }
}

template<class T>
void ListaEnlazada<T>::borrarInicio(){

    if  (cabecera!=0){
        --tama;
        NodoL<T> *borrado = cabecera;
        cabecera= cabecera->sig;
        delete borrado;
        // Caso especial al borrar el  ltimo nodo
        if (cabecera == 0)
            cola = 0;
    }
}

template<class T>
void ListaEnlazada<T>::borrarFinal(){
    NodoL<T> *anterior = 0;
    if (cabecera != cola) {
        --tama;
        anterior = cabecera;
        while (anterior->sig != cola)
            anterior = anterior->sig;

        delete cola;   // sino OJO cuando est  vac a intenta un delete absurdo!!
        cola = anterior;

        anterior->sig = 0;

    } else{    //else para cuando hay 1 o ninguno
        if (cabecera){
            delete cabecera;
            cabecera=cola=0;
            tama=0;
        }
    }
}

template<class T>
void ListaEnlazada<T>::borra(Iterador<T> &p){
    NodoL<T> *anterior;
    if (!p.fin()) {
        --tama;
        if (p.nodo==cabecera){
            borrarInicio();
            return;
        }
        if (p.nodo==cola){
            borrarFinal();
            return;
        }
        anterior = cabecera;
        while (anterior->sig != p.nodo)
            anterior = anterior->sig;
        anterior->sig = p.nodo->sig;
        delete p.nodo;
    }
}

template<class T>
ListaEnlazada<T> ListaEnlazada<T>::concatena(const ListaEnlazada<T> &l){

    ListaEnlazada<T> ret(*this);
    NodoL<T>* p=l.cabecera;
    while (p){
        NodoL<T> *nuevo;
        ret.tama++;
        nuevo = new NodoL<T>(p->dato,0);
        // Caso especial: si la lista estaba vac a, poner la cabecera apuntando al nodo
        if (ret.cabecera == 0)
            ret.cabecera = nuevo;
        if (ret.cola != 0)
            ret.cola->sig = nuevo;
        ret.cola = nuevo;

        p=p->sig;
    }

    return ret;
}

template<class T>
ListaEnlazada<T> ListaEnlazada<T>::operator+(const ListaEnlazada<T> &l){
    return this->concatena(l);
}

template<class T>
void ListaEnlazada<T>::destruyeLista(){
    if (cabecera) {
        NodoL<T> *borra= cabecera;
        while ( borra ){
            cabecera= cabecera->sig;
            delete borra;
            borra=cabecera;
        }
        cola = 0;
        tama = 0;
    }
}

#endif // LISTAS_H_INCLUDED