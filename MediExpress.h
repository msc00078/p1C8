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

class MediExpress {
public:

    MediExpress();
    MediExpress(const string &nomFichPaMed, const string &nomFichLab, const string &nomFichFar);

    void suministrarMed(PaMedicamento* pa, Laboratorio* l);
    Laboratorio* buscarLab(const string &nombreLab);
    Vdinamico<Laboratorio*> buscarLabCiudad(const string &nombreCiudad);
    Vdinamico<PaMedicamento*> buscarCompuesto(const string &nombrePA);
    PaMedicamento* buscarCompuesto(int id_num);
    Vdinamico<PaMedicamento*> getMedicamentoSinLab();
    void suministrarFarmacia(Farmacia* f, int id_num);
    Farmacia* buscarFarmacia(const string &cif);
    Vdinamico<Laboratorio*> buscarLabs(const string &nombrePA);


private:
    Vdinamico<PaMedicamento> medication;
    ListaEnlazada<Laboratorio> labs;
    Avl<Farmacia> pharmacy;
};

#endif