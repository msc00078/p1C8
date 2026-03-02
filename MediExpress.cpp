#include "MediExpress.h"
#include <sstream>
#include <fstream>
#include "VDinamico.h"
#include <iostream>
#include "Laboratorio.h"
#include "Farmacia.h"
#include "PaMedicamento.h"


MediExpress::MediExpress() : medication(), labs() {}
MediExpress::MediExpress(const string &nomFichPaMed, const string &nomFichLab,
                         const string &nomFichFar){
    std::ifstream archivo;
    std::stringstream streamDeLinea;
    std::string lineaActual;
    int registros = 0;

    // --- Carga de Medicamentos ---
    int medIdNum = 0;
    std::string medIdAlpha = "";
    std::string medNombre = "";
    std::string idComoString = "";

    archivo.open(nomFichPaMed);
    if (archivo.good()) {

        while (getline(archivo, lineaActual)) {
            if (lineaActual != "") {
                streamDeLinea.str(lineaActual);

                getline(streamDeLinea, idComoString, ';');
                getline(streamDeLinea, medIdAlpha, ';');
                getline(streamDeLinea, medNombre, ';');
                medIdNum = stoi(idComoString);

                lineaActual = "";
                streamDeLinea.clear();

                PaMedicamento nuevoMedicamento(medIdNum, medIdAlpha, medNombre);
                medication.insertar(nuevoMedicamento);
            }
        }
        archivo.close();
    } else {
        std::cout << "Error critico al abrir el archivo de medicamentos: " << nomFichPaMed << std::endl;
    }

    //--- SEGUNDO FICHERO (Laboratorios) ---

    int labId = 0;
    std::string labNombre = "";
    std::string labDireccion = "";
    std::string labCP = "";
    std::string labLocalidad = "";

    archivo.open(nomFichLab);
    if (archivo.good()) {

        while (getline(archivo, lineaActual)) {
            if (lineaActual != "") {
                streamDeLinea.str(lineaActual);

                getline(streamDeLinea, idComoString, ';');
                getline(streamDeLinea, labNombre, ';');
                getline(streamDeLinea, labDireccion, ';');
                getline(streamDeLinea, labCP, ';');
                getline(streamDeLinea, labLocalidad, '\r');

                labId = stoi(idComoString);
                lineaActual = "";
                streamDeLinea.clear();

                Laboratorio nuevoLaboratorio(labId, labNombre, labDireccion, labCP, labLocalidad); // Renombrado
                //buscar posicion ordenada por id
                ListaEnlazada<Laboratorio>::Iterador it=labs.iterador();
                while (!it.fin() && it.dato().get_id() < labId){ // Renombrado
                    it.siguiente();
                }
                labs.insertaDelante(it, nuevoLaboratorio);
            }
        }
        archivo.close();
    } else {
        std::cout << "Error critico al abrir el archivo de laboratorios: " << nomFichLab << std::endl;
    }


    //--- TERCER FICHERO (Farmacias) ---

    std::string farmCIF = "";
    std::string farmProvincia = "";
    std::string farmLocalidad = "";
    std::string farmNombre = "";
    std::string farmDireccion= "";
    std::string farmCodPostal= "";

    archivo.open(nomFichFar);
    if (archivo.good()) {

        while (getline(archivo, lineaActual)) {
            if (lineaActual != "") {
                streamDeLinea.str(lineaActual);

                getline(streamDeLinea, farmCIF, ';');
                getline(streamDeLinea, farmProvincia, ';');
                getline(streamDeLinea, farmLocalidad, ';');
                getline(streamDeLinea, farmNombre, ';');
                getline(streamDeLinea, farmDireccion, ';');
                getline(streamDeLinea, farmCodPostal, '\r');

                lineaActual = "";
                streamDeLinea.clear();

                Farmacia nuevaFarmacia(farmCIF, farmProvincia, farmLocalidad, farmNombre, farmDireccion, farmCodPostal, this); // Renombrado
                pharmacy.inserta(nuevaFarmacia);

                // --- COUT MODIFICADO ---
                std::cout << "Farma [Registro " << ++registros
                          << "] CIF=" << farmCIF
                          << ", Nombre=" << farmNombre
                          << ", Localidad=" << farmLocalidad << std::endl;
            }
        }
        archivo.close();
    } else {
        std::cout << "Error critico al abrir el archivo de farmacias: " << nomFichFar << std::endl;
    }

    //--- ENLAZAMOS CADA 2 PAMEDIC. CON UN LABORATORIO ---

    ListaEnlazada<Laboratorio>::Iterador iteradorLab = labs.iterador(); // Renombrado
    for (int i=0; i<medication.tamlog() && !iteradorLab.fin(); i+=2){
        suministrarMed(&medication[i], &iteradorLab.dato());
        iteradorLab.siguiente();
    }

    //--- laboratorios madrid ---
    Vdinamico<Laboratorio*> labsEnMadrid = buscarLabCiudad("Madrid"); // Renombrado
    //--- Medicamentos sin laboratorio ---
    Vdinamico<PaMedicamento*> medsSinLaboratorio = getMedicamentoSinLab(); // Renombrado

    for (int i=0; i<labsEnMadrid.tamlog() && i<medsSinLaboratorio.tamlog(); i++){
        suministrarMed(medsSinLaboratorio[i], labsEnMadrid[i]);

        // --- COUT MODIFICADO ---
        cout << "Enlace [Madrid]: Med ID " << medsSinLaboratorio[i]->get_id_num() << " -> Lab ID " <<
             medsSinLaboratorio[i]->lab1()->get_id() << endl;
    }

    //--- MOSTRAR PARA COMPROBAR ---
    int conteoSinAsignar = 0; // Renombrado
    for (int i=0; i<medication.tamlog(); i++){
        if (medication[i].lab1())
            // --- COUT MODIFICADO ---
            cout << "  - Verificado: Med " << medication[i].get_id_num() <<
                 " --enlazado_con--> Lab " << medication[i].lab1()->get_id() << endl;
        else
            conteoSinAsignar++;
    }
    // --- COUT MODIFICADO ---
    cout << "Total de medicamentos sin laboratorio: " << conteoSinAsignar << endl;

//--- SEGUNDA LECTURA DEL TERCER FICHERO ---
    Vdinamico<string> vectorDeCifs; // Renombrado
    registros=0;

    archivo.open(nomFichFar);
    if (archivo.good()) {

        while (getline(archivo, lineaActual)) {
            if (lineaActual != "") {
                streamDeLinea.str(lineaActual);

                getline(streamDeLinea, farmCIF, ';'); // Reutilizamos farmCIF

                lineaActual = "";
                streamDeLinea.clear();

                vectorDeCifs.insertar(farmCIF);

                // --- COUT MODIFICADO ---
                std::cout << " CIF " << ++registros
                          << ": " << farmCIF << std::endl;
            }
        }
        archivo.close();
        // --- COUT MODIFICADO ---
        std::cout << "Total de farmacias unicas en sistema: " << pharmacy.numElementos() << endl;
    } else {
        // --- COUT MODIFICADO ---
        std::cout << "Error al releer el archivo de farmacias: " << nomFichFar << std::endl;
    }

    //--- ASOCIAMOS PaMedicamentos a cada farmacia del AVL ---
    int indiceMedicamento = 0; // Renombrado
    for (int i=0; i<vectorDeCifs.tamlog(); i++){
        Farmacia busca;
        busca.setCif(vectorDeCifs[i]);
        Farmacia* f=pharmacy.buscaIt(busca);
        int contadorStock = 0; // Renombrado
        while (contadorStock < 100){
            suministrarFarmacia(f, medication[indiceMedicamento].get_id_num());
            if (indiceMedicamento == medication.tamlog()-1)
                indiceMedicamento = 0;
            else
                indiceMedicamento++;
            contadorStock++;
            }
     }

}


