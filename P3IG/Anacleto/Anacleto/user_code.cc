//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************
//**************************************************************************
// Práctica 3
//
// Realizado por:
//
// Nikolai Giovanni González López
//
// DNI: 74692748-H
//**************************************************************************
#include <vector>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <functional>
#include "vertex.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <unistd.h>

#include "user_code.h"
#include "file_ply_stl.h"

vector<_vertex3f> Figura::get_v()
{
	return v;
}

vector<_vertex3i> Figura::get_c()
{
	return c;
}

//**************************************************************************
// Funcion para transformar los datos de las figuras en vectores
// de la clase vertex
//***************************************************************************

void Figura::leer_datos(vector <float> v1, vector<int> c1)
{
    v.resize(v1.size()/3);
    c.resize(c1.size()/3);
    for (int i=0; i<v.size();i++)
    {
        v[i].x = v1[i*3];
        v[i].y = v1[i*3+1];
        v[i].z = v1[i*3+2];
    }
    
    for (int j=0;j<c.size();j++)
    {
        c[j]._0 = c1[j*3];
        c[j]._1 = c1[j*3+1];
        c[j]._2 = c1[j*3+2];
    }
}

//**************************************************************************
// Funcion para leer archivo ply
//***************************************************************************

void Figura::leer_ply(const char* fichero)
{  
    vector<GLfloat> vertices;
    vector<GLint> caras;
    ply::read(fichero, vertices, caras);
    leer_datos(vertices,caras);  
}
//**************************************************************************
// Funcion para dibujar los vértices (puntos)
//***************************************************************************

void Figura::dibujar_vertices()
{
    
    glColor3f(0,0,1);
    glPointSize(4);
    glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
    glBegin(GL_POINTS);
    for (unsigned i=0;i<v.size();i++){
        glVertex3f(v[i].x, v[i].y, v[i].z);
    }
    glEnd();
}

//**************************************************************************
// Funcion para dibujar las aristas.
//***************************************************************************

void Figura::dibujar_aristas()
{  
    glColor3f(0,0,0);
    glPointSize(4);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_TRIANGLES);
    for (unsigned i=0;i<c.size();i++)
    {
        glColor3f(0,0,0);
        glVertex3f(v[c[i]._0].x, v[c[i]._0].y, v[c[i]._0].z);
        glVertex3f(v[c[i]._1].x, v[c[i]._1].y, v[c[i]._1].z);
	glVertex3f(v[c[i]._2].x, v[c[i]._2].y, v[c[i]._2].z);
    }
    glEnd();
}


//**************************************************************************
// Funcion para dibujar los triangulos del modelo
//***************************************************************************

void Figura::dibujar_triangulos()
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);
    glColor3f(0,0.8,0.5);
    
    for (int i=0; i<c.size();i++)
    {
	glVertex3f(v[c[i]._0].x, v[c[i]._0].y, v[c[i]._0].z);
        glVertex3f(v[c[i]._1].x, v[c[i]._1].y, v[c[i]._1].z);
	glVertex3f(v[c[i]._2].x, v[c[i]._2].y, v[c[i]._2].z);
    }
   glEnd();  
}

//**************************************************************************
// Funcion para dibujar el sólido ajedrez del modelo
//***************************************************************************

void Figura::dibujar_triangulos_ajedrez()
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);
    glColor3f(0,1,0);
    
    for (int i=0; i<c.size();i++)
    {
	if(i%2==0)
	{
      		glColor3f(0.3,0.3,0.3);
       	}
       	else
	{
       		glColor3f(0.7,0.7,0.7);
       	}
        glVertex3f(v[c[i]._0].x, v[c[i]._0].y, v[c[i]._0].z);
        glVertex3f(v[c[i]._1].x, v[c[i]._1].y, v[c[i]._1].z);
	glVertex3f(v[c[i]._2].x, v[c[i]._2].y, v[c[i]._2].z);
    }
    glEnd();   
}

