#include "MediExpress.h"
#include <sstream>
#include <fstream>
#include "ListaEnlazada.h"

MediExpress::MediExpress() : medication(), labs() {}

MediExpress::MediExpress(const string &nomFichPaMed, const string &nomFichLab){
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;
    int contador = 0;

    int id_num = 0;
    std::string id_alpha = "";
    std::string nombre = "";
    std::string num = "";

    is.open(nomFichPaMed); //"../pa_medicamentos.csv"
    if (is.good()) {

        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);


                getline(columnas, num, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, id_alpha, ';');
                getline(columnas, nombre, ';');
                id_num = stoi(num);

                fila = "";
                columnas.clear();

                PaMedicamento dato(id_num,id_alpha,nombre);

                medication.insertar(dato);

                std::cout << ++contador
                          << " PActivo: ( id_num=" << id_num
                          << " id_alpha=" << id_alpha << " nombre=" << nombre
                          << ")" << std::endl;
            }
        }
        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    //SEGUNDO FICHERO

    int id = 0;
    std::string nombrelab = "";
    std::string direccion = "";
    std::string cp = "";
    std::string localidad = "";

    is.open(nomFichLab);
    if (is.good()) {

        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);

                getline(columnas, num, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, nombre, ';');
                getline(columnas, direccion, ';');
                getline(columnas, cp, ';');
                getline(columnas, localidad, '\r');
                //localidad[localidad.length()-1]=' ';
                id_num = stoi(num);

                fila = "";
                columnas.clear();

                Laboratorio dato(id_num,nombre,direccion,cp,localidad);
                //buscar posicion ordenada por id
                ListaEnlazada<Laboratorio>::Iterador<Laboratorio> it=labs.iterador();
                while (!it.fin() && it.dato().get_id()<id_num){
                    it.siguiente();
                }
                labs.insertaDelante(it,dato);

                std::cout << ++contador
                          << " Id_Lab: ( id_num=" << id_num
                          << " nombre=" << nombre << " direccion=" << direccion
                          << " codPostal=" << cp << " localidad=" << localidad
                          << ")" << std::endl;
            }
        }
        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    //MOSTRAMOS LISTA ORDENADA POR ID_LAB
    cout << "Mostramos lista laboratorios: " << endl;
    ListaEnlazada<Laboratorio>::Iterador<Laboratorio> it=labs.iterador();
    while (!it.fin() ){
        cout << "id_lab=" << it.dato().get_id() << endl;
        it.siguiente();
    }
    cout << "Fin lista laboratorios. Total: " << labs.tam() << endl;

    //ENLAZAMOS CADA 2 PAMEDIC. CON UN LABORATORIO

    ListaEnlazada<Laboratorio>::Iterador<Laboratorio> itl = labs.iterador();
    int i = 0; // Índice para los medicamentos

    // Itera mientras queden laboratorios Y medicamentos
    while (!itl.fin() && i < medication.tamlog()) {

        // 1. Obtén el laboratorio actual UNA SOLA VEZ
        Laboratorio* labActual = &itl.dato();

        // 2. Asigna el primer medicamento (medication[i])
        suministrarMed(&medication[i], labActual);
        i++; // Avanza al siguiente medicamento

        // 3. Comprueba si queda otro medicamento para asignar
        if (i < medication.tamlog()) {
            // Asigna el segundo medicamento (medication[i+1]) AL MISMO LABORATORIO
            suministrarMed(&medication[i], labActual);
            i++; // Avanza al siguiente medicamento
        }

        // 4. Ahora sí, avanza al siguiente laboratorio
        itl.siguiente();
    }

    //MOSTRAR PARA COMPROBAR
    cout << "\n--- Comprobando enlaces ---" << endl;
    int cont = 0;
    for (int i = 0; i < medication.tamlog(); i++) {
        // CAMBIO: Usamos el GETTER para obtener el laboratorio
        Laboratorio* labAsignado = medication[i].lab1();
        if (labAsignado != nullptr) {
            cout << "PaMedicamento: " << medication[i].get_id_num()
                 << " es servido por Laboratorio: " << labAsignado->get_id() << endl;
        } else {
            cont++;
        }
    }
    cout << "Medicamentos sin asignar: " << cont << endl;
}

MediExpress::MediExpress(const MediExpress &orig):
                        medication(orig.medication),
                        labs(orig.labs)
                        {}

MediExpress::~MediExpress() {}

void MediExpress::suministrarMed(PaMedicamento *pa, Laboratorio *l){
    if (pa){
        pa->set_lab(l);
    }
}
Laboratorio* MediExpress::buscarLab(std::string nombreLab){
    ListaEnlazada<Laboratorio>::Iterador<Laboratorio> it=labs.iterador();
    while (!it.fin()){
        if (it.dato().get_nombre_lab().find(nombreLab) != string::npos)
            return &(it.dato());
        it.siguiente();
    }
    return nullptr;
}

Vdinamico<Laboratorio*> MediExpress::buscarLabCiudad(const std::string &nombreCiudad) {
    Vdinamico<Laboratorio*> labor;
    ListaEnlazada<Laboratorio>::Iterador<Laboratorio> it=labs.iterador();
    while (!it.fin()){
        if (it.dato().get_localidad().find(nombreCiudad) != string::npos)
            labor.insertar(&it.dato());
        it.siguiente();
    }
    return labor;
}

Vdinamico<PaMedicamento*> MediExpress::buscarCompuesto(const std::string &nombrePA) {
    Vdinamico<PaMedicamento*> compu;
    for (int i = 0; i < medication.tamlog(); i++) {
        if (medication[i].get_nombre().find(nombrePA) != string::npos) {
            compu.insertar(&medication[i]);
        }
    }
    return compu;
}

Vdinamico<PaMedicamento*> MediExpress::PaMedSinLab() {
    Vdinamico<PaMedicamento*> sin;
    for (int i = 0; i < medication.tamlog(); i++) {
        if (!medication[i].lab1())
            sin.insertar(&medication[i]);
    }
    return sin;
}
