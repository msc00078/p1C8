#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

#include "Avl.h"
#include "MediExpress.h"


using namespace std;

void cargaFarmacias(Avl<Farmacia> &af, Vdinamico<Farmacia> &vf) {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;
    int contador = 0;

    std::string ciff, provinciaf, localidadf, nombref, direccionf, codpostalf;

    is.open("./farmacias.csv");
    if (!is.good()) {
        std::cout << "Error critico: No se pudo abrir el archivo farmacias.csv" << std::endl;
        return;
    }

    // Descartar la primera fila (cabeceras)
    getline(is, fila);

    while (getline(is, fila)) {
        if (fila.empty()) continue;

        columnas.clear();
        columnas.str(fila);

        getline(columnas, ciff, ';');
        getline(columnas, provinciaf, ';');
        getline(columnas, localidadf, ';');
        getline(columnas, nombref, ';');
        getline(columnas, direccionf, ';');
        getline(columnas, codpostalf, '\r');

        Farmacia datof(ciff, provinciaf, localidadf, nombref, direccionf, codpostalf, 0);

        af.inserta(datof);
        vf.insertar(datof);
        contador++;
    }

    is.close();

    cout << "Proceso de carga finalizado. Se han procesado " << contador << " registros de farmacias." << endl;
}

int main() {
    try {
        // --- PRUEBA 1: Comparativa de Rendimiento AVL vs Vector ---
        clock_t t_ini;

        Avl<Farmacia> afarma;
        Vdinamico<Farmacia> vfarma;
        cargaFarmacias(afarma, vfarma);

        Vdinamico<string> aux;
        for (int i=0; i<vfarma.tamlog() && i<500; i++){
            aux.insertar(vfarma[i].getCif());
        }

        Farmacia dato;
        t_ini = clock();
        for (int i=0; i<aux.tamlog(); i++){
            dato.setCif(aux[i]);
            afarma.buscaRec(dato);
        }

        cout << endl << "Rendimiento AVL (clock): " << ((clock() - t_ini) / (float)CLOCKS_PER_SEC) << " segs." << endl;

        t_ini = clock();
        auto start= std::chrono::high_resolution_clock::now();
        for (int i=0; i<aux.tamlog(); i++){
            bool enc=false;
            for (int j=0; j<vfarma.tamlog() && !enc; j++) {
                if (aux[i] == vfarma[j].getCif())
                    enc = true;
            }
        }
        auto end= std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        cout << "Rendimiento V. Dinamico (chrono): " << elapsed.count() << " ms\n";
        cout << "Rendimiento V. Dinamico (clock): " << ((clock() - t_ini) / (float)CLOCKS_PER_SEC)*1000 << " segs." << endl;

        // Estadísticas del Árbol AVL
        cout << "\n--- Estadisticas del Arbol ---" << endl;
        cout << "Estadisticas del Arbol: Altura -> " << afarma.altura() << endl;
        cout << "Estadisticas del Arbol: Nodos -> " << afarma.numElementos() << endl;

        Vdinamico<Farmacia*> v= afarma.recorreInorden();
        cout << "\nRecorrido Inorden (Primeros 100):" << endl;
        for (int i=0; i<v.tamlog() && i<100; i++) {
            cout << "  - Nodo: [CIF: " << v[i]->getCif() << "]" << endl;
        }

        //  PRUEBA 2: Lógica de MediExpress
        cout << endl << "\n--- Iniciando Prueba 2: Funcionalidad MediExpress ---" << endl;

        cout << "Cargando datos de MediExpress (Medicamentos, Labs, Farmacias)..." << endl;

        MediExpress medi("./pa_medicamentos.csv","./lab2.csv","./farmacias.csv");
        try {
            string cif[27] = {"37656422V","46316032N", "77092934Q", "33961602D", "B62351861", "B62351861",
                        "B65828113", "46138599R", "35069965W", "37579913Y", "37682300C",
                        "37643742X", "46112335A", "47980171D", "38116138D", "46315600V",
                        "37640233C", "37931842N", "33964303L", "35022080A", "B66046640",
                        "E66748344", "47640201W", "B66621954", "46121385Z", "X6806622W","46046390E"};

            int cont_no=0;
            for (int i=0; i<27; i++) {
                Farmacia* f=medi.buscarFarmacia(cif[i]);
                if (f) {
                    if (f->buscaMedicam(3640))
                        cout << "  [OK] Farmacia " << cif[i] << " ya tiene el med 3640" << endl;
                    else {
                         medi.suministrarFarmacia(f,3640);
                       // cout << "  [+] Suministrando med 3640 a Farmacia " << cif[i] << endl;
                        cont_no++;
                    }
                }
            }
            cout << "\nConteo de farmacias sin stock (Antes): " << cont_no << endl;
            cont_no=0;
            for (int i=0; i<27; i++) {
                Farmacia* f=medi.buscarFarmacia(cif[i]);
                if (f) {
                    if (!f->buscaMedicam(3640))
                        cont_no++;
                }
            }
            cout << "Conteo de farmacias sin stock (Despues): " << cont_no << endl;

            Vdinamico<Laboratorio*> vlab=medi.buscarLabs("MAGNESIO");
            Avl<Laboratorio*> alab;
            for (int i=0; i<vlab.tamlog(); i++) {
                alab.inserta(vlab[i]);
            }
            cout << "\nMedicamentos encontrados para 'MAGNESIO': " << vlab.tamlog() << endl;
            cout << "Laboratorios unicos que lo suministran: " << alab.numElementos() << endl;


        }catch (std::bad_alloc &e) {
            std::cerr << "Error fatal: Memoria insuficiente (en Prueba 2)." << std::endl;
        }
    }catch (std::bad_alloc &e) {
        std::cerr << "Error fatal: Memoria insuficiente (en Main)." << std::endl;
    }
}