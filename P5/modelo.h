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
void Dibuja ();

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

void activarEsSeleccionado();
void activarGruaSeleccionada();

class Objeto3D 
{
protected:
    int id;
    bool textura = false;
    struct Material{
        float specular[4];
        float diffuse[4];
        float ambient[4];
        float brillo;
    };
    Material material;
    float blanco[4] = {1.0, 1.0, 1.0, 0.0};
public:
    Objeto3D(int id) {
        this->id = id;
    }
    void setSelectionColor();

    GLuint texId;
    unsigned int ancho, alto;
    virtual void draw( ) = 0; // Dibuja el objeto
    unsigned char *asignarTextura (const char *archivo){
        return LeerArchivoJPEG( archivo, ancho, alto);
    }
    void setMaterial(float ambient[4], float diffuse[4],
                     float specular[4], float brillo);
} ;

class Ejes:Objeto3D {
public:
    Ejes() : Objeto3D(id) {
        id = 0;
    };
    float longitud = 30;

// Dibuja el objeto
    void draw() override;
};

class Cubo: public Objeto3D {
private:
    float l;
public:
    Cubo(float lado, int id);
    void draw();
    void cargarTextura();
    void setDadoOriginal();
};

class mallaTriangulos : public Objeto3D{
private:
    void drawFlat();
    void drawSmooth();

public:

    explicit mallaTriangulos(const char archivo[50], int id);
    explicit mallaTriangulos(int id);

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
    //mallaTriangulos() : Objeto3D(id){}

    //Par de 2 doubles donde almacenamos u y v
    std::pair <double, double> coordenada;

    //Vector de pair donde almacenamos cada coordenada
    std::vector<std::pair<float, float>> coordenadas;

    //Variable lógica para verificar si es textura
    boolean esTextura = false;

    bool sombraPlana = false;

    float reflectividad = GL_AMBIENT_AND_DIFFUSE;

    void setReflectividad(float vision);

    void obtenerNormales();

    void draw();
};

//Getters de los ángulos de la grúa
int getAnguloR1();
int getAnguloR2();
int getAnguloR3();

//Setters de los ángulos de la grúa
void setAnguloR1(int angulo);
void setAnguloR2(int angulo);
void setAnguloR3(int angulo);

class Grua : public Objeto3D {
private:
    //Colores
    float rojo[4] = {1.0f, 0.0f, 0.0f, 0.0f };
    float amarillo[4] = {1.0f, 1.0f, 0.0f, 1 };
    float gris[4] = {0.5f, 0.5f, 0.5f};

    float alturaPie;
    float largoBrazoGrande;
    float alturaCuerda;
    float largoBrazoPeq;

    void A (float xzPie, float yPie, int numMallas);
    void B (float xCaja, float yCaja, float zCaja);
    void C (float xzTorre, float yTorre, int numMallas);
    void D (float xBrazoGrande, float zBrazoGrande, int numMallas);
    void E (float xCaja, float yCaja, float zCaja);
    void F (float yCuerda);
    void G (float yGancho);
    void H (float xBrazoPequenyo, float altoMalla, float anchoMalla, int numMallas);
    void I (float xCaja, float yCaja, float zCaja);

    void brazoPequenyoConCaja(float xBrazoPequenyo);
    void brazoGrandeConCaja(float xBrazoGrande);
    void cuerdaConGancho(float yCuerda);
    void brazoGrande (float xBrazoGrande, float yCuerda);
    void brazoGrandeConCubo (float xBrazoGrande, float yCuerda);
    void brazoGrandeConCuboYBrazoPequenyo(float xBrazoGrande,
                                          float yCuerda, float xBrazoPequenyo);
    void construirGrua(float xBrazoGrande, float yCuerda,
                       float xBrazoPequenyo, float yPie);
public:
    Grua(float alturaPie, float largoBrazoGrande, float alturaCuerda,
         float largoBrazoPeq, int id);
    void draw();
    void animaciones();
};

class mallaRevolucion : public mallaTriangulos {
private:
    std::vector<vertice> perfilPrimitivo;

    int n; //número de réplicas
    int m; //tamaño de perfilPrimitivo
    vertice v; //vértice
    cara c; //cara

public:

    mallaRevolucion(const char archivo[50], int veces, int id);
    void cargarTextura(const char archivo[50]);
    float obtenerDistancias(vertice v1, vertice v2);
    void obtenerCoordenadasLateral();
    void obtenerCoordenadasTapayBase(float desplazamiento);
    void setLataOriginal();
};

int pick(int x, int y);
void initMenu();
void manejadorMenu(int choice);