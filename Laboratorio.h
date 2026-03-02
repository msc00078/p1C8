#ifndef PR2EEDD_LABORATORIO_H
#define PR2EEDD_LABORATORIO_H
#include <string>


class Laboratorio {

    int id;
    std::string nombreLab;
    std::string direccionLab;
    std::string codPostal;
    std::string localidad;

public:
    Laboratorio(int id, const std::string &nombre_lab, const std::string &direccion_lab, const std::string &cod_postal,
        const std::string &localidad)
        : id(id),
          nombreLab(nombre_lab),
          direccionLab(direccion_lab),
          codPostal(cod_postal),
          localidad(localidad) {
    }

    [[nodiscard]] int get_id() const {
        return id;
    }

    void set_id(int id) {
        this->id = id;
    }

    [[nodiscard]] std::string get_nombre_lab() const {
        return nombreLab;
    }

    void set_nombre_lab(const std::string &nombre_lab) {
        nombreLab = nombre_lab;
    }

    [[nodiscard]] std::string get_direccion_lab() const {
        return direccionLab;
    }

    void set_direccion_lab(const std::string &direccion_lab) {
        direccionLab = direccion_lab;
    }

    [[nodiscard]] std::string get_cod_postal() const {
        return codPostal;
    }

    void set_cod_postal(const std::string &cod_postal) {
        codPostal = cod_postal;
    }

    [[nodiscard]] std::string get_localidad() const {
        return localidad;
    }

    void set_localidad(const std::string &localidad) {
        this->localidad = localidad;
    }

    Laboratorio(const Laboratorio &other)
        : id(other.id),
          nombreLab(other.nombreLab),
          direccionLab(other.direccionLab),
          codPostal(other.codPostal),
          localidad(other.localidad) {
    }

    Laboratorio(Laboratorio &&other) noexcept
        : id(other.id),
          nombreLab(std::move(other.nombreLab)),
          direccionLab(std::move(other.direccionLab)),
          codPostal(std::move(other.codPostal)),
          localidad(std::move(other.localidad)) {
    }

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