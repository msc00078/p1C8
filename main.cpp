#include <iostream>

#include "ListaEnlazada.h"
#include "Laboratorio.h"
#include "MediExpress.h"
#include "PaMedicamento.h"
#include "Vdinamico.h"

/**  @author Alejandro Barranco Rivera abr00070@red.ujaen.es */


void mostrarLista_confor(ListaEnlazada<int> &lista) {

    for (ListaEnlazada<int>::Iterador it = lista.iterador();!it.fin();it.siguiente()) {
        cout << it.dato() << ",";
    }
    cout << endl;
}
void mostrarLista(ListaEnlazada<int> &lista) {
    ListaEnlazada<int>::Iterador it = lista.iterador();
    while (!it.fin()) {
        cout << it.dato() << ",";
        it.siguiente();
    }
    cout << endl;
}

int main() {

    try {

        //PRUEBA1: Probando lista de enteros
        ListaEnlazada<int> lista;
        for (int i = 101; i <= 200; i++)
            lista.insertarFin(i);
        mostrarLista(lista);

        for (int i = 98; i >= 1; i--)
            lista.insertarInicio(i);
        mostrarLista(lista);

        ListaEnlazada<int>::Iterador it = lista.iterador();
        while (it.dato() != 101) {
            it.siguiente();
        }
        lista.insertaDelante(it, 100);
        mostrarLista(lista);

        ListaEnlazada<int>::Iterador it1 = lista.iterador();
        while (it.dato() != 101) {
            it.siguiente();
        }
        lista.insertaDelante(it, 100);
        mostrarLista(lista);

        ListaEnlazada<int>::Iterador it2 = lista.iterador();
        while (it2.dato() != 98) {
            it2.siguiente();
        }

        lista.insertaDetras(it2, 99);
        mostrarLista(lista);

        for (int i = 0; i < 10; i++) {
            lista.borrarInicio();
        }
        mostrarLista(lista);

        for (int i = 0; i < 10; i++) {
            lista.borrarFinal();
        }
        mostrarLista(lista);
        ListaEnlazada<int>::Iterador itborrado=lista.iterador();
        while (!it.fin()) {
            if (it.dato() % 10 == 0) {
                itborrado = it;
                itborrado.siguiente();
                lista.borra(it);
                it = itborrado;
            } else
                it.siguiente();
        }

        cout << "PRUEBA1: LISTA FINAL:" << endl;
        mostrarLista(lista);

    }catch (std::bad_alloc &e){
        std::cerr << "No hay memoria suficiente." << std::endl;
    }


    cout << endl << "PRUEBA2: MediExpress:" << endl;

    cout << "Comienzo de lectura de ficheros y carga de DATOS " << endl;

    MediExpress medi("../pa_medicamentos.csv","../lab2.csv");
    char c;
    try {
        //laboratorios granada
        Vdinamico<Laboratorio*> granada= medi.buscarLabCiudad("Granada");
        for (int i=0; i<granada.tamlog(); i++){
            cout << "id_Lab=" << granada[i]->get_id() << " Nombre=" <<
                granada[i]->get_nombre_lab() << " Direccion=" <<
                granada[i]->get_direccion_lab()  << " " <<
                granada[i]->get_localidad()  << endl;
        }

        //laboratorios jaen
        Vdinamico<Laboratorio*> jaen= medi.buscarLabCiudad("Jaen");
        cout << "Total Lab. en jaen:" << jaen.tamlog() << endl;

        //laboratorios madrid
        Vdinamico<Laboratorio*> madrid= medi.buscarLabCiudad("Madrid");
        cout << "Total Lab. en madrid:" << madrid.tamlog() << endl;
        for (int i=0; i<madrid.tamlog() && i<10; i++){
            cout << "id_Lab=" << madrid[i]->get_id() << " Nombre=" <<
            madrid[i]->get_nombre_lab() << " Direccion=" <<
            madrid[i]->get_direccion_lab()  << endl;
        }

        //laboratorios q suministran ACEITES
        Vdinamico<PaMedicamento*> aceites= medi.buscarCompuesto("ACEITE");
        Vdinamico<Laboratorio*> laboAceite;
        for (int i = 0; i < aceites.tamlog(); i++) {
            // CORREGIDO: Usamos getLaboratorio() y comprobamos que no sea nulo.
            Laboratorio* lab = aceites[i]->lab1();
            if (lab) { // Si el laboratorio existe (no es nullptr)
                int id = lab->get_id();
                bool enc = false;
                for (int j = 0; j < laboAceite.tamlog() && !enc; j++) {
                    if (id == laboAceite[j]->get_id())
                        enc = true;
                }
                if (!enc)
                    laboAceite.insertar(lab);
            }
        }
        cout << endl << "Laboratorios que elaboran ACEITES:" << endl;
        for (int i=0; i<laboAceite.tamlog(); i++)
        {
            cout << "id_Lab=" << laboAceite[i]->get_id() << " Nombre=" <<
            laboAceite[i]->get_nombre_lab() << " Direccion=" <<
            laboAceite[i]->get_direccion_lab()  << endl;
        }

        //Medicamentos sin laboratorio
        Vdinamico<PaMedicamento*> sin= medi.PaMedSinLab();
        cout << "Total PaMedic. sin Laboratorio:" << sin.tamlog() << endl;

        for (int i=0; i<madrid.tamlog() && i<sin.tamlog(); i++){
            // cout << i << endl;
            medi.suministrarMed(sin[i],madrid[i]);
            // sin[i]->servidoPor(madrid[i]);
            Laboratorio* lab_asignado = sin[i]->lab1();
            if (lab_asignado) {
                cout << "Id_PaMed=" << sin[i]->get_id_num() << " Laboratorio asig.=" <<
                     lab_asignado->get_id() << endl;
            }
        }
        cout << endl << "FIN DE LA APLICACION....";
    }catch (std::out_of_range &e){
    std::cerr << e.what() << std::endl;
    }catch (std::runtime_error &e){ //std::ifstream::failure &e){
    std::cerr << "Excepcion en fichero: " << e.what() << std::endl;
    }catch (std::bad_alloc &e){
    std::cerr << "No hay memoria suficiente para el objeto dinamico" << std::endl;
    }


    return 0;
    }