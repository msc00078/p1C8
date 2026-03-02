#ifndef PR3EEDD_AVL_H
#define PR3EEDD_AVL_H

#include "VDinamico.h"


template <class T>
class NodoAVL
{
public:
    NodoAVL<T> *izq;
    NodoAVL<T> *der;
    char bal;
    T dato;

    NodoAVL(const T &ele): izq(0), der(0), bal(0), dato(ele){}
    NodoAVL(const NodoAVL<T> &orig): izq(orig.izq), der(orig.der), bal(orig.bal), dato(orig.dato){}
};

template <class T>
class Avl {
    NodoAVL<T> *raiz;
    unsigned int tam;

    void inorden(NodoAVL<T>* p, int nivel, Vdinamico<T*> &vectorResultado);

    NodoAVL<T> *buscaClave ( const T &dato, NodoAVL<T> *p);

    int insertaDato(NodoAVL<T>* &c, const T &dato);

    void destruyeArbol(NodoAVL<T>* &p);

    void rotDer(NodoAVL<T>* &p);
    void rotIzq(NodoAVL<T>* &p);

    void copiaAvl(NodoAVL<T>* &q, NodoAVL<T> *p);
    NodoAVL<T>* copiaAvl2(NodoAVL<T> *p);

    unsigned int numElementosPr(NodoAVL<T>* p);

    void alturaPr(NodoAVL<T>* p, int nivel, int &result);
    unsigned alturaPr2(NodoAVL<T>* p);

public:

    Avl() : raiz(0), tam(0) {}
    Avl(const Avl<T>& orig);
    Avl<T>& operator=(const Avl<T>& orig);

    T* buscaRec (const T &dato);
    T* buscaIt(const T &dato);
    bool inserta(const T &dato);

    unsigned int numElementos();
    unsigned int altura();
    unsigned int altura2();
    unsigned int getTam(){ return tam;};

    ~Avl(){
        destruyeArbol(raiz);
    };

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