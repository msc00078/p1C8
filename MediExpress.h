//
// Created by David on 05/10/2025.
//

#ifndef PRAC2_MEDIEXPRESS_H
#define PRAC2_MEDIEXPRESS_H

#include <iostream>
#include "Vdinamico.h"
#include "ListaEnlazada.h"
#include "PaMedicamento.h"
#include "Laboratorio.h"

class MediExpress {
public:
    MediExpress();
    MediExpress(const string &nomFichPaMed, const string &nomFichLab);
    MediExpress(const MediExpress &orig);
    virtual ~MediExpress();

    void suministrarMed(PaMedicamento *pa, Laboratorio *l);
    Laboratorio* buscarLab(std::string nombreLab);
    Vdinamico<Laboratorio*> buscarLabCiudad(const std::string &nombreCiudad);
    Vdinamico<PaMedicamento*> buscarCompuesto(const std::string &nombrePA);

    Vdinamico<PaMedicamento*> PaMedSinLab();

private:
    Vdinamico<PaMedicamento> medication;
    ListaEnlazada<Laboratorio> labs;

};


#endif //PRAC2_MEDIEXPRESS_H
