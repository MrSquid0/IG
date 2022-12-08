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

class mallaTriangulos:Objeto3D{
private:

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
    mallaTriangulos(){}

    //Constructor de la malla pasándole por argumento la figura que queramos dibujar
    mallaTriangulos(const char archivo[50]) {
        char fichero[50];
        sprintf(fichero, "./plys/%s", archivo);
        ply::read(fichero, vertices_ply, caras_ply);

        int contador = 0; //Contador de vértices

        //Introducimos las 3 coordenadas (x,y,z) en cada vértice
        vertices.resize(vertices_ply.size() / 3);
        for (int i = 0; i < vertices_ply.size(); i += 3) {
            vertices[contador].x = vertices_ply[i];
            vertices[contador].y = vertices_ply[i + 1];
            vertices[contador].z = vertices_ply[i + 2];
            contador++;
        }
        contador = 0; //Reseteamos a 0 para ser ahora contador de caras

        //Introducimos los 3 vértices en cada cara (v1, v2, v3)
        caras.resize(caras_ply.size() / 3);
        for (int i = 0; i < caras_ply.size(); i += 3) {
            caras[contador].v1 = caras_ply[i];
            caras[contador].v2 = caras_ply[i + 1];
            caras[contador].v3 = caras_ply[i + 2];
            contador++;
        }

        obtenerNormales();

    }

void obtenerNormales(){
    //Calculamos las normales de las caras
    normalesCaras.resize(caras.size());
    for (int i=0; i<caras.size(); i++){
        vertice vector1, vector2, prodVec;
        float modulo;

        //Calculamos el vector 1 de la cara (P0, P1)
        vector1.x = vertices[caras[i].v2].x - vertices[caras[i].v1].x;
        vector1.y = vertices[caras[i].v2].y - vertices[caras[i].v1].y;
        vector1.z = vertices[caras[i].v2].z - vertices[caras[i].v1].z;

        //Calculamos el vector 2 de la cara (P0, P2)
        vector2.x = vertices[caras[i].v3].x - vertices[caras[i].v1].x;
        vector2.y = vertices[caras[i].v3].y - vertices[caras[i].v1].y;
        vector2.z = vertices[caras[i].v3].z - vertices[caras[i].v1].z;

        //Calculamos el producto vectorial de vector1 con vector2
        prodVec.x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
        prodVec.y = -1 * ((vector1.x * vector2.z) - (vector1.z * vector2.x));
        prodVec.z = (vector1.x * vector2.y) - (vector1.y * vector2.x);

        //Calculamos el módulo
        modulo = sqrt(pow(prodVec.x, 2) + pow(prodVec.y, 2) + pow(prodVec.z, 2));

        normalesCaras[i].x = prodVec.x / modulo;
        normalesCaras[i].y = prodVec.y / modulo;
        normalesCaras[i].z = prodVec.z / modulo;
    }

    //Inicializamos todas las posiciones de normalesVertices l 0,0,0
    vertice verticesACero;
    verticesACero.x = 0;
    verticesACero.y = 0;
    verticesACero.z = 0;
    for(int i=0; i<vertices.size(); i++){
        normalesVertices.push_back(verticesACero);
    }

    //Calculamos las normales de los vértices
    normalesVertices.resize(vertices.size());
    for (int i=0; i<normalesVertices.size(); i++){

        //Calculamos la normal del vértice 1 de la cara
        normalesVertices[caras[i].v1].x += normalesCaras[i].x;
        normalesVertices[caras[i].v1].y += normalesCaras[i].y;
        normalesVertices[caras[i].v1].z += normalesCaras[i].z;

        //Calculamos la normal del vértice 2 de la cara
        normalesVertices[caras[i].v2].x += normalesCaras[i].x;
        normalesVertices[caras[i].v2].y += normalesCaras[i].y;
        normalesVertices[caras[i].v2].z += normalesCaras[i].z;

        //Calculamos la normal del vértice 3 de la cara
        normalesVertices[caras[i].v3].x += normalesCaras[i].x;
        normalesVertices[caras[i].v3].y += normalesCaras[i].y;
        normalesVertices[caras[i].v3].z += normalesCaras[i].z;
    }

    for (int i=0; i<normalesVertices.size(); i++){
        float modulo = sqrt(pow(normalesVertices[i].x, 2) + pow(normalesVertices[i].y, 2) +
                            pow (normalesVertices[i].z, 2));

        if (modulo > 0){
            normalesVertices[i].x = normalesVertices[i].x/modulo;
            normalesVertices[i].y = normalesVertices[i].y/modulo;
            normalesVertices[i].z = normalesVertices[i].z/modulo;
        }
    }
}

