#include <stdio.h>  
#include <stdlib.h>
#include <string.h>

struct Asistencia{
    char fecha[20];
    char materia[50];
    char estado [20];
};

struct Estudiante{
    char nombre[50];
    int edad;
    float promedio;
    char materias[10][50];
    struct Asistencia asistencia[100];
    int numMaterias;
    int numAsistencias;
};

struct AsistenciaException{
    char mensaje[100];
};

void mostrarEstudiante(const struct Estudiante* estudiante){
    printf("Nombre: %s\n", estudiante->nombre);
    printf("Edad: %d\n", estudiante->edad); 
    printf("Promedio: %.2f\n", estudiante->promedio);

    printf("Materias: \n");
    for(int i = 0; i < estudiante->numMaterias; ++i){
        printf("%s\n", estudiante->materias[i]);
    }

    printf("\nAsistencias: \n");
    for(int i = 0; i < estudiante->numAsistencias; ++i){
        printf("Fecha: %s\n", estudiante->asistencia[i].fecha);
        printf("Materia: %s\n", estudiante->asistencia[i].materia);
        printf("Estado: %s\n", estudiante->asistencia[i].estado);
        printf("\n");
    }
}

void registrarAsistencia(struct Estudiante* estudiante, const struct Asistencia* asistencia){
    int materiaInscrita = 0;
    for (int i = 0; i < estudiante->numMaterias; ++i){
        if(strcmp(estudiante->materias[i], asistencia->materia) == 0){
            materiaInscrita = 1;
            break;
        }
    }
    if (!materiaInscrita){
        struct AsistenciaException ex;
        snprintf(ex.mensaje, "El estudiante no esta inscrito en la materia");
        printf("Error: %s\n", ex.mensaje);
        exit (EXIT_FAILURE);
    }
    strcpy(estudiante->asistencia[estudiante->numAsistencias].fecha, asistencia->fecha);
    strcpy(estudiante->asistencia[estudiante->numAsistencias].materia, asistencia->materia);    
    strcpy(estudiante->asistencia[estudiante->numAsistencias].estado, asistencia->estado);
    estudiante->numAsistencias++;
}
int main()