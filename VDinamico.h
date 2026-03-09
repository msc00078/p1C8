/**
 * @file VDinamico.h
 * @author Asistente de Calidad (assistant@domain.com)
 * @brief Declaración e implementación de la plantilla de clase Vdinamico.
 * @version 0.1
 * @date 2026-03-09
 * * @copyright Copyright (c) 2026
 */
#ifndef VDINAMICO_H
#define VDINAMICO_H

#include <stdexcept>
#include <iostream>
#include <algorithm>

/**
 * @class Vdinamico
 * @brief Implementa un vector dinámico genérico.
 * Gestiona de forma automática la memoria dinámica, redimensionando
 * el espacio de almacenamiento físico según el crecimiento lógico de datos.
 */
template<class T>
class Vdinamico {
private:
    T *v;                      ///< Puntero al array de datos genéricos.
    unsigned long int tamal;   ///< Tamaño Lógico (número de elementos reales almacenados).
    unsigned long int tamaf;   ///< Tamaño Físico (capacidad actual de memoria reservada).


public:

    /**
     * @brief Ajusta un tamaño dado a la potencia de 2 inmediatamente superior.
     * @param tama Referencia al tamaño a ajustar.
     */
    void tamabase2(unsigned long int &tama);

    /**
     * @brief Redimensiona el tamaño físico del vector multiplicándolo por 2.
     */
    void redimensionar();

    /**
     * @brief Ordena internamente los elementos del vector.
     */
    void ordenar();

    /**
     * @brief Inserta un dato en una posición concreta.
     * @param dato Dato a insertar.
     * @param pos Posición donde insertar (por defecto al final).
     */
    void insertar(const T& dato, unsigned int pos = UINT_MAX);

    /**
     * @brief Devuelve el tamaño lógico actual del vector.
     * @return unsigned long int Tamaño lógico.
     */
    unsigned long int tamlog() const;

    /**
     * @brief Constructor por defecto. Inicializa un vector vacío.
     */
    Vdinamico();

    /**
     * @brief Constructor que reserva un tamaño inicial específico.
     * @param tama Tamaño físico inicial deseado.
     */
    Vdinamico(unsigned long int tama);

    /**
     * @brief Constructor de copia.
     * @param orig Vector dinámico original.
     */
    Vdinamico(const Vdinamico<T> &orig);

    /**
     * @brief Constructor parcial que copia un segmento de otro vector.
     * @param origen Vector origen.
     * @param inicio Índice desde donde empezar a copiar.
     * @param num Cantidad de elementos a copiar.
     */
    Vdinamico(const Vdinamico<T>& origen, unsigned long int inicio, unsigned long int num);

    /**
     * @brief Destructor del vector dinámico.
     */
    ~Vdinamico(); 

    /**
     * @brief Sobrecarga del operador de asignación.
     * @param arr Vector dinámico a asignar.
     * @return Vdinamico<T>& Referencia al vector actual.
     */
    Vdinamico<T> &operator=(const Vdinamico<T> &arr);
    
    /**
     * @brief Obtiene el tamaño lógico.
     * @return unsigned long int Tamaño lógico.
     */
    unsigned long int size() const { return tamal; }

    /**
     * @brief Obtiene la capacidad (tamaño físico).
     * @return unsigned long int Tamaño físico.
     */
    unsigned long int capacity() const { return tamaf; }

    /**
     * @brief Sobrecarga del operador de acceso.
     * @param pos Índice del elemento.
     * @return T& Referencia al elemento en la posición dada.
     */
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