void Figura::revoluciones(const char *fichero, int num_perfiles)
{
    vector<float> vp,v1;
    vector<int>c1;
    v.clear();
    c.clear();
    v1.clear();
    c1.clear();
    bool sup=false,inf=false;
    ply::read_vertices(fichero,vp);
 
    if(vp[0]==0.0 && vp[2]==0.0)
    {
	inf=true;
    }

    if(vp[vp.size()-3]==0.0 && vp[vp.size()-1]==0.0)
    {
	sup=true;
    }
        
    revolucion_vertices(vp,v1,num_perfiles,sup,inf);
    revolucion_caras(c1,num_perfiles,vp.size()/3,sup,inf);
        
    leer_datos(v1, c1);
}


void Figura::revolucion_vertices(vector<float> vp,vector<float> &v1,int num_perfiles,bool sup, bool inf)
{
    double n;

    if(inf&&sup)
    {
    	//Generacion de los vertices laterales con tecnica de revolucion (rotacion sobre el eje)
    	//Primero metemos el punto central de la tapa inferior
	v1.push_back(vp[0]);
	v1.push_back(vp[1]);
	v1.push_back(vp[2]);

	//Ahora genero los demas puntos, ke formaran la malla o caras laterales
    	for(int j=0;j<num_perfiles;j++)
    	{ 
 	    n = j*(2*M_PI/(num_perfiles-1));
	    for(int i=3;i<vp.size()-3;i+=3)
	    {
       	    	v1.push_back(cos(n)*vp[i] + sin(n)*vp[i+2]); 
	    	v1.push_back(vp[i+1]); 
	    	v1.push_back(-sin(n)*vp[i] + cos(n)*vp[i+2]); 
	    }			
    	}

	//Ahora introduzco el punto central de la capa superior
	v1.push_back(vp[vp.size()-3]);
	v1.push_back(vp[vp.size()-2]);
	v1.push_back(vp[vp.size()-1]);
    }
    else
    {
	if(inf)
	{
	    //Generacion de los vertices laterales con tecnica de revolucion (rotacion sobre el eje)
	    //Primero metemos el punto central de la tapa inferior
	    v1.push_back(vp[0]);
	    v1.push_back(vp[1]);
	    v1.push_back(vp[2]);

	    //Ahora genero los demas puntos, ke formaran la malla o caras laterales
    	    for(int j=0;j<num_perfiles;j++)
    	    { 
 	    	n = j*(2*M_PI/(num_perfiles-1));
	    	for(int i=3;i<vp.size();i+=3)
	    	{
       	    	    v1.push_back(cos(n)*vp[i] + sin(n)*vp[i+2]); 
	    	    v1.push_back(vp[i+1]); 
	    	    v1.push_back(-sin(n)*vp[i] + cos(n)*vp[i+2]); 
	    	}			
    	    }
	}
	else
	{
	    if(sup)
	    {
		//Generacion de los vertices laterales con tecnica de revolucion (rotacion sobre el eje)
    	    	for(int j=0;j<num_perfiles;j++)
    	    	{ 
 	    	    n = j*(2*M_PI/(num_perfiles-1));
	            for(int i=0;i<vp.size()-3;i+=3)
	            {
       	    	    	v1.push_back(cos(n)*vp[i] + sin(n)*vp[i+2]); 
	    	    	v1.push_back(vp[i+1]); 
	    	    	v1.push_back(-sin(n)*vp[i] + cos(n)*vp[i+2]); 
	    	    }
		}
		//Meto el punto del eje Y que está en la tapa superior
		v1.push_back(vp[vp.size()-3]);
		v1.push_back(vp[vp.size()-2]);
		v1.push_back(vp[vp.size()-1]);
	    }
	    else
	    {
	    	//Generacion de los vertices con tecnica de revolucion (rotacion sobre el eje)
    	    	for(int j=0;j<num_perfiles;j++)
    	    	{ 
 	    	    n = j*(2*M_PI/(num_perfiles-1));
	    	    for(int i=0;i<vp.size();i+=3)
	    	    {
       	    	    	v1.push_back(cos(n)*vp[i] + sin(n)*vp[i+2]); 
	    	    	v1.push_back(vp[i+1]); 
	    	    	v1.push_back(-sin(n)*vp[i] + cos(n)*vp[i+2]); 
	    	    }			
    	    	}
	    }
	}
    }
}

