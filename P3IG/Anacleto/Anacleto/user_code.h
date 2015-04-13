//**************************************************************************
// Práctica 3
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************
//**************************************************************************
// Realizado por:
//
// Nikolai Giovanni González López
//
// DNI: 74692748-H
//**************************************************************************
#include <OpenGL/gl.h>
#include <iostream>
#include <vector>
#include "vertex.h"
#include <stdlib.h>
#include <GLUT/glut.h>

using namespace std;

class Figura
{
    private:
	vector<_vertex3f> v; //vector de vertices
	vector<_vertex3i> c; //vector de caras
	vector<_vertex3f> nv; //vector de vertices normales
	vector<_vertex3f> nc; //vector de caras normales

    public:
       	//Práctica 1
	Figura(){}; 
	void dibujar_vertices();
	void dibujar_aristas();
	void dibujar_triangulos();
	void dibujar_triangulos_ajedrez();
	void leer_ply(const char* fichero);
	void leer_datos(vector<float> vertices, vector<int> caras);

	//Práctica 2 
	void revoluciones(const char *fichero, int numPerfiles);
	void revolucion_vertices(vector<float> vp,vector<float> &v1,int num_perfiles,bool sup, bool inf);
	void revolucion_caras(vector<int> &c1, int num_perfiles, int n, bool sup, bool inf);
	void cubo_revolucion();
	void calcular_normales();
	void dibujar_aristas_perfil();
	void dibujar_normales_vertices();
	void dibujar_normales_caras();
	vector<_vertex3f> get_v();
	vector<_vertex3i> get_c();
};

//A partir de aqui Practica 3 (Robot)

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
	vector<_vertex3f> vc; //vector de vertices
	vector<_vertex3i> cc; //vector de caras
	int tipo; // 0 -> Puntos; 1 -> Aristas; 2 -> Sólido y 3 -> Ajedrez

    public:
	Cubo();
	void dibujar(float a, float b, float c, int n);
	void cubo_defecto();
	void escalar(float x, float y, float z);
	void trasladar(float x, float y, float z);
};

class Circulo
{
    private:
	vector<_vertex3f> vc; //vector de vertices
	vector<_vertex3i> cc; //vector de caras
	int tipo; // 0 -> Puntos; 1 -> Aristas; 2 -> Sólido y 3 -> Ajedrez
    public:
	Circulo();
	void circulo_defecto();
	void leer_datos(vector<float> vertices, vector<int> caras);
	void revoluciones(int numPerfiles);
	void revolucion_vertices(vector<float> vp,vector<float> &v1,int num_perfiles/*, bool sup, bool inf*/);
	void revolucion_caras(vector<int> &c1, int num_perfiles, int n/*, bool sup, bool inf*/);
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
	float d_laser; //Distancia de laser
	bool act_laser; //Control de laser
	bool act_g_manos; // Control del giro de manos
	bool adelante; //true si camina hacia adelante

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
};
