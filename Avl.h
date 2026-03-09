/**
 * @file Avl.h
 * @author Asistente de Calidad (assistant@domain.com)
 * @brief Declaración e implementación de un Árbol AVL genérico.
 * @version 0.1
 * @date 2026-03-09
 * * @copyright Copyright (c) 2026
 */
#ifndef PR3EEDD_AVL_H
#define PR3EEDD_AVL_H

#include "VDinamico.h"

/**
 * @class NodoAVL
 * @brief Nodo para un árbol binario de búsqueda balanceado (AVL).
 * Almacena el dato, el balance y los punteros a los hijos izquierdo y derecho.
 */
template <class T>
class NodoAVL
{
public:
    NodoAVL<T> *izq;    ///< Puntero al subárbol izquierdo.
    NodoAVL<T> *der;    ///< Puntero al subárbol derecho.
    char bal;           ///< Factor de balanceo del nodo.
    T dato;             ///< Información almacenada en el nodo.

    /**
     * @brief Constructor a partir de un dato.
     * @param ele Dato a almacenar.
     */
    NodoAVL(const T &ele): izq(0), der(0), bal(0), dato(ele){}

    /**
     * @brief Constructor de copia de nodo.
     * @param orig Nodo original a copiar.
     */
    NodoAVL(const NodoAVL<T> &orig): izq(orig.izq), der(orig.der), bal(orig.bal), dato(orig.dato){}
};

/**
 * @class Avl
 * @brief Representa un Árbol AVL balanceado de elementos genéricos.
 * Mantiene sus elementos siempre ordenados y balanceados para 
 * garantizar un acceso, inserción y búsqueda eficientes.
 */
template <class T>
class Avl {
    NodoAVL<T> *raiz; ///< Puntero a la raíz del árbol.
    unsigned int tam; ///< Número de elementos en el árbol.

    /**
     * @brief Recorrido inorden recursivo interno.
     * @param p Nodo actual en la recursión.
     * @param nivel Nivel actual de profundidad.
     * @param vectorResultado Vector donde se insertan los resultados ordenados.
     */
    void inorden(NodoAVL<T>* p, int nivel, Vdinamico<T*> &vectorResultado);

    /**
     * @brief Búsqueda recursiva interna.
     * @param dato Dato a buscar.
     * @param p Nodo actual en la recursión.
     * @return NodoAVL<T>* Puntero al nodo encontrado o 0 si no existe.
     */
    NodoAVL<T> *buscaClave ( const T &dato, NodoAVL<T> *p);

    /**
     * @brief Inserción recursiva interna balanceada.
     * @param c Referencia al puntero del nodo actual.
     * @param dato Dato a insertar.
     * @return int Valor que indica si hubo cambio de altura.
     */
    int insertaDato(NodoAVL<T>* &c, const T &dato);

    /**
     * @brief Destruye el árbol recursivamente.
     * @param p Referencia al puntero del nodo a destruir.
     */
    void destruyeArbol(NodoAVL<T>* &p);

    /**
     * @brief Rotación simple a la derecha.
     * @param p Referencia al puntero del nodo desbalanceado.
     */
    void rotDer(NodoAVL<T>* &p);

    /**
     * @brief Rotación simple a la izquierda.
     * @param p Referencia al puntero del nodo desbalanceado.
     */
    void rotIzq(NodoAVL<T>* &p);

    /**
     * @brief Copia recursiva de un árbol AVL.
     * @param q Referencia al puntero del nodo destino.
     * @param p Puntero al nodo origen.
     */
    void copiaAvl(NodoAVL<T>* &q, NodoAVL<T> *p);

    /**
     * @brief Copia recursiva de un árbol AVL (variante 2).
     * @param p Puntero al nodo origen.
     * @return NodoAVL<T>* Puntero a la nueva copia del nodo.
     */
    NodoAVL<T>* copiaAvl2(NodoAVL<T> *p);

    /**
     * @brief Cuenta los elementos de forma recursiva.
     * @param p Nodo actual.
     * @return unsigned int Número de elementos en el subárbol.
     */
    unsigned int numElementosPr(NodoAVL<T>* p);

    /**
     * @brief Calcula la altura máxima de forma recursiva.
     * @param p Nodo actual.
     * @param nivel Nivel de profundidad actual.
     * @param result Referencia donde se almacena la altura máxima encontrada.
     */
    void alturaPr(NodoAVL<T>* p, int nivel, int &result);