void MediExpress::suministrarMed(PaMedicamento *pa, Laboratorio *l){
    if (pa){
        pa->set_lab(l);
    }
}
Laboratorio* MediExpress::buscarLab(const string &nombreLab){
    ListaEnlazada<Laboratorio>::Iterador<Laboratorio> it=labs.iterador();
    while (!it.fin()){
        if (it.dato().get_nombre_lab().find(nombreLab) != string::npos)
            return &(it.dato());
        it.siguiente();
    }
    return nullptr;
}

Vdinamico<Laboratorio*> MediExpress::buscarLabCiudad(const std::string &nombreCiudad) {
    Vdinamico<Laboratorio*> resultados; // Renombrado
    ListaEnlazada<Laboratorio>::Iterador<Laboratorio> it=labs.iterador();
    while (!it.fin()){
        if (it.dato().get_localidad().find(nombreCiudad) != string::npos)
            resultados.insertar(&it.dato());
        it.siguiente();
    }
    return resultados;
}

Vdinamico<PaMedicamento*> MediExpress::buscarCompuesto(const std::string &nombrePA) {
    Vdinamico<PaMedicamento*> encontrados; // Renombrado
    for (int i = 0; i < medication.tamlog(); i++) {
        if (medication[i].get_nombre().find(nombrePA) != string::npos) {
            encontrados.insertar(&medication[i]);
        }
    }
    return encontrados;
}

Vdinamico<PaMedicamento*> MediExpress::getMedicamentoSinLab() {
    Vdinamico<PaMedicamento*> sinAsignar; // Renombrado
    for (int i = 0; i < medication.tamlog(); i++) {
        if (!medication[i].lab1())
            sinAsignar.insertar(&medication[i]);
    }
    return sinAsignar;
}


PaMedicamento* MediExpress::buscarCompuesto(int id_num) {
    for (unsigned long i = 0; i < medication.tamlog(); i++) {
        if (medication[i].get_id_num() == id_num) {
            return &medication[i];
        }
    }
    return nullptr;
}

void MediExpress::suministrarFarmacia(Farmacia* f, int id_num) {
    if (f == nullptr) {
        return;
    }

    PaMedicamento* med_encontrado = this->buscarCompuesto(id_num);

    if (med_encontrado != nullptr) {
        f->dispensaMedicam(med_encontrado);
    }
}

Farmacia* MediExpress::buscarFarmacia(const string &cif) {
    Farmacia temp_busqueda;
    temp_busqueda.setCif(cif);

    return pharmacy.buscaIt(temp_busqueda);
}

Vdinamico<Laboratorio*> MediExpress::buscarLabs(const string &nombrePA) {
    Vdinamico<Laboratorio*> resultadosUnicos; // Renombrado

    for (unsigned long i = 0; i < medication.tamlog(); i++) {

        if (medication[i].get_nombre().find(nombrePA) != string::npos) {

            Laboratorio* lab = medication[i].lab1();

            if (lab != nullptr) {
                bool esDuplicado = false; // Renombrado
                for (unsigned long j = 0; j < resultadosUnicos.tamlog(); j++) {
                    if (resultadosUnicos[j]->get_id() == lab->get_id()) {
                        esDuplicado = true; // Renombrado
                        break;
                    }
                }

                if (!esDuplicado) { // Renombrado
                    resultadosUnicos.insertar(lab);
                }
            }
        }
    }
    return resultadosUnicos; // Renombrado
}