void Figura::revolucion_caras(vector<int> &c1, int num_perfiles, int n, bool sup, bool inf)
{	
    //Generacion de las caras de la tapa inferior y superior
    if(inf&&sup)
    {
	//Primera la tapa inferior
	for(int i=0;i<num_perfiles-1;i++)
	{
	    c1.push_back(0);;
	    c1.push_back(((n-2)*i)+(n-1));
	    c1.push_back(((n-2)*i)+(n-3));
    	}
	
      	//Segundo los laterales
	for(int i=0;i<n-3;i++)
	{
	    for(int j=0;j<num_perfiles-1;j++)
	    {
		//Primer triangulo "b"
		c1.push_back((i+1)+(2*j));
		c1.push_back((i+1)+(2*j)+(n-1));
		c1.push_back((i+1)+(2*j)+(n-3));

		//Segundo triangulo "a";
		c1.push_back((i+1)+(2*j));;
		c1.push_back((i+1)+(2*j)+(n-2));
		c1.push_back((i+1)+(2*j)+(n-1));
	    }
	}

	//Por último creo la tapa superior
	for(int i=0;i<num_perfiles-1;i++)
	{
	    c1.push_back((num_perfiles)*(n-2)+(n-3));
	    c1.push_back(((n-2)*i)+(n-2));
	    c1.push_back(((n-2)*i)+n);
    	}
    }
    else 
    {
   	//Generacion de las caras de la tapa inferior en caso de solo existir esta
	if(inf)
    	{ 
	    //Primera la tapa inferior
	    for(int i=0;i<num_perfiles-1;i++)
	    {
	    	c1.push_back(0);
	    	c1.push_back(((n-1)*i)+n);
		c1.push_back(((n-1)*i)+(n-2));
    	    }
	    //Segundo los laterales
	    for(int i=0;i<n-2;i++)
	    {
		for(int j=0;j<num_perfiles-1;j++)
		{
		    //Primer triangulo "b"
		    c1.push_back((i+1)+(2*j));
		    c1.push_back((i+1)+(2*j)+n);
		    c1.push_back((i+1)+(2*j)+(n-2));

		    //Segundo triangulo "a"
		    c1.push_back((i+1)+(2*j));
		    c1.push_back((i+1)+(2*j)+(n-1));
		    c1.push_back((i+1)+(2*j)+n);;
		}
	    }
        }
	else
	{
   	    //Generacion de las caras de la tapa superior en caso de solo existir esta
  	    if(sup)
    	    {   
	    	//Primero los laterales
		for(int i=0;i<n-2;i++)
		{
		    for(int j=0;j<num_perfiles-1;j++)
		    {
		    	//Primer triangulo "b"
		    	c1.push_back((i+1)+(2*j));;
		    	c1.push_back((i+1)+(2*j)+(n-2));
		    	c1.push_back((i+1)+(2*j)-(n-2));

			//Segundo triangulo "a"
		    	c1.push_back((i+1)+(2*j));
		    	c1.push_back((i+1)+(2*j)+(n-1));
		    	c1.push_back((i+1)+(2*j)+(n-2));
		    }
		}

		//Ahora introduzco las caras que formarán la tapa superior.
		for(int i=0;i<num_perfiles-1;i++)
		{
		    c1.push_back((num_perfiles)*(n-1));
	    	    c1.push_back(((n-1)*i)+n);
	    	    c1.push_back(((n-1)*i)+(n-2));
    	        }
	    }
	    else
	    {
		for(int i=0;i<num_perfiles-1;i++)
    		{
		    for(int j=0;j<n-1;j++)
		    {
	      		//Primer triangulo
            		c1.push_back(n*i+j);
	    		c1.push_back(n*i+j+1);
	    		c1.push_back((n*(i+1)+j+1)%(n*(num_perfiles+1)));
	    		//Segundo triangulo
	    		c1.push_back(n*i+j);
	    		c1.push_back((n*(i+1)+j)%(n*(num_perfiles+1)));
	    		c1.push_back((n*(i+1)+j+1)%(n*(num_perfiles+1)));
		    }
    		}
	    }
	}
    }
}

