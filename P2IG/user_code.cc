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

#define PI 3.14159265

//std::vector<float> vertices;
//std::vector<int> caras;
vector<_vertex3f> vertices1;
vector<_vertex3i> caras1;

//***********************************
// Funciones utiles para los calculos
//***********************************


Tupla3r producto_vectorial(Tupla3r U, Tupla3r V)
{
    Tupla3r W;
    W.coo[0] = U.coo[1]*V.coo[2] - U.coo[2]*V.coo[1];
    W.coo[1] = U.coo[2]*V.coo[0] - U.coo[0]*V.coo[1];
    W.coo[2] = U.coo[0]*V.coo[1] - U.coo[1]*V.coo[0];
    
    return W;
}


Tupla3r sum_vector(Tupla3r U, Tupla3r V)
{
    Tupla3r W;
    W.coo[0] = U.coo[0] + V.coo[0];
    W.coo[1] = U.coo[1] + V.coo[1];
    W.coo[2] = U.coo[2] + V.coo[2];
    
    return W;
}

double distancia(Tupla3r a, Tupla3r b)
{
    double x = pow((b.coo[0]-a.coo[0]), 2);
    double y = pow((b.coo[1]-a.coo[1]), 2);
    
    return sqrt((double)(x+y));
}



void leer_ply(const char* nombre_fichero, bool revolucion, vector<float> &vertices, vector<int> &caras, int P){
    
    if(revolucion==true)
    {
        vector<float> vertices_perfil;
        ply::read_vertices(nombre_fichero,vertices_perfil);
        
        generar_vertices(vertices_perfil,vertices,P,'Y');
        
        generar_caras(caras,P,vertices_perfil.size()/3);
    }
    else
    {
        ply::read(nombre_fichero, vertices, caras);
    }
    
}

void generar_malla(MallaTVT* malla, const char* nombre_fichero, bool revolucion, int N){
    
    vector<float> vertices;
    vector<int> caras;
    
    leer_ply(nombre_fichero, revolucion, vertices, caras, N);
    
    malla->num_ver = vertices.size()/3;
    malla->num_tri = caras.size()/3;
    malla->ver = (Tupla3r *)malloc(sizeof(Tupla3r) * malla->num_ver);
    malla->tri = (Tupla3n *)malloc(sizeof(Tupla3n) * malla->num_tri);
    
    malla->tam_ver = sizeof(Real)*3L*malla->num_ver;
    malla->tam_tri = sizeof(Natural)*3L*malla->num_tri;
    
    malla->nor_ver = (Tupla3r *)malloc(sizeof(Tupla3r) * malla->num_ver);
    malla->nor_tri = (Tupla3r *)malloc(sizeof(Tupla3r) * malla->num_tri);
    
    unsigned int i=0, j=0;
    
    while(i<vertices.size())
    {
        Tupla3r vert;
        vert.coo[0] = vertices[i];
        vert.coo[1] = vertices[i+1];
        vert.coo[2] = vertices[i+2];
        malla->ver[j] = vert;
        
        i+=3;
        j++;
    }
    
    i=0;
    j=0;
    while(i<caras.size())
    {
        Tupla3n tri;
        tri.ind[0] = caras[i];
        tri.ind[1] = caras[i+1];
        tri.ind[2] = caras[i+2];
        malla->tri[j] = tri;
        
        i+=3;
        j++;
    }
    
    calcular_normales_tri(malla);
    calcular_normales_ver(malla);
    
    MTVT_Crear_VBOs(malla);
}


//**************************************************************************************
// Funciones para generar y almacenar los vertices y caras (malla generada por revolucion)
//**************************************************************************************

