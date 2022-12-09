/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: 

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informticos
	(Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================

	 modelo.h
*/

#include <vector>
#include "lector-jpg.h"

/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja (void);

/**
	Funcion de fondo
**/
void idle (int v);

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel ();

/**
	Funcion para cambiar el modo de visualización de las figuras
**/
void setModo (int M);

/**
	Funcion para activar/desactivar la iluminación general de las figuras
**/
void setIluminacionGeneral ();

/**
	Funcion para activar/desactivar la iluminación 1 de las figuras
**/

void setIluminacion1();

/**
	Funcion para activar/desactivar la iluminación 2 de las figuras
**/

void setIluminacion2();

struct vertice{
    float x, y, z; //Coordenadas x, y, z que componen un vértice
};

struct cara{
    int v1, v2, v3; //Índice de vértices que componen una cara
};



class Objeto3D 
{
public:
    GLuint texId;
    unsigned int ancho, alto;
    unsigned int material = GL_AMBIENT_AND_DIFFUSE;
    float color[4];
    virtual void draw( ) = 0; // Dibuja el objeto
    unsigned char *asignarTextura (const char *archivo){
        return LeerArchivoJPEG( archivo, ancho, alto);
    }
    void setMaterialColorLuz(unsigned int material, float colorMaterial[4],
                             unsigned int luz);
} ;

class Ejes:Objeto3D {
public:
    float longitud = 30;

// Dibuja el objeto
    void draw();
};

class Cubo: public Objeto3D {
private:
    float l;
public:
    Cubo(float lado);
    void draw();
    void cargarTextura();
};

class mallaTriangulos : public Objeto3D{
private:
    void drawFlat();
    void drawSmooth();
public:
    //Almacena todos los vértices y caras de los archivos '.ply'
    std::vector<float> vertices_ply;
    std::vector<int> caras_ply;

    //Almacena los vértices y las caras de los anteriores vectores
    std::vector<struct vertice> vertices;
    std::vector<struct cara> caras;

    //Almacena las normales de los vértices y de las caras
    std::vector<struct vertice> normalesCaras;
    std::vector<struct vertice> normalesVertices;

    //Constructor por defecto
    mallaTriangulos(){}

    //Par de 2 doubles donde almacenamos u y v
    std::pair <double, double> coordenada;

    //Vector de pair donde almacenamos cada coordenada
    std::vector<std::pair<double, double>> coordenadas;

    //Variable lógica para verificar si es textura
    boolean esTextura = false;

    float reflectividad = GL_AMBIENT_AND_DIFFUSE;

    explicit mallaTriangulos(const char archivo[50]);

    void setReflectividad(float vision);

    void obtenerNormales();

    void draw();

    void cargarTextura(const char archivo[50]);
};

class mallaRevolucion : public mallaTriangulos {
private:
    std::vector<vertice> perfilPrimitivo;

    int n; //número de réplicas
    int m; //tamaño de perfilPrimitivo
    vertice v; //vértice
    cara c; //cara

public:

    mallaRevolucion(const char archivo[50], int veces);
    float obtenerDistancias(vertice v1, vertice v2);
    void obtenerCoordenadasLateral();
    void obtenerCoordenadasTapayBase(float desplazamiento);
};