    //Función para pintar la figura con sombra plana
    void drawFlat(){
        glShadeModel(GL_FLAT);
        glBegin (GL_TRIANGLES);
        {
            for (int i=0; i<caras.size(); i++){
                //Dibujamos la normal de la figura
                glNormal3f(normalesCaras[i].x, normalesCaras[i].y, normalesCaras[i].z);
                //Dibujamos los vértices de las caras
                glVertex3f (vertices[caras[i].v1].x, vertices[caras[i].v1].y, vertices[caras[i].v1].z);
                glVertex3f (vertices[caras[i].v2].x, vertices[caras[i].v2].y, vertices[caras[i].v2].z);
                glVertex3f (vertices[caras[i].v3].x, vertices[caras[i].v3].y, vertices[caras[i].v3].z);
            }
        }
        glEnd();
    }

    //Función para pintar la figura con sombra suave
    void drawSmooth(){
        glShadeModel(GL_SMOOTH);
        glBegin (GL_TRIANGLES);
        {
            for (int i = 0; i < caras.size(); i++) {
                glNormal3f(normalesVertices[caras[i].v1].x, normalesVertices[caras[i].v1].y,
                           normalesVertices[caras[i].v1].z);
                glVertex3f(vertices[caras[i].v1].x, vertices[caras[i].v1].y, vertices[caras[i].v1].z);

                glNormal3f(normalesVertices[caras[i].v2].x, normalesVertices[caras[i].v2].y,
                           normalesVertices[caras[i].v2].z);
                glVertex3f(vertices[caras[i].v2].x, vertices[caras[i].v2].y, vertices[caras[i].v2].z);

                glNormal3f(normalesVertices[caras[i].v3].x, normalesVertices[caras[i].v3].y,
                           normalesVertices[caras[i].v3].z);
                glVertex3f(vertices[caras[i].v3].x, vertices[caras[i].v3].y, vertices[caras[i].v3].z);
            }
        }
        glEnd();
    }

    //Lo dejamos sin implementar, ya que de lo contrario, da error y en su lugar, usamos la función pinta() de abajo
    void draw(){

    }

//Método para dibujar la malla
void pinta(bool sombra){
    if (sombraPlana)
        drawSmooth();
    else
        drawFlat();
}
};

class mallaRevolucion : public mallaTriangulos{
        private:
        std::vector<vertice> perfilPrimitivo;

        int n; //número de réplicas
        int m; //tamaño de perfilPrimitivo
        vertice v; //vértice
        cara c; //cara

        public:

        mallaRevolucion(const char archivo[50], int veces) {
            n = veces;
            char fichero[50];
            sprintf(fichero, "./plys/%s", archivo);
            ply::read_vertices(fichero, vertices_ply);

            //Rellenamos los vértices en perfilPrimitivo
            for (int i=0; i<vertices_ply.size(); i+=3){
                v.x = vertices_ply[i];
                v.y = vertices_ply[i+1];
                v.z = vertices_ply[i+2];

                perfilPrimitivo.push_back(v);
            }

            //Asignamos a m el tamaño de perfilPrimitivo
            m = perfilPrimitivo.size();

            //Rellenamos la lista de vértices
            for (int i=0; i<n; i++){
                for (int j=0; j<m; j++){
                    v.x = perfilPrimitivo[j].x * cos((2*i*M_PI)/(n-1));
                    v.y = perfilPrimitivo[j].y;
                    v.z = perfilPrimitivo[j].x * sin((2*i*M_PI)/(n-1));

                    vertices.push_back(v);
                }
            }

            //Creamos dos triángulos nuevos que son adyacentes a ese vértice en cada iteración
            for (int i=0; i<n-1; i++){
                for (int j=0; j<m-1; j++){

                    int k = i * m + j;
                    c.v1 = k;
                    c.v3 = k+m;
                    c.v2 = k+m+1;

                    caras.push_back(c);

                    c.v1 = k;
                    c.v3 = k+m+1;
                    c.v2 = k+1;

                    caras.push_back(c);
                }
            }

            //Calculamos las normales de la malla de revolución
            obtenerNormales();
        }

};



/**
 * Instanciamos objetos de los ejes y las cuatro figuras
 */

Ejes ejesCoordenadas;
mallaTriangulos busto("beethoven.ply");
mallaRevolucion peon("perfil.ply", 30);
mallaTriangulos coche("big_dodge.ply");


/**	void Dibuja( void )
Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
**/

void Dibuja (void)
{
    //Colores para dibujar las figuras
    float verde[4] = {0.0f, 1.0f, 0.0f};
    float rosa[4] = { 0.8, 0.0, 1, 1 };
    float rojo[4] = {1.0f, 0.0f, 0.0f, 0.0f};

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

    glTranslatef( -8, 0, 0 ); //Traslada la primera figura a -50x

    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);
    busto.pinta(sombraPlana); //Dibuja la malla de triángulos

    glTranslatef( 8, 0, 0 ); //Traslada la siguiente figura

    glScalef(3,3,3);
    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rosa);
    peon.pinta(sombraPlana); //Dibuja la malla de revolución

    glTranslatef( 5, 0, 0 ); //Traslada la siguiente figura

    glScalef(0.5,0.5,0.5);
    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    coche.pinta(sombraPlana); //Dibuja la malla de triángulos

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