void generar_vertices( vector<float> vertices, vector<float> &vertices_final, int N, char eje)
{
    int i,j;
    double alpha;
    
    //Insercion del primero perfil en la lista
    for(i=0;i<vertices.size();i++)
        vertices_final.push_back(vertices[i]);
    
    //Generacion de los vertices con tecnica de revolucion (rotacion sobre el eje)
    for(j=0;j<N-1;j++)
    {
        alpha = j * (2*PI/(N-1));
        for(i=0;i<vertices.size();i+=3)
        {
            float vx, vy, vz;
            if(eje == 'X')
            {
                vx = vertices[i];
                vy = cos(alpha)*vertices[i+1] - sin(alpha)*vertices[i+2];
                vz = sin(alpha)*vertices[i+1] + cos(alpha)*vertices[i+2];
            }
            else if(eje == 'Y')
            {
                vx = cos(alpha)*vertices[i] + sin(alpha)*vertices[i+2];
                vy = vertices[i+1];
                vz = -sin(alpha)*vertices[i] + cos(alpha)*vertices[i+2];
            }
            else
            {
                vx = cos(alpha)*vertices[i] - sin(alpha)*vertices[i+1];
                vy = sin(alpha)*vertices[i] + cos(alpha)*vertices[i+1];
                vz = vertices[i+2];
            }
            
            vertices_final.push_back(vx);
            vertices_final.push_back(vy);
            vertices_final.push_back(vz);
        }
    }
    
    //Generacion del ultimo perfil (igual al primero)
    alpha = 0;
    for(i=0;i<vertices.size();i+=3)
    {
        float vx, vy, vz;
        if(eje == 'X')
        {
            vx = vertices[i];
            vy = cos(alpha)*vertices[i+1] - sin(alpha)*vertices[i+2];
            vz = sin(alpha)*vertices[i+1] + cos(alpha)*vertices[i+2];
        }
        else if(eje == 'Y')
        {
            vx = cos(alpha)*vertices[i] + sin(alpha)*vertices[i+2];
            vy = vertices[i+1];
            vz = -sin(alpha)*vertices[i] + cos(alpha)*vertices[i+2];
        }
        else
        {
            vx = cos(alpha)*vertices[i] - sin(alpha)*vertices[i+1];
            vy = sin(alpha)*vertices[i] + cos(alpha)*vertices[i+1];
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
        vx1 = vertices[0];
        vy1 = 0;
        vz1 = 0;
        
        vx2 = vertices[vertices.size()-3];
        vy2 = 0;
        vz2 = 0;
    }
    else if(eje == 'Y')
    {
        vx1 = 0;
        vy1 = vertices[1];
        vz1 = 0;
        
        vx2 = 0;
        vy2 = vertices[vertices.size()-2];
        vz2 = 0;
    }
    else
    {
        vx1 = 0;
        vy1 = 0;
        vz1 = vertices[2];
        
        vx2 = 0;
        vy2 = 0;
        vz2 = vertices[vertices.size()-1];
    }
    
    vertices_final.push_back(vx1);
    vertices_final.push_back(vy1);
    vertices_final.push_back(vz1);
    
    vertices_final.push_back(vx2);
    vertices_final.push_back(vy2);
    vertices_final.push_back(vz2);
}


void generar_caras(vector<int> &caras, int N, int M)
{
    for(unsigned int i=0;i<N+1;i++)
    {
        int i1, i2, i3, i4, i5, i6 ;
        for(unsigned int j=0;j<M-1;j++)
        {
            //primero triangulo
            i1=M*i+j;
            i2=M*i+j+1;
            i3=(M*(i+1)+j+1)%(M*(N+1));
            
            //segundo triangulo
            i4=M*i+j;
            i5=(M*(i+1)+j)%(M*(N+1));
            i6=(M*(i+1)+j+1)%(M*(N+1));
            
            caras.push_back(i1);
            caras.push_back(i2);
            caras.push_back(i3);
            caras.push_back(i4);
            caras.push_back(i5);
            caras.push_back(i6);
        }
   	}
    
    //Generacion de las caras de la tapa superior
    for(unsigned int i=0;i<N;i++)
    {
        int i1, i2, i3;
        i1=M*(N+1);
        i2=M*i;
        i3=(M*(i+1))%(M*(N+1));
        
        caras.push_back(i1);
        caras.push_back(i2);
        caras.push_back(i3);
    }
    
    
    //Generacion de las caras de la tapa inferior
    for(unsigned int i=0;i<N;i++)
    {
        int i1, i2, i3;
        i1=M*(N+1)+1;
        i2=M*(i+1)-1;
        i3=(M*(i+2)-1)%(M*(N+1));
        
        caras.push_back(i1);
        caras.push_back(i2);
        caras.push_back(i3);
    }
}

//*****************************************************************************************************
// Funciones para generar y almacenar los normales a los vertices y caras (malla generada por revolucion)
//*****************************************************************************************************

void calcular_normales_tri(MallaTVT* malla)
{
    for(unsigned int i=0; i<malla->num_tri; i++)
    {
        //Vectores
        Tupla3r AB, BC, N;
        
        //Puntos
        Tupla3r A, B, C;
        
        A = malla->ver[malla->tri[i].ind[0]];
        B = malla->ver[malla->tri[i].ind[1]];
        C = malla->ver[malla->tri[i].ind[2]];
        
        AB.coo[0] = B.coo[0] - A.coo[0];
        AB.coo[1] = B.coo[1] - A.coo[1];
        AB.coo[2] = B.coo[2] - A.coo[2];
        BC.coo[0] = C.coo[0] - B.coo[0];
        BC.coo[1] = C.coo[1] - B.coo[1];
        BC.coo[2] = C.coo[2] - B.coo[2];
        
        N = producto_vectorial(AB, BC);
        
        malla->nor_tri[i] = N;
    }
    
}

void calcular_normales_ver(MallaTVT * malla)
{
    for(unsigned int i=0; i<malla->num_ver; i++)
    {
        Tupla3r N;
        vector<int> indices_tri;
        
        for(unsigned int j=0; j<malla->num_tri; j++)
        {
            if(malla->tri[j].ind[0] == i || malla->tri[j].ind[1] == i || malla->tri[j].ind[2] == i)
                indices_tri.push_back(j);
        }
        
        for(unsigned int k=0; k<indices_tri.size(); k++)
            N = sum_vector(N, malla->nor_tri[indices_tri[k]]);
        
        
        for(unsigned int j=0; j<3; j++)
            N.coo[j] = N.coo[j]/indices_tri.size();		
        
        malla->nor_ver[i] = N;	
        
    }
}


void draw_matriz(MallaTVT* malla, int modo)
{
    if(modo==1)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);//Puntos
    if(modo==2)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Aristas
    if(modo==3)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//Solido
    if(modo==4){
        glPolygonMode(GL_FRONT, GL_FILL);//Ajedrez

    }
    
    
    MTVT_Visualizar_VBOs_AV(malla);
}

