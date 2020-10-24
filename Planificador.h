#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

class Planificador
{
public:
    Lista<Proceso> misprocesos;  ///original
    Lista<Proceso> ListadeEjecucion;
    Lista<Proceso> ListaLlegadas; //
    Lista<Proceso> igualesExe;
    Lista<Proceso> igualesPriori;
    NodoLista<Proceso> *Apunt;
    Proceso pos;
    int tarea=1;
    int procesamiento=1;
    int otiempo=1;
    int oprioridad=1;
    int opid=2;
    int canales=0;
    int ordendeExe[3];
    int contLlegadas=0;
    int contTiempoL;
    int contPrioriAlta;
public:
    Planificador();
    void Tipo();
    void Orden();
    void InsertaP(Proceso);
    void MostrarProcesos();
    void Planificar();
    void ejecutarMonoMono();
    void ejecutarMonoMult();
    void ejecutarMultMono();
    void ejecutarMultMult();
    Proceso mPid(Lista <Proceso>);
    Proceso MPid(Lista <Proceso>);
    void eliminarProceso(Proceso);
    void eliminarProcesoLE(Proceso);
    Proceso ReducirExecucion(Proceso);
    Proceso mExe(Lista <Proceso>);
    Proceso MExe();
    Proceso mPrioridad();
    Proceso MPrioridad(Lista<Proceso> listaEvaluar);
    void ObtenLlegadas(int);
    void cargarArchivo(string);
    int regresarValor(int, int);
    void evaluarCriterio(Lista <Proceso>, int);
    int tiempoMenor(Lista <Proceso>);
    int prioridadAlta(Lista <Proceso>);
    void vaciarLista(Lista <Proceso>);
};
Planificador::Planificador()
{
    /*Tipo();
    Orden();*/
    ordendeExe[0]=3;
    ordendeExe[1]=2;
    ordendeExe[2]=1;

}
void Planificador::Tipo()
{
    int opc;
    cout<<"\nElija una opcion"<<endl;
    cout<<"1.- Monotarea  " << endl;
    cout<<"2.- Multitarea " << endl;
    cin >> opc;
    tarea=opc;
    cout<<"\nElija una opcion"<<endl;
    cout<<"1.- Monoproceso  " << endl;
    cout<<"2.- Multiproceso " << endl;
    cin >> opc;
    procesamiento=opc;
    if(opc==2)
    {
            cout <<"\nIngrese el numero de canales" <<endl;
            cin >> opc;
            canales=opc;
    }
}
void Planificador::Orden()
{
    int cont=0,o;
    cout<<"\nElige el primer criterio a evaluar"<<endl;
    cout<<"1.- Tiempo de Ejecucion  " << endl;
    cout<<"2.- Prioridad " << endl;
    cout<<"3.- PID " << endl;
    cin >> o;
    ordendeExe[0]=o;
    switch(o)
    {
        case 1:
        cout<<"\nElige el segundo criterio a evaluar" << endl;
        cout<<"2.- Prioridad " << endl;
        cout<<"3.- PID " << endl;
        cin >> o;
        ordendeExe[1]=o;
        cout<<"\nSelecciona tipo de PID" << endl;
            cout<<"1.- PID Ascendente  " << endl;
            cout<<"2.- PID Descendente " << endl;
            cin >> o;
            opid=o;
            ordendeExe[2]=regresarValor(ordendeExe[0],ordendeExe[1]);
        cout << ordendeExe[0]<< " : " << ordendeExe[1]<< " : " << ordendeExe[2]<< endl;
        break;
        case 2:
        cout<<"\nElige el segundo criterio a evaluar" << endl;
        cout<<"1.- Tiempo de Ejecucion  " << endl;
        cout<<"3.- PID " << endl;
        cin >> o;
        ordendeExe[1]=o;
        cout<<"\nSelecciona tipo de PID" << endl;
            cout<<"1.- PID Ascendente  " << endl;
            cout<<"2.- PID Descendente " << endl;
            cin >> o;
            opid=o;
        ordendeExe[2]=regresarValor(ordendeExe[0],ordendeExe[1]);
        cout << ordendeExe[0]<< " : " << ordendeExe[1]<< " : " << ordendeExe[2]<< endl;
        break;
        case 3:
            cout<<"\nSelecciona tipo de PID" << endl;
            cout<<"1.- PID Ascendente  " << endl;
            cout<<"2.- PID Descendente " << endl;
            cin >> o;
            opid=o;
        cout<<"\nElige el segundo criterio a evaluar  " << endl;
        cout<<"1.- Tiempo de Ejecucion  " << endl;
        cout<<"2.- Prioridad " << endl;
        cin >> o;
        ordendeExe[1]=o;
        ordendeExe[2]=regresarValor(ordendeExe[0],ordendeExe[1]);
        cout << ordendeExe[0]<< " : " << ordendeExe[1]<< " : " << ordendeExe[2]<< endl;
        break;
        default:cout <<"Elija una opcion"<< endl;
    }

}
void Planificador::InsertaP(Proceso a)
{
    misprocesos.InsertaFinal(a);
}
void  Planificador::MostrarProcesos()
{
    misprocesos.ImprimeIterativo();
}
void  Planificador::Planificar()
{
    switch(tarea)
    {
        case 1:
                switch(procesamiento)
                {
                    case 1: ejecutarMonoMono();
                    break;
                    case 2: ejecutarMonoMult();
                    break;
                }
        break;
        case 2:
                switch(procesamiento)
                {
                    case 1:ejecutarMultMono();
                    break;
                    case 2:ejecutarMultMult();
                    break;
                }
        break;
    }
}
int Planificador::tiempoMenor(Lista <Proceso> listEvaluar)
{
    int tiempo = 10;
    NodoLista<Proceso> *P,*LP;
    Proceso paux;
    P=listEvaluar.RegresaPrimero();
    while(P)
    {
        if(P->RegresaInfo().obtenexecucion() < tiempo)
        {
            tiempo = P->RegresaInfo().obtenexecucion();
        }
        P=P->Liga;
    }
    return tiempo;
}
int Planificador::prioridadAlta(Lista <Proceso> listEvaluar)
{
    int priori = 10;
    NodoLista<Proceso> *P,*LP;
    P=listEvaluar.RegresaPrimero();
    while(P)
    {
        if(P->RegresaInfo().obtenprioridad() < priori)
        {
            priori = P->RegresaInfo().obtenprioridad();
        }
        P=P->Liga;
    }
    return priori;
}
Proceso Planificador::mExe(Lista<Proceso> listaEvaluar)
{
    int tiempito = tiempoMenor(listaEvaluar);
    contTiempoL = 0;
    NodoLista<Proceso> *P,*LP;
    Proceso paux;
    P=listaEvaluar.RegresaPrimero();
    cout << "Tiempo de execucion menor:  " << tiempito<< endl ;
    while(P)
    {
        if(P->RegresaInfo().obtenexecucion() == tiempito)
        {
            igualesExe.InsertaFinal(P->RegresaInfo());
            contTiempoL+=1;
            paux=P->RegresaInfo();
        }
        P=P->Liga;
    }
    //igualesExe.ImprimeIterativo();
    return paux;
}
Proceso Planificador::MPrioridad(Lista<Proceso> listaEvaluar)
{
    int priori = prioridadAlta(listaEvaluar);
    contPrioriAlta = 0;
    NodoLista<Proceso> *P,*LP;
    Proceso paux;
    P=listaEvaluar.RegresaPrimero();
    cout << "Prioridad alta :  " << priori<< endl ;
    while(P)
    {
        if(P->RegresaInfo().obtenprioridad() == priori)
        {
            igualesPriori.InsertaFinal(P->RegresaInfo());
            contPrioriAlta+=1;
            paux=P->RegresaInfo();
        }
        P=P->Liga;
    }
    //igualesExe.ImprimeIterativo();
    return paux;
}
Proceso Planificador::MExe()
{
    NodoLista<Proceso> *S,*P;
    Proceso paux;
    P=misprocesos.RegresaPrimero();
    S=P->Liga;
    while(S)
    {
        //if(P->RegresaInfo().pid <= S->RegresaInfo().pid))Volver public
        if(P->RegresaInfo().obtenexecucion() > S->RegresaInfo().obtenexecucion())
        {
            paux=P->RegresaInfo();
        }
        else
            {
                P=S;
                paux=S->RegresaInfo();
            }
        S=S->Liga;

    }
    return paux;
}
void Planificador::evaluarCriterio(Lista <Proceso> listaEntrada, int pos)
{
    int np = pos +1 ;
    switch(ordendeExe[pos])
    {
        case 1:
        {
            Proceso obtenido = mExe(listaEntrada);
            if(contTiempoL == 1)
            {
                ListadeEjecucion.InsertaFinal(obtenido);
                misprocesos.EliminaUnNodo(obtenido);
                ListaLlegadas.EliminaUnNodo(obtenido);
                igualesExe.EliminaUltimo();
                obtenido.mostrarproceso();
            }
            else
            {
                evaluarCriterio(igualesExe, np);
            }
        }
        break;
        case 2:
        {
            Proceso obtenido1 = MPrioridad(listaEntrada);
            if(contPrioriAlta == 1)
            {
                ListadeEjecucion.InsertaFinal(obtenido1);
                misprocesos.EliminaUnNodo(obtenido1);
                ListaLlegadas.EliminaUnNodo(obtenido1);
                igualesPriori.EliminaUltimo();
            }
            else
            {
                igualesPriori.ImprimeIterativo();
                evaluarCriterio(igualesPriori, np);
            }

        }
        break;
        case 3:
        {
            if(opid == 1) ///pid asc
            {
                Proceso obtenido3 = mPid(listaEntrada);
                obtenido3.mostrarproceso();
            }
            else /// pid desc
            {
                Proceso obtenido3 = MPid(listaEntrada);
                obtenido3.mostrarproceso();
            }
        }
        break;
    }


}
void Planificador::ejecutarMonoMono()
{
    ObtenLlegadas(0);
    //cout << contLlegadas << endl;
    if(contLlegadas == 1)
    {

    }
    else
    {
        if(contLlegadas == 0)
        {

        }
        else{
            evaluarCriterio(ListaLlegadas, 0);
        }



    }

    /*switch(ordendeExe[1])
    {
        case 1: switch(otiempo)
                {
                    case 1: {

                            }
                    break;
                    case 2:
                    break;
                }
        break;
        case 2: switch(oprioridad)
                {
                    case 1:
                    break;
                    case 2:
                    break;
                }
        break;
        case 3: switch(opid)
                {
                    case 1:
                    break;
                    case 2:
                    break;
                }
        break;
    }*/
}
void Planificador::ejecutarMonoMult()
{}
void Planificador::ejecutarMultMono()
{}
void Planificador::ejecutarMultMult()
{}
Proceso Planificador::mPid(Lista <Proceso> listaEvalua)
{
    NodoLista<Proceso> *S,*P;
    Proceso paux;
    P=listaEvalua.RegresaPrimero();
    paux = P->RegresaInfo();
    return paux;
}