    /**
     * @brief Calcula la altura máxima de forma recursiva (variante 2).
     * @param p Nodo actual.
     * @return unsigned int Altura del subárbol.
     */
    unsigned alturaPr2(NodoAVL<T>* p);

public:

    /**
     * @brief Constructor por defecto del árbol AVL.
     */
    Avl() : raiz(0), tam(0) {}

    /**
     * @brief Constructor de copia.
     * @param orig Árbol AVL original a copiar.
     */
    Avl(const Avl<T>& orig);

    /**
     * @brief Sobrecarga del operador de asignación.
     * @param orig Árbol AVL a asignar.
     * @return Avl<T>& Referencia al árbol actual.
     */
    Avl<T>& operator=(const Avl<T>& orig);

    /**
     * @brief Busca un dato en el árbol de forma recursiva.
     * @param dato Dato a buscar.
     * @return T* Puntero al dato encontrado o 0 si no existe.
     */
    T* buscaRec (const T &dato);

    /**
     * @brief Busca un dato en el árbol de forma iterativa.
     * @param dato Dato a buscar.
     * @return T* Puntero al dato encontrado o 0 si no existe.
     */
    T* buscaIt(const T &dato);

    /**
     * @brief Inserta un dato en el árbol AVL.
     * @param dato Dato a insertar.
     * @return bool True si se insertó con éxito, False si el dato ya existía.
     */
    bool inserta(const T &dato);

    /**
     * @brief Obtiene el número de elementos en el árbol.
     * @return unsigned int Cantidad de elementos actuales.
     */
    unsigned int numElementos();

    /**
     * @brief Obtiene la altura del árbol.
     * @return unsigned int Altura máxima del árbol.
     */
    unsigned int altura();

    /**
     * @brief Obtiene la altura del árbol (variante 2).
     * @return unsigned int Altura máxima del árbol.
     */
    unsigned int altura2();

    /**
     * @brief Obtiene el valor de la variable de tamaño.
     * @return unsigned int Tamaño almacenado.
     */
    unsigned int getTam(){ return tam;};

    /**
     * @brief Destructor del árbol AVL. Libera todos los nodos.
     */
    ~Avl(){
        destruyeArbol(raiz);
    };

