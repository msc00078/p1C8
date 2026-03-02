#ifndef FARMACIA_H_
#define FARMACIA_H_

#include <iostream>
#include "VDinamico.h"
class PaMedicamento;



class MediExpress;

class Farmacia {
public:
    Farmacia();

    Farmacia(const std::string &cif, const std::string &provincia, const std::string &localidad,
             const std::string &nombre, const std::string &direcion,
             const std::string &codPostal, MediExpress* med);

    Farmacia(const Farmacia &orig);

    virtual ~Farmacia();

    const std::string &getCif() const;
    const std::string &getProvincia() const;
    const std::string &getLocalidad() const;
    const std::string &getNombre() const;
    const std::string &getDirecion() const;
    const std::string &getCodPostal() const;

    void setCif(const std::string &cif);
    void setProvincia(const std::string &provincia);
    void setLocalidad(const std::string &localidad);
    void setNombre(const std::string &nombre);
    void setDirecion(const std::string &direcion);
    void setCodPostal(const std::string &codPostal);

    bool operator==(const Farmacia &rhs) const;  //por si acaso
    bool operator<(const Farmacia &rhs) const;   //para buscar en el arbol

    void pedidoMedicam(int id_num);
    PaMedicamento* buscaMedicam(int id_num);
    void dispensaMedicam(PaMedicamento *pa);

    Vdinamico<PaMedicamento*> buscaMedicamentoNombre(std::string nombre);

private:
    std::string cif;
    std::string provincia;
    std::string localidad;
    std::string nombre;
    std::string direcion;
    std::string codPostal;

    Vdinamico<PaMedicamento*> dispense;
    MediExpress*linkMedi;

};

#endif // FARMACIA_H_