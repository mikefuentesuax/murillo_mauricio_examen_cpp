#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura Asistencia
struct Asistencia {
    char fecha[20];
    char materia[50];
    char estado[20];  // Puede ser "asistió", "falta" o "tardanza"
};

// Definición de la estructura Estudiante
struct Estudiante {
    char nombre[50];
    int edad;
    float promedio;
    char materias[10][50];  // Array para almacenar las materias
    struct Asistencia asistencias[100];  // Array para almacenar las asistencias
    int numMaterias;
    int numAsistencias;
};
// Excepción personalizada para manejar errores relacionados con la asistencia
struct AsistenciaException {
    char message[100];
};

// Función para mostrar un estudiante
void mostrarEstudiante(const struct Estudiante* estudiante) {
    printf("Nombre: %s\n", estudiante->nombre);
    printf("Edad: %d años\n", estudiante->edad);
    printf("Promedio: %.2f\n", estudiante->promedio);

    printf("Materias Inscritas:\n");
    for (int i = 0; i < estudiante->numMaterias; ++i) {
        printf("  %s\n", estudiante->materias[i]);
    }

    printf("\nAsistencias Registradas:\n");
    for (int i = 0; i < estudiante->numAsistencias; ++i) {
        printf("Fecha: %s - Materia: %s - Estado: %s\n", estudiante->asistencias[i].fecha,
               estudiante->asistencias[i].materia, estudiante->asistencias[i].estado);
    }
}

// Función para registrar la asistencia de un estudiante
void registrarAsistencia(struct Estudiante* estudiante, const struct Asistencia* asistencia) {
    // Verificar si la materia de la asistencia está inscrita por el estudiante
    int materiaInscrita = 0;
    for (int i = 0; i < estudiante->numMaterias; ++i) {
        if (strcmp(estudiante->materias[i], asistencia->materia) == 0) {
            materiaInscrita = 1;
            break;
        }
    }

    if (!materiaInscrita) {
        struct AsistenciaException ex;
        snprintf(ex.message, sizeof(ex.message), "El estudiante no está inscrito en la materia de la asistencia.");
        // Lanzar la excepción
        printf("Error de asistencia: %s\n", ex.message);
        exit(EXIT_FAILURE);
    }

    // Registrar la asistencia
    strcpy(estudiante->asistencias[estudiante->numAsistencias].fecha, asistencia->fecha);
    strcpy(estudiante->asistencias[estudiante->numAsistencias].materia, asistencia->materia);
    strcpy(estudiante->asistencias[estudiante->numAsistencias].estado, asistencia->estado);
    estudiante->numAsistencias++;
}

int main() {
    // Crear un estudiante
    struct Estudiante estudiante1;
    strcpy(estudiante1.nombre, "Juan");
    estudiante1.edad = 20;
    estudiante1.promedio = 8.5;

    // Agregar materias
    strcpy(estudiante1.materias[0], "Matemáticas");
    strcpy(estudiante1.materias[1], "Programación");
    estudiante1.numMaterias = 2;

    // Mostrar la información del estudiante
    mostrarEstudiante(&estudiante1);

    // Registrar asistencia
    struct Asistencia asistencia1 = {"2023-01-15", "Matemáticas", "asistió"};
    registrarAsistencia(&estudiante1, &asistencia1);

    // Mostrar la información actualizada
    printf("\nDespués de registrar asistencia:\n");
    mostrarEstudiante(&estudiante1);

    // Intentar registrar asistencia en una materia no inscrita
    struct Asistencia asistenciaInvalida = {"2023-01-20", "Historia", "asistió"};
    registrarAsistencia(&estudiante1, &asistenciaInvalida);  // Esto debería lanzar una excepción

    return 0;
}