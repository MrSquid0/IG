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

class mallaTriangulos:Objeto3D{
    private:

    std::vector<float> vertices_ply;
    std::vector<int> caras_ply;

    std::vector<struct vertice> vertices;
    std::vector<struct cara> caras;

    public:
    //Constructor de la malla
    mallaTriangulos(){
        ply::read("./plys/beethoven.ply", vertices_ply, caras_ply);

        vertices.resize(vertices_ply.size() / 3);
        int contador = 0;


        //Introducimos las 3 coordenadas (x,y,z) en cada vértice
        for (int i=0; i<vertices_ply.size(); i+=3){
            vertices[contador].x = vertices_ply[i];
            vertices[contador].y = vertices_ply[i+1];
            vertices[contador].z = vertices_ply[i+2];
            contador++;
        }

        //Introducimos los 3 vértices en cada cara (v1, v2, v3)
        caras.resize(caras_ply.size() / 3);
        contador = 0;
        for (int i=0; i<caras_ply.size(); i+=3){
            caras[contador].v1 = caras_ply[i];
            caras[contador].v2 = caras_ply[i+1];
            caras[contador].v3 = caras_ply[i+2];
            contador++;
        }
    }
    //Método para dibujar la malla
    void draw(){
        glBegin (GL_TRIANGLES);
        {
            for (int i=0; i<caras.size(); i++){
                glVertex3f (vertices[caras[i].v1].x, vertices[caras[i].v1].y, vertices[caras[i].v1].z);
                glVertex3f (vertices[caras[i].v2].x, vertices[caras[i].v2].y, vertices[caras[i].v2].z);
                glVertex3f (vertices[caras[i].v3].x, vertices[caras[i].v3].y, vertices[caras[i].v3].z);
            }
        }
        glEnd();
    }
};


/**
 * Instanciamos objetos de los ejes y las cuatro figuras
 */

Ejes ejesCoordenadas;
mallaTriangulos malla;


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
        glEnable(GL_LIGHTING); //Activa
    else
        glDisable(GL_LIGHTING); //Desactiva

    glPolygonMode (GL_FRONT_AND_BACK, modo) ; //Cambia los modos de visualización

    malla.draw(); //Dibuja la malla de triángulos

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