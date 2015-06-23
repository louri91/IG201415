//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************


#include "user_code.h"
#include "vertex.h"
#include "file_ply_stl.hpp"
#include <GLUT/glut.h>

#include <vector>

//std::vector<float> vertices;
//std::vector<int> caras;
vector<_vertex3f> vertices1;
vector<_vertex3i> caras1;
//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************

/*void draw_cube_vertices()
{
    GLfloat Vertices[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};
     
     glColor3f(0,1,0);
     glPointSize(4);
     
     glBegin(GL_POINTS);
     for (unsigned i=0;i<8;i++){
     glVertex3fv((GLfloat *) &Vertices[i]);
     }
     glEnd();
}

void draw_cube_aristas(vector<_vertex3f> &Vertices){
    
}


void draw_cube_solido(vector<_vertex3f> &Vertices, vector<_vertex3f> &Caras){
    
}

void draw_cube_ajedrez(vector<_vertex3f> &Vertices, vector<_vertex3f> &Caras){
    
}*/
//**************************************************************************
// Funcion para transformar los datos de las figuras en vectores
// de la clase vertex
//***************************************************************************

void leer_datos(vector <float> vertices3, vector<int> caras3)
{
    //vector<float> vertices;
    //vector<int> caras;
    vertices1.resize(vertices3.size()/3);
    caras1.resize(caras3.size()/3);
    for (int i=0; i<vertices1.size();i++){
        vertices1[i].x = vertices3[i*3];
        vertices1[i].y = vertices3[i*3+1];
        vertices1[i].z = vertices3[i*3+2];
    }
    
    for (int j=0;j<caras1.size();j++){
        caras1[j]._0 = caras3[j*3];
        caras1[j]._1 = caras3[j*3+1];
        caras1[j]._2 = caras3[j*3+2];
    }
}

//**************************************************************************
// Funcion para leer archivo ply
//***************************************************************************

void leer_ply(char* archivo)
{
    vector<float> vertices;
    vector<int> caras;
    ply::read(archivo, vertices, caras);
    vertices1.resize(vertices.size()/3);
    caras1.resize(caras.size()/3);
    for (int i=0; i<vertices1.size();i++){
        vertices1[i].x = vertices[i*3];
        vertices1[i].y  = vertices[i*3+1];
        vertices1[i].z = vertices[i*3+2];
        
    }

    for (int j=0;j<caras1.size();j++){
        caras1[j]._0 = caras[j*3];
        caras1[j]._1 = caras[j*3+1];
        caras1[j]._2 = caras[j*3+2];
    }
    
}
//**************************************************************************
// Funcion para dibujar los vértices
//***************************************************************************


void draw_vertices()
{
    
    glColor3f(0,0,1);
    glPointSize(4);
    
    glBegin(GL_POINTS);
    for (unsigned i=0;i<vertices1.size();i++){
        glVertex3fv((GLfloat *) &vertices1[i]);
    }
    glEnd();
}

//**************************************************************************
// Funcion para dibujar las aristas.
//***************************************************************************

void dibujar_aristas(){
    
    glColor3f(1,0,0);
    glPointSize(4);
    
   // glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_LINES);
    for (unsigned j=0;j<caras1.size();j++){
        
        glVertex3f(vertices1[caras1[j]._0].x, vertices1[caras1[j]._0].y, vertices1[caras1[j]._0].z);
        glVertex3f(vertices1[caras1[j]._1].x, vertices1[caras1[j]._1].y, vertices1[caras1[j]._1].z);
        glVertex3f(vertices1[caras1[j]._1].x, vertices1[caras1[j]._1].y, vertices1[caras1[j]._1].z);
        glVertex3f(vertices1[caras1[j]._2].x, vertices1[caras1[j]._2].y, vertices1[caras1[j]._2].z);
        glVertex3f(vertices1[caras1[j]._2].x, vertices1[caras1[j]._2].y, vertices1[caras1[j]._2].z);
        glVertex3f(vertices1[caras1[j]._0].x, vertices1[caras1[j]._0].y, vertices1[caras1[j]._0].z);

    }
    glEnd();
}


//**************************************************************************
// Funcion para dibujar los triangulos del modelo
//***************************************************************************

void dibujar_triangulos(){
    glBegin(GL_TRIANGLES);
    glColor3f(0,1,0);
    
    for (int i=0; i<caras1.size();i++)
    {
        glVertex3f(vertices1[caras1[i]._0].x, vertices1[caras1[i]._0].y, vertices1[caras1[i]._0].z);
        glVertex3f(vertices1[caras1[i]._1].x, vertices1[caras1[i]._1].y, vertices1[caras1[i]._1].z);
        glVertex3f(vertices1[caras1[i]._2].x, vertices1[caras1[i]._2].y, vertices1[caras1[i]._2].z);
        
    }
    
    glEnd();
    
    
}

//**************************************************************************
// Funcion para dibujar el sólido ajedrez del modelo
//***************************************************************************

void dibujar_triangulos_ajedrez(){
    glBegin(GL_TRIANGLES);
    glColor3f(0,1,0);
    
    for (int i=0; i<caras1.size();i++)
    {
        if(i%2==0){
            glColor3f(1, 1, 1);
        }
        else{
            glColor3f(0, 0, 0);
            }
        glVertex3f(vertices1[caras1[i]._0].x, vertices1[caras1[i]._0].y, vertices1[caras1[i]._0].z);
        glVertex3f(vertices1[caras1[i]._1].x, vertices1[caras1[i]._1].y, vertices1[caras1[i]._1].z);
        glVertex3f(vertices1[caras1[i]._2].x, vertices1[caras1[i]._2].y, vertices1[caras1[i]._2].z);
        
    }
    
    glEnd();
    
    
}

//**************************************************************************
// Funcion para dibujar. Dependiendo de la tecla que se haya pulsado
// se va a ejecutar una función u otra.
//***************************************************************************



void dibujar(int numero)
{
    switch (numero) {
        case 0:
            draw_vertices();
            break;
            
        case 1 :
            dibujar_aristas();
            break;
        case 2:
            dibujar_triangulos();
            break;
        case 3:
            dibujar_triangulos_ajedrez();
            break;

    }
}
