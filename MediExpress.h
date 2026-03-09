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
     * @brief Constructor por defecto de la clase MediExpress.
     */
    MediExpress();

    /**
     * @brief Constructor parametrizado que carga los datos del sistema desde archivos.
     * @param nomFichPaMed Nombre del archivo de principios activos/medicamentos.
     * @param nomFichLab Nombre del archivo de laboratorios.
     * @param nomFichFar Nombre del archivo de farmacias.
     */
    MediExpress(const string &nomFichPaMed, const string &nomFichLab, const string &nomFichFar);

    /**
     * @brief Asigna un medicamento a un laboratorio para su suministro.
     * @param pa Puntero al medicamento a asignar.
     * @param l Puntero al laboratorio que suministrará el medicamento.
     */
    void suministrarMed(PaMedicamento* pa, Laboratorio* l);

    /**
     * @brief Busca un laboratorio registrado por su nombre exacto.
     * @param nombreLab Nombre del laboratorio a buscar.
     * @return Laboratorio* Puntero al laboratorio si se encuentra, 0 (nullptr) en caso contrario.
     */
    Laboratorio* buscarLab(const string &nombreLab);

    /**
     * @brief Busca todos los laboratorios ubicados en una ciudad específica.
     * @param nombreCiudad Nombre de la localidad/ciudad a consultar.
     * @return Vdinamico<Laboratorio*> Vector dinámico con los laboratorios encontrados.
     */
    Vdinamico<Laboratorio*> buscarLabCiudad(const string &nombreCiudad);

    /**
     * @brief Busca medicamentos (compuestos) por el nombre de su principio activo.
     * @param nombrePA Nombre del principio activo a buscar.
     * @return Vdinamico<PaMedicamento*> Vector dinámico con los medicamentos coincidentes.
     */
    Vdinamico<PaMedicamento*> buscarCompuesto(const string &nombrePA);

    /**
     * @brief Busca un medicamento específico a través de su identificador numérico.
     * @param id_num Identificador numérico único del medicamento.
     * @return PaMedicamento* Puntero al medicamento si se encuentra, 0 en caso contrario.
     */
    PaMedicamento* buscarCompuesto(int id_num);

    /**
     * @brief Obtiene una lista de todos los medicamentos que aún no tienen un laboratorio asignado.
     * @return Vdinamico<PaMedicamento*> Vector dinámico con los medicamentos "huérfanos".
     */
    Vdinamico<PaMedicamento*> getMedicamentoSinLab();

    /**
     * @brief Suministra un medicamento específico a una farmacia.
     * @param f Puntero a la farmacia destino.
     * @param id_num Identificador numérico del medicamento a suministrar.
     */
    void suministrarFarmacia(Farmacia* f, int id_num);

    /**
     * @brief Busca una farmacia en el sistema a través de su Código de Identificación Fiscal (CIF).
     * @param cif CIF de la farmacia a buscar.
     * @return Farmacia* Puntero a la farmacia si se encuentra en el árbol AVL, 0 si no existe.
     */
    Farmacia* buscarFarmacia(const string &cif);

    /**
     * @brief Busca qué laboratorios fabrican un principio activo específico.
     * @param nombrePA Nombre del principio activo.
     * @return Vdinamico<Laboratorio*> Vector dinámico con los laboratorios que lo suministran.
     */
    Vdinamico<Laboratorio*> buscarLabs(const string &nombrePA);


private:
    Vdinamico<PaMedicamento> medication;    ///< Colección de todos los medicamentos registrados en el sistema.
    ListaEnlazada<Laboratorio> labs;        ///< Lista enlazada que gestiona los laboratorios disponibles.
    Avl<Farmacia> pharmacy;                 ///< Árbol AVL para el almacenamiento y búsqueda rápida de farmacias.
};

#endif