Proceso Planificador::MPid(Lista <Proceso> listaUltimo)
{
    NodoLista<Proceso> *S,*P;
    Proceso paux;
    P=listaUltimo.RegresaPrimero();
    while(P)
    {
        paux=P->RegresaInfo();
        P=P->Liga;
    }
    return paux;

}
void Planificador::eliminarProceso(Proceso a)
{
    misprocesos.EliminaUnNodo(a);
}
void Planificador::eliminarProcesoLE(Proceso a)
{
    ListadeEjecucion.EliminaUnNodo(a);
}
Proceso Planificador::ReducirExecucion(Proceso a)
{
    a.restarexecucionToda();
}

void Planificador::ObtenLlegadas(int llegada)
{
    contLlegadas = 0;
    NodoLista<Proceso> *P,*LP;
    Proceso paux;
    P=misprocesos.RegresaPrimero();
    //cout << "Tiempo de llegada: " << llegada ;
    while(P)
    {
        if(P->RegresaInfo().obtenllegada() == llegada)
        {
            ListaLlegadas.InsertaFinal(P->RegresaInfo());
            contLlegadas+=1;
        }
        P=P->Liga;
    }
    /*LP=Lis}
    if(Lista)*/
}
void Planificador::cargarArchivo(string nombre)
{
    string nombre2="archivo.txt";
    ifstream leeA("tabla.txt");
    int a,b,c,d;
        while(!leeA.eof())
        {
            leeA >> a >> b >> c >> d;
            Proceso nuevo(a,b,c,d);
            InsertaP(nuevo);
        }
}
int Planificador::regresarValor(int val1, int val2)
{
    int suma = val1 + val2;
    int val3;
    switch(suma)
    {
        case 3 :
        {
            val3 = 3;
            return val3;
        }
        break;
        case 4 :
        {
            val3 = 2;
            return val3;
        }
        break;
        case 5 :
        {
            val3 = 1;
            return val3;
        }
        break;
    }
}
void Planificador::vaciarLista(Lista <Proceso> listaAEliminar)
{

}
