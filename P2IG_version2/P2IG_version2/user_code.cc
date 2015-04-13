//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************
//
//
//
//  Amanda Fernández Piedra
//
//**************************************************************************
#include "user_code.h"
#include "vertex.h"
#include "file_ply_stl.hpp"
#include <GLUT/glut.h>
#include <math.h>
#include <vector>

//std::vector<float> vertices;
//std::vector<int> caras;

vector<_vertex3f> vertices1;
vector<_vertex3i> caras1;
vector<_vertex3f> normalesTriangulos;
vector<_vertex3f> puntosNormales;


//***********************************
// Funciones utiles para los calculos
//***********************************

void leer_ply(const char* nombre_fichero, bool revolucion, vector<float> &vertices, vector<int> &caras, int numRevoluciones){
    
    if(revolucion==true)
    {
        vertices.clear();
        caras.clear();
        vertices1.clear();
        caras1.clear();
        vector<float> vertices_perfil;
        ply::read_vertices(nombre_fichero,vertices_perfil);
        bool inferior,superior;
        inferior = false;
        superior = false;
        if(vertices_perfil[0]==0.0 && vertices_perfil[2]==0.0){
            inferior = true;
        }
        if(vertices_perfil[vertices_perfil.size()-3]==0.0 && vertices_perfil[vertices_perfil.size()-1]==0.0){
            superior = true;
        }
        generar_vertices(vertices_perfil,vertices,numRevoluciones,'Y',inferior, superior);
        generar_caras(caras,numRevoluciones,(vertices_perfil.size())/3,inferior,superior);
        leer_datos(vertices, caras);
        calcular_normales_triangulos(caras1, vertices1);
    }
    else
    {
        ply::read(nombre_fichero, vertices, caras);
        leer_datos(vertices, caras);
    }
}

void generar_vertices( vector<float> vertices, vector<float> &vertices_final, int numRevoluciones, char eje, bool inferior, bool superior)
{
    int i,j;
    double alpha = 30*M_PI/180;
    double betha = 270*M_PI/180;
    double angulo = alpha;
    
    //Insercion del primero perfil en la lista
    //Para que empiece desde cero:
    //for(k=0;k<vertices.size();k++)
        //vertices_final.push_back(vertices[k]);
    
    //Generacion de los vertices con tecnica de revolucion (rotacion sobre el eje)
    for(j=0;j<numRevoluciones;j++)
    {
        angulo = (j*((betha-alpha)/(numRevoluciones-1)))+alpha;
        //anguloFinal = alpha/(numRevoluciones-1);
        //alpha = j * (2*PI/(numRevoluciones-1));
        for(i=0;i<vertices.size();i+=3)
        {
            float vx, vy, vz;
            if(eje == 'X')
            {
                vx = vertices[i];
                vy = cos(angulo)*vertices[i+1] - sin(angulo)*vertices[i+2];
                vz = sin(angulo)*vertices[i+1] + cos(angulo)*vertices[i+2];
            }
            else if(eje == 'Y')
            {
                vx = cos(angulo)*vertices[i] + sin(angulo)*vertices[i+2];
                vy = vertices[i+1];
                vz = -sin(angulo)*vertices[i] + cos(angulo)*vertices[i+2];
            }
            else
            {
                vx = cos(angulo)*vertices[i] - sin(angulo)*vertices[i+1];
                vy = sin(angulo)*vertices[i] + cos(angulo)*vertices[i+1];
                vz = vertices[i+2];
            }
            
            vertices_final.push_back(vx);
            vertices_final.push_back(vy);
            vertices_final.push_back(vz);
        }
    }
    
    //Generacion del ultimo perfil (igual al primero)
    //alpha = 0;
    for(i=0;i<vertices.size();i+=3)
    {
        float vx, vy, vz;
        if(eje == 'X')
        {
            vx = vertices[i];
            vy = cos(angulo)*vertices[i+1] - sin(angulo)*vertices[i+2];
            vz = sin(angulo)*vertices[i+1] + cos(angulo)*vertices[i+2];
        }
        else if(eje == 'Y')
        {
            vx = cos(angulo)*vertices[i] + sin(angulo)*vertices[i+2];
            vy = vertices[i+1];
            vz = -sin(angulo)*vertices[i] + cos(angulo)*vertices[i+2];
        }
        else
        {
            vx = cos(angulo)*vertices[i] - sin(angulo)*vertices[i+1];
            vy = sin(angulo)*vertices[i] + cos(angulo)*vertices[i+1];
            vz = vertices[i+2];
        }
        
        vertices_final.push_back(vx);
        vertices_final.push_back(vy);
        vertices_final.push_back(vz);
    }
    
    //Generacion de los 2 ultimos vertices para las tapas inferior y superior
    

    float vx1, vy1, vz1, vx2, vy2, vz2;
    if(eje == 'X')
    {
    if(inferior==true){
    vx1 = vertices[0];
    vy1 = 0;
    vz1 = 0;
    }
    if(superior==true){
        vx2 = vertices[vertices.size()-3];
        vy2 = 0;
        vz2 = 0;
    }
   
    }
    else if(eje == 'Y')
    {
        if(inferior==true){
            vx1 = 0;
            vy1 = vertices[1];
            vz1 = 0;
        }
    if(superior==true){
        vx2 = 0;
        vy2 = vertices[vertices.size()-2];
        vz2 = 0;
        }
    }
    else
    {
        if(inferior==true){
        vx1 = 0;
        vy1 = 0;
        vz1 = vertices[2];
        }
        if(superior==true){
        vx2 = 0;
        vy2 = 0;
        vz2 = vertices[vertices.size()-1];
        }
    }
    
    if(inferior==true){
        vertices_final.push_back(vx1);
        vertices_final.push_back(vy1);
        vertices_final.push_back(vz1);
    }
    
    if(superior==true){
        vertices_final.push_back(vx2);
        vertices_final.push_back(vy2);
        vertices_final.push_back(vz2);
    }
    
}


