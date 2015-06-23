//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************
//
//  user_code.cc
//  P3IG
//
//  Created by Louri on 2/12/14.
//  Copyright (c) 2014 Louri. All rights reserved.
//
// Realizado por: Amanda Fernández Piedra
//
//**************************************************************************

#include "user_code.h"
#include "vertex.h"
#include "file_ply_stl.hpp"
#include <GLUT/glut.h>
#include <vector>
#include "math.h"
#include <unistd.h>


#define amarillo 0
#define gris 1
#define rojo 2
#define	marron 3
#define celeste 4
#define marron2 5
#define verde 6
#define azul 7

//Parámetros para la construcción
float giro_cabeza;
float giro_brazod, giro_brazoi;
float rcuello,rmanod,rmanoi;
float cuerpo,cabeza,hombro;
float giro_manos;
bool act_g_manos; // Control del giro de manos
bool adelante;

int miTipo;

vector<float> vertices10;
vector<int> caras10;
vector<_vertex3f> vertices1;
vector<_vertex3i> caras1;
vector<_vertex3f> normalesTriangulos;
vector<_vertex3f> puntosNormales;
char *cuboPly = "/Users/Louri/Google Drive/PRACTICASUGR/IG/P3IG/P3IG/P3IG/cubo.ply";
char *cilindroPly = "/Users/Louri/Google Drive/PRACTICASUGR/IG/P3IG/P3IG/P3IG/cilindro.ply";
char *beethoven = "/Users/Louri/Google Drive/PRACTICASUGR/IG/P3IG/P3IG/P3IG/beethoven.ply";
char *cilindro = "/Users/Louri/Google Drive/PRACTICASUGR/IG/P3IG/P3IG/P3IG/cilindro.ply";

float color[8][4]={{1,.8,.3,1.},{0.7,0.7,0.7,1},{1.0,0.0,0.0,1},
    {0.7,0.6,0.2,1},{0.2,1.0,1.0,1},{1.0,0.86,0.3,1},
    {0.0,1.0,0.0,1.0}, {0.0,0.0,1.0,1.0}};

//*************************************************************************
// PRACTICA 3 || Robot
//*************************************************************************

Cubo::Cubo()
{
    cubo();
}

void Cubo::cubo()
{
    vc.resize(8);
    cc.resize(12);
    //vertices
    vc[0].x = -0.5;
    vc[0].y = 0.0;
    vc[0].z = 0.5;
    vc[1].x = 0.5;
    vc[1].y = 0.0;
    vc[1].z = 0.5;
    vc[2].x = 0.5;
    vc[2].y = 1.0;
    vc[2].z = 0.5;
    vc[3].x = -0.5;
    vc[3].y = 1.0;
    vc[3].z = 0.5;
    vc[4].x = -0.5;
    vc[4].y = 0.0;
    vc[4].z = -0.5;
    vc[5].x = 0.5;
    vc[5].y = 0.0;
    vc[5].z = -0.5;
    vc[6].x = 0.5;
    vc[6].y = 1.0;
    vc[6].z = -0.5;
    vc[7].x = -0.5;
    vc[7].y = 1.0;
    vc[7].z = -0.5;
    //caras
    cc[0].x = 0;
    cc[0].y = 1;
    cc[0].z = 3;
    cc[1].x = 1;
    cc[1].y = 2;
    cc[1].z = 3;
    cc[2].x = 1;
    cc[2].y = 5;
    cc[2].z = 2;
    cc[3].x = 5;
    cc[3].y = 6;
    cc[3].z = 2;
    cc[4].x = 2;
    cc[4].y = 6;
    cc[4].z = 3;
    cc[5].x = 3;
    cc[5].y = 6;
    cc[5].z = 7;
    cc[6].x = 7;
    cc[6].y = 4;
    cc[6].z = 0;
    cc[7].x = 3;
    cc[7].y = 7;
    cc[7].z = 0;
    cc[8].x = 5;
    cc[8].y = 1;
    cc[8].z = 0;
    cc[9].x = 0;
    cc[9].y = 4;
    cc[9].z = 5;
    cc[10].x = 6;
    cc[10].y = 5;
    cc[10].z = 4;
    cc[11].x = 4;
    cc[11].y = 7;
    cc[11].z = 6;
}

