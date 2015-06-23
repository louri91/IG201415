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
typedef GLfloat Real ;

typedef GLuint Natural ;

const unsigned int X=0, Y=1, Z=2 ;	// indices enteros de los ejes


struct Tupla3r		// tupla con 3 valores reales que representan coordenas
{
    Real coo[3];
} ;

struct Tupla3n		// tupla de 3 entero no negativos (naturales)
{
    Natural ind[3];
} ;

struct CVerTri		// Coordenadas de los 3 vertices de un triangulo
{
    Tupla3r ver[3];
} ;

struct MallaTVT		// Malla con tabla de vertices y triangulos
{
    Natural num_ver ;	//numero de vertices
    Natural num_tri	;	//numero de triangulos
    Tupla3r * ver ;		//tabla de vertices (num_ver entradas)
    Tupla3n * tri ;		//tabla de triangulos (num_tri entradas)
				//Atributos
    Tupla3r * nor_tri ;	//normales de triangulos (num_tri entradas)
    Tupla3r * nor_ver ;	//normales de vertices (num_ver entradas)
    Tupla3r * col_tri ; 	//colores de triangulos(num_tri entradas)
    Tupla3r * col_ver ;	//colores de vertices (num_ver entradas)
    
    GLuint id_vbo_ver ; 	//identificador del VBO con la tabla de vertices
    GLuint id_vbo_tri ; 	//identificador del VBO con la tabla de triangulos
    
    GLuint id_vbo_col_ver;
    GLuint id_vbo_nor_ver;
    GLuint id_vbo_nor_tri;
    
    unsigned int tam_ver ; 	//tamano en bytes de la table de vertices
    unsigned int tam_tri ;	//tamano en bytes de la tabla de triangulos
    
} ;


void draw_cube();
void dibujar_aristas();
void dibujar_triangulos();
void dibujar_triangulos_ajedrez();
void dibujar(int num);
void draw_vertices();
void draw_vertices_rotado();
void leer_ply(char* archivo);
void leer_datos(vector<float> vertices, vector<int> caras);

//****************************************************************************
// Funciones para generar una malla (leer ply y generar atributos de la malla)
//****************************************************************************

void leer_ply(const char* nombre_fichero, bool revolucion, vector<float> &vertices, vector<int> &caras, int N);

void generar_malla(MallaTVT* malla, const char* nombre_fichero, bool revolucion, int N);


//****************************************************************************************
// Funciones para generar y almacenar los vertices y caras (malla generada por revolucion)
//****************************************************************************************

void generar_vertices( vector<float> vertices, vector<float> &vertices_final, int N, char eje);

void generar_caras(vector<int> &caras, int N, int M);


//*******************************************************************************************************
// Funciones para generar y almacenar los normales a los vertices y caras (malla generada por revolucion)
//*******************************************************************************************************

void calcular_normales_tri(MallaTVT* malla);

void calcular_normales_ver(MallaTVT * malla);

//********************************************************************
// Funciones para dibujar una malla (creacion y visualizacion de VBOs)
//*********************************************************************

void draw_matriz(MallaTVT* malla, int modo);

void MTVT_Visualizar_VA(MallaTVT * pm);

GLuint VBO_Crear(GLuint tipo, GLuint tamanio, GLvoid * puntero);

void MTVT_Crear_VBOs(MallaTVT * pm);

void MTVT_Visualizar_VBOs(MallaTVT *pm);

void MTVT_Visualizar_VBOs_AV(MallaTVT *pm);