void MTVT_Visualizar_VBOs_AV(MallaTVT *pm)
{
    if(pm->col_ver!=NULL)
    {
        glBindBuffer(GL_ARRAY_BUFFER, pm->id_vbo_col_ver);	//act. VBO col. v.
        glColorPointer(3, GL_FLOAT, 0 , 0);	//formato y offset de colores
        glEnableClientState(GL_COLOR_ARRAY);	//activa uso de colores de v.
    }
    if(pm->nor_ver!=NULL)
    {
        glBindBuffer(GL_ARRAY_BUFFER, pm->id_vbo_nor_ver);	//act. VBO nor. v.
        glNormalPointer(GL_FLOAT, 0 , 0);	//formato y offset de normales
        glEnableClientState(GL_NORMAL_ARRAY);	//activa uso de normales
    }
    
    MTVT_Visualizar_VBOs(pm);	//viualizacion con glDrawElements
    
    if(pm->col_ver!=NULL)
        glDisableClientState(GL_COLOR_ARRAY);	//desact. array de colores
    if(pm->nor_ver!=NULL)
        glDisableClientState(GL_NORMAL_ARRAY);	//desact. array de normales
    
}

void MTVT_Visualizar_VBOs(MallaTVT *pm)
{
    //especificar formato de los vertices en su VBO (y offset)
    glBindBuffer(GL_ARRAY_BUFFER, pm->id_vbo_ver) ;		//act. VBO
    glVertexPointer(3, GL_FLOAT, 0, 0);		//formato y offset (0)
    glBindBuffer(GL_ARRAY_BUFFER, 0);		//desact VBO
    glEnableClientState(GL_VERTEX_ARRAY);		//act. uso VA
    
    //visualizar con glDrawElements (puntero a tabla == NULL)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pm->id_vbo_tri);
    glDrawElements(GL_TRIANGLES, 3L*pm->num_tri, GL_UNSIGNED_INT, NULL) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    //desactivar uso de array de vertices
    glDisableClientState(GL_VERTEX_ARRAY);
}