void Cubo::escalar(float x, float y, float z)
{
    for(int i=0;i<vc.size();i++)
    {
        vc[i].x = x*vc[i].x;
        vc[i].y = y*vc[i].y;
        vc[i].z = z*vc[i].z;
    }
}

void Cubo::trasladar(float x, float y, float z)
{
    for(int i=0;i<vc.size();i++)
    {
        vc[i].x = x+vc[i].x;
        vc[i].y = y+vc[i].y;
        vc[i].z = z+vc[i].z;
    }
}

void Cubo::dibujar(float a, float b, float c, int n)
{
    tipo = n;
    if(tipo == 0)
    {
        glColor3f(1,0,0);
        glPointSize(4);
        glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
        glBegin(GL_POINTS);
        
        for (unsigned i=0;i<vc.size();i++)
        {
            glVertex3f(vc[i].x, vc[i].y, vc[i].z);
        }
        glEnd();
    }
    if(tipo == 1)
    {
        glColor3f(1,0,0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glBegin(GL_TRIANGLES);
        
        for (unsigned i=0;i<cc.size();i++)
        {
            glVertex3f(vc[cc[i]._0].x, vc[cc[i]._0].y, vc[cc[i]._0].z);
            glVertex3f(vc[cc[i]._1].x, vc[cc[i]._1].y, vc[cc[i]._1].z);
            glVertex3f(vc[cc[i]._2].x, vc[cc[i]._2].y, vc[cc[i]._2].z);
        }
        glEnd();
    }
    if(tipo == 2)
    {
        glColor3f(0,0,1);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBegin(GL_TRIANGLES);
        
        for (int i=0; i<cc.size();i++)
        {
            glVertex3f(vc[cc[i]._0].x, vc[cc[i]._0].y, vc[cc[i]._0].z);
            glVertex3f(vc[cc[i]._1].x, vc[cc[i]._1].y, vc[cc[i]._1].z);
            glVertex3f(vc[cc[i]._2].x, vc[cc[i]._2].y, vc[cc[i]._2].z);
        }
        glEnd();
    }
    if(tipo == 3)
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBegin(GL_TRIANGLES);
        glColor3f(0,1,0);
        
        for (int i=0; i<cc.size();i++)
        {
            if(i%2==0)
                glColor3f(0,0,0);
            else glColor3f(0,0,1);
            
            glVertex3f(vc[cc[i]._0].x, vc[cc[i]._0].y, vc[cc[i]._0].z);
            glVertex3f(vc[cc[i]._1].x, vc[cc[i]._1].y, vc[cc[i]._1].z);
            glVertex3f(vc[cc[i]._2].x, vc[cc[i]._2].y, vc[cc[i]._2].z);
        }
        glEnd();
    }
}

Circulo::Circulo()
{
    circulo();
}

void Circulo::circulo()
{
    revoluciones(20);
}

void Circulo::leer_datos(vector <float> v1, vector<int> c1)
{
    vc.resize(v1.size()/3);
    cc.resize(c1.size()/3);
    
    for (int i=0; i<vc.size();i++)
    {
        vc[i].x = v1[i*3];
        vc[i].y = v1[i*3+1];
        vc[i].z = v1[i*3+2];
    }
    
    for (int j=0;j<cc.size();j++)
    {
        cc[j]._0 = c1[j*3];
    	  	cc[j]._1 = c1[j*3+1];
        cc[j]._2 = c1[j*3+2];
    }
}

void Circulo::revoluciones(int num_perfiles)
{
    vector<float> vp,v1;
    vector<int>c1;
    vc.clear();
    cc.clear();
    v1.clear();
    c1.clear();
    vp.resize(6);
    vp[0]=0.0;
    vp[1]=0.0;
    vp[2]=0.0;
    vp[3]=0.5;
    vp[4]=0.0;
    vp[5]=0.0;
    
    revolucion_vertices(vp,v1,num_perfiles);
    revolucion_caras(c1,num_perfiles,2);
    
    leer_datos(v1, c1);
}

