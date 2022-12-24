/*	Prácticas de Informática Gráfica
	Grupo C					Curso 2022-23

	Codigo base para la realización de las practicas de IG

	Estudiante: Gonzalo Jose Lopez Castilla
=======================================================
	G. Arroyo, J.C. Torres
	Dpto. Lenguajes y Sistemas Informáticos
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
#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>        // Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include <vector>
#include "file_ply_stl.h"


/**	void initModel()
Inicializa el modelo y de las variables globales
**/

int modo = GL_FILL;
bool iluminacionGeneral = true;
bool iluminacion1 = false;
bool iluminacion2 = false;

void setModo(int M) {
    modo = M;
}

void setIluminacionGeneral() {
    if (iluminacionGeneral)
        iluminacionGeneral = false;
    else
        iluminacionGeneral = true;
}

void setIluminacion1() {
    if (iluminacion1)
        iluminacion1 = false;
    else
        iluminacion1 = true;
}

void setIluminacion2() {
    if (iluminacion2)
        iluminacion2 = false;
    else
        iluminacion2 = true;
}

void mallaTriangulos::setMaterial(float ambient[4], float diffuse[4],
                                  float specular[4], float brillo) {
    for (int i = 0; i < 4; i++) {
        material.ambient[i] = ambient[i];
    }
    for (int i = 0; i < 4; i++) {
        material.diffuse[i] = diffuse[i];
    }
    for (int i = 0; i < 4; i++) {
        material.specular[i] = specular[i];
    }
    material.brillo = brillo;
    glPushAttrib(GL_LIGHTING_BIT);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material.brillo);
}

void Ejes::draw() {
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    {
        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, longitud, 0);

        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(longitud, 0, 0);

        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, longitud);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

Cubo::Cubo(float lado) {
    l = lado;
}

void Cubo::draw() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);
    //Construye un cubo dado un lado

    float blanco[4] = {1.0, 1.0, 1.0, 0.0};
    glBegin(GL_QUADS);
    {    //Cara inferior
        glNormal3f(0.0, -1, 0.0);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0.75, 0.5);
        glVertex3f(l, 0, 0);
        glTexCoord2f(0.75, 0.75);
        glVertex3f(l, 0, l);
        glTexCoord2f(0.5, 0.75);
        glVertex3f(0, 0, l);


        //Cara superior
        glNormal3f(0.0, 1, 0.0);
        glTexCoord2f(0.25, 0.5);
        glVertex3f(0, l, 0);
        glTexCoord2f(0.25, 0.75);
        glVertex3f(0, l, l);
        glTexCoord2f(0, 0.75);
        glVertex3f(l, l, l);
        glTexCoord2f(0, 0.5);
        glVertex3f(l, l, 0);
    }
    glEnd();

    glBegin(GL_QUADS);
    {
        //Cara delantera
        glNormal3f(0.0, 0.0, 1);
        glTexCoord2f(0.5, 1);
        glVertex3f(0, l, l);
        glTexCoord2f(0.5, 0.75);
        glVertex3f(0, 0, l);
        glTexCoord2f(0.75, 0.75);
        glVertex3f(l, 0, l);
        glTexCoord2f(0.75, 1);
        glVertex3f(l, l, l);

        //Cara izquierda
        glNormal3f(-1, 0.0, 0.0);
        glTexCoord2f(0.25, 0.5);
        glVertex3f(0, l, 0);
        glTexCoord2f(0.25, 0.75);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0.5, 0.75);
        glVertex3f(0, 0, l);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0, l, l);

        //Cara trasera
        glNormal3f(0.0, 0.0, -1);
        glTexCoord2f(0.5, 0.25);
        glVertex3f(0, l, 0);
        glTexCoord2f(0.75, 0.25);
        glVertex3f(l, l, 0);
        glTexCoord2f(0.75, 0.5);
        glVertex3f(l, 0, 0);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0, 0, 0);

        //Cara derecha
        glNormal3f(1, 0.0, 0.0);
        glTexCoord2f(1, 0.5);
        glVertex3f(l, l, 0);
        glTexCoord2f(1, 0.75);
        glVertex3f(l, l, l);
        glTexCoord2f(0.75, 0.75);
        glVertex3f(l, 0, l);
        glTexCoord2f(0.75, 0.5);
        glVertex3f(l, 0, 0);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopAttrib();
}

void Cubo::cargarTextura() {
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, asignarTextura("jpg/dado.jpg"));
}

