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

#include "stdlib.h"
#include "stdio.h"
#include <GLUT/glut.h>
#include <ctype.h>
#include "user_code.h"
#include <iostream>
#include <string.h>
#include <vector>
#include "vertex.h"    
#include "file_ply_stl.h"
#include <OpenGL/gl.h>

// Caras y vertices
std::vector<GLfloat> vertices_ply; // coordenadas de vértices
std::vector<GLint> caras_ply;    // índices de vértices de triángulos
const char* fichero;
int n;
Figura figura;
typedef enum {ROBOT,FIG} _object_type;

_object_type Object_type;

Robot robot;
// tamaño de los ejes
const int AXIS_SIZE=5000;

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

    //formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
    // Front_plane>0  Back_plane>PlanoDelantero)
    glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{
    //posicion del observador
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
    //eje X, color rojo
    glColor3f(1,0,0);
    glVertex3f(-AXIS_SIZE,0,0);
    glVertex3f(AXIS_SIZE,0,0);
    //eje Y, color verde
    glColor3f(0,1,0);
    glVertex3f(0,-AXIS_SIZE,0);
    glVertex3f(0,AXIS_SIZE,0);
    //eje Z, color azul
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
    glColor3f(0,1,0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    // Codigo para dibujar objetos

    switch (Object_type)
    {
	case ROBOT: robot.dibujar(n); break;
    	case FIG:
	{
	    switch (n) 
    	    {
    	        case 0:
          	    figura.dibujar_vertices(); //modo puntos
         	    break;           
        	case 1 :
        	    figura.dibujar_aristas(); //modo aristas
        	    break;
        	case 2:
        	    figura.dibujar_triangulos(); //modo solido
        	    break;
        	case 3:
        	    figura.dibujar_triangulos_ajedrez(); //modo ajedrez
        	    break;
    	    }
	}; break;
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
    switch (toupper(Tecla1)) 
    {
        case 'Q': exit(0); break;
	case 'P': n = 0; break;
	case 'L': n = 1; break;
	case 'S': n = 2; break;
	case 'A': n = 3; break;
	case '1': Object_type=FIG;figura.leer_ply("perfil");figura.dibujar_aristas_perfil(); break; //perfil
        case '2': Object_type=FIG;figura.revoluciones("perfil", 20); break; //objeto por revolucion
        case 'W': Object_type=FIG;figura.revoluciones("perfil", 20);figura.dibujar_normales_vertices(); break;
        case 'E': Object_type=FIG;figura.revoluciones("perfil", 20);figura.dibujar_normales_caras(); break;
	case '3': Object_type=ROBOT;robot.dibujar(n); break;
        case ' ': Object_type=ROBOT;robot.caminar(); break;
        case 'Z': Object_type=ROBOT;robot.cabeza_izquierda(); break;
	case 'X': Object_type=ROBOT;robot.cabeza_derecha(); break;
	case 'C': Object_type=ROBOT;robot.brazos_arriba(); break;
	case 'V': Object_type=ROBOT;robot.brazos_abajo(); break;
	case 'B': Object_type=ROBOT;robot.paso_adelante(); break;
	case 'N': Object_type=ROBOT;robot.paso_atras(); break;
	case 'D': Object_type=ROBOT;robot.brazod_arriba(); break;
	case 'F': Object_type=ROBOT;robot.brazod_abajo(); break;
	case 'G': Object_type=ROBOT;robot.brazoi_arriba(); break;
	case 'H': Object_type=ROBOT;robot.brazoi_abajo(); break;
	case '.': Object_type=ROBOT;robot.cuello_aumentar(); break;
	case ',': Object_type=ROBOT;robot.cuello_disminuir(); break;
	case 'J': Object_type=ROBOT;robot.piernad_arriba(); break;
	case 'K': Object_type=ROBOT;robot.piernad_abajo(); break;
	case 'O': Object_type=ROBOT;robot.piernai_arriba(); break;
	case 'I': Object_type=ROBOT;robot.piernai_abajo(); break;
	case 'U': Object_type=ROBOT;robot.brazod_aumentar(); break;
	case 'Y': Object_type=ROBOT;robot.brazod_disminuir(); break;
	case 'T': Object_type=ROBOT;robot.brazoi_aumentar(); break;
	case 'R': Object_type=ROBOT;robot.brazoi_disminuir(); break;
	case '-': Object_type=ROBOT;robot.act_giro_manos(); break;
	case '<': Object_type=ROBOT;robot.put_act_laser(); break;

	default: glutPostRedisplay();	
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
    switch (Tecla1)
    {
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	case GLUT_KEY_F1:Observer_distance*=1.2;break;
    	case GLUT_KEY_F2:Observer_distance/=1.2;break;
	case GLUT_KEY_F12:Object_type=ROBOT; robot.robot_defecto(); break;
    }
    glutPostRedisplay();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
    //se inicalizan la ventana y los planos de corte
    Window_width=1;
    Window_height=1;
    Front_plane=2;
    Back_plane=2000;

    //se inicia la posicion del observador, en el eje z
    Observer_distance=3*Front_plane;
    Observer_angle_x=0;
    Observer_angle_y=0;

    //se indica cual sera el color para limpiar la ventana	(r,v,a,al)
    //blanco=(1,1,1,1) rojo=(1,0,0,1), ...
    glClearColor(1,1,1,1);

    //se habilita el z-bufer
    glEnable(GL_DEPTH_TEST);
    change_projection();
    glViewport(0,0,UI_window_width,UI_window_height);

    Object_type=ROBOT;
}

//******************************************************************************
// Funcion IDLE
// Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.
//******************************************************************************
void idle()
{
    if (Object_type==ROBOT)
	robot.control_animacion();

    if(robot.get_laser())
	robot.laser();

    if(robot.get_g_manos())
	robot.girar_manos();

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
    glutCreateWindow("Practica 3: Anacleto");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // asignación de la funcion "idle" para ejecución de fondo
    glutIdleFunc(idle);

    // funcion de inicialización
    initialize();

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}
