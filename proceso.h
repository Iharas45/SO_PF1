#include <iostream>
using namespace std;

class Proceso
{
private:
    int pid;
    int llegada;
    int execucion;
    int prioridad;
    int espera;
    int finalizada=0;
public:
    Proceso();
    Proceso(int,int,int,int);
    void insertar(int,int,int,int);
    int obtenpid();
    int obtenllegada();
    int obtenexecucion();
    int obtenprioridad();
    int obtenespera();
    void mostrarproceso();
    void restarexecucion();
    void restarexecucionToda();
    int obtenTespera();
    int operator < (Proceso);
    int operator != (Proceso);
    int operator == (Proceso);
    friend ostream &operator << (ostream &, Proceso &);
};
Proceso::Proceso()
{}
Proceso::Proceso(int a,int b,int c,int d)
{
    pid=a;
    llegada=b;
    execucion=c;
    prioridad=d;
    espera=0;
}
void Proceso::insertar(int a,int b,int c,int d)
{
    pid=a;
    llegada=b;
    execucion=c;
    prioridad=d;
    espera=0;
}
int Proceso::obtenpid()
{
    return pid;
}
int Proceso::obtenllegada()
{
    return llegada;
}
int Proceso::obtenexecucion()
{
    return execucion;
}
int Proceso::obtenprioridad()
{
    return prioridad;
}
int Proceso::obtenespera()
{
    return espera;
}
void Proceso::mostrarproceso()
{
    cout << " PID: " << obtenpid();
    cout << " T.LL : " << obtenllegada();
    cout << " T.exe: " << obtenexecucion();
    cout << " Prioridad : " << obtenprioridad();
    cout << " T.espera : " << obtenespera();
    cout << endl;
}
void Proceso::restarexecucion()
{
    execucion--;
}
void Proceso::restarexecucionToda()
{
    execucion=0;
}
int Proceso::operator != (Proceso Prod)
{
    int Resp = 0;
	if (pid != Prod.pid)
	   Resp = 1;
	return Resp;
}
int Proceso::operator < (Proceso Prod)
{
    int Resp = 0;
	if (pid < Prod.pid)
	   Resp = 1;
	return Resp;
}
int Proceso::operator == (Proceso Prod)
{
    int Resp = 0;
	if (pid == Prod.pid)
	   Resp = 1;
	return Resp;
}
ostream &operator << (ostream &Escribe, Proceso &ObjProd)
{
    //Escribe << "\n\nDatos del proceso\n";
    Escribe << "PID  : " << ObjProd.pid << " | ";
    Escribe << "T.ll :" << ObjProd.llegada<< " | ";
    Escribe << "T.exe: " << ObjProd.execucion<< " | ";
    Escribe << "Prioridad : " << ObjProd.prioridad<< " | ";
    Escribe << "T.espera : " << ObjProd.espera;
    Escribe << endl;
    return Escribe;
}
int Proceso::obtenTespera()
{
    return finalizada-llegada-execucion;
}