//Constructor de la malla pasándole por argumento la figura que queramos dibujar
mallaTriangulos::mallaTriangulos(const char archivo[50]) {
    esTextura = false;
    char fichero[50];
    sprintf(fichero, "./plys/%s", archivo);
    ply::read(fichero, vertices_ply, caras_ply);

    int contador = 0; //Contador de vértices

    //Introducimos las 3 coordenadas (x, y, z) en cada vértice
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

void mallaTriangulos::setReflectividad(float vision) {
    reflectividad = vision;
}

void mallaTriangulos::obtenerNormales() {
    //Calculamos las normales de las caras
    normalesCaras.resize(caras.size());
    for (int i = 0; i < caras.size(); i++) {
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

    //Inicializamos todas las posiciones de normalesVertices a 0,0,0
    vertice verticesACero;
    verticesACero.x = 0;
    verticesACero.y = 0;
    verticesACero.z = 0;
    for (int i = 0; i < vertices.size(); i++) {
        normalesVertices.push_back(verticesACero);
    }

    //Calculamos las normales de los vértices
    normalesVertices.resize(vertices.size());
    for (int i = 0; i < normalesVertices.size(); i++) {

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

    for (int i = 0; i < normalesVertices.size(); i++) {
        float modulo = sqrt(pow(normalesVertices[i].x, 2) + pow(normalesVertices[i].y, 2) +
                            pow(normalesVertices[i].z, 2));

        if (modulo > 0) {
            normalesVertices[i].x = normalesVertices[i].x / modulo;
            normalesVertices[i].y = normalesVertices[i].y / modulo;
            normalesVertices[i].z = normalesVertices[i].z / modulo;
        }
    }
}

//Función para pintar la figura con sombra plana
void mallaTriangulos::drawFlat() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);
    glShadeModel(GL_FLAT);
    glBegin(GL_TRIANGLES);
    {
        for (int i = 0; i < caras.size(); i++) {

            if (esTextura) {
                //Dibujamos la normal de la figura
                glNormal3f(normalesCaras[i].x, normalesCaras[i].y, normalesCaras[i].z);
                //Dibujamos los vértices de las caras
                glTexCoord2f(coordenadas[caras[i].v1].first, coordenadas[caras[i].v1].second);
                glVertex3f(vertices[caras[i].v1].x, vertices[caras[i].v1].y, vertices[caras[i].v1].z);
                glTexCoord2f(coordenadas[caras[i].v2].first, coordenadas[caras[i].v2].second);
                glVertex3f(vertices[caras[i].v2].x, vertices[caras[i].v2].y, vertices[caras[i].v2].z);
                glTexCoord2f(coordenadas[caras[i].v3].first, coordenadas[caras[i].v3].second);
                glVertex3f(vertices[caras[i].v3].x, vertices[caras[i].v3].y, vertices[caras[i].v3].z);
            } else {
                //Dibujamos la normal de la figura
                glNormal3f(normalesCaras[i].x, normalesCaras[i].y, normalesCaras[i].z);
                //Dibujamos los vértices de las caras
                glVertex3f(vertices[caras[i].v1].x, vertices[caras[i].v1].y, vertices[caras[i].v1].z);
                glVertex3f(vertices[caras[i].v2].x, vertices[caras[i].v2].y, vertices[caras[i].v2].z);
                glVertex3f(vertices[caras[i].v3].x, vertices[caras[i].v3].y, vertices[caras[i].v3].z);
            }
        }
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

//Función para pintar la figura con sombra suave
void mallaTriangulos::drawSmooth() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);
    {
        for (int i = 0; i < caras.size(); i++) {
            if (esTextura) {
                glNormal3f(normalesVertices[caras[i].v1].x, normalesVertices[caras[i].v1].y,
                           normalesVertices[caras[i].v1].z);
                glTexCoord2f(coordenadas[caras[i].v1].first, coordenadas[caras[i].v1].second);
                glVertex3f(vertices[caras[i].v1].x, vertices[caras[i].v1].y, vertices[caras[i].v1].z);
                glNormal3f(normalesVertices[caras[i].v2].x, normalesVertices[caras[i].v2].y,
                           normalesVertices[caras[i].v2].z);
                glTexCoord2f(coordenadas[caras[i].v2].first, coordenadas[caras[i].v2].second);
                glVertex3f(vertices[caras[i].v2].x, vertices[caras[i].v2].y, vertices[caras[i].v2].z);

                glNormal3f(normalesVertices[caras[i].v3].x, normalesVertices[caras[i].v3].y,
                           normalesVertices[caras[i].v3].z);
                glTexCoord2f(coordenadas[caras[i].v3].first, coordenadas[caras[i].v3].second);
                glVertex3f(vertices[caras[i].v3].x, vertices[caras[i].v3].y, vertices[caras[i].v3].z);
            } else {
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
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void mallaTriangulos::draw() {
    if (sombraPlana)
        drawSmooth();
    else
        drawFlat();
    glPopAttrib();
}

mallaRevolucion::mallaRevolucion(const char *archivo, int veces) {
    esTextura = false;
    n = veces;
    char fichero[50];
    sprintf(fichero, "./plys/%s", archivo);
    ply::read_vertices(fichero, vertices_ply);

    //Rellenamos los vértices en perfilPrimitivo
    for (int i = 0; i < vertices_ply.size(); i += 3) {
        v.x = vertices_ply[i];
        v.y = vertices_ply[i + 1];
        v.z = vertices_ply[i + 2];

        perfilPrimitivo.push_back(v);
    }

    //Asignamos a m el tamaño de perfilPrimitivo
    m = perfilPrimitivo.size();

    //Rellenamos la lista de vértices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            v.x = perfilPrimitivo[j].x * cos((2 * i * M_PI) / (vertices_ply.size() - 1));
            v.y = perfilPrimitivo[j].y;
            v.z = perfilPrimitivo[j].x * sin((2 * i * M_PI) / (vertices_ply.size() - 1));

            vertices.push_back(v);
        }
    }

    //Creamos dos triángulos nuevos que son adyacentes a ese vértice en cada iteración
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {

            int k = i * m + j;
            c.v1 = k;
            c.v3 = k + m;
            c.v2 = k + m + 1;

            caras.push_back(c);

            c.v1 = k;
            c.v3 = k + m + 1;
            c.v2 = k + 1;

            caras.push_back(c);
        }
    }

    //Calculamos las normales de la malla de revolución
    obtenerNormales();

    //Calculamos las coordenadas de la malla de revolución (textura)

    if (archivo == "lata-pcue.ply")
        mallaRevolucion::obtenerCoordenadasLateral();

    if (archivo == "lata-psup.ply")
        mallaRevolucion::obtenerCoordenadasTapayBase(0);

    if (archivo == "lata-pinf.ply")
        mallaRevolucion::obtenerCoordenadasTapayBase(0.5);
}

void mallaRevolucion::cargarTextura(const char archivo[50]) {
    char fichero[50];
    sprintf(fichero, "./jpg/%s", archivo);
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, asignarTextura(fichero));
    esTextura = true;
}

float mallaRevolucion::obtenerDistancias(vertice v1, vertice v2) {
    //Fórmula de cálculo de distancia entre 2 puntos
    float distancia = sqrt(pow(v2.x - v1.x, 2)
                           + pow(v2.y - v1.y, 2));
    return distancia;
}

void mallaRevolucion::obtenerCoordenadasLateral() {
    //Calculamos las distancias
    std::vector<float> distancias;
    float sumaDistancias = 0;
    //Recorremos el vector y almacenamos distancias
    for (int i = 0; i < perfilPrimitivo.size() - 1; i++) {
        sumaDistancias += obtenerDistancias(
                perfilPrimitivo[i], perfilPrimitivo[i + 1]);
        distancias.push_back(sumaDistancias);
    }

    //Calculamos las coordenadas
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            //Calculamos coordenada u
            double angulo = (2 * i * M_PI) / (vertices_ply.size() - 1);
            coordenada.first = ((angulo) * 180 / M_PI) / 360;

            //Calculamos coordenada v
            unsigned long distanciaMaxima = distancias.size() - 1;
            coordenada.second = distancias[j] / distancias[distanciaMaxima];

            //Almacenamos ambas coordenadas en el vector
            coordenadas.push_back(coordenada);
        }
    }
}