    /**
     * @brief Realiza un recorrido Inorden del árbol devolviendo sus elementos.
     * @return Vdinamico<T*> Vector con los punteros a los datos ordenados.
     */
    Vdinamico<T*> recorreInorden() {
        Vdinamico<T*> vectorResultado;
        inorden(raiz, 0, vectorResultado);
        return vectorResultado;
    };
};

    template<class T>
    void Avl<T>::copiaAvl(NodoAVL<T>* &q,NodoAVL<T> *p){
        if (p){
            q= new NodoAVL<T> (p->dato);
            q->bal=p->bal;
            copiaAvl(q->izq,p->izq);
            copiaAvl(q->der,p->der);
        }else
            q=0;
    }

    template<class T>
    NodoAVL<T>* Avl<T>::copiaAvl2(NodoAVL<T> *p){
        if (p){
            NodoAVL<T> *q= new NodoAVL<T> (*p);
            q->izq= copiaAvl2(p->izq);
            q->der= copiaAvl2(p->der);
            return q;
        }else
            return 0;
    }

    template<class T>
    Avl<T>::Avl(const Avl<T>& orig){
        copiaAvl(raiz,orig.raiz);
        tam=orig.tam;
    }

    template<class T>
    Avl<T>& Avl<T>::operator=(const Avl<T>& orig){
        if (this!=&orig){
            destruyeArbol(raiz);
            copiaAvl(raiz,orig.raiz);
            tam=orig.tam;
        }
        return *this;
    }


    template <class T>
    void Avl<T>::inorden (NodoAVL<T>* p, int nivel, Vdinamico<T*> &vectorResultado){
        if (p){
            inorden (p->izq, nivel+1, vectorResultado);
            vectorResultado.insertar(&(p->dato));
            inorden (p->der, nivel+1, vectorResultado);
        }
    }

    template <class T>
    NodoAVL<T> *Avl<T>::buscaClave (const T &dato, NodoAVL<T> *p){
        NodoAVL<T> *nodoActual = p;
        if (!nodoActual)
            return 0;
        else{
            if (dato < nodoActual->dato)
                return buscaClave (dato, nodoActual->izq);
            else if ( nodoActual->dato < dato)
                return buscaClave (dato, nodoActual->der);
            else
                return nodoActual;
        }
    }

    template <class T>
    T* Avl<T>::buscaRec (const T &dato){
        NodoAVL<T> *nodoEncontrado = buscaClave (dato, raiz);
        T* ptrAlDato;
        if (nodoEncontrado){
            ptrAlDato = &(nodoEncontrado->dato);
            return ptrAlDato;
        }
        return 0;
    }

    template <class T>
    T* Avl<T>::buscaIt (const T &dato){
        NodoAVL<T> *nodoActual = raiz;
        T* ptrAlDato;
        while (nodoActual){
            if (dato < nodoActual->dato)
                nodoActual = nodoActual->izq;
            else
                if (nodoActual->dato < dato)
                    nodoActual = nodoActual->der;
                else{
                    ptrAlDato = &(nodoActual->dato);
                    return ptrAlDato;
                }
        }
        return 0;
    }
    template <class T>
    bool Avl<T>::inserta(const T &dato){
        if (buscaRec(dato))
            return false;
        insertaDato(raiz, dato);
        tam++;
        return true;

    }

    template <class T>
    void Avl<T>::destruyeArbol(NodoAVL<T>* &p){
        if (p){
            destruyeArbol(p->izq);
            destruyeArbol(p->der);
            delete p;
            p=0;
        }
    }
    template <class T>
    void Avl<T>::alturaPr(NodoAVL<T>* p, int nivel, int &result){
        int& alturaMax = result;
        NodoAVL<T>* nodoActual = p;

        if (nodoActual){
            alturaPr(nodoActual->izq, nivel+1, alturaMax);
            if (nivel > alturaMax)
                alturaMax = nivel;
            alturaPr(nodoActual->der, nivel+1, alturaMax);
        }
    }

    template <class T>
    unsigned int Avl<T>::altura(){
        int alturaMax = 0;
        alturaPr(raiz, 0, alturaMax);
        return alturaMax;
    }
    template <class T>
    void Avl<T>::rotIzq(NodoAVL<T>* &p) {
        NodoAVL<T> *q = p, *r;
        p = r = q->der;
        q->der = r->izq;
        r->izq = q;

        q->bal++;
        if (r->bal < 0) {
            q->bal += -r->bal;
        }

        r->bal++;
        if (q->bal > 0) {
            r->bal += q->bal;
        }
    }

    template <class T>
    void Avl<T>::rotDer(NodoAVL<T>* &p) {
        NodoAVL<T> *q = p, *l;
        p = l = q->izq;
        q->izq = l->der;
        l->der = q;

        q->bal--;
        if (l->bal > 0) {
            q->bal -= l->bal;
        }

        l->bal--;
        if (q->bal < 0) {
            l->bal -= -q->bal;
        }
    }
template <class T>
int Avl<T>::insertaDato(NodoAVL<T>* &c, const T &dato) {
        NodoAVL<T>* &nodoRef = c;
        NodoAVL<T> *nodoActual = nodoRef;

        int cambioAltura = 0;
        if (!nodoActual) {
            nodoActual = new NodoAVL<T>(dato);
            nodoRef = nodoActual;
            cambioAltura = 1;
        }
        else if (dato < nodoActual->dato) {
            if (insertaDato(nodoActual->izq, dato)) {
                nodoActual->bal++;

                if (nodoActual->bal == 1) {
                    cambioAltura = 1;
                }
                else if (nodoActual->bal == 2) {
                    if (nodoActual->izq->bal == -1) {
                        rotIzq(nodoActual->izq);
                    }
                    rotDer(nodoRef);
                }
            }
        }
        else if (nodoActual->dato < dato) {
            if (insertaDato(nodoActual->der, dato)) {
                nodoActual->bal--;

                if (nodoActual->bal == -1) {
                    cambioAltura = 1;
                }
                else if (nodoActual->bal == -2) {
                    if (nodoActual->der->bal == 1) {
                        rotDer(nodoActual->der);
                    }
                    rotIzq(nodoRef);
                }
            }
        }
        return cambioAltura;
    }
template <class T>
unsigned int Avl<T>::numElementos() {
        return this->tam;
    }

#endif //PR3EEDD_AVL_H