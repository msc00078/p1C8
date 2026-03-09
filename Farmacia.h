/**
 * @file Farmacia.h
 * @author Asistente de Calidad (assistant@domain.com)
 * @brief Declaración de la clase Farmacia.
 * @version 0.1
 * @date 2026-03-09
 * * @copyright Copyright (c) 2026
 */
#ifndef FARMACIA_H_
#define FARMACIA_H_

#include <iostream>
#include "VDinamico.h"

class PaMedicamento;
class MediExpress;

/**
 * @class Farmacia
 * @brief Gestiona la información y las operaciones de una farmacia.
 * Se encarga de administrar los datos de la sucursal, así como de buscar,
 * dispensar y realizar pedidos de medicamentos.
 */
class Farmacia {
public:
    /**
     * @brief Constructor por defecto de la clase Farmacia.
     */
    Farmacia();

    /**
     * @brief Constructor parametrizado de la clase Farmacia.
     * @param cif CIF de la farmacia.
     * @param provincia Provincia donde se ubica.
     * @param localidad Localidad donde se ubica.
     * @param nombre Nombre de la farmacia.
     * @param direcion Dirección física.
     * @param codPostal Código postal.
     * @param med Puntero al sistema central MediExpress.
     */
    Farmacia(const std::string &cif, const std::string &provincia, const std::string &localidad,
             const std::string &nombre, const std::string &direcion,
             const std::string &codPostal, MediExpress* med);

    /**
     * @brief Constructor de copia.
     * @param orig Objeto Farmacia original a copiar.
     */
    Farmacia(const Farmacia &orig);

    /**
     * @brief Destructor virtual de la clase Farmacia.
     */
    virtual ~Farmacia();
    
    /**
     * @brief Obtiene el CIF de la farmacia.
     * @return const std::string& Referencia al CIF.
     */
    const std::string &getCif() const;

    /**
     * @brief Obtiene la provincia de la farmacia.
     * @return const std::string& Referencia a la provincia.
     */
    const std::string &getProvincia() const;

    /**
     * @brief Obtiene la localidad de la farmacia.
     * @return const std::string& Referencia a la localidad.
     */
    const std::string &getLocalidad() const;

    /**
     * @brief Obtiene el nombre de la farmacia.
     * @return const std::string& Referencia al nombre.
     */
    const std::string &getNombre() const;

    /**
     * @brief Obtiene la dirección de la farmacia.
     * @return const std::string& Referencia a la dirección.
     */
    const std::string &getDirecion() const;

    /**
     * @brief Obtiene el código postal de la farmacia.
     * @return const std::string& Referencia al código postal.
     */
    const std::string &getCodPostal() const;

    /**
     * @brief Establece el CIF de la farmacia.
     * @param cif Nuevo CIF.
     */
    void setCif(const std::string &cif);

    /**
     * @brief Establece la provincia de la farmacia.
     * @param provincia Nueva provincia.
     */
    void setProvincia(const std::string &provincia);

    /**
     * @brief Establece la localidad de la farmacia.
     * @param localidad Nueva localidad.
     */
    void setLocalidad(const std::string &localidad);

    /**
     * @brief Establece el nombre de la farmacia.
     * @param nombre Nuevo nombre.
     */
    void setNombre(const std::string &nombre);

    /**
     * @brief Establece la dirección de la farmacia.
     * @param direcion Nueva dirección.
     */
    void setDirecion(const std::string &direcion);

    /**
     * @brief Establece el código postal de la farmacia.
     * @param codPostal Nuevo código postal.
     */
    void setCodPostal(const std::string &codPostal);

    /**
     * @brief Sobrecarga del operador de igualdad.
     * @param rhs Farmacia a comparar.
     * @return bool True si son iguales, False en caso contrario.
     */
    bool operator==(const Farmacia &rhs) const;

    /**
     * @brief Sobrecarga del operador menor que, útil para inserción en árboles.
     * @param rhs Farmacia a comparar.
     * @return bool True si es menor, False en caso contrario.
     */
    bool operator<(const Farmacia &rhs) const;

    /**
     * @brief Realiza el pedido de un medicamento por su ID.
     * @param id_num Identificador numérico del medicamento a pedir.
     */
    void pedidoMedicam(int id_num);

    /**
     * @brief Busca un medicamento en el inventario por su ID.
     * @param id_num Identificador numérico del medicamento.
     * @return PaMedicamento* Puntero al medicamento si se encuentra, 0 o nullptr si no.
     */
    PaMedicamento* buscaMedicam(int id_num);

    /**
     * @brief Dispensa un medicamento específico.
     * @param pa Puntero al medicamento a dispensar.
     */
    void dispensaMedicam(PaMedicamento *pa);

    /**
     * @brief Busca medicamentos por nombre parcial o total.
     * @param nombre Nombre a buscar.
     * @return Vdinamico<PaMedicamento*> Vector dinámico con los punteros a los medicamentos encontrados.
     */
    Vdinamico<PaMedicamento*> buscaMedicamentoNombre(std::string nombre);

    /**
     * @brief Sobrecarga del operador de asignación.
     * @param other Farmacia a asignar.
     * @return Farmacia& Referencia a la farmacia actual.
     */
    Farmacia& operator=(const Farmacia& other); 

private:
    std::string cif;       ///< Código de Identificación Fiscal.
    std::string provincia; ///< Provincia de ubicación.
    std::string localidad; ///< Localidad de ubicación.
    std::string nombre;    ///< Nombre comercial de la farmacia.
    std::string direcion;  ///< Dirección postal física.
    std::string codPostal; ///< Código postal.

    Vdinamico<PaMedicamento*> dispense; ///< Vector de medicamentos dispensados/disponibles.
    MediExpress* linkMedi;              ///< Enlace al sistema gestor central.
};

#endif // FARMACIA_H_