GLuint VBO_Crear(GLuint tipo, GLuint tamanio, GLvoid * puntero)
{
    assert(tipo==GL_ARRAY_BUFFER || tipo==GL_ELEMENT_ARRAY_BUFFER) ;
    GLuint id_vbo ;		//resultado: identificador de VBO
    glGenBuffers(1, &id_vbo) ;	//crear nuevo VBO, obterner identificador
    glBindBuffer(tipo, id_vbo) ; 	//activar el VBO usando su identificador
    glBufferData(tipo, tamanio, puntero, GL_STATIC_DRAW) ;		//transferencia RAM->GPU
    glBindBuffer(tipo, 0);		//desactivacion del VBO (activar 0)
    return id_vbo ;		//devolver el identificador resultado
}

void MTVT_Crear_VBOs(MallaTVT * pm)
{
    //crear VBO conteniendo la tabla de vertices
    pm->id_vbo_ver = VBO_Crear(GL_ARRAY_BUFFER, pm->tam_ver, pm->ver);
    
    //crear VBO con la tabla de triangulos (indices de vertices)
    pm->id_vbo_tri = VBO_Crear(GL_ARRAY_BUFFER, pm->tam_tri, pm->tri);
    
    //crear VBO con los colores de los vertices
    if(pm->col_ver != NULL)
        pm->id_vbo_col_ver = VBO_Crear(GL_ARRAY_BUFFER, pm->tam_ver, pm->col_ver);
    
    //crear VBO con las normales de los vertices
    if(pm->nor_ver != NULL)
        pm->id_vbo_nor_ver = VBO_Crear(GL_ARRAY_BUFFER, pm->tam_ver, pm->nor_ver);
    
    //crear VBO con las normales de los triangulos
    if(pm->nor_tri != NULL)
        pm->id_vbo_nor_tri = VBO_Crear(GL_ARRAY_BUFFER, pm->tam_tri, pm->nor_tri);
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

void leer_ply(char* archivo)
{
    vector<float> vertices;
    vector<int> caras;
    ply::read(archivo, vertices, caras);
    leer_datos(vertices, caras);
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
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_LINE_STRIP);
    for (int j=0;j<vertices1.size();j++){
        glVertex3fv((GLfloat*) &vertices1[j]);
        //glVertex3f(vertices1[caras1[j]._1].x, vertices1[caras1[j]._1].y, vertices1[caras1[j]._1].z);
        //glVertex3f(vertices1[caras1[j]._2].x, vertices1[caras1[j]._2].y, vertices1[caras1[j]._2].z);

    }
    glEnd();
}

void dibujar_aristas_rotado(){
    glPushMatrix();
    int numeroRotaciones = 123;
    for(int j=0;j<numeroRotaciones;j++){
        dibujar_aristas();
        glRotatef(10, 0, 1, 0);
    }
    glPopMatrix();
}

//**************************************************************************
// Funcion para dibujar los triangulos del modelo
//***************************************************************************

void dibujar_triangulos(){
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_TRIANGLE_STRIP);
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
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_TRIANGLES);
    
    for (int i=0; i<caras1.size();i++)
    {
        if(i%2!=0){
            glColor3f(1,0,0);
        }
        else{
            glColor3f(0,1,0);
        }
        glVertex3f(vertices1[caras1[i]._0].x, vertices1[caras1[i]._0].y, vertices1[caras1[i]._0].z);
        glVertex3f(vertices1[caras1[i]._1].x, vertices1[caras1[i]._1].y, vertices1[caras1[i]._1].z);
        glVertex3f(vertices1[caras1[i]._2].x, vertices1[caras1[i]._2].y, vertices1[caras1[i]._2].z);
    }
    
    glEnd();
    
    
}

void dibujar_triangulos_rotados(){
    glPushMatrix();
    int numeroRotaciones = 2;
    for(int j=0;j<numeroRotaciones;j++){
        dibujar_triangulos();
        glRotatef(25, 0, 1, 0);
    }
    glPopMatrix();
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
            dibujar_aristas_rotado();
            break;
        case 2:
            dibujar_triangulos_rotados();
            break;

    }
}*/



