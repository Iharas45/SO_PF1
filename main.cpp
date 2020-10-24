#include <iostream>
#include <string.h>
#include <fstream>
#include "Lista.h"
#include "proceso.h"
#include "Planificador.h"




int main()
{
    Planificador uno;
    string nombre;
    cout << "ingrese nombre del archivo " <<endl;
    cin>> nombre;
    uno.cargarArchivo(nombre);
    uno.MostrarProcesos();
    //uno.Orden();
    uno.ejecutarMonoMono();

   return 0;
}