void Figura::calcular_normales()
{
    int x, y, z;
    float a[3],b[3],prod[3],mod;

    nc.resize(c.size());
    nv.resize(v.size());
    
    for(int i=0;i<v.size();i++)
    {    
        nv[i]._0 = 0; 
        nv[i]._1 = 0;
        nv[i]._2 = 0;     
    }

    for(int i=0;i<c.size();i++)
    {      
        x = c[i]._0;
        y = c[i]._1;
        z = c[i]._2;
        //Obtenemos los vectores apartir de los vertices.
        // Vector [x,y]
        a[0] = v[y]._0 - v[x]._0;
        a[1] = v[y]._1 - v[x]._1;
        a[2] = v[y]._2 - v[x]._2;
        // Vector [x,z]
        b[0] = v[z]._0 - v[x]._0;
        b[1] = v[z]._1 - v[x]._1;
        b[2] = v[z]._2 - v[x]._2;
        //Producto vectorial de los vectores obtenidos anteriormente, me da como resultado un vector N, 
	prod[0] =(a[1]*b[2])-(a[2]*b[1]);
        prod[1] = -((a[0]*b[2])-(a[2]*b[0]));
        prod[2] =(a[0]*b[1])-(a[1]*b[0]);
	
        //Normalizacion: Realizamos el modulo para normalizar los vectores a modulo 1.
        mod = sqrt(pow(prod[0], 2) + pow(prod[1], 2) + pow(prod[2], 2));
        prod[0] = prod[0] / mod;
        prod[1] = prod[1] / mod;
        prod[2] = prod[2] / mod;

        nc[i].x = prod[0];
        nc[i].y = prod[1];
        nc[i].z = prod[2];
        
        nv[x]._0 += nc[i]._0;
        nv[x]._1 += nc[i]._1;
        nv[x]._2 += nc[i]._2;
        
        nv[y]._0 += nc[i]._0;
        nv[y]._1 += nc[i]._1;
        nv[y]._2 += nc[i]._2;
        
        nv[z]._0 += nc[i]._0;
        nv[z]._1 += nc[i]._1;
        nv[z]._2 += nc[i]._2;
    }
    
    for(int i=0;i<v.size();i++)
    {
        nv[i].normalize();
    }   
}

void Figura::dibujar_aristas_perfil()
{  
    glColor3f(0,0,0);
    glPointSize(4);
    glPolygonMode(GL_FRONT,GL_LINE);
    glBegin(GL_LINE_STRIP);
    for (unsigned i=0;i<c.size();i++)
    {
        glVertex3f(v[c[i]._0].x, v[c[i]._0].y, v[c[i]._0].z);
        glVertex3f(v[c[i]._1].x, v[c[i]._1].y, v[c[i]._1].z);
	glVertex3f(v[c[i]._2].x, v[c[i]._2].y, v[c[i]._2].z);
    }
    glEnd();
}

void Figura::dibujar_normales_vertices()
{
    calcular_normales();
    dibujar_aristas();

    glColor3f(0,0,0);
    glPointSize(2);
    
    glBegin(GL_LINES);

    for(int i=0;i<c.size();i++)
    {
        glVertex3f(v[c[i]._0].x, v[c[i]._0].y, v[c[i]._0].z);       
        glVertex3f((v[c[i]._0].x)+nv[c[i]._0].x, (v[c[i]._0].y)+nv[c[i]._0].y, (v[c[i]._0].z)+nv[c[i]._0].z);
        glVertex3f(v[c[i]._1].x, v[c[i]._1].y, v[c[i]._1].z);        
        glVertex3f((v[c[i]._1].x)+nv[c[i]._1].x, (v[c[i]._1].y)+nv[c[i]._1].y, (v[c[i]._1].z)+nv[c[i]._1].z);
        glVertex3f(v[c[i]._2].x, v[c[i]._2].y, v[c[i]._2].z);       
        glVertex3f((v[c[i]._2].x)+nv[c[i]._2].x, (v[c[i]._2].y)+nv[c[i]._2].y, (v[c[i]._2].z)+nv[c[i]._2].z);
    }
  
    glEnd();
}

