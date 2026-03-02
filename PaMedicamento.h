
#ifndef PR1EEDD_PAMEDICAMENTO_H
#define PR1EEDD_PAMEDICAMENTO_H

#include <string>

class Laboratorio;
class Farmacia;


using namespace std;

class PaMedicamento {
private:

    int id_num;
    std::string id_alpha;
    std::string nombre;
    Laboratorio* lab;

public:
    PaMedicamento() = default;

    PaMedicamento(int id_num, const std::string &id_alpha, const std::string &nombre)
        : id_num(id_num),
          id_alpha(id_alpha),
          nombre(nombre),
          lab(nullptr) {
    }

    [[nodiscard]] int get_id_num() const {
        return id_num;
    }

    [[nodiscard]] std::string get_id_alpha() const {
        return id_alpha;
    }

    [[nodiscard]] std::string get_nombre() const {
        return nombre;
    }

    void set_id_num(int id_num) {
        this->id_num = id_num;
    }

    void set_id_alpha(const std::string &id_alpha) {
        this->id_alpha = id_alpha;
    }

    void set_nombre(const std::string &nombre) {
        this->nombre = nombre;
    }
    [[nodiscard]] Laboratorio * lab1() const {
        return lab;
    }

    void set_lab(Laboratorio *l) {
        this->lab = l;
    }

    friend bool operator==(const PaMedicamento &lhs, const PaMedicamento &rhs) {
        return lhs.id_num == rhs.id_num
               && lhs.id_alpha == rhs.id_alpha
               && lhs.nombre == rhs.nombre;
    }

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

    friend bool operator<=(const PaMedicamento &lhs, const PaMedicamento &rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>(const PaMedicamento &lhs, const PaMedicamento &rhs) {
        return rhs < lhs;
    }

    friend bool operator>=(const PaMedicamento &lhs, const PaMedicamento &rhs) {
        return !(lhs < rhs);
    }

    friend bool operator!=(const PaMedicamento &lhs, const PaMedicamento &rhs) {
        return !(lhs == rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const PaMedicamento& pm) {
        os << "[ID N: " << pm.id_num
           << " | ID A: " << pm.id_alpha
           << " | Nombre: " << pm.nombre << "]";
        return os;
    }

    bool operator<(const PaMedicamento& otro) const {
        return this->id_num < otro.get_id_num();
    }

    bool servidoPor( Laboratorio& l)  {
        if (lab == nullptr) {
            return false;
        }
        return lab->get_id() == l.get_id();
    }


};
























#endif //PR1EEDD_PAMEDICAMENTO_H