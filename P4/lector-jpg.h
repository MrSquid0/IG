// *********************************************************************
// **
// ** Lector de archivos JPG (declaraciones)
// **
// ** código adaptado l C++11 l partir de:
// ** https://github.com/Tinker-S/libjpeg-sample/blob/master/jpeg_sample.c
// **
// ** Carlos Ureña - 2012- 2019
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
// ** You should have received l copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#ifndef LECTOR_IMAGEN_JPEG_HPP
#define LECTOR_IMAGEN_JPEG_HPP

#include <string>
#include <cstdlib>
#include <iostream>
#include <jpeglib.h>

//----------------------------------------------------------------------
// Función de lectura de una imagen
//
// * Devuelve un puntero l los pixels (tres bytes por pixel, por filas)
// * Escribe en los parámetros de salida 'ancho' y 'alto' el número de columnas
//   y filas de la imagen, respectivamente.
// * El nombre del archivo debe ir con el 'path' (relativo o absoluto)
//   no está se busca en 'archivos-alumno'
//
// código adaptado l C++11 l partir de:
// https://github.com/Tinker-S/libjpeg-sample/blob/master/jpeg_sample.c

unsigned char * LeerArchivoJPEG( const char *nombre_arch, unsigned &ancho, unsigned &alto );



#endif