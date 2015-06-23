//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************
//
//  practica3.cc
//  P3IG
//
//  Created by Louri on 2/12/14.
//  Copyright (c) 2014 Louri. All rights reserved.
//
// Realizado por: Amanda Fernández Piedra
//
//**************************************************************************


#include "stdlib.h"
#include "stdio.h"
#include <GLUT/glut.h>
#include <ctype.h>
#include "user_code.h"
#include <vector>
#include <math.h>

using namespace std;

typedef enum {ROBOT,FIG} _object_type;

_object_type Object_type;

Robot robot;
bool avanzarRobot=true;
int contador=0;
bool pararAndar =false;
// tamaño de los ejes
const int AXIS_SIZE=5000;

//CAMBIAR RUTA
char *archivoPly = "/Users/Louri/Google Drive/PRACTICASUGR/IG/P3IG/P3IG/P3IG/beethoven.ply";
char *perfil_1 = "/Users/Louri/Google Drive/PRACTICASUGR/IG/P3IG/P3IG/P3IG/cilindro.ply";
char *perfil_2 = "/Users/Louri/Google Drive/PRACTICASUGR/IG/P3IG/P3IG/P3IG/perfil_2.ply";
char *perfil_3 = "/Users/Louri/Google Drive/PRACTICASUGR/IG/P3IG/P3IG/P3IG/perfil_3.ply";
char *perfil_4 = "/Users/Louri/Google Drive/PRACTICASUGR/IG/P3IG/P3IG/P3IG/perfil_4.ply";
char *perfil_5 = "/Users/Louri/Google Drive/PRACTICASUGR/IG/P3IG/P3IG/P3IG/perfil_5.ply";
char *perfil_6 = "/Users/Louri/Google Drive/PRACTICASUGR/IG/P3IG/P3IG/P3IG/perfil_6.ply";
//char *cuboPly = "/Users/Louri/Google Drive/PRACTICASUGR/IG/P3IG/P3IG/P3IG/cubo.ply";
int modo = 4;
int numero;
char* archivo;
vector<_vertex3f> Vertices;
vector<_vertex3i> Triangulos;
vector<_vertex3f> Puntos;

int num;
vector<float> vertices;
vector<int> caras;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
    switch (Object_type)
    {
        case ROBOT: robot.dibujar(modo);
            break;
    }
}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
    if (toupper(Tecla1)=='Q') exit(0);
    
    
    switch (Tecla1)
    {
        case 'p': modo=0;break;
        case 'l': modo=1;break;
        case 's': modo=2;break;
        case 'a': modo=3;break;
        case 'n': modo = 5;break;
        case '1': leer_ply(archivoPly, false, vertices, caras, 0);break;
        case '2': leer_ply(perfil_1, true, vertices, caras, 7);break;
        case '3': Object_type=ROBOT; robot.dibujar(modo);break;
        case '-': Observer_distance*=1.2;break;
        case '+': Observer_distance/=1.2;break;
        case 'Z': Object_type=ROBOT;robot.cabeza_izquierda(); break;
        case 'z': Object_type=ROBOT;robot.cabeza_derecha(); break;
        case 'X': Object_type=ROBOT;robot.brazos_arriba(); break;
        case 'x': Object_type=ROBOT;robot.brazos_abajo(); break;
        case 'C': Object_type=ROBOT;robot.brazod_arriba(); break;
        case 'c': Object_type=ROBOT;robot.brazod_abajo(); break;
        case 'V': Object_type=ROBOT;robot.brazoi_arriba(); break;
        case 'v': Object_type=ROBOT;robot.brazoi_abajo(); break;
        case 'B': Object_type=ROBOT;robot.paso_adelante(); break;
        case 'b': Object_type=ROBOT;robot.paso_atras(); break;
        case 'N': Object_type=ROBOT;robot.piernad_arriba(); break;
        case 'M': Object_type=ROBOT;robot.piernad_abajo(); break;
        case 'm': Object_type=ROBOT;robot.piernai_arriba(); break;
        case 'L': Object_type=ROBOT;robot.piernai_abajo(); break;
        case 'A': Object_type=ROBOT;robot.activarCaminar(); break;
        case 'O': robot.aumentarVelocidad++;break;
        case 'o': robot.aumentarVelocidad--;break;
        case 'P': robot.act_giro_manos(); break;
        default:glutPostRedisplay();
    }
    glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
    case GLUT_KEY_F1:Observer_distance*=1.2;break;
    case GLUT_KEY_F2:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=1;
Window_height=1;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=3*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);
}

void idle()
{
    if (Object_type==ROBOT)
        robot.control_animacion();
    if(robot.get_g_manos())
        robot.girar_manos();
    if(robot.getActivarCaminar()){
        if(avanzarRobot==true){
            robot.paso_adelante();
            robot.cabeza_derecha();
        }
        else{
            robot.paso_atras();
            robot.cabeza_izquierda();
        }
    }
    if(contador%35==0){
        avanzarRobot=!avanzarRobot;
    }
    contador++;
    glutPostRedisplay();
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
    // se llama a la inicialización de glut
    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Práctica 3. Robot");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // asignaci√≥n de la funcion "idle" para ejecuci√≥n de fondo
    glutIdleFunc(idle);

    // funcion de inicialización
    initialize();

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}