void Figura::dibujar_normales_caras()
{  
    calcular_normales();
    dibujar_triangulos();

    glColor3f(0,0,0);
    glPointSize(2);
    glBegin(GL_LINES);
    
    for(int i=0;i<c.size();i++)
    {
        glVertex3f(
		   (v[c[i]._0].x+v[c[i]._1].x+v[c[i]._2].x)/3,
		   (v[c[i]._0].y+v[c[i]._1].y+v[c[i]._2].y)/3,
		   (v[c[i]._0].z+v[c[i]._1].z+v[c[i]._2].z)/3);
        
        glVertex3f(
		   ((v[c[i]._0].x+v[c[i]._1].x+v[c[i]._2].x)/3)-nc[i].x, 
		   ((v[c[i]._0].y+v[c[i]._1].y+v[c[i]._2].y)/3)-nc[i].y,
		   ((v[c[i]._0].z+v[c[i]._1].z+v[c[i]._2].z)/3)-nc[i].z);
    }
    glEnd();
}

//A partir de aqui Practica 3 (Anacleto)
//índice de colores
//amarillo 	(1.0,0.8,0.3) 	// ojos y manos
//gris 		(0.7,0.7,0.7)	// cuello
//rojo 		(1.0,0.1,0.0) 	// pupilas, láser, muslos y piernas
//celeste 	(0.2,1.0,1.0) 	// cabeza
//marron 	(1.0,0.86,0.3) 	// brazo
//verde 	(0.0,1.0,0.0) 	// cuerpo
//azul 		(0.0,0.0,1.0) 	// antebrazo
//negro		(0.0,0.0,0.0)	// zapatos(pies)

Cubo::Cubo()
{
	cubo_defecto();
}

void Cubo::cubo_defecto()
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
	//caras (en triangulos)	
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
		glColor3f(a,b,c);
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
		glColor3f(a,b,c);
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
		glColor3f(a,b,c);
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
			{
      				glColor3f(0.3,0.3,0.3);
       			}
       			else
			{
       				glColor3f(0.7,0.7,0.7);
       			}
        		glVertex3f(vc[cc[i]._0].x, vc[cc[i]._0].y, vc[cc[i]._0].z);
        		glVertex3f(vc[cc[i]._1].x, vc[cc[i]._1].y, vc[cc[i]._1].z);
			glVertex3f(vc[cc[i]._2].x, vc[cc[i]._2].y, vc[cc[i]._2].z);
    		}
    		glEnd();
	}
}

Circulo::Circulo()
{
	circulo_defecto();
}

void Circulo::circulo_defecto()
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
	//Generacion de los vertices laterales con tecnica de revolucion (rotacion sobre el eje)
	//Primero metemos el punto central de la tapa inferior
	v1.push_back(vp[0]);
	v1.push_back(vp[1]);
	v1.push_back(vp[2]);

	//Ahora genero los demas puntos, ke formaran la malla o caras laterales
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
		glColor3f(a,b,c);
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
		glColor3f(a,b,c);
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
		glColor3f(a,b,c);
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
			{
      				glColor3f(0.3,0.3,0.3);
       			}
       			else
			{
       				glColor3f(0.7,0.7,0.7);
       			}
        		glVertex3f(vc[cc[i]._0].x, vc[cc[i]._0].y, vc[cc[i]._0].z);
        		glVertex3f(vc[cc[i]._1].x, vc[cc[i]._1].y, vc[cc[i]._1].z);
			glVertex3f(vc[cc[i]._2].x, vc[cc[i]._2].y, vc[cc[i]._2].z);
    		}
    		glEnd();
	}
}

