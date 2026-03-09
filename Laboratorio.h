/**
 * @file Laboratorio.h
 * @author Asistente de Calidad (assistant@domain.com)
 * @brief Declaración de la clase Laboratorio.
 * @version 0.1
 * @date 2026-03-09
 * * @copyright Copyright (c) 2026
 */
#ifndef PR2EEDD_LABORATORIO_H
#define PR2EEDD_LABORATORIO_H
#include <string>
#include "VDinamico.h"

class PaMedicamento;

/**
 * @class Laboratorio
 * @brief Representa a un laboratorio fabricante de medicamentos.
 * Gestiona los datos básicos del laboratorio y mantiene un registro
 * de los medicamentos que este produce.
 */
class Laboratorio {

    int id;                         ///< Identificador único del laboratorio.
    std::string nombreLab;          ///< Nombre del laboratorio.
    std::string direccionLab;       ///< Dirección física del laboratorio.
    std::string codPostal;          ///< Código postal.
    std::string localidad;          ///< Localidad donde está ubicado.
    Vdinamico<PaMedicamento*> labs; ///< Medicamentos asociados a este laboratorio.

public:
    /**
     * @brief Constructor parametrizado de Laboratorio.
     * @param id Identificador numérico.
     * @param nombre_lab Nombre del laboratorio.
     * @param direccion_lab Dirección física.
     * @param cod_postal Código postal.
     * @param localidad Ciudad o localidad.
     */
    Laboratorio(int id, const std::string &nombre_lab, const std::string &direccion_lab, const std::string &cod_postal,
        const std::string &localidad)
        : id(id),
          nombreLab(nombre_lab),
          direccionLab(direccion_lab),
          codPostal(cod_postal),
          localidad(localidad) {
    }

    /**
     * @brief Obtiene el ID del laboratorio.
     * @return int Identificador único.
     */
    [[nodiscard]] int get_id() const {
        return id;
    }

    /**
     * @brief Establece el ID del laboratorio.
     * @param id Nuevo identificador.
     */
    void set_id(int id) {
        this->id = id;
    }

    /**
     * @brief Obtiene el nombre del laboratorio.
     * @return std::string Nombre del laboratorio.
     */
    [[nodiscard]] std::string get_nombre_lab() const {
        return nombreLab;
    }

    /**
     * @brief Establece el nombre del laboratorio.
     * @param nombre_lab Nuevo nombre.
     */
    void set_nombre_lab(const std::string &nombre_lab) {
        nombreLab = nombre_lab;
    }

    /**
     * @brief Obtiene la dirección del laboratorio.
     * @return std::string Dirección.
     */
    [[nodiscard]] std::string get_direccion_lab() const {
        return direccionLab;
    }

    /**
     * @brief Establece la dirección del laboratorio.
     * @param direccion_lab Nueva dirección.
     */
    void set_direccion_lab(const std::string &direccion_lab) {
        direccionLab = direccion_lab;
    }

    /**
     * @brief Obtiene el código postal del laboratorio.
     * @return std::string Código postal.
     */
    [[nodiscard]] std::string get_cod_postal() const {
        return codPostal;
    }

    /**
     * @brief Establece el código postal del laboratorio.
     * @param cod_postal Nuevo código postal.
     */
    void set_cod_postal(const std::string &cod_postal) {
        codPostal = cod_postal;
    }

    /**
     * @brief Obtiene la localidad del laboratorio.
     * @return std::string Localidad.
     */
    [[nodiscard]] std::string get_localidad() const {
        return localidad;
    }

    /**
     * @brief Establece la localidad del laboratorio.
     * @param localidad Nueva localidad.
     */
    void set_localidad(const std::string &localidad) {
        this->localidad = localidad;
    }

    /**
     * @brief Constructor de copia.
     * @param other Objeto Laboratorio original a copiar.
     */
    Laboratorio(const Laboratorio &other)
        : id(other.id),
          nombreLab(other.nombreLab),
          direccionLab(other.direccionLab),
          codPostal(other.codPostal),
          localidad(other.localidad) {
    }

    /**
     * @brief Constructor de movimiento.
     * @param other Objeto Laboratorio a mover.
     */
    Laboratorio(Laboratorio &&other) noexcept
        : id(other.id),
          nombreLab(std::move(other.nombreLab)),
          direccionLab(std::move(other.direccionLab)),
          codPostal(std::move(other.codPostal)),
          localidad(std::move(other.localidad)) {
    }

    /**
     * @brief Sobrecarga del operador de asignación (copia).
     * @param other Laboratorio a asignar.
     * @return Laboratorio& Referencia al laboratorio actual.
     */
    Laboratorio & operator=(const Laboratorio &other) {
        if (this == &other)
            return *this;
        id = other.id;
        nombreLab = other.nombreLab;
        direccionLab = other.direccionLab;
        codPostal = other.codPostal;
        localidad = other.localidad;
        return *this;
    }

    /**
     * @brief Sobrecarga del operador de asignación (movimiento).
     * @param other Laboratorio a mover.
     * @return Laboratorio& Referencia al laboratorio actual.
     */
    Laboratorio & operator=(Laboratorio &&other) noexcept {
        if (this == &other)
            return *this;
        id = other.id;
        nombreLab = std::move(other.nombreLab);
        direccionLab = std::move(other.direccionLab);
        codPostal = std::move(other.codPostal);
        localidad = std::move(other.localidad);
        return *this;
    }
};

#endif //PR2EEDD_LABORATORIO_H