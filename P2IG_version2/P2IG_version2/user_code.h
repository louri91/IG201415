//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include <OpenGL/gl.h>
#include <vector>
#include "vertex.h"



using namespace std;

void draw_cube();
void dibujar_aristas();
void dibujar_triangulos();
void dibujar_triangulos_ajedrez();
void dibujar(int num);
void draw_vertices();
void draw_vertices_rotado();
void leer_ply(char* archivo);
void leer_datos(vector<float> vertices, vector<int> caras);
void generar_vertices( vector<float> vertices, vector<float> &vertices_final, int numRevoluciones, char eje, bool inferior, bool superior);
void generar_caras(vector<int> &caras, int numRevoluciones, int numCaras, bool inferior, bool superior);
void leer_ply(const char* nombre_fichero, bool revolucion, vector<float> &vertices, vector<int> &caras, int numRevoluciones);
void calcular_normales_triangulos(vector<_vertex3i> &caras, vector<_vertex3f> &vertices);
void dibujar_normales_triangulos();
void dibujar_puntos_normales_triangulos();
void quitar_triangulos_repetidos();