#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

using namespace std;
#include <iostream>

template<class T>
class NodoL {

public:
    T dato;
    NodoL *sig;
    NodoL(const T &aDato, NodoL *aSig = 0):dato(aDato), sig(aSig) {}
    ~NodoL() {}
};

template<class T>
class ListaEnlazada {

//declaracion del Nodo local

    NodoL<T> *cabecera, *cola;
    unsigned tama;

public:

    //IMPLEMENTACION DEL ITERADOR
    template <class U>
    class Iterador {
        NodoL<U> *nodo;
    public:
        friend class ListaEnlazada<U>;

        Iterador(NodoL<U> *aNodo=0) : nodo(aNodo) {}

        bool fin() { return nodo == 0; }

        void siguiente() {
            nodo = nodo->sig;
        }
        // Nodo<T> *vernodo() { return nodo; }
        T &dato() { return nodo->dato; }
        ~Iterador() {}
    };

    ListaEnlazada() : cabecera(0), cola(0), tama(0) {}
    ~ListaEnlazada();
    ListaEnlazada(const ListaEnlazada<T> &l);
    ListaEnlazada &operator=(const ListaEnlazada<T> &l);
    Iterador<T> iterador() const;
    void insertarInicio(const T &dato);
    void insertarFin(const T &dato);
    void insertaDelante(Iterador<T> &p, const T &dato);
    void insertaDetras( Iterador<T> &p, const T &dato);
    void borrarInicio();
    void borrarFinal();
    void borra(Iterador<T> &i);
    int tam(){ return tama;}
    void destruyeLista();  //puede/debe ir en private

    ListaEnlazada<T> concatena(const ListaEnlazada<T> &l);
    ListaEnlazada<T> operator+(const ListaEnlazada<T> &l);

    T &inicio(){
        if (!cabecera)
            throw std::invalid_argument("No existe ese elemento");
        return cabecera->dato;
    };
    T &fin(){
        if (!cola)
            throw std::invalid_argument("No existe ese elemento");
        return cola->dato;
    };
};

template<class T>
ListaEnlazada<T>::Iterador<T> ListaEnlazada<T>::iterador() const{
    return Iterador (cabecera);
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