void Circulo::revolucion_vertices(vector<float> vp,vector<float> &v1,int num_perfiles)
{
    double n;
    v1.push_back(vp[0]);
    v1.push_back(vp[1]);
    v1.push_back(vp[2]);
    
    for(int j=0;j<num_perfiles;j++)
    {
        n = j*(2*M_PI/(num_perfiles-1));
        v1.push_back(cos(n)*vp[3] + sin(n)*vp[5]);
        v1.push_back(vp[4]);
        v1.push_back(-sin(n)*vp[3] + cos(n)*vp[5]);
    }
}

void Circulo::revolucion_caras(vector<int> &c1, int num_perfiles, int n)
{
    //Primera la tapa inferior
    for(int i=0;i<num_perfiles-1;i++)
    {
        c1.push_back(0);
        c1.push_back(((n-1)*i)+n);
        c1.push_back(((n-1)*i)+(n-2));
    }
}

void Circulo::escalar(float x, float y, float z)
{
    for(int i=0;i<vc.size();i++)
    {
        vc[i].x = x*vc[i].x;
        vc[i].y = y*vc[i].y;
        vc[i].z = z*vc[i].z;
    }
}

void Circulo::trasladar(float x, float y, float z)
{
    for(int i=0;i<vc.size();i++)
    {
        vc[i].x = x+vc[i].x;
        vc[i].y = y+vc[i].y;
        vc[i].z = z+vc[i].z;
    }
}

void Circulo::dibujar(float a, float b, float c, int n)
{
    tipo = n;
    if(tipo == 0)
    {
        glColor3f(1,0,0);
        glPointSize(4);
        glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
        glBegin(GL_POINTS);
        
        for (unsigned i=0;i<vc.size();i++)
        {
            glVertex3f(vc[i].x, vc[i].y, vc[i].z);
        }
        glEnd();
    }
    if(tipo == 1)
    {
        glColor3f(1,0,0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glBegin(GL_TRIANGLES);
        
        for (unsigned i=0;i<cc.size();i++)
        {
            glVertex3f(vc[cc[i]._0].x, vc[cc[i]._0].y, vc[cc[i]._0].z);
            glVertex3f(vc[cc[i]._1].x, vc[cc[i]._1].y, vc[cc[i]._1].z);
            glVertex3f(vc[cc[i]._2].x, vc[cc[i]._2].y, vc[cc[i]._2].z);
        }
        glEnd();
    }
    if(tipo == 2)
    {
        glColor3f(0,0,1);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBegin(GL_TRIANGLES);
        
        for (int i=0; i<cc.size();i++)
        {
            glVertex3f(vc[cc[i]._0].x, vc[cc[i]._0].y, vc[cc[i]._0].z);
            glVertex3f(vc[cc[i]._1].x, vc[cc[i]._1].y, vc[cc[i]._1].z);
            glVertex3f(vc[cc[i]._2].x, vc[cc[i]._2].y, vc[cc[i]._2].z);
        }
        glEnd();
    }
    if(tipo == 3)
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBegin(GL_TRIANGLES);
        glColor3f(0,1,0);
        
        for (int i=0; i<cc.size();i++)
        {
            if(i%2==0)
                glColor3f(0,0,0);
            else glColor3f(0,0,1);
            
            glVertex3f(vc[cc[i]._0].x, vc[cc[i]._0].y, vc[cc[i]._0].z);
            glVertex3f(vc[cc[i]._1].x, vc[cc[i]._1].y, vc[cc[i]._1].z);
            glVertex3f(vc[cc[i]._2].x, vc[cc[i]._2].y, vc[cc[i]._2].z);
        }
        glEnd();
    }
}



//*************************************************************************
// obj3D
//*************************************************************************

Obj3D::Obj3D()
{
    punto=3.0;
    linea=1.0;
}

//*************************************************************************
//
//*************************************************************************

void Obj3D::dibujar(){}

//*************************************************************************
// Robot
//*************************************************************************

Robot::Robot()
{
    robot_defecto();
}

//*************************************************************************
//
//*************************************************************************

