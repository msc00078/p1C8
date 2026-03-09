/**
 * @file MediExpress.h
 * @author Asistente de Calidad (assistant@domain.com)
 * @brief Declaración de la clase MediExpress.
 * @version 0.1
 * @date 2026-03-09
 * * @copyright Copyright (c) 2026
 */
#ifndef MEDIEXPRESS_H
#define MEDIEXPRESS_H

#include <string>
#include "Avl.h"
#include "Laboratorio.h"
#include "PaMedicamento.h"
#include "Farmacia.h"
#include "ListaEnlazada.h"
#include "VDinamico.h"

using namespace std;

/**
 * @class MediExpress
 * @brief Sistema central de gestión para medicamentos, laboratorios y farmacias.
 * Actúa como la fachada principal del sistema para coordinar el suministro
 * de medicamentos entre los laboratorios que los fabrican y las farmacias.
 */
class MediExpress {
public:
    /**
     * @brief Constructor por defecto de MediExpress.
     */
    MediExpress();

    /**
     * @brief Constructor parametrizado que carga datos desde archivos.
     * @param nomFichPaMed Ruta al archivo CSV de medicamentos.
     * @param nomFichLab Ruta al archivo CSV de laboratorios.
     * @param nomFichFar Ruta al archivo CSV de farmacias.
     */
    MediExpress(const string &nomFichPaMed, const string &nomFichLab, const string &nomFichFar);

    /**
     * @brief Asigna un medicamento a un laboratorio que lo suministrará.
     * @param pa Puntero al medicamento.
     * @param l Puntero al laboratorio suministrador.
     */
    void suministrarMed(PaMedicamento* pa, Laboratorio* l);

    /**
     * @brief Busca un laboratorio por su nombre.
     * @param nombreLab Nombre exacto del laboratorio.
     * @return Laboratorio* Puntero al laboratorio encontrado, o 0 si no existe.
     */
    Laboratorio* buscarLab(const string &nombreLab);

    /**
     * @brief Busca todos los laboratorios ubicados en una ciudad específica.
     * @param nombreCiudad Nombre de la ciudad.
     * @return Vdinamico<Laboratorio*> Vector con los laboratorios encontrados.
     */
    Vdinamico<Laboratorio*> buscarLabCiudad(const string &nombreCiudad);

    /**
     * @brief Busca medicamentos (compuestos) por el nombre del principio activo.
     * @param nombrePA Nombre del principio activo.
     * @return Vdinamico<PaMedicamento*> Vector de medicamentos coincidentes.
     */
    Vdinamico<PaMedicamento*> buscarCompuesto(const string &nombrePA);

    /**
     * @brief Busca un compuesto específico por su identificador numérico.
     * @param id_num Identificador numérico del medicamento.
     * @return PaMedicamento* Puntero al medicamento si se encuentra, 0 en caso contrario.
     */
    PaMedicamento* buscarCompuesto(int id_num);

    /**
     * @brief Obtiene una lista de todos los medicamentos que no tienen un laboratorio asignado.
     * @return Vdinamico<PaMedicamento*> Vector con los medicamentos "huérfanos".
     */
    Vdinamico<PaMedicamento*> getMedicamentoSinLab();

    /**
     * @brief Suministra un medicamento específico a una farmacia.
     * @param f Puntero a la farmacia destino.
     * @param id_num Identificador numérico del medicamento a suministrar.
     */
    void suministrarFarmacia(Farmacia* f, int id_num);

    /**
     * @brief Busca una farmacia registrada en el sistema por su CIF.
     * @param cif CIF de la farmacia a buscar.
     * @return Farmacia* Puntero a la farmacia si se encuentra, 0 si no.
     */
    Farmacia* buscarFarmacia(const string &cif);

    /**
     * @brief Obtiene una lista de laboratorios que fabrican un principio activo específico.
     * @param nombrePA Nombre del principio activo.
     * @return Vdinamico<Laboratorio*> Vector de laboratorios suministradores.
     */
    Vdinamico<Laboratorio*> buscarLabs(const string &nombrePA);

private:
    Vdinamico<PaMedicamento> medication; ///< Colección de todos los medicamentos registrados.
    ListaEnlazada<Laboratorio> labs;     ///< Lista enlazada de los laboratorios del sistema.
    Avl<Farmacia> pharmacy;              ///< Árbol AVL para la búsqueda rápida de farmacias.
};

#endif