void cono(float x0, float y0, float z0, float x1, float y1, float z1, float a, int n)
{
	float m,x,z,i,xf,zf,da;

	glPushMatrix();
	glTranslatef(x0,y0,z0);
	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);
	glShadeModel(GL_SMOOTH);

   	// Caras transversales
   	xf = a;
   	zf = 0.0;
   	da = 2*M_PI/n;
   	glBegin(GL_TRIANGLE_FAN);
   	  glVertex3f(x1,y1,z1);
   	  for(i=0; i <= n; ++i) 
	  {
		x = a*cos(da*i);
		z = -a*sin(da*i);
  	    	glNormal3f(z,0.0,x);
		glVertex3f(x,0.0,z);
      	  }
    	glEnd();
   	glShadeModel(GL_FLAT);

   	// Tapaderas
 	glBegin(GL_POLYGON);
	  glNormal3f(0.0,-1.0,0.0);
   	  for(i=0;i<=n;++i) 
	  {
		x = a*cos(da*i);
		z = a*sin(da*i);
	  	glVertex3f(x,0,z);
      	  }
     	glEnd();
	
	glPopMatrix();
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

	glPushMatrix(); 
	glScalef(2,2,2);
	
	// BLOQUE CABEZA = CABEZA + OJOS + OJOSL
    
	glPushMatrix();
	glRotatef(giro_cabeza,0,1,0);

	//Cabeza
	glPushMatrix();	
	c.escalar(1.5,1.5,1.5);
	c.trasladar(0,4+rcuello,0);
	c.dibujar(0.2,1.0,1.0,tipo);
	glPopMatrix();
	c.cubo_defecto();

	// Ojos
	// Ojo derecho
	glPushMatrix();
	cir.escalar(0.2,0.2,0.2);
	glTranslatef(-0.3,5+rcuello,0.8);
	glScalef(2,2,1.5);
	glRotatef(-90,1,0,0);
	cir.dibujar(1.0,0.8,0.3,tipo);
	glPopMatrix();
	cir.circulo_defecto();

	//Ojo izquierdo
	glPushMatrix();
	cir.escalar(0.2,0.2,0.2);
	glTranslatef(0.3,5+rcuello,0.8);
	glScalef(2,2,1.5);
	glRotatef(-90,1,0,0);
	cir.dibujar(1.0,0.8,0.3,tipo);
	glPopMatrix();

	//Láser ojos
	//Láser ojo derecho
	glPushMatrix();
	glColor3f(1.0,0.1,0.0);
	glTranslatef(-0.3,5+rcuello,0.8);
	glRotatef(180,1,0,0);
	glutWireCone(0.1,1*d_laser,50,20);
	glPopMatrix();

	//Láser ojo izquierdo
	glPushMatrix();
	glColor3f(1.0,0.1,0.0);
	glTranslatef(0.3,5+rcuello,0.8);
	glRotatef(180,1,0,0);
	glutWireCone(0.1,1*d_laser,50,20);
	glPopMatrix();
	
	glPopMatrix();
	
	//Cuello
	glPushMatrix();
	c.escalar(1.0,rcuello,1.0);
	c.trasladar(0.0,4.0,0.0);
	c.dibujar(0.7,0.7,0.7,tipo);
	glPopMatrix();
	c.cubo_defecto();

	// Cuerpo
	glPushMatrix();
	c.escalar(3.0,4.0,2.0);
	c.dibujar(0.0,1.0,0.0,tipo);
	glPopMatrix();
	c.cubo_defecto();

	//BLOQUE PIERNAS
	//Pierna derecha
	glPushMatrix();
	c.escalar(-1.0,4.0,1.0);
	glRotatef(-180,0,0,1);
	c.trasladar(-1.0,0.0,0.0);
	// TRANSLACION NECESARIA PARA EL GIRO CORRECTO
	glRotatef(-giro_piernad,-1,0,0);
	c.dibujar(1.0,0.1,0.0,tipo);
	glPopMatrix();
	c.cubo_defecto();

	//Pierna izquierda
	glPushMatrix();
	c.escalar(-1.0,4.0,1.0);
	c.trasladar(1.0,0.0,0.0);
	glRotatef(-180,0,0,1);
	// TRANSLACION NECESARIA PARA EL GIRO CORRECTO
	glRotatef(giro_piernai,1,0,0);
	c.dibujar(1.0,0.1,0.0,tipo);
	glPopMatrix();
	c.cubo_defecto();

	//Pie derecho
	glPushMatrix();
	c.escalar(1.2,0.5,2.2);
	c.trasladar(1,-4.5,0);
	glRotatef(-giro_piernad,1,0,0);
	c.dibujar(0.0,0.0,0.0,tipo);
	glPopMatrix();
	c.cubo_defecto();

	//Pie izquierdo
	glPushMatrix();
	c.escalar(1.2,0.5,2.2);
	c.trasladar(-1.0,-4.5,0);
	glRotatef(-giro_piernai,1,0,0);
	c.dibujar(0.0,0.0,0.0,tipo);
	glPopMatrix();
	c.cubo_defecto();

	//BLOQUE BRAZOS
	// Brazo derecho
	glPushMatrix();
	c.escalar(0.5,rbrazod,0.5);
	glRotatef(-90,0,0,1);
	c.trasladar(-3.5,1.5,0.0);
	c.dibujar(1.0,0.86,0.3,tipo);
	glPopMatrix();
	c.cubo_defecto();

	// Brazo izquierdo
	glPushMatrix();
	c.escalar(0.5,rbrazoi,0.5);
	glRotatef(90,0,0,1);
	c.trasladar(3.5,1.5,0.0);
	c.dibujar(1.0,0.86,0.3,tipo);
	glPopMatrix();
	c.cubo_defecto();

  	//PARTE DEL BRAZO QUE SE VA A ROTAR 
	// Antebrazo derecho
	glPushMatrix();
	c.escalar(2.0,1.0,1.0);
	glRotatef(-90,0,0,1);	
	glTranslatef(-3.0,1.5+rbrazod,0.0);	
	// TRANSLACION NECESARIA PARA EL GIRO CORRECTO
	glTranslatef(-0.5,0.0,0.0);
	glRotatef(giro_brazod,0,-1,0);
	glTranslatef(0.5,0.0,0.0);
	c.dibujar(0.0,0.0,1.0,tipo);
	glPopMatrix();
	c.cubo_defecto();
	
	// Antebrazo izquierdo
	glPushMatrix();
	c.escalar(2.0,1.0,1.0);
	glRotatef(90,0,0,1);
	glTranslatef(3.0,(1.5+rbrazoi),0.0);
	// TRANSLACION NECESARIA PARA EL GIRO CORRECTO
	glTranslatef(0.5,0,0);
	glRotatef(giro_brazoi,0,1,0);
	glTranslatef(-0.5,0,0);
	c.dibujar(0.0,0.0,1.0,tipo);
	glPopMatrix();
	c.cubo_defecto();

	// Mano derecha
	glPushMatrix();
	c.escalar(0.5,0.5,0.5);
	glTranslatef(2+rbrazod,1.6,0);
	// TRANSLACION NECESARIA PARA EL GIRO CORRECTO
	glTranslatef(0,1.9,0);
	glRotatef(-giro_brazod,1,0,0);
	glRotatef(giro_manos,0,1,0);
	glTranslatef(0,-1.9,0);
	c.dibujar(1.0,0.8,0.3,tipo);
	glPopMatrix();
	c.cubo_defecto();
	
	// Mano izquierda
	glPushMatrix();
	c.escalar(0.5,0.5,0.5);
	glTranslatef(-2-rbrazoi,1.6,0);
	// TRANSLACION NECESARIA PARA EL GIRO CORRECTO
	glTranslatef(0,1.9,0);
	glRotatef(-giro_brazoi,1,0,0);
	glRotatef(giro_manos,0,1,0);
	glTranslatef(0,-1.9,0);
	c.dibujar(1.0,0.8,0.3,tipo);
	glPopMatrix();

	glPopMatrix();
}

