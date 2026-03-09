/**
 * @file PaMedicamento.h
 * @author Asistente de Calidad (assistant@domain.com)
 * @brief Declaración de la clase PaMedicamento.
 * @version 0.1
 * @date 2026-03-09
 * * @copyright Copyright (c) 2026
 */
#ifndef PR1EEDD_PAMEDICAMENTO_H
#define PR1EEDD_PAMEDICAMENTO_H

#include <string>

class Laboratorio;
class Farmacia;

using namespace std;

/**
 * @class PaMedicamento
 * @brief Representa un medicamento o principio activo.
 * Gestiona la información básica de un medicamento, incluyendo sus
 * identificadores y el laboratorio que lo fabrica o suministra.
 */
class PaMedicamento {
private:
    int id_num;             ///< Identificador numérico único del medicamento.
    std::string id_alpha;   ///< Código alfanumérico del medicamento.
    std::string nombre;     ///< Nombre descriptivo o principio activo.
    Laboratorio* lab;       ///< Puntero al laboratorio que lo suministra.

public:
    /**
     * @brief Constructor por defecto de la clase PaMedicamento.
     */
    PaMedicamento() = default;

    /**
     * @brief Constructor parametrizado de la clase PaMedicamento.
     * @param id_num Identificador numérico.
     * @param id_alpha Código alfanumérico.
     * @param nombre Nombre del medicamento.
     */
    PaMedicamento(int id_num, const std::string &id_alpha, const std::string &nombre)
        : id_num(id_num),
          id_alpha(id_alpha),
          nombre(nombre),
          lab(nullptr) {
    }

    /**
     * @brief Obtiene el identificador numérico del medicamento.
     * @return int Identificador numérico.
     */
    [[nodiscard]] int get_id_num() const {
        return id_num;
    }

    /**
     * @brief Obtiene el identificador alfanumérico.
     * @return std::string Código alfanumérico.
     */
    [[nodiscard]] std::string get_id_alpha() const {
        return id_alpha;
    }

    /**
     * @brief Obtiene el nombre del medicamento.
     * @return std::string Nombre del medicamento.
     */
    [[nodiscard]] std::string get_nombre() const {
        return nombre;
    }

    /**
     * @brief Establece un nuevo identificador numérico.
     * @param id_num Nuevo identificador numérico.
     */
    void set_id_num(int id_num) {
        this->id_num = id_num;
    }

    /**
     * @brief Establece un nuevo identificador alfanumérico.
     * @param id_alpha Nuevo identificador alfanumérico.
     */
    void set_id_alpha(const std::string &id_alpha) {
        this->id_alpha = id_alpha;
    }

    /**
     * @brief Establece un nuevo nombre para el medicamento.
     * @param nombre Nuevo nombre.
     */
    void set_nombre(const std::string &nombre) {
        this->nombre = nombre;
    }

    /**
     * @brief Obtiene el laboratorio asociado al medicamento.
     * @return Laboratorio* Puntero al laboratorio suministrador.
     */
    [[nodiscard]] Laboratorio * lab1() const {
        return lab;
    }

    /**
     * @brief Asigna un laboratorio suministrador a este medicamento.
     * @param l Puntero al nuevo laboratorio.
     */
    void set_lab(Laboratorio *l) {
        this->lab = l;
    }

    /**
     * @brief Sobrecarga del operador de igualdad.
     * @param lhs Operando izquierdo.
     * @param rhs Operando derecho.
     * @return bool True si son iguales en ID y nombre.
     */
    friend bool operator==(const PaMedicamento &lhs, const PaMedicamento &rhs) {
        return lhs.id_num == rhs.id_num
               && lhs.id_alpha == rhs.id_alpha
               && lhs.nombre == rhs.nombre;
    }

    /**
     * @brief Sobrecarga del operador de inserción para ordenamiento.
     * @param lhs Operando izquierdo.
     * @param rhs Operando derecho.
     * @return bool True si lhs es estrictamente menor que rhs.
     */
    friend bool operator<<(const PaMedicamento &lhs, const PaMedicamento &rhs) {
        if (lhs.id_num < rhs.id_num)
            return true;
        if (rhs.id_num < lhs.id_num)
            return false;
        if (lhs.id_alpha < rhs.id_alpha)
            return true;
        if (rhs.id_alpha < lhs.id_alpha)
            return false;
        return lhs.nombre < rhs.nombre;
    }

    /**
     * @brief Sobrecarga del operador menor o igual.
     */
    friend bool operator<=(const PaMedicamento &lhs, const PaMedicamento &rhs) {
        return !(rhs < lhs);
    }

    /**
     * @brief Sobrecarga del operador mayor.
     */
    friend bool operator>(const PaMedicamento &lhs, const PaMedicamento &rhs) {
        return rhs < lhs;
    }

    /**
     * @brief Sobrecarga del operador mayor o igual.
     */
    friend bool operator>=(const PaMedicamento &lhs, const PaMedicamento &rhs) {
        return !(lhs < rhs);
    }

    /**
     * @brief Sobrecarga del operador de desigualdad.
     */
    friend bool operator!=(const PaMedicamento &lhs, const PaMedicamento &rhs) {
        return !(lhs == rhs);
    }

    /**
     * @brief Sobrecarga del operador de flujo de salida.
     * @param os Flujo de salida.
     * @param pm Medicamento a imprimir.
     * @return std::ostream& Referencia al flujo.
     */
    friend std::ostream& operator<<(std::ostream& os, const PaMedicamento& pm) {
        os << "[ID N: " << pm.id_num
           << " | ID A: " << pm.id_alpha
           << " | Nombre: " << pm.nombre << "]";
        return os;
    }

    /**
     * @brief Compara si este medicamento es menor que otro basándose en su ID numérico.
     * @param otro Medicamento a comparar.
     * @return bool True si el ID de este es menor que el de 'otro'.
     */
    bool operator<(const PaMedicamento& otro) const {
        return this->id_num < otro.get_id_num();
    }

    /**
     * @brief Verifica si este medicamento es servido por un laboratorio específico.
     * @param l Laboratorio a comprobar.
     * @return bool True si el laboratorio 'l' sirve este medicamento.
     */
    bool servidoPor( Laboratorio& l)  {
        if (lab == nullptr) {
            return false;
        }
        return lab->get_id() == l.get_id();
    }
};

#endif //PR1EEDD_PAMEDICAMENTO_H