void generar_caras(vector<int> &caras, int numRevoluciones, int numCaras, bool inferior, bool superior)
{
    for(unsigned int i=0;i<numRevoluciones;i++)
    {
        int i1, i2, i3, i4, i5, i6 ;
        for(unsigned int j=0;j<numCaras-1;j++)
        {
            
            if(i!=numRevoluciones || i!=numRevoluciones-1 || i!=numRevoluciones-2){
            //primero triangulo
            //if(){
                i1=numCaras*i+j;
                i2=numCaras*i+j+1;
                i3=(numCaras*(i+1)+j+1);
                
                //segundo triangulo
                i4=numCaras*i+j;
                i5=(numCaras*(i+1)+j);
                i6=(numCaras*(i+1)+j+1);
                
                caras.push_back(i1);
                caras.push_back(i2);
                caras.push_back(i3);
                caras.push_back(i4);
                caras.push_back(i5);
                caras.push_back(i6);
                
                }
           // }
            
            /*i1=numCaras*i+j;
            i2=numCaras*i+j+1;
            i3=(numCaras*(i+1)+j+1)%(numCaras*(numRevoluciones+1));
            
            //segundo triangulo
            i4=numCaras*i+j;
            i5=(numCaras*(i+1)+j)%(numCaras*(numRevoluciones+1));
            i6=(numCaras*(i+1)+j+1)%(numCaras*(numRevoluciones+1));
            
            caras.push_back(i1);
            caras.push_back(i2);
            caras.push_back(i3);
            caras.push_back(i4);
            caras.push_back(i5);
            caras.push_back(i6);*/
        }
   	}
    
    //Generacion de las caras de la tapa inferior

    
    if(inferior==true){
        for(unsigned int i=0;i<numRevoluciones;i++)
        {
            int i1, i2, i3;
            i1=numCaras*(numRevoluciones+1);
            i2=numCaras*i;
            i3=(numCaras*(i+1));
            
            caras.push_back(i1);
            caras.push_back(i2);
            caras.push_back(i3);
        }
    }
    
    
    //Generacion de las caras de la tapa superior
    
    if(superior==true){
        for(unsigned int i=0;i<numRevoluciones;i++)
        {
            int i1, i2, i3;
            i1=numCaras*(numRevoluciones+1)+1;
            i2=numCaras*(i+1)-1;
            i3=(numCaras*(i+2)-1);
            
            caras.push_back(i1);
            caras.push_back(i2);
            caras.push_back(i3);
        }
    }
    
}

//Generar y almacenar normales de triángulos y vértices

void calcular_normales_triangulos(vector<_vertex3i> &caras, vector<_vertex3f> &vertices){
    normalesTriangulos.resize(caras.size());
    puntosNormales.resize(caras.size());
    float vx1,vy1,vz1,vx2,vy2,vz2,vx3,vy3,vz3;
    for (int i=0; i<caras.size();i++){
        vx1 = vertices[caras[i]._1].x - vertices[caras[i]._0].x;
        vy1 = vertices[caras[i]._1].y - vertices[caras[i]._0].y;
        vz1 = vertices[caras[i]._1].z - vertices[caras[i]._0].z;
        vx2 = vertices[caras[i]._2].x - vertices[caras[i]._1].x;
        vy2 = vertices[caras[i]._2].y - vertices[caras[i]._1].y;
        vz2 = vertices[caras[i]._2].z - vertices[caras[i]._1].z;
        
        vx3 = vy1*vz2 - vz1*vy2;
        vy3 = vz1*vx2 - vx1*vz2;
        vz3 = vx1*vy2 - vy1*vx2;
        normalesTriangulos[i].x = vx3;
        normalesTriangulos[i].y = vy3;
        normalesTriangulos[i].z = vz3;
    }
    
    for(int i=0; i<caras.size();i++){
        puntosNormales[i]._0 = (vertices[caras[i]._0].x+vertices[caras[i]._1].x+vertices[caras[i]._2].x)/3;
        puntosNormales[i]._1 = (vertices[caras[i]._0].y+vertices[caras[i]._1].y+vertices[caras[i]._2].y)/3;
        puntosNormales[i]._2 = (vertices[caras[i]._0].z+vertices[caras[i]._1].z+vertices[caras[i]._2].z)/3;
    }
    
    /*normalesTriangulos.resize(caras.size());
     float vx1,vy1,vz1,vx2,vy2,vz2,vx3,vy3,vz3;
     for (int i=0; i<caras.size();i++){
     vx1 = vertices[caras[i+1]._0].x - vertices[caras[i]._0].x;
     vy1 = vertices[caras[i+1]._0].y - vertices[caras[i]._0].y;
     vz1 = vertices[caras[i+1]._0].z - vertices[caras[i]._0].z;
     vx2 = vertices[caras[i+2]._0].x - vertices[caras[i+1]._0].x;
     vy2 = vertices[caras[i+2]._0].y - vertices[caras[i+1]._0].y;
     vz2 = vertices[caras[i+2]._0].z - vertices[caras[i+1]._0].z;
     
     vx3 = vy1*vz2 - vz1*vy2;
     vy3 = vz1*vx2 - vx1*vz2;
     vz3 = vx1*vy2 - vy1*vx2;
     normalesTriangulos[i].x = vx3;
     normalesTriangulos[i].y = vy3;
     normalesTriangulos[i].z = vz3;
     }
*/
    
}







