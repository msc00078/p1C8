#include "Farmacia.h"
#include "MediExpress.h"

Farmacia::Farmacia() :
        cif("-"),
        provincia("-"),
        localidad("-"),
        nombre("-"),
        direcion("-"),
        codPostal("-"),
        dispense(),
        linkMedi(0){}

Farmacia::Farmacia(const std::string &cif, const std::string &provincia, const std::string &localidad,
                   const std::string &nombre, const std::string &direcion,
                   const std::string &codPostal, MediExpress* med) :
                   cif(cif),
                   provincia(provincia),
                   localidad(localidad),
                   nombre(nombre),
                   direcion(direcion),
                   codPostal(codPostal),
                   dispense(),
                   linkMedi(med){}

Farmacia::Farmacia(const Farmacia &orig):
                cif(orig.cif),
                provincia(orig.provincia),
                localidad(orig.localidad),
                nombre(orig.nombre),
                direcion(orig.direcion),
                codPostal(orig.codPostal),
                dispense(orig.dispense),
                linkMedi(orig.linkMedi){}

Farmacia::~Farmacia() {

}

const std::string &Farmacia::getCif() const {
    return cif;
}

const std::string &Farmacia::getProvincia() const {
    return provincia;
}

const std::string &Farmacia::getLocalidad() const {
    return localidad;
}

const std::string &Farmacia::getNombre() const {
    return nombre;
}

const std::string &Farmacia::getDirecion() const {
    return direcion;
}

const std::string &Farmacia::getCodPostal() const {
    return codPostal;
}

void Farmacia::setCif(const std::string &cif) {
    Farmacia::cif = cif;
}

void Farmacia::setProvincia(const std::string &provincia) {
    Farmacia::provincia = provincia;
}

void Farmacia::setLocalidad(const std::string &localidad) {
    Farmacia::localidad = localidad;
}

void Farmacia::setNombre(const std::string &nombre) {
    Farmacia::nombre = nombre;
}

void Farmacia::setDirecion(const std::string &direcion) {
    Farmacia::direcion = direcion;
}

void Farmacia::setCodPostal(const std::string &codPostal) {
    Farmacia::codPostal = codPostal;
}

bool Farmacia::operator==(const Farmacia &rhs) const {
    return cif == rhs.cif;
}

bool Farmacia::operator<(const Farmacia &rhs) const {
    return this->cif < rhs.cif;
}

void Farmacia::pedidoMedicam(int id_num){
    if (linkMedi){
        linkMedi->suministrarFarmacia(this,id_num);
    }
}
PaMedicamento* Farmacia::buscaMedicam(int id_num){

    for (int i=0; i<dispense.tamlog(); i++){
        if (dispense[i]->get_id_num()==id_num)
            return dispense[i];
    }
    return nullptr;
}
void Farmacia::dispensaMedicam(PaMedicamento *pa){
    dispense.insertar(pa);
}

Vdinamico<PaMedicamento*> Farmacia::buscaMedicamentoNombre(std::string nombre) {
    Vdinamico<PaMedicamento*> v;
    for (int i=0; i<dispense.tamlog(); i++) {
        if (dispense[i]->get_nombre().find(nombre)!=string::npos) {
            v.insertar(dispense[i]);
        }
    }return v;
}