//*************************************************************************

void Robot::cabeza_derecha()
{
	giro_cabeza -= 2.0;
}

//*************************************************************************

void Robot::cabeza_izquierda()
{
	giro_cabeza += 2.0;
}

//*************************************************************************

void Robot::brazos_arriba()
{
	giro_brazod += 2.0;
	giro_brazoi += 2.0;
}

//*************************************************************************

void Robot::brazos_abajo()
{
	giro_brazod -= 2.0;
	giro_brazoi -= 2.0;
}

//*************************************************************************

void Robot::piernad_abajo()
{
	giro_piernad -= 2.0;
}

//*************************************************************************

void Robot::piernad_arriba()
{
	giro_piernad += 2.0;
}

//*************************************************************************

void Robot::piernai_abajo()
{
	giro_piernai -= 2.0;
}

//*************************************************************************

void Robot::piernai_arriba()
{
	giro_piernai += 2.0;
}

//*************************************************************************

void Robot::paso_adelante()
{
	piernai_arriba();
	piernad_abajo();
	brazoi_abajo();
	brazod_arriba();
}

//*************************************************************************

void Robot::paso_atras()
{
	piernai_abajo();
	piernad_arriba();
	brazoi_arriba();
	brazod_abajo();
}

//*************************************************************************
void Robot::caminar()
{
	adelante = true;
	giro_piernai = 0.0;
	giro_piernad = 0.0;
	cout<<"giro_piernai: "<<giro_piernai<<endl;

	while(((-47.0 >= giro_piernai)&&(giro_piernai <= 47.0))==0)
	{
		if(giro_piernai == 46.0)
			adelante = false;

		if(giro_piernai == -46.0)
			adelante = true;

		cout<<"dentro del while"<<endl;
		if(adelante && (giro_piernai < 46.0))
		{	cout<<"dentro del if1"<<endl;	
			piernai_arriba();
			piernad_abajo();
			brazoi_abajo();
			brazod_arriba();
			cout<<"giro_piernai: "<<giro_piernai<<", giro_brazoi: "<<giro_brazoi<<endl;
			sleep(2);
		}
/*
		if(!adelante && (giro_piernai > -46.0))
		{cout<<"dentro del if2"<<endl;
			piernai_abajo();
			piernad_arriba();
			brazoi_arriba();
			brazod_abajo();
			sleep(2);
		}*/
  		
		glutPostRedisplay();
		cout<<"final del while"<<endl;
	}
}

