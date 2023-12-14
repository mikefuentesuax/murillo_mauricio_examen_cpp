#include <iostream>
#include <string>
#include <vector>   
#include <stdexcept> 
#include <algorithm>       

using namespace std;    

struct Asistencia{
    string fecha;
    string materia;
    string estado;
    //Aqui puede ser "asistio","falat","retraso"
};

struct Estudiante{
    string nombre;
    int edad;
    float promedio;
    vector <string> materias;
    vector <Asistencia> asistencias;
};

class AsistenciaExcepcion : public runtime_error{
    public:
        AsistenciaExcepcion(const string& message) : runtime_error("Error en la asistencia"){}
};

//Funcion para mostrar un estudiante
void mostrarEstudiante(const Estudiante& estudiante){
    cout << "Nombre: " << estudiante.nombre << endl;
    cout << "Edad: " << estudiante.edad << endl;
    cout << "Promedio: " << estudiante.promedio << endl;

    cout << "Materias: " << endl;
    for (const auto& materia : estudiante.materias){
        cout << "  " << materia << endl;
    }
    
    cout << "\nAsistencias: " << endl;
    for (const auto& asistencia : estudiante.asistencias){
        cout << "Fecha:  " << asistencia.fecha << " - Materia: " << asistencia.materia << " - Estado: " << asistencia.estado << endl;
    }
}

//Funcion para agregar una asistencia
void registrarAsistencia(Estudiante& estudiante, const Asistencia& asistencia){
    if (find(estudiante.materias.begin(), estudiante.materias.end(), asistencia.materia) == estudiante.materias.end()){
        throw AsistenciaExcepcion("La materia no existe");
    }  
    estudiante.asistencias.push_back(asistencia);
}

int main(){
    try{
    //Clase estudiante
    Estudiante estudiante;
    estudiante.nombre = "Juan";
    estudiante.edad = 20;
    estudiante.promedio = 8.5;


    //Agregar materias
    estudiante.materias.push_back("Matematicas");
    estudiante.materias.push_back("Programacion");


    mostrarEstudiante(estudiante);


    //Agregar asistencia
    Asistencia asistencia = {"2021-05-10", "Matematicas", "asistio"};
    registrarAsistencia(estudiante, asistencia);

    //mostrar informacion actualizada
    cout << "\nInformacion actualizada: " << endl;
    mostrarEstudiante(estudiante); 

    //Registra asistencia con error
    Asistencia asistenciaInvalida = {"2021-05-10", "Fisica", "asistio"};
    registrarAsistencia(estudiante, asistenciaInvalida);

    } catch (const AsistenciaExcepcion& e){
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}