//**************************************************************************
// Funcion para transformar los datos de las figuras en vectores
// de la clase vertex
//***************************************************************************


void leer_datos(vector <float> vertices3, vector<int> caras3)
{
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

/*void leer_ply(char* archivo)
{
    vector<float> vertices;
    vector<int> caras;
    ply::read(archivo, vertices, caras);
    leer_datos(vertices, caras);
}*/


//**************************************************************************
// Funcion para dibujar los vértices
//***************************************************************************

void draw_vertices()
{
    glColor3f(0,0,1);
    glPointSize(3);
    glBegin(GL_POINTS);
    for (int i=0;i<vertices1.size();i++){
        glVertex3f(vertices1[i]._0,vertices1[i]._1,vertices1[i]._2);
    }

    glEnd();
}



//**************************************************************************
// Funcion para dibujar las aristas.
//***************************************************************************

void dibujar_aristas(){
    
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    for (int j=0;j<caras1.size();j++){
        //glVertex3fv((GLfloat*) &vertices1[j]);
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
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_TRIANGLES);
    glColor3f(0,0.5,0);
    
    for (int i=0; i<caras1.size();i++)
    {
            glVertex3f(vertices1[caras1[i]._0].x, vertices1[caras1[i]._0].y, vertices1[caras1[i]._0].z);
            glVertex3f(vertices1[caras1[i]._1].x, vertices1[caras1[i]._1].y, vertices1[caras1[i]._1].z);
            glVertex3f(vertices1[caras1[i]._2].x, vertices1[caras1[i]._2].y, vertices1[caras1[i]._2].z);
        
    }
    glEnd();
}

void dibujar_triangulos_ajedrez(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    
    for (int i=0; i<caras1.size();i++)
    {
        if(i%2!=0){
            glColor3f(0.3,0.3,0.3);
        }
        else{
            glColor3f(0.7,0.7,0.7);
        }
            glVertex3f(vertices1[caras1[i]._0].x, vertices1[caras1[i]._0].y, vertices1[caras1[i]._0].z);
            glVertex3f(vertices1[caras1[i]._1].x, vertices1[caras1[i]._1].y, vertices1[caras1[i]._1].z);
            glVertex3f(vertices1[caras1[i]._2].x, vertices1[caras1[i]._2].y, vertices1[caras1[i]._2].z);
    }
    glEnd();
}

void dibujar_puntos_normales_triangulos(){
    glPointSize(3);
    glBegin(GL_POINTS);

    glColor3f(1,0,0);
    for (int i=0;i<puntosNormales.size();i++){
        glVertex3f(puntosNormales[i]._0,puntosNormales[i]._1,puntosNormales[i]._2);
    }
    glEnd();
    
    /*for (int i=0;i<normalesTriangulos.size();i++){
     glVertex3f(normalesTriangulos[i]._0,normalesTriangulos[i]._1,normalesTriangulos[i]._2);
     }*/
}

void dibujar_normales_triangulos(){
    glPointSize(3);
    glBegin(GL_LINES);
    glColor3f(0,1,0);
    
    for (int i=0;i<puntosNormales.size();i++){
        glVertex3f(puntosNormales[i]._0,puntosNormales[i]._1,puntosNormales[i]._2);
        glVertex3f(puntosNormales[i]._0+normalesTriangulos[i]._0,puntosNormales[i]._1+normalesTriangulos[i]._1,puntosNormales[i]._2+normalesTriangulos[i]._2);
    }
    glEnd();
}
//**************************************************************************
// Funcion para dibujar. Dependiendo de la tecla que se haya pulsado
// se va a ejecutar una función u otra.
//***************************************************************************



/*void dibujar(int numero)
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
}*/