//*************************************************************************

void Robot::brazod_abajo()
{
	giro_brazod -= 2.0;
}

//*************************************************************************

void Robot::brazod_arriba()
{
	giro_brazod += 2.0;
}


//*************************************************************************

void Robot::brazoi_abajo()
{
	giro_brazoi -= 2.0;
}

//*************************************************************************

void Robot::brazoi_arriba()
{
	giro_brazoi += 2.0;
}

//*************************************************************************

void Robot::cuello_aumentar()
{
	rcuello += 0.5;
}

//*************************************************************************

void Robot::brazoi_aumentar()
{
	rbrazoi += 0.5;
}

//*************************************************************************

void Robot::brazoi_disminuir()
{
	rbrazoi -= 0.5;
}

//*************************************************************************

void Robot::brazod_aumentar()
{
	rbrazod += 0.5;
}

//*************************************************************************

void Robot::brazod_disminuir()
{
	rbrazod -= 0.5;
}

//*************************************************************************

void Robot::cuello_disminuir()
{
	rcuello -= 0.5;
}

//*************************************************************************

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
}

//*************************************************************************

void Robot::girar_manos()
{
	giro_manos -= 30.0;
}

//*************************************************************************

void Robot::act_giro_manos()
{	
	act_g_manos = true;	
}

//*************************************************************************

bool Robot::get_g_manos()
{	
	return act_g_manos;	
}

//*************************************************************************
void Robot::laser()
{	
	d_laser = d_laser - 5;	
}

//*************************************************************************

void Robot::put_act_laser()
{	
	 act_laser = true;	
	
}

//*************************************************************************

bool Robot::get_laser()
{	
	return act_laser;	
	
}

//*************************************************************************
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
    	if(d_laser < -90.0)
	{ 
		d_laser = 0.0; 
		act_laser = false;
	}
}