void Robot::dibujar(int tipo)
{
    Cubo c;
    Circulo cir;
    miTipo=tipo;
    glPushMatrix();
    glScalef(2,2,2);
    
    // BLOQUE CABEZA = CABEZA + OJOS + OJOSL
    
    glPushMatrix();
    glRotatef(giro_cabeza,0,1,0);
    glPushMatrix();
    leer_ply(cilindro, true, vertices10, caras10, 30);
    glTranslatef(0, 6+rcuello, 0);
    glScalef(0.75, 0.75, 0.75);
    dibujar2(tipo, vertices1, caras1);
    glPopMatrix();
    
    //Cabeza
    glPushMatrix();
    c.escalar(1.5,1.5,1.5);
    c.trasladar(0,4+rcuello,0);
    c.dibujar(0.2,1.0,1.0,tipo);
    glPopMatrix();
    c.cubo();
    
    // Ojos
    // Ojo derecho
    glPushMatrix();
    cir.escalar(0.2,0.2,0.2);
    glTranslatef(-0.3,5+rcuello,0.8);
    glScalef(2,2,1.5);
    glRotatef(-90,1,0,0);
    cir.dibujar(1.0,0.8,0.3,tipo);
    glPopMatrix();
    cir.circulo();
    
    //Ojo izquierdo
    glPushMatrix();
    cir.escalar(0.2,0.2,0.2);
    glTranslatef(0.3,5+rcuello,0.8);
    glScalef(2,2,1.5);
    glRotatef(-90,1,0,0);
    cir.dibujar(1.0,0.8,0.3,tipo);
    glPopMatrix();
    
    glPopMatrix();
    
    //Cuello
    glPushMatrix();
    c.escalar(1.0,rcuello,1.0);
    c.trasladar(0.0,4.0,0.0);
    c.dibujar(0.7,0.7,0.7,tipo);
    glPopMatrix();
    c.cubo();
    
    // Cuerpo
    glPushMatrix();
    c.escalar(3.0,4.0,2.0);
    c.dibujar(0.0,1.0,0.0,tipo);
    glPopMatrix();
    c.cubo();
    
    //BLOQUE PIERNAS
    //Pierna derecha
    glPushMatrix();
    glPushMatrix();
    glTranslatef(-1.0,0.0,0.0);
    glScalef(2,4,2);
    glRotatef(-giro_piernad, -1, 0, 0);
    leer_ply(cilindro, true, vertices10, caras10, 30);
    glPopMatrix();
    c.escalar(-1.0,4.0,1.0);
    glRotatef(-180,0,0,1);
    c.trasladar(-1.0,0.0,0.0);
    glRotatef(-giro_piernad,-1,0,0);
    c.dibujar(1.0,0.1,0.0,tipo);
    glPopMatrix();
    c.cubo();
    
    //Pierna izquierda
    glPushMatrix();
    c.escalar(-1.0,4.0,1.0);
    c.trasladar(1.0,0.0,0.0);
    glRotatef(-180,0,0,1);
    glRotatef(giro_piernai,1,0,0);
    c.dibujar(1.0,0.1,0.0,tipo);
    glPopMatrix();
    c.cubo();
    
    //Pie derecho
    glPushMatrix();
    c.escalar(1.2,0.5,2.2);
    c.trasladar(1,-4.5,0);
    glRotatef(-giro_piernad,1,0,0);
    c.dibujar(0.0,0.0,0.0,tipo);
    glPopMatrix();
    c.cubo();
    
    //Pie izquierdo
    glPushMatrix();
    c.escalar(1.2,0.5,2.2);
    c.trasladar(-1.0,-4.5,0);
    glRotatef(-giro_piernai,1,0,0);
    c.dibujar(0.0,0.0,0.0,tipo);
    glPopMatrix();
    c.cubo();
    
    //BLOQUE BRAZOS
    // Hombro Derecho
    glPushMatrix();
    c.escalar(0.5,rbrazod,0.5);
    glRotatef(-90,0,0,1);
    c.trasladar(-3.5,1.5,0.0);
    c.dibujar(1.0,0.86,0.3,tipo);
    glPopMatrix();
    c.cubo();
    
    // Hombro izquierdo
    glPushMatrix();
    c.escalar(0.5,rbrazoi,0.5);
    glRotatef(90,0,0,1);
    c.trasladar(3.5,1.5,0.0);
    c.dibujar(1.0,0.86,0.3,tipo);
    glPopMatrix();
    c.cubo();
    
    //Brazo que se mueve
    // Antebrazo derecho
    glPushMatrix();
    c.escalar(2.0,1.0,1.0);
    glRotatef(-90,0,0,1);
    glTranslatef(-3.0,1.5+rbrazod,0.0);
    glTranslatef(-0.5,0.0,0.0);
    glRotatef(giro_brazod,0,-1,0);
    glTranslatef(0.5,0.0,0.0);
    c.dibujar(0.0,0.0,1.0,tipo);
    glPopMatrix();
    c.cubo();
    
    // Antebrazo izquierdo
    glPushMatrix();
    c.escalar(2.0,1.0,1.0);
    glRotatef(90,0,0,1);
    glTranslatef(3.0,(1.5+rbrazoi),0.0);
    glTranslatef(0.5,0,0);
    glRotatef(giro_brazoi,0,1,0);
    glTranslatef(-0.5,0,0);
    c.dibujar(0.0,0.0,1.0,tipo);
    glPopMatrix();
    c.cubo();
    
    // Mano derecha
    glPushMatrix();
    c.escalar(0.5,0.5,0.5);
    glTranslatef(2+rbrazod,1.6,0);
    glTranslatef(0,1.9,0);
    glRotatef(-giro_brazod,1,0,0);
    glRotatef(giro_manos,0,1,0);
    glTranslatef(0,-1.9,0);
    c.dibujar(1.0,0.8,0.3,tipo);
    glPopMatrix();
    c.cubo();

    
    // Mano izquierda
    glPushMatrix();
    c.escalar(0.5,0.5,0.5);
    glTranslatef(-2-rbrazoi,1.6,0);
    glTranslatef(0,1.9,0);
    glRotatef(-giro_brazoi,1,0,0);
    glRotatef(giro_manos,0,1,0);
    glTranslatef(0,-1.9,0);
    c.dibujar(1.0,0.8,0.3,tipo);
    glTranslatef(0,-0.8,0);
    leer_ply(beethoven, false, vertices10, caras10, 0);
    glScalef(0.15, 0.15, 0.15);
    dibujar2(tipo, vertices1, caras1);

    glPopMatrix();
    
    glPopMatrix();
}



