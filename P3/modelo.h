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
	Funcion para activar/desactivar la iluminación de las figuras
**/
void iluminacionON ();

/**
	Funcion para cambiar la sombra de las figuras (sombreado plano o suave)
**/
void setSombra ();

struct vertice{
    float x, y, z; //Coordenadas x,y,z que componen un vértice
};

struct cara{
    int v1, v2, v3; //Índice de vértices que componen una cara
};

int getAnguloR1();
int getAnguloR2();
int getAnguloR3();

void setAnguloR1(int angulo);
void setAnguloR2(int angulo);

void setAnguloR3(int angulo);



class Objeto3D 
{ 
public: 

virtual void draw( ) = 0; // Dibuja el objeto
} ;

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
         float largoBrazoPeq);
    void draw();
    void animaciones();
};