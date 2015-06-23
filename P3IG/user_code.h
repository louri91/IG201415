//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************
//
//  user_code.h
//  P3IG
//
//  Created by Louri on 2/12/14.
//  Copyright (c) 2014 Louri. All rights reserved.
//
//
// Realizado por: Amanda Fernández Piedra
//
//**************************************************************************
#ifndef _OBJETOS
#define _OBJETOS

#include <GLUT/glut.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <vector>
#include "vertex.h"



using namespace std;



const float POINT_SIZE=3;
const float LINE_WIDTH=1;

void caja( float a, float b, float m);

void cono(float x0, float y0, float z0, float x1, float y1, float z1, float a, int n);

class Obj3D
{
public:
    
    Obj3D();
    void dibujar();
    
    float punto;
    float linea;
};

class Cubo
{
private:
    vector<_vertex3f> vc;
    vector<_vertex3i> cc;
    int tipo;
    
public:
    Cubo();
    void dibujar(float a, float b, float c, int n);
    void cubo();
    void escalar(float x, float y, float z);
    void trasladar(float x, float y, float z);
};

class Circulo
{
private:
    vector<_vertex3f> vc;
    vector<_vertex3i> cc;
    int tipo;
public:
    Circulo();
    void circulo();
    void leer_datos(vector<float> vertices, vector<int> caras);
    void revoluciones(int numPerfiles);
    void revolucion_vertices(vector<float> vp,vector<float> &v1,int num_perfiles);
    void revolucion_caras(vector<int> &c1, int num_perfiles, int n);
    void escalar(float x, float y, float z);
    void trasladar(float x, float y, float z);
    void dibujar(float a, float b, float c, int n);
};

//*************************************************************************
// ROBOT
//*************************************************************************

class Robot: public Obj3D
{
private:
    // Parámetros de construcción
    float giro_cabeza;
    float giro_brazod, giro_brazoi;
    float giro_piernad, giro_piernai;
    float rcuello,rbrazod,rbrazoi;
    float giro_manos;
    float camino;
    float d_laser; //Distancia de laser
    bool act_laser; //Control de laser
    bool act_g_manos; // Control del giro de manos
    bool activarCamino;
    bool avanzar;
    
public:
    
    Robot();
    void dibujar(int tipo);
    
    void cabeza_derecha();
    void cabeza_izquierda();
    void laser();
    void brazos_arriba();
    void brazos_abajo();
    void brazod_abajo();
    void brazod_arriba();
    void brazoi_abajo();
    void brazoi_arriba();
    void piernad_arriba();
    void piernad_abajo();
    void piernai_arriba();
    void piernai_abajo();
    void paso_adelante();
    void paso_atras();
    void caminar();
    void cuello_aumentar();
    void cuello_disminuir();
    void brazod_aumentar();
    void brazod_disminuir();
    void brazoi_aumentar();
    void brazoi_disminuir();
    void girar_manos();
    bool get_g_manos();
    void act_giro_manos();
    void robot_defecto();
    void put_act_laser();
    bool get_laser();
    void control_animacion();
    void activarCaminar();
    void caminar1();
    bool getActivarCaminar();
    int aumentarVelocidad;
    
};


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
void lector_cubo(vector<_vertex3f> &Vertices, vector<_vertex3i> &Triangulos);
void dibujar2(int num, vector<_vertex3f> &Vertices, vector<_vertex3i> &Triangulos);
void dibujaajedrez(vector<_vertex3f> &Vertices, vector<_vertex3i> &Triangulos);
void dibujasolido(vector<_vertex3f> &Vertices, vector<_vertex3i> &Triangulos);
void dibujapuntos(vector<_vertex3f> &Vertices);
void dibujaaristas(vector<_vertex3f> &Vertices, vector<_vertex3i> &Triangulos);
void draw_vertices(vector<_vertex3f> &Vertices);

#endif

