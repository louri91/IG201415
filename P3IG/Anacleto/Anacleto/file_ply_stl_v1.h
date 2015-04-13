// *********************************************************************
// **
// ** Función ply::read (declaración)
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

#ifndef _PLY_H
#define _PLY_H


#include <vector>


namespace ply
{


// **********************************************************************
// **
// ** ply::read 
// **
// **  lee un archivo ply y lo carga en 'vertices' y 'caras'
// **
// **   - 'nombre_archivo' no debe incluir la extensión .ply 
// **     (se le añade antes de abrirlo)
// **   - si hay un error, aborta
// **   - elimina cualquier contenido previo en los 
// **     vectores 'vertices' y 'caras'
// **   - lee el archivo .ply y lo carga en 'vertices' y 'faces'
// **   - solo admite plys con triángulos, 
// **   - no lee colores, coordenadas de textura, ni normales.
// **
// *********************************************************************

void read
(  
   const char *         nombre_archivo_se, // entrada: nombre de archivo sin extensión
   std::vector<float> & vertices,          // salida:  vector de coords. de vert.
   std::vector<int> &   caras              // salida:  vector de triángulos (índices)
);
   
} ; // fin namespace ply

#endif // _PLY_H
