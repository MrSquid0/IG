/*	Prácticas de Informática Gráfica
	Grupo C					Curso 2022-23

	Codigo base para la realización de las practicas de IG

	Estudiante: Gonzalo Jose Lopez Castilla
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
=======================================================/
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include <vector>
#include "file_ply_stl.h"
#include "estructura.h"

/**	void initModel()
Inicializa el modelo y de las variables globales
**/
void
initModel ()
{


}

int anguloR1 = 0, anguloR2 = 0, anguloR3 = 0, anguloAnimacion = 0;

int getAnguloR1(){
    return anguloR1;
};
int getAnguloR2(){
    return anguloR2;
};
int getAnguloR3(){
    return anguloR3;
};

void setAnguloR1(int angulo){
    anguloR1 = angulo;
};

void setAnguloR2(int angulo){
    anguloR2 = angulo;
};

void setAnguloR3(int angulo){
    anguloR3 = angulo;
};

void animaciones(){
    //Aumentanmos R1
    setAnguloR1(getAnguloR1()+1);
    if (getAnguloR1()>360)
        setAnguloR1(getAnguloR1()-360);

    if (anguloAnimacion < anguloR2 || anguloR2 == -90){
        anguloAnimacion = anguloR2;
        //Aumentamos R2
        setAnguloR2(getAnguloR2()+1);
        if (getAnguloR2()>90)
            setAnguloR2(90);
    } else if (anguloAnimacion > anguloR2 || anguloR2 == 90){
        anguloAnimacion = anguloR2;
        //Decrementamos R2
        setAnguloR2(getAnguloR2()-1);
        if (getAnguloR2()<-90)
            setAnguloR2(-90);
    } else {
        //Aumentamos R2
        setAnguloR2(getAnguloR2()+1);
        if (getAnguloR2()>90)
            setAnguloR2(90);
    }

    //Aumentamos R3
    setAnguloR3(getAnguloR3()+1);
    if (getAnguloR3()>360)
        setAnguloR3(getAnguloR3()-360);
}


int modo = GL_FILL;
bool iluminacion = true;
bool sombraPlana = false;

void setModo (int M){
    modo = M;
}

void iluminacionON (){
    if (iluminacion)
        iluminacion = false;
    else
        iluminacion = true;
}

void setSombra (){
    if (sombraPlana)
        sombraPlana = false;
    else
        sombraPlana = true;
}

class Ejes:Objeto3D
{
public:
float longitud = 30;
// Dibuja el objeto
void draw( )
{
    glDisable (GL_LIGHTING);
    glBegin (GL_LINES);
    {
        glColor3f (0, 1, 0);
        glVertex3f (0, 0, 0);
        glVertex3f (0, longitud, 0);

        glColor3f (1, 0, 0);
        glVertex3f (0, 0, 0);
        glVertex3f (longitud, 0, 0);

        glColor3f (0, 0, 1);
        glVertex3f (0, 0, 0);
        glVertex3f (0, 0, longitud);
    }
    glEnd ();
    glEnable (GL_LIGHTING);
}
};
/**
 * Colores
 */
    float rojo[4] = {1.0f, 0.0f, 0.0f, 0.0f };
    float amarillo[4] = {1.0f, 1.0f, 0.0f, 1 };
    float gris[4] = {0.5f, 0.5f, 0.5f};

    //Figuras según el grafo
    void A (float xzPie, float yPie, int numMallas){
        glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarillo);
        creaEstructura(0, 0, 0, 0, yPie, 0, xzPie, xzPie, numMallas);
    }


    void B (float xCaja, float yCaja, float zCaja){
        glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarillo);
        paralelepipedo(0, 0, 0, 0, yCaja, 0, xCaja, zCaja);
    }

    void C (float xzTorre, float yTorre, int numMallas){
        glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
        creaTorre(0, 0, 0, 0, yTorre, 0, xzTorre, xzTorre, numMallas);
    }

    void D (float xBrazoGrande, float zBrazoGrande, int numMallas){
        glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarillo);
        creaBrazo(0, 0, 0, xBrazoGrande, 0, 0, zBrazoGrande, numMallas);
    }

    void E (float xCaja, float yCaja, float zCaja){
        glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
        paralelepipedo(0, 0, 0, 0, yCaja, 0, xCaja, zCaja);
    }

    void F (float yCuerda){
        glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gris);
        cilindro(0, 0, 0, 0, yCuerda, 0, 0.1);
    }

    void G (float yGancho){
        glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gris);
        creaGancho(0, 0, 0, yGancho);
    }

    void H (float xBrazoPequenyo, float altoMalla, float anchoMalla, int numMallas){
        glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarillo);
        creaEstructura(0, 0, 0, xBrazoPequenyo, 0, 0, altoMalla, anchoMalla, numMallas);
    }

    void I (float xCaja, float yCaja, float zCaja){
        glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gris);
        caja(xCaja,yCaja,zCaja);
    }


//H+I
    void brazoPequenyoConCaja(float xBrazoPequenyo){

        int numMallas = xBrazoPequenyo/2;
        float altoMalla = 0.5, anchoMalla = 1;
        H (xBrazoPequenyo, altoMalla, anchoMalla, numMallas);

        float xCaja = xBrazoPequenyo/3, yCaja = altoMalla, zCaja = anchoMalla;
        glTranslatef(xBrazoPequenyo-xCaja/2, altoMalla / 2 - yCaja * 2, 0); //T5
        I (xCaja, yCaja, zCaja);
    }

