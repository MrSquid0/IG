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


/**	void initModel()

Inicializa el modelo y de las variables globales


**/
void
initModel ()
{


}

int modo = GL_FILL;
bool iluminacion = true;

void setModo (int M){
    modo = M;
}

void iluminacionON (){
    if (iluminacion)
        iluminacion = false;
    else
        iluminacion = true;
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

class Cubo:Objeto3D{
private:
float l;
public:
Cubo (float lado){
    l = lado;
};
void draw(){
    //Construye un cubo dado un lado

    float color[4] = { 0.8, 0.0, 1, 1 };
    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glBegin (GL_QUAD_STRIP);
    {				/* Caras transversales */
        glNormal3f (0.0, 0.0, 1.0);	/*Vertical delantera */
        glVertex3f (l, l, l);
        glVertex3f (0, l, l);
        glVertex3f (l, 0, l);
        glVertex3f (0, 0, l);
        glNormal3f (0.0, -1.0, 0.0);	/*Inferior */
        glVertex3f (l, 0, 0);
        glVertex3f (0, 0, 0);
        glNormal3f (0.0, 0.0, -1.0);	/* Vertical hacia atras */
        glVertex3f (l, l, 0);
        glVertex3f (0, l, 0);
        glNormal3f (0.0, 1.0, 0.0);	/* Superior, horizontal */
        glVertex3f (l, l, l);
        glVertex3f (0, l, l);
    }
    glEnd ();
    glBegin (GL_QUADS);
    {				/* Costados */
        glNormal3f (1.0, 0.0, 0.0);
        glVertex3f (l, 0, 0);
        glVertex3f (l, l, 0);
        glVertex3f (l, l, l);
        glVertex3f (l, 0, l);
        glNormal3f (-1.0, 0.0, 0.0);
        glVertex3f (0, 0, 0);
        glVertex3f (0, 0, l);
        glVertex3f (0, l, l);
        glVertex3f (0, l, 0);
    }
    glEnd ();
}
};

class Piramide:Objeto3D{
private:
float l, a;
float B, normalY, normalXZ;
public:
Piramide (float lado, float alto){
    l = lado;
    a = alto;
    B = sqrt(l*l + a*a);
    normalY = a / B;
    normalXZ = l / B;
};
void draw(){
    //Construye una pirámide dado un lado y el alto

    float color2[4] = { 0.0, 1.0, 0.0, 1 };
    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
    glBegin (GL_QUADS);
    {				/* Caras transversales */
        glNormal3f (0.0, -normalY, 0.0);
        glVertex3f (0, 0, 0);
        glVertex3f (l, 0, 0);
        glVertex3f (l, 0, l);
        glVertex3f (0, 0, l);
    }
    glEnd ();

    glBegin (GL_TRIANGLES);
    {
        glNormal3f (-normalXZ, normalY, 0.0);
        glVertex3f (l/2, a, l/2);
        glVertex3f (0, 0, 0);
        glVertex3f (0, 0, l);

        glNormal3f (0.0, normalY, -normalXZ);
        glVertex3f (l/2, a, l/2);
        glVertex3f (l, 0, 0);
        glVertex3f (0, 0, 0);

        glNormal3f (normalXZ, normalY, 0.0);
        glVertex3f (l/2, a, l/2);
        glVertex3f (l, 0, l);
        glVertex3f (l, 0, 0);

        glNormal3f (0.0, normalY, normalXZ);
        glVertex3f (l/2, a, l/2);
        glVertex3f (0, 0, l);
        glVertex3f (l, 0, l);

    }
    glEnd ();
}
};

class Rectangulo:Objeto3D{
private:
float l, a
float B, normalY, normalXZ;
public:
Piramide (float lado, float alto){
    l = lado;
    a = alto;
    B = sqrt(l*l + a*a);
    normalY = a / B;
    normalXZ = l / B;
};
void draw(){
    //Construye una pirámide dado un lado y el alto

    float color2[4] = { 0.0, 1.0, 0.0, 1 };
    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
    glBegin (GL_QUADS);
    {				/* Caras transversales */
        glNormal3f (0.0, -normalY, 0.0);
        glVertex3f (0, 0, 0);
        glVertex3f (l, 0, 0);
        glVertex3f (l, 0, l);
        glVertex3f (0, 0, l);
    }
    glEnd ();

    glBegin (GL_TRIANGLES);
    {
        glNormal3f (-normalXZ, normalY, 0.0);
        glVertex3f (l/2, a, l/2);
        glVertex3f (0, 0, 0);
        glVertex3f (0, 0, l);

        glNormal3f (0.0, normalY, -normalXZ);
        glVertex3f (l/2, a, l/2);
        glVertex3f (l, 0, 0);
        glVertex3f (0, 0, 0);

        glNormal3f (normalXZ, normalY, 0.0);
        glVertex3f (l/2, a, l/2);
        glVertex3f (l, 0, l);
        glVertex3f (l, 0, 0);

        glNormal3f (0.0, normalY, normalXZ);
        glVertex3f (l/2, a, l/2);
        glVertex3f (0, 0, l);
        glVertex3f (l, 0, l);

    }
    glEnd ();
}
};




Ejes ejesCoordenadas;
Cubo cubo(5);
Piramide piramide(5,6);


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

    if (iluminacion) //Activa / desactiva la iluminación de las figuras
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);

    glPolygonMode (GL_FRONT_AND_BACK, modo) ; //Cambia los modos de visualización

    cubo.draw(); //Dibuja el cubo

    glTranslatef( 7, 0, 0 ); //Traslada la siguiente figura

    piramide.draw(); //Dibuja la pirámide

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
}