void mallaRevolucion::obtenerCoordenadasTapayBase(float desplazamiento) {
    float radio = vertices[0].x;

    //Calculamos las coordenadas
    for (int i = 0; i < vertices.size(); i++) {
        //Calculamos coordenada u
        coordenada.first = desplazamiento + (((vertices[i].x + radio) / (2 * radio)) / 2);

        //Calculamos coordenada v
        coordenada.second = (vertices[i].z + radio) / (2 * radio);

        //Almacenamos ambas coordenadas en el vector
        coordenadas.push_back(coordenada);
    }
}


/**
 * Instanciamos objetos de los ejes y las cuatro figuras
 */

Ejes ejesCoordenadas;
Cubo dado(5);
mallaRevolucion lata("lata-pcue.ply", 90);
mallaRevolucion lataTapa("lata-psup.ply", 60);
mallaRevolucion lataBase("lata-pinf.ply", 60);
mallaTriangulos busto("beethoven.ply");
mallaRevolucion peon("perfil.ply", 60);

void initModel() {
    dado.cargarTextura();
    lata.cargarTextura("Cruzcampo.jpg");
    lataTapa.cargarTextura("tapas.jpg");
    lataBase.cargarTextura("tapas.jpg");
}

/**	void Dibuja( void )
Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
**/