//D+E
    void brazoGrandeConCaja(float xBrazoGrande){
        int numMallas = xBrazoGrande/2;
        float zBrazoGrande = 1;
        D(xBrazoGrande, zBrazoGrande, numMallas);

        float xCaja = xBrazoGrande/numMallas, yCaja = zBrazoGrande/8, zCaja = zBrazoGrande;
        glTranslatef(xCaja/2,-yCaja,0); //T8
        E(xCaja, yCaja, zCaja);
    }

//F+G
    void cuerdaConGancho(float yCuerda){
        glRotatef(anguloR2, 0,0,1);//R2
        F(yCuerda);

        float yGancho = yCuerda/4;
        glTranslatef(0, yCuerda/4-yGancho, 0); //T9
        glRotatef(anguloR3, 0,1,0);//R3
        G(yGancho);
    }

//D+E+F+G
    void brazoGrande (float xBrazoGrande, float yCuerda){

        glPushMatrix();
        brazoGrandeConCaja(xBrazoGrande);
        glPopMatrix();

        int numMallas = xBrazoGrande/8;
        if (xBrazoGrande <= 15)
            numMallas = xBrazoGrande/8 * 2;
        if (xBrazoGrande <= 8)
            numMallas = xBrazoGrande/8 * 4;

        glTranslatef(numMallas/2,-yCuerda,0); //T7
        glPushMatrix();
        cuerdaConGancho(yCuerda);
        glPopMatrix();
    }

//D+E+F+G+B
    void brazoGrandeConCubo (float xBrazoGrande, float yCuerda){
        int numMallas = xBrazoGrande/2;
        glPushMatrix();
        brazoGrande(xBrazoGrande, yCuerda);
        glPopMatrix();

        float xCajaCubo = numMallas/4, yCajaCubo = -xCajaCubo/2, zCajaCubo = numMallas/4;

        glPushMatrix();
        glTranslatef(xBrazoGrande+xCajaCubo/2,0,0); //T6
        B(xCajaCubo, yCajaCubo, zCajaCubo);
        glPopMatrix();
    }

//D+E+F+G+B+H+I

    void brazoGrandeConCuboYBrazoPequenyo(float xBrazoGrande, float yCuerda, float xBrazoPequenyo){
        glRotatef(anguloR1, 0,1,0); //R1
        glTranslatef(-xBrazoGrande, 0, 0); //T3
        glPushMatrix();
        brazoGrandeConCubo(xBrazoGrande, yCuerda);
        glPopMatrix();

        int numMallas = xBrazoGrande/2;
        float xCajaCubo = numMallas/4, yCajaCubo = xCajaCubo/2;
        glTranslatef(xBrazoGrande+xCajaCubo, yCajaCubo-yCajaCubo/2,0); //T4
        glPushMatrix();
        brazoPequenyoConCaja(xBrazoPequenyo);
        glPopMatrix();
    }

//A+C+D+E+F+G+B+H+I
    void construirGrua(float xBrazoGrande, float yCuerda, float xBrazoPequenyo,
                       float yPie){
        //Construimos figura A
        int numMallasPie = xBrazoGrande/2;
        float xzPieYTorre = 1;
        A(xzPieYTorre, yPie, numMallasPie);

        //Construimos figura brazoGrandeConCuboYBrazoPequenyo
        int numMallas = xBrazoGrande/2;
        float xCajaCubo = numMallas/4, yCajaCubo = xCajaCubo/2;
        glTranslatef(xCajaCubo/2 - xzPieYTorre, yPie + yCajaCubo, 0); //T1
        glPushMatrix();
        brazoGrandeConCuboYBrazoPequenyo(xBrazoGrande, yCuerda, xBrazoPequenyo);
        glPopMatrix();

        //Construimos figura C
        glTranslatef(xCajaCubo/2,0,0); //T2
        float yTorre = xBrazoGrande/5;
        int numMallasTorre = numMallas/2;
        C(xzPieYTorre, yTorre, numMallasTorre);
    }
    void dibujaGrua(float alturaPie, float largoBrazoGrande, float alturaCuerda,
                    float largoBrazoPeq){
        construirGrua(largoBrazoGrande,alturaCuerda,
                      largoBrazoPeq,alturaPie);
    }

/**
 * Instanciamos objetos de los ejes y de la grúa
 */

Ejes ejesCoordenadas;



/**	void Dibuja( void )
Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
**/

void Dibuja (void)
{
    static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

    float  color[4] = { 0.8, 0.0, 1, 1 };

    glPushMatrix ();		// Apila la transformacion geometrica actual

    glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

    transformacionVisualizacion ();	// Carga transformacion de visualizacion

    glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

    ejesCoordenadas.draw();			// Dibuja los ejes

    dibujaGrua(10,10,3,6);

    if (iluminacion) //Activa / desactiva la iluminación de las figuras
        glEnable(GL_LIGHTING); //Activa
    else
        glDisable(GL_LIGHTING); //Desactiva

    glPolygonMode (GL_FRONT_AND_BACK, modo) ; //Cambia los modos de visualización

    /* Dibujos de la PRÁCTICA 2
    glTranslatef( -50, 0, 0 ); //Traslada la primera figura a -50x

    malla.pinta(sombraPlana); //Dibuja la malla de triángulos

    glTranslatef( 50, 0, 0 ); //Traslada la siguiente figura

    mallaDos.pinta(sombraPlana);

    glTranslatef( 50, 0, 0 ); //Traslada la siguiente figura

    mallaTres.pinta(sombraPlana);
    */

    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

    // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)

    glPopMatrix ();		// Desapila la transformacion geometrica


    glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**	void idle()
Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.
**/
void idle (int v) {

    glutPostRedisplay();        // Redibuja
    glutTimerFunc(30, idle, 0);    // Vuelve a activarse dentro de 30 ms
    animaciones();
}