void Robot::cabeza_derecha()
{
    giro_cabeza -= 2.0+aumentarVelocidad;
}



void Robot::cabeza_izquierda()
{
    giro_cabeza += 2.0+aumentarVelocidad;
}



void Robot::brazos_arriba()
{
    giro_brazod += 2.0+aumentarVelocidad;
    giro_brazoi += 2.0+aumentarVelocidad;
}



void Robot::brazos_abajo()
{
    giro_brazod -= 2.0+aumentarVelocidad;
    giro_brazoi -= 2.0+aumentarVelocidad;
}



void Robot::piernad_abajo()
{
    giro_piernad -= 2.0+aumentarVelocidad;
}



void Robot::piernad_arriba()
{
    giro_piernad += 2.0+aumentarVelocidad;
}



void Robot::piernai_abajo()
{
    giro_piernai -= 2.0+aumentarVelocidad;
}



void Robot::piernai_arriba()
{
    giro_piernai += 2.0+aumentarVelocidad;
}



void Robot::paso_adelante()
{
    piernai_arriba();
    piernad_abajo();
    brazoi_abajo();
    brazod_arriba();
}



void Robot::paso_atras()
{
    piernai_abajo();
    piernad_arriba();
    brazoi_arriba();
    brazod_abajo();
}


void Robot::brazod_abajo()
{
    giro_brazod -= 2.0+aumentarVelocidad;
}



void Robot::brazod_arriba()
{
    giro_brazod += 2.0+aumentarVelocidad;
}




void Robot::brazoi_abajo()
{
    giro_brazoi -= 2.0+aumentarVelocidad;
}



void Robot::brazoi_arriba()
{
    giro_brazoi += 2.0+aumentarVelocidad;
}



void Robot::cuello_aumentar()
{
    rcuello += 0.5;
}



void Robot::brazoi_aumentar()
{
    rbrazoi += 0.5;
}



void Robot::brazoi_disminuir()
{
    rbrazoi -= 0.5;
}



void Robot::brazod_aumentar()
{
    rbrazod += 0.5;
}



void Robot::brazod_disminuir()
{
    rbrazod -= 0.5;
}



