#ifndef VDINAMICO_H
#define VDINAMICO_H

#include <stdexcept>
#include <iostream>
#include <algorithm>

template<class T>
class Vdinamico {
private:
    T *v;                // Puntero al array de datos
    unsigned long int tamal;   // Tamaño Lógico (elementos reales)
    unsigned long int tamaf;   // Tamaño Físico (capacidad del array v)


public:

    void tamabase2(unsigned long int &tama);
    void redimensionar();
    void ordenar();
    void insertar(const T& dato, unsigned int pos = UINT_MAX);
    unsigned long int tamlog() const;

    Vdinamico();

    Vdinamico(unsigned long int tama);

    Vdinamico(const Vdinamico<T> &orig);

    Vdinamico(const Vdinamico<T>& origen, unsigned long int inicio, unsigned long int num);

    ~Vdinamico(); 

    Vdinamico<T> &operator=(const Vdinamico<T> &arr);
    
    unsigned long int size() const { return tamal; }
    unsigned long int capacity() const { return tamaf; }


T &operator[](unsigned long int pos);
};


//IMPLEMENTACIONES

template<class T>
void Vdinamico<T>::tamabase2(unsigned long int &tama) { //Cambiar el tamaño por potenciabase2
    if (tama == 0) {
        tama = 1;
        return;
    }
    unsigned long int p = 1;
    while (p < tama) {
        p = p * 2;
    }
    tama = p;
}


template<class T>
Vdinamico<T>::Vdinamico(){
    tamal=0;
    v = new T[tamaf = 1];
};

template<class T>
Vdinamico<T>::Vdinamico(unsigned long int tama){
    tamal=0;
    tamabase2(tama);
    v = new T[tamaf = tama];
};
//Constructor de copia
template<class T>
Vdinamico<T>::Vdinamico(const Vdinamico<T> &orig): tamal(orig.tamal){
    v = new T[tamaf = orig.tamaf];
    for (unsigned long int i=0; i<tamal; i++)
        v[i] = orig.v[i];
};
//Constructor parcial
template<class T>
Vdinamico<T>::Vdinamico(const Vdinamico<T>& origen, unsigned long int inicio,unsigned long int num){
    if (inicio>=origen.tamal || num>origen.tamal || inicio+num>origen.tamal)
        throw std::out_of_range("Posicion incorrecta");
    
    unsigned long int nuevotama=num;
    tamabase2(nuevotama);
    
    v = new T[tamaf = nuevotama];
    tamal=num;
    for (unsigned long int c = inicio; c <inicio+num; c++) {
        v[c-inicio] = origen.v[c];
    }
}

// Operador de Asignación

template<class T>
Vdinamico<T> &Vdinamico<T>::operator=(const Vdinamico<T> &arr){
    if (this!=&arr){
        // 1. Liberar memoria antigua
        delete[] v;
        
        // 2. Copiar tamaños y reservar nueva memoria
        tamal = arr.tamal;
        v = new T[tamaf=arr.tamaf];
        
        // 3. Copiar elementos
        for (unsigned long int c = 0; c < tamal; c++) {
            v[c] = arr.v[c];
        }
    }
    return *this;
};

template<class T>
T &Vdinamico<T>::operator[](unsigned long int pos) {
    if (pos >= tamal) {
        throw std::out_of_range("Indice fuera de los limites del vector.");
    }
    return v[pos];
}

template<class T>
void Vdinamico<T>::redimensionar() {

    unsigned long int nuevo_tamaf = tamaf * 2;

    T *v_nuevo = new T[nuevo_tamaf];

    for (unsigned long int i = 0; i < tamal; i++) {
        v_nuevo[i] = v[i];
    }

    delete[] v; //Liberar array antiguo
    v = v_nuevo;
    tamaf = nuevo_tamaf;
}

template<class T>
void Vdinamico<T>::insertar(const T& dato, unsigned int pos) {

    if (pos == UINT_MAX || pos == tamal) { //Si no se pasa pos,se inserta en el ultimo elemento
        pos = tamal;
    }
    if (pos > tamal) {
        throw std::out_of_range("Posicion de insercion invalida.");
    }

    if (tamal == tamaf) {
        redimensionar();
    }

    for (unsigned long int i = tamal; i > pos; i--) {
        v[i] = v[i - 1];
    }

    v[pos] = dato;
    tamal++;
}

template<class T>
void Vdinamico<T>::ordenar() {

    std::sort(v, v + tamal); //Se compara el primer elemento y el ultimo
}

template<class T>
unsigned long int Vdinamico<T>::tamlog() const {
    return tamal;
}

template<class T>
Vdinamico<T>::~Vdinamico(){
    delete[] v;
    v = nullptr; // Buena práctica
    tamal = 0;
    tamaf = 0;
}




#endif // VDINAMICO_H