void Dibuja(void) {
    static GLfloat luzAmbiente[4] = {5.0, 5.0, 10.0, 0.0};    // Posicion de la fuente de luz
    static GLfloat morado[3] = {1.0, 0.0, 1.0};
    static GLfloat pos1[4] = {0.0, 20.0, 40.0, 1.0};
    static GLfloat verde[3] = {0.0, 1.0, 0.0};
    static GLfloat pos2[4] = {20.0, 0.0, 1.0, 40.0};

    float cobreAmbient[4] = {0.19125, 0.0735, 0.0225, 1.00};
    float cobreDiffuse[4] = {0.7038, 0.27048, 0.0828, 1.00};
    float cobreSpecular[4] = {0.256777, 0.137622, 0.086014, 1.00};
    float cobreBrillo = 0.1;

    float turquesaAmbient[4] = {0.1, 0.18, 0.1745, 1.00};
    float turquesaDiffuse[4] = {0.396, 0.74151, 0.69102, 1.00};
    float turquesaSpecular[4] = {0.297254, 0.30829, 0.306678, 1.00};
    float turquesaBrillo = 0.1;

    float plataAmbient[4] = {0.19225, 0.19225, 0.19225, 1.00};
    float plataDiffuse[4] = {0.50754, 0.50754, 0.50754, 1.00};
    float plataSpecular[4] = {0.508273, 0.508273, 0.508273, 1.00};
    float plataBrillo = 0.4;


    glPushMatrix();        // Apila la transformacion geometrica actual

    glClearColor(0.0, 0.0, 0.0, 1.0);    // Fija el color de fondo l negro

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Inicializa el buffer de color y el Z-Buffer

    transformacionVisualizacion();    // Carga transformacion de visualizacion

    glLightfv(GL_LIGHT0, GL_POSITION, luzAmbiente);    // Declaracion de luz. Colocada aqui esta fija en la escena

    glLightfv(GL_LIGHT1, GL_POSITION, pos1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, morado);

    glLightfv(GL_LIGHT2, GL_POSITION, pos2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, verde);


    ejesCoordenadas.draw();            // Dibuja los ejes

    if (iluminacionGeneral) //Activa / desactiva la iluminación general de las figuras
        glEnable(GL_LIGHTING); //Activa
    else
        glDisable(GL_LIGHTING); //Desactiva

    if (iluminacion1) //Activa / desactiva la iluminación 1 de las figuras beethoven
        glEnable(GL_LIGHT1); //Activa
    else
        glDisable(GL_LIGHT1); //Desactiva

    if (iluminacion2) //Activa / desactiva la iluminación 2 de las figuras beethoven
        glEnable(GL_LIGHT2); //Activa
    else
        glDisable(GL_LIGHT2); //Desactiva

    glPolygonMode(GL_FRONT_AND_BACK, modo); //Cambia los modos de visualización

    glTranslatef(-10, 0, 0);
    dado.draw();

    glTranslatef(10, 0, 0);

    glPushMatrix();
    glRotatef(100, 0, 1, 0);
    lata.draw();
    lataTapa.draw();
    lataBase.draw();
    glPopMatrix();

    glTranslatef(5, 0, 0);

    busto.setMaterial(cobreAmbient, cobreDiffuse, cobreSpecular, cobreBrillo);
    busto.draw();

    glTranslatef(-5, 0, 10);
    peon.setMaterial(turquesaAmbient, turquesaDiffuse, turquesaSpecular, turquesaBrillo);
    peon.draw();


    // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)

    glPopMatrix();        // Desapila la transformacion geometrica


    glutSwapBuffers();        // Intercambia el buffer de dibujo y visualizacion
}


/**	void idle()
Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.
**/
void idle(int v) {

    glutPostRedisplay();        // Redibuja
    glutTimerFunc(30, idle, 0);    // Vuelve l activarse dentro de 30 ms
}