void Robot::cuello_disminuir()
{
    rcuello -= 0.5;
}



void Robot::robot_defecto()
{
    giro_cabeza = 0.0;
    giro_brazod = 0.0;
    giro_brazoi = 0.0;
    giro_piernad = 0.0;
    giro_piernai = 0.0;
    rcuello = 0.5;
    rbrazod = 1;
    rbrazoi = 1;
    avanzar=true;
}

void Robot::activarCaminar(){
    adelante=true;
}

bool Robot::getActivarCaminar()
{
    return adelante;
}


void Robot::girar_manos()
{
    giro_manos -= 30.0;
}



void Robot::act_giro_manos()
{
    act_g_manos = true;
}



bool Robot::get_g_manos()
{
    return act_g_manos;
}


void Robot::control_animacion()
{
    if(giro_cabeza > 90.0) 
        giro_cabeza = 90.0;
    
    if(giro_cabeza < -90.0) 
        giro_cabeza = -90.0;
    
    if(rcuello < 0.5) 
        rcuello = 0.5;
    
    if(rcuello > 3.0) 
        rcuello = 3.0;
    
    if(rbrazoi < 1.0) 
        rbrazoi = 1.0;
    
    if(rbrazoi > 3.0) 
        rbrazoi = 3.0;
    
    if(rbrazod < 1.0) 
        rbrazod = 1.0;
    
    if(rbrazod > 3.0) 
        rbrazod = 3.0;
    
    if(giro_brazod > 46.0)
        giro_brazod =46.0;
    
    if(giro_brazod < -46.0)
        giro_brazod = -46.0;
    
    if(giro_brazoi > 46.0)
        giro_brazoi = 46.0;
    
    if(giro_brazoi < -46.0)
        giro_brazoi = -46.0;
    
    if(giro_piernad > 46.0)
        giro_piernad = 46.0;
    
    if(giro_piernad < -46.0)
        giro_piernad = -46.0;
    
    if(giro_piernai > 46.0)
        giro_piernai = 46.0;
    
    if(giro_piernai < -46.0)
        giro_piernai = -46.0;
    
    if(giro_manos <- 5000.0) 
    {
        giro_manos = 0.0; 
        act_g_manos = false;
    }
    if(camino <-5000.0)
    {
        camino = 0.0;
        activarCamino = false;
    }
}

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
    double alpha = 0*M_PI/180;
    double betha = 360*M_PI/180;
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


void dibujar2(int num, vector<_vertex3f> &Vertices, vector<_vertex3i> &Triangulos){
    switch (num){
        case 0: dibujapuntos(Vertices);break;
        case 1: dibujaaristas(Vertices,Triangulos);break;
        case 2: dibujasolido(Vertices,Triangulos);break;
        case 3: dibujaajedrez(Vertices,Triangulos);break;
    }
    
}

void dibujaajedrez(vector<_vertex3f> &Vertices, vector<_vertex3i> &Triangulos){
    glPolygonMode(GL_FRONT,GL_FILL);
    glBegin(GL_TRIANGLES);
    for(unsigned int i=0; i<Triangulos.size(); i++) {
        
        if(i%2==0)
            glColor3f(0,0,0);
        else glColor3f(0,0,1);
        
        glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
        glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
        glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
    }
    glEnd();
    
}

void dibujasolido(vector<_vertex3f> &Vertices, vector<_vertex3i> &Triangulos){
    
    glPolygonMode(GL_FRONT,GL_FILL);
    glBegin(GL_TRIANGLES);
    glColor3f(0,0,1);
    for(unsigned int i=0; i<Triangulos.size(); i++){
        glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
        glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
        glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
    }
    glEnd();
    
}

void dibujapuntos(vector<_vertex3f> &Vertices){
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    for(unsigned int i=0; i<Vertices.size(); i++){
        glVertex3f (Vertices[i].x, Vertices[i].y, Vertices[i].z);
    }
    glEnd();
}

void dibujaaristas(vector<_vertex3f> &Vertices, vector<_vertex3i> &Triangulos){
    
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    for(unsigned int i=0; i<Triangulos.size(); i++) {
        glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
        glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
        glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
    }
    glEnd();
    
}




