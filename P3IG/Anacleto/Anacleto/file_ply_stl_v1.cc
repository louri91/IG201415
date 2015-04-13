// *********************************************************************
// **
// ** Función ply::read (declaraciones)
// ** 
// ** Carlos Ureña - 2012- 2013
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <assert.h>

#include "file_ply_stl.h"


namespace ply 
{

using namespace std ;

//**********************************************************************
// funciones auxiliares:

void abrir_archivo() ;
void leer_cabecera() ;
void error( const char *msg_error ) ;
void leer_vertices( vector<float> & vertices ) ;
void leer_caras( vector<int> & caras ) ;

//**********************************************************************
// variables usadas por todas las funciones:


const streamsize 
      tam_buffer = streamsize(10)*streamsize(1024) ;
char 
      buffer[unsigned(tam_buffer)];
string 
      token,
      nombre_archivo ;
long long int 
      num_vertices = 0, 
      num_caras   = 0 ;
unsigned
      state    = 0; // 0 antes de leer 'element vertex' (o 'element face'), 1 antes de leer 'element face', 2 después
bool 
      en_cabecera = true ;
ifstream  
      src ;
      
//**********************************************************************
// funcion principal de lectura

void read
(  const char *    nombre_archivo_se, 
   vector<float> & vertices, 
   vector<int> &   caras
)
{
   // modelos ply en:
   // http://graphics.im.ntu.edu.tw/~robin/courses/cg03/model/
   // http://people.sc.fsu.edu/~jburkardt/data/ply/ply.html
   // univ stanford ?
   
   nombre_archivo = nombre_archivo_se ;
   nombre_archivo += ".ply" ;
   
   abrir_archivo() ;
   leer_cabecera() ;
   leer_vertices(vertices) ;
   leer_caras(caras) ;   
   
   cout << "archivo ply leido." << endl << flush ;
}


//**********************************************************************

void leer_vertices( vector<float> & vertices )
{
   // leer vértices:
      
   vertices.resize( num_vertices*3 );

   cout << "  leyendo " << num_vertices << " vértices ...." << endl << flush ;
     
   for( long long iv = 0 ; iv < num_vertices ; iv++ )
   {
      if ( src.eof() ) 
         error("fin de archivo prematuro en la lista de vértices");

      double x,y,z ;

      src >> x >> y >> z ;
      //cout << "vertex #" << iv << " readed: (" << x << "," << y << "," << z << ")" << endl ;
      
      src.getline(buffer,tam_buffer); // ignore more properties, so far ...
      
      // add new vertex
      long long base = iv*3 ;
      vertices[base+0] = x ;
      vertices[base+1] = y ;
      vertices[base+2] = z ; 
   }
   cout << "  fin de la lista de vértices" << endl << flush ;   
}

//**********************************************************************

void leer_caras(  vector<int> & caras )
{
   cout << "  leyendo " << num_caras << " caras ...." << endl << flush ;
   
   caras.resize( num_caras*3 );
   
   for( long long ifa = 0 ; ifa < num_caras ; ifa++ )
   {
      if ( src.eof() ) 
         error("fin de archivo prematuro en la lista de caras");

      unsigned nv ;
      src >> nv ;
      //cout << "reading face #" << ifa << " with " << nv << " vertexes: " ;
      
      if ( nv != 3 )
         error("encontrada una cara con un número de vértices distinto de 3");
         
      long long iv0, iv1, iv2 ;

      src >> iv0 >> iv1 >> iv2 ;
      //cout << " " << iv0 << ", " << iv1 << ", " << iv2 << endl ;

      if ( iv0 >= num_vertices || iv1 >= num_vertices || iv2 >= num_vertices )
         error("encontrado algún índice de vértice igual o superior al número de vértices");
         
      src.getline(buffer,tam_buffer); // ignore more properties, so far ...
      
      long long base = ifa*3 ; 
      caras[base+0] = iv0 ;
      caras[base+1] = iv1 ;
      caras[base+2] = iv2 ;
   }
   cout << "  fin de la lista de caras." << endl ;
}

//**********************************************************************

void leer_cabecera()
{
   // leer cabecera:
   
   while( en_cabecera )
   {
      if ( src.eof() ) 
         error("fin de archivo prematuro antes de end_header");

     src >> token ;

     if ( token == "end_header" )
     {  if ( state != 2 )
           error("no encuentro 'element vertex' o 'element face' en la cabecera");
        src.getline(buffer,tam_buffer);
        en_cabecera = false ;
     }
     else if ( token == "comment" )
     {  src.getline(buffer,tam_buffer);
        cout << "  comment: " << buffer << endl ;
     }
     else if ( token == "format" )
     {  src >> token ;
        if ( token != "ascii" )
        {  string msg = string("el formato del ply no es 'ascii' es '")+token+"', no lo puedo leer" ;
           error(msg.c_str());
        }
        src.getline(buffer,tam_buffer);
     }
     else if ( token == "element" )
     {  src >> token ;
        if ( token == "vertex" )
        {  if ( state != 0 )
              error("la línea 'element vertex' va después de 'element face'");
           src >> num_vertices ;
           cout << "  numero de vértices == " << num_vertices << endl ;
           state = 1 ;
        }
        else if ( token == "face" )
        {  if ( state != 1 )
              error("advertencia 'element vertex' va después de 'element face'");
           src >> num_caras ;
           cout << "  número de caras == " << num_caras << endl ;
           state = 2 ;
        }
        else
        {  cout << "  elemento '" + token + "' ignorado." << endl ;
        }
        src.getline(buffer,tam_buffer);
     }
     else if ( token == "property" )
     {  src.getline(buffer,tam_buffer); // ignore properties, so far ...
     }
   } // end of while( en_cabecera )

   if ( num_vertices == 0 || num_caras == 0 )
      error("no se ha encontrado el número de vértices o caras, o bien alguno de los dos es 0.");
      
   if ( num_vertices > numeric_limits<unsigned>::max() )
      error("el número de vértices es superior al valor 'int' más grande posible.");
      
   
   if ( num_caras > numeric_limits<unsigned>::max() )
      error("el número de caras es superior al valor 'int' más grande posible.");
}

//**********************************************************************


void abrir_archivo()
{
   using namespace std ;

   src.open( nombre_archivo.c_str() ) ; // abrir (¿en modo lectura?)
      
   if ( ! src.is_open() ) 
   {
      string msg = string("no puedo abrir el archivo '") + nombre_archivo + "' para lectura." ; 
      error(msg.c_str());
   }
    
   src >> token ;

   if ( token != "ply" )
      error("el archivo de entrada no comienza con 'ply'");

   src.getline(buffer,tam_buffer);

   cout << "leyendo archivo ply '" + nombre_archivo + "'" << endl ;
}


//**********************************************************************

void error( const char *msg_error )
{
   using namespace std ;
   cout << "error leyendo archivo ply: " << msg_error << endl 
        << "programa terminado." << endl
        << flush ; 
        
   exit(1);
}




} // fin namespace _file_ply
