/*	Prácticas de Informática Gráfica
	Grupo C					Curso 2022-23

	Codigo base para la realización de las prácticas de IG

	Estudiante: Gonzalo Jose Lopez Castilla
=======================================================
	G. Arroyo, J.C. Torres
	Dpto. Lenguajes y Sistemas Informáticos
	(Univ. de Granada)
=======================================================/
*/
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>        // Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include <vector>
#include "file_ply_stl.h"
#include "estructura.h"     //Librería para usar piezas de la grúa


/**	void initModel()
Inicializa el modelo y de las variables globales
**/

int modo = GL_FILL;
bool iluminacionGeneral = true;
bool iluminacion1 = false;
bool iluminacion2 = false;
bool animacionActivada = true;

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

void activarDesactivarAnimacion(){
    if (animacionActivada)
        animacionActivada = false;
    else
        animacionActivada = true;
}

//Ángulos de las rotaciones de la grúa (con sus setters y getters)
int anguloR1 = 0, anguloR2 = 0, anguloR3 = 0, anguloAnimacion = 0;

int getAnguloR1() {
    return anguloR1;
};

int getAnguloR2() {
    return anguloR2;
};

int getAnguloR3() {
    return anguloR3;
};

void setAnguloR1(int angulo) {
    anguloR1 = angulo;
};

void setAnguloR2(int angulo) {
    anguloR2 = angulo;
};

void setAnguloR3(int angulo) {
    anguloR3 = angulo;
};

bool esSeleccionado = false;
bool gruaSeleccionada = false;

void activarEsSeleccionado() {
    esSeleccionado = true;
}

void activarGruaSeleccionada() {
    gruaSeleccionada = true;
}

bool gruaAzul = false;
bool gruaRojo = false;
bool gruaAmarillo = false;

//Colores
float azul[4] = {0.0, 1.0, 1.0, 1.0};
float rojo[4] = {1.0, 0.0, 0.0, 0.0};
float amarilloMenu[4] = {1.0f, 1.0f, 0.0f, 1};
float lila[4] = {2.0, 0.5, 1.0};

//Materiales
float cobreAmbient[4] = {0.19125, 0.0735, 0.0225, 1.00};
float cobreDiffuse[4] = {0.7038, 0.27048, 0.0828, 1.00};
float cobreSpecular[4] = {0.256777, 0.137622, 0.086014, 1.00};
float cobreBrillo = 0.1;

float turquesaAmbient[4] = {0.1, 0.18, 0.1745, 1.00};
float turquesaDiffuse[4] = {0.396, 0.74151, 0.69102, 1.00};
float turquesaSpecular[4] = {0.297254, 0.30829, 0.306678, 1.00};
float turquesaBrillo = 0.1;

float esmeraldaAmbient[4] = {0.0215, 0.1745, 0.0215, 1.00};
float esmeraldaDiffuse[4] = {0.07568, 0.61424, 0.07568, 1.00};
float esmeraldaSpecular[4] = {0.633, 0.727811, 0.633, 1.00};
float esmeraldaBrillo = 0.6;

//Velocidades
bool Fvel = false, Gvel = false;

void setF(){ //Aumenta/disminuye en 3 la velocidad
    if (Fvel)
        Fvel = false;
    else
        Fvel = true;
}

void setG() { //Aumenta/disminuye en 8 la velocidad
    if (Gvel)
        Gvel = false;
    else
        Gvel = true;
}

void Grua::animaciones(){
    //Aumentanmos R1
    if (Fvel){
        Gvel = false;
        setAnguloR1(getAnguloR1()+3);
    }
    if (Gvel){
        Fvel = false;
        setAnguloR1(getAnguloR1()+15);
    }
    else
        setAnguloR1(getAnguloR1()+1);
    if (getAnguloR1()>360)
        setAnguloR1(getAnguloR1()-360);

    if (anguloAnimacion < anguloR2 || anguloR2 == -90){
        anguloAnimacion = anguloR2;

        //Aumentamos R2
        if (Fvel){
            Gvel = false;
            setAnguloR2(getAnguloR2()+3);
        }
        if (Gvel){
            Fvel = false;
            setAnguloR2(getAnguloR2()+8);
        }
        else
            setAnguloR2(getAnguloR2()+1);
        if (getAnguloR2()>90)
            setAnguloR2(90);
    } else if (anguloAnimacion > anguloR2 || anguloR2 == 90){
        anguloAnimacion = anguloR2;

        //Decrementamos R2
        if (Fvel){
            Gvel = false;
            setAnguloR2(getAnguloR2()-3);
        }
        if (Gvel){
            Fvel = false;
            setAnguloR2(getAnguloR2()-8);
        }
        else
            setAnguloR2(getAnguloR2()-1);
        if (getAnguloR2()<-90)
            setAnguloR2(-90);
    } else {
        //Aumentamos R2
        if (Fvel){
            Gvel = false;
            setAnguloR2(getAnguloR2()+3);
        }
        if (Gvel){
            Fvel = false;
            setAnguloR2(getAnguloR2()+8);
        }
        else
            setAnguloR2(getAnguloR2()+1);
        if (getAnguloR2()>90)
            setAnguloR2(90);
    }

    //Aumentamos R3
    setAnguloR3(getAnguloR3()+1);
    if (getAnguloR3()>360)
        setAnguloR3(getAnguloR3()-360);
}

Grua::Grua(float alturaPie, float largoBrazoGrande,
           float alturaCuerda, float largoBrazoPeq, int id) : Objeto3D(id) {
    this->alturaPie = alturaPie;
    this->largoBrazoGrande = largoBrazoGrande;
    this->alturaCuerda = alturaCuerda;
    this->largoBrazoPeq = largoBrazoPeq;
}

//Figuras según el grafo
void Grua::A(float xzPie, float yPie, int numMallas) {
    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
    else
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarillo);

    if (gruaAzul)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    else if (gruaRojo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    else if (gruaAmarillo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    creaEstructura(0, 0, 0, 0, yPie, 0, xzPie, xzPie, numMallas);
}


void Grua::B(float xCaja, float yCaja, float zCaja) {
    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
    else
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarillo);

    if (gruaAzul)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    else if (gruaRojo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    else if (gruaAmarillo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    paralelepipedo(0, 0, 0, 0, yCaja, 0, xCaja, zCaja);
}

void Grua::C(float xzTorre, float yTorre, int numMallas) {
    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
    else
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);

    if (gruaAzul)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    else if (gruaRojo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    else if (gruaAmarillo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    creaTorre(0, 0, 0, 0, yTorre, 0, xzTorre, xzTorre, numMallas);
}

void Grua::D(float xBrazoGrande, float zBrazoGrande, int numMallas) {
    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
    else
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarillo);

    if (gruaAzul)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    else if (gruaRojo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    else if (gruaAmarillo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    creaBrazo(0, 0, 0, xBrazoGrande, 0, 0, zBrazoGrande, numMallas);
}

void Grua::E(float xCaja, float yCaja, float zCaja) {
    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
    else
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);

    if (gruaAzul)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    else if (gruaRojo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    else if (gruaAmarillo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    paralelepipedo(0, 0, 0, 0, yCaja, 0, xCaja, zCaja);
}

void Grua::F(float yCuerda) {
    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
    else
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gris);

    if (gruaAzul)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    else if (gruaRojo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    else if (gruaAmarillo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    cilindro(0, 0, 0, 0, yCuerda, 0, 0.1);
}

void Grua::G(float yGancho) {
    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
    else
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gris);

    if (gruaAzul)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    else if (gruaRojo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    else if (gruaAmarillo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    creaGancho(0, 0, 0, yGancho);
}

void Grua::H(float xBrazoPequenyo, float altoMalla, float anchoMalla, int numMallas) {
    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
    else
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarillo);

    if (gruaAzul)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    else if (gruaRojo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    else if (gruaAmarillo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    creaEstructura(0, 0, 0, xBrazoPequenyo, 0, 0, altoMalla, anchoMalla, numMallas);
}

void Grua::I(float xCaja, float yCaja, float zCaja) {
    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
    else
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gris);

    if (gruaAzul)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    else if (gruaRojo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    else if (gruaAmarillo)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (gruaSeleccionada)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    caja(xCaja, yCaja, zCaja);
}


//H+I
void Grua::brazoPequenyoConCaja(float xBrazoPequenyo) {

    int numMallas = xBrazoPequenyo / 2;
    float altoMalla = 0.5, anchoMalla = 1;
    H(xBrazoPequenyo, altoMalla, anchoMalla, numMallas);

    float xCaja = xBrazoPequenyo / 3, yCaja = altoMalla, zCaja = anchoMalla;
    glTranslatef(xBrazoPequenyo - xCaja / 2, altoMalla / 2 - yCaja * 2, 0); //T4
    I(xCaja, yCaja, zCaja);
}

//D+E
void Grua::brazoGrandeConCaja(float xBrazoGrande) {
    int numMallas = xBrazoGrande / 2;
    float zBrazoGrande = 1;
    D(xBrazoGrande, zBrazoGrande, numMallas);

    float xCaja = xBrazoGrande / numMallas, yCaja = zBrazoGrande / 8, zCaja = zBrazoGrande;
    glTranslatef(xCaja / 2, -yCaja, 0); //T7
    E(xCaja, yCaja, zCaja);
}

//F+G
void Grua::cuerdaConGancho(float yCuerda) {
    glRotatef(anguloR2, 0, 0, 1);//R2
    F(-yCuerda);

    float yGancho = yCuerda / 4;
    glTranslatef(0, -yCuerda, 0); //T8
    glRotatef(anguloR3, 0, 1, 0);//R3
    G(yGancho);
}

//D+E+F+G
void Grua::brazoGrande(float xBrazoGrande, float yCuerda) {

    glPushMatrix();
    brazoGrandeConCaja(xBrazoGrande);
    glPopMatrix();

    int numMallas = xBrazoGrande / 8;
    if (xBrazoGrande <= 15)
        numMallas = xBrazoGrande / 8 * 2;
    if (xBrazoGrande <= 8)
        numMallas = xBrazoGrande / 8 * 4;

    glTranslatef(numMallas / 2, 0, 0); //T6
    glPushMatrix();
    cuerdaConGancho(yCuerda);
    glPopMatrix();
}

//D+E+F+G+B
void Grua::brazoGrandeConCubo(float xBrazoGrande, float yCuerda) {
    int numMallas = xBrazoGrande / 2;
    glPushMatrix();
    brazoGrande(xBrazoGrande, yCuerda);
    glPopMatrix();

    float xCajaCubo = numMallas / 4, yCajaCubo = -xCajaCubo / 2, zCajaCubo = numMallas / 4;

    glPushMatrix();
    glTranslatef(xBrazoGrande + xCajaCubo / 2, 0, 0); //T5
    B(xCajaCubo, yCajaCubo, zCajaCubo);
    glPopMatrix();
}

//D+E+F+G+B+H+I

void Grua::brazoGrandeConCuboYBrazoPequenyo(float xBrazoGrande,
                                            float yCuerda, float xBrazoPequenyo) {
    int numMallas = xBrazoGrande / 2;
    float xCajaCubo = numMallas / 4, yCajaCubo = xCajaCubo / 2;

    glRotatef(anguloR1, 0, 1, 0); //R1
    glTranslatef(-xBrazoGrande - xCajaCubo / 2, 0, 0); //T2
    glPushMatrix();
    brazoGrandeConCubo(xBrazoGrande, yCuerda);
    glPopMatrix();

    glTranslatef(xBrazoGrande + xCajaCubo, yCajaCubo - yCajaCubo / 2, 0); //T3
    glPushMatrix();
    brazoPequenyoConCaja(xBrazoPequenyo);
    glPopMatrix();
}

//A+C+D+E+F+G+B+H+I
void Grua::construirGrua(float xBrazoGrande, float yCuerda, float xBrazoPequenyo,
                         float yPie) {
    //Construimos figura A
    int numMallasPie = xBrazoGrande / 2;
    float xzPieYTorre = 1;
    A(xzPieYTorre, yPie, numMallasPie);

    //Construimos figura brazoGrandeConCuboYBrazoPequenyo
    int numMallas = xBrazoGrande / 2;
    float xCajaCubo = numMallas / 4, yCajaCubo = xCajaCubo / 2;
    glTranslatef(xCajaCubo / 2 - xzPieYTorre + xCajaCubo / 2, yPie + yCajaCubo, 0); //T1
    glPushMatrix();
    brazoGrandeConCuboYBrazoPequenyo(xBrazoGrande, yCuerda, xBrazoPequenyo);
    glPopMatrix();

    //Construimos figura C
    float yTorre = xBrazoGrande / 5;
    int numMallasTorre = numMallas / 2;
    C(xzPieYTorre, yTorre, numMallasTorre);
}

void Grua::draw() {
    glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT);
    construirGrua(largoBrazoGrande, alturaCuerda,
                  largoBrazoPeq, alturaPie);
    glPopAttrib();
    glPopMatrix();
}

void Objeto3D::setMaterial(float ambient[4], float diffuse[4],
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

Cubo::Cubo(float lado, int id) : Objeto3D(id) {
    l = lado;
}

void Cubo::setDadoOriginal() {
    textura = true;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blanco);
}

void Cubo::draw() {
    if (textura)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);

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
mallaTriangulos::mallaTriangulos(int id) : Objeto3D(id) {

}

mallaTriangulos::mallaTriangulos(const char archivo[50], int id) : Objeto3D(id) {
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
    if (textura)
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

void mallaRevolucion::setLataOriginal() {
    textura = true;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blanco);
}

mallaRevolucion::mallaRevolucion(const char *archivo, int veces, int id) : mallaTriangulos(id) {
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
Cubo dado(5, 1);
mallaRevolucion lata("lata-pcue.ply", 90, 2);
mallaRevolucion lataTapa("lata-psup.ply", 60, 2);
mallaRevolucion lataBase("lata-pinf.ply", 60, 2);
mallaTriangulos busto("beethoven.ply", 3);
mallaRevolucion peon("perfil.ply", 60, 4);
mallaTriangulos coche("big_dodge.ply", 5);
Grua grua(10, 10, 3, 6, 6);

void initModel() {
    dado.cargarTextura();
    lata.cargarTextura("Cruzcampo.jpg");
    lataTapa.cargarTextura("tapas.jpg");
    lataBase.cargarTextura("tapas.jpg");
}

bool opcionMenu1 = false; //Azul
bool opcionMenu2 = false; //Rojo
bool opcionMenu3 = false; //Amarillo

//1
bool hayCambio1Dado = false;
bool hayCambio2Dado = false;
bool hayCambio3Dado = false;

//2
bool hayCambio1Lata = false;
bool hayCambio2Lata = false;
bool hayCambio3Lata = false;

//3
bool hayCambio1Busto = false;
bool hayCambio2Busto = false;
bool hayCambio3Busto = false;

//4
bool hayCambio1Peon = false;
bool hayCambio2Peon = false;
bool hayCambio3Peon = false;

//5
bool hayCambio1Coche = false;
bool hayCambio2Coche = false;
bool hayCambio3Coche = false;

//6
bool hayCambio1Grua = false;
bool hayCambio2Grua = false;
bool hayCambio3Grua = false;


bool dadoSeleccionado = false;
bool lataSeleccionado = false;
bool bustoSeleccionado = false;
bool peonSeleccionado = false;
bool cocheSeleccionado = false;
bool gruaSeleccionadoMenu = false;

int anteriorFigura;

void escena(bool useRealColors) {
    //Dado
    glTranslatef(-10, 0, 0);
    if (useRealColors) {
        if (!esSeleccionado || getFiguraActual() != 1) {
            dado.setDadoOriginal();
            if (opcionMenu1 && dadoSeleccionado) {
                hayCambio1Dado = true;
                hayCambio2Dado = false;
                hayCambio3Dado = false;
            }
            else if (opcionMenu2 && dadoSeleccionado) {
                hayCambio1Dado = false;
                hayCambio2Dado = true;
                hayCambio3Dado = false;
            }
            else if (opcionMenu3 && dadoSeleccionado) {
                hayCambio1Dado = false;
                hayCambio2Dado = false;
                hayCambio3Dado = true;
            }
        } else if (getFiguraActual() == 1) {
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
            dadoSeleccionado = true;
        }
    } else {
        glPopAttrib();
        dado.setSelectionColor();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
        glPushAttrib(GL_LIGHTING);
    }

    if (hayCambio1Dado)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    if (hayCambio2Dado)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    if (hayCambio3Dado)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (getFiguraActual() == 1)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    dado.draw();

    //Lata
    glTranslatef(10, 0, 0);
    glPushMatrix();
    glRotatef(100, 0, 1, 0);
    if (useRealColors) {
        if (!esSeleccionado || getFiguraActual() != 2) {
            lata.setLataOriginal();
            lataTapa.setLataOriginal();
            lataBase.setLataOriginal();
            if (opcionMenu1 && lataSeleccionado) {
                hayCambio1Lata = true;
                hayCambio2Lata = false;
                hayCambio3Lata = false;
            }
            else if (opcionMenu2 && lataSeleccionado) {
                hayCambio1Lata = false;
                hayCambio2Lata = true;
                hayCambio3Lata = false;
            }
            else if (opcionMenu3 && lataSeleccionado) {
                hayCambio1Lata = false;
                hayCambio2Lata = false;
                hayCambio3Lata = true;
            }
        } else if (getFiguraActual() == 2) {
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
            lataSeleccionado = true;
        }
    } else {
        glPopAttrib();
        lata.setSelectionColor();
        lataTapa.setSelectionColor();
        lataBase.setSelectionColor();
        glDisable(GL_TEXTURE);
        glDisable(GL_LIGHTING);
        glPushAttrib(GL_LIGHTING);
    }

    if (hayCambio1Lata)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    if (hayCambio3Lata)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    if (hayCambio3Lata)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (getFiguraActual() == 2)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    lata.draw();
    lataTapa.draw();
    lataBase.draw();
    glPopMatrix();

    //Busto de Beethoven
    glTranslatef(5, 0, 0);
    if (useRealColors) {
        if (!esSeleccionado || getFiguraActual() != 3) {
            busto.setMaterial(cobreAmbient, cobreDiffuse, cobreSpecular, cobreBrillo);
            if (opcionMenu1 && bustoSeleccionado) {
                hayCambio1Busto = true;
                hayCambio2Busto = false;
                hayCambio3Busto = false;
            }
            else if (opcionMenu2 && bustoSeleccionado) {
                hayCambio1Busto = false;
                hayCambio2Busto = true;
                hayCambio3Busto = false;
            }
            else if (opcionMenu3 && bustoSeleccionado) {
                hayCambio1Busto = false;
                hayCambio2Busto = false;
                hayCambio3Busto = true;
            }
        } else if (getFiguraActual() == 3) {
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
            bustoSeleccionado = true;
        }
    } else {
        glPopAttrib();
        busto.setSelectionColor();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
        glPushAttrib(GL_LIGHTING);
    }

    if (hayCambio1Busto)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    if (hayCambio2Busto)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    if (hayCambio3Busto)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (getFiguraActual() == 3)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    busto.draw();


    //Peón
    glTranslatef(-5, 0, 10);
    if (useRealColors) {
        if (!esSeleccionado || getFiguraActual() != 4){
            peon.setMaterial(turquesaAmbient, turquesaDiffuse, turquesaSpecular, turquesaBrillo);
            if (opcionMenu1 && peonSeleccionado) {
                hayCambio1Peon = true;
                hayCambio2Peon = false;
                hayCambio3Peon = false;
            }
            else if (opcionMenu2 && peonSeleccionado) {
                hayCambio1Peon = false;
                hayCambio2Peon = true;
                hayCambio3Peon = false;
            }
            else if (opcionMenu3 && peonSeleccionado) {
                hayCambio1Peon = false;
                hayCambio2Peon = false;
                hayCambio3Peon = true;
            }
        }
        else if (getFiguraActual() == 4) {
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
            peonSeleccionado = true;
        }
    } else {
        glPopAttrib();
        peon.setSelectionColor();
        glDisable(GL_LIGHTING);
        glPushAttrib(GL_LIGHTING);
    }

    if (hayCambio1Peon)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    if (hayCambio2Peon)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    if (hayCambio3Peon)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (getFiguraActual() == 4)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    peon.draw();

    //Grúa
    glTranslatef(10, 0, 0);
    if (useRealColors) {
        if (!esSeleccionado || getFiguraActual() != 6){
            gruaSeleccionada = false;
            if (opcionMenu1 && gruaSeleccionadoMenu) {
                hayCambio1Grua = true;
                hayCambio2Grua = false;
                hayCambio3Grua = false;
            }
            else if (opcionMenu2 && gruaSeleccionadoMenu) {
                hayCambio1Grua = false;
                hayCambio2Grua = true;
                hayCambio3Grua = false;
            }
            else if (opcionMenu3 && gruaSeleccionadoMenu) {
                hayCambio1Grua = false;
                hayCambio2Grua = false;
                hayCambio3Grua = true;
            }
        }
        else if (getFiguraActual() == 6) {
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
            gruaSeleccionadoMenu = true;
        }
    } else {
        glPopAttrib();
        grua.setSelectionColor();
        glDisable(GL_LIGHTING);
        glPushAttrib(GL_LIGHTING);
    }

    if (hayCambio1Grua)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    if (hayCambio2Grua)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    if (hayCambio3Grua)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (getFiguraActual() == 6)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    grua.draw();

    //Coche
    glTranslatef(-22, 0, 0);
    if (useRealColors) {
        if (!esSeleccionado || getFiguraActual() != 5){
            coche.setMaterial(esmeraldaAmbient, esmeraldaDiffuse, esmeraldaSpecular, esmeraldaBrillo);
            if (opcionMenu1 && cocheSeleccionado) {
                hayCambio1Coche = true;
                hayCambio2Coche = false;
                hayCambio3Coche = false;
            }
            else if (opcionMenu2 && cocheSeleccionado) {
                hayCambio1Coche = false;
                hayCambio2Coche = true;
                hayCambio3Coche = false;
            }
            else if (opcionMenu3 && cocheSeleccionado) {
                hayCambio1Coche = false;
                hayCambio2Coche = false;
                hayCambio3Coche = true;
            }
        }
        else if (getFiguraActual() == 5) {
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);
            cocheSeleccionado = true;
        }
    } else {
        glPopAttrib();
        coche.setSelectionColor();
        glDisable(GL_LIGHTING);
        glPushAttrib(GL_LIGHTING);
    }

    if (hayCambio1Coche)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    if (hayCambio2Coche)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    if (hayCambio3Coche)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarilloMenu);

    if (getFiguraActual() == 5)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lila);

    coche.draw();

    if (getFiguraActual() == 0)
        esSeleccionado = false;
}

bool realColors = true;

void dibujoEscena() {
    //Luces
    static GLfloat luzAmbiente[4] = {5.0, 5.0, 10.0, 0.0};    // Posicion de la fuente de luz
    static GLfloat morado[3] = {1.0, 0.0, 1.0};
    static GLfloat pos1[4] = {0.0, 20.0, 40.0, 1.0};
    static GLfloat verde[3] = {0.0, 1.0, 0.0};
    static GLfloat pos2[4] = {20.0, 0.0, 1.0, 40.0};

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

    //escena(realColors); //Dibuja la escena con todas las figuras de las prácticas 2, 3 y 4
    escena(realColors);

    glPopMatrix();        // Desapila la transformacion geometrica
}

/**	void Dibuja( void )
Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
**/

void Dibuja() {
    dibujoEscena();    //Dibuja la escena
    glutSwapBuffers(); //Intercambia el buffer de dibujo y visualizacion
}

void Objeto3D::setSelectionColor() {
    unsigned char r = (this->id & 0xFF);
    glColor3ub(r, 0, 0);
    textura = false;
}

int pick(int x, int y) {
    GLint viewport[4];
    unsigned char data[4];

    glGetIntegerv(GL_VIEWPORT, viewport);
    glDisable(GL_DITHER);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    realColors = false;
    dibujoEscena();

    glReadPixels(x, viewport[3] - y, 1, 1,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);
    glEnable(GL_LIGHTING);
    glEnable(GL_DITHER);
    glFlush();
    glFinish();
    realColors = true;

    int result = data[0];

    glutPostRedisplay();
    return result;
}

void initMenu() {
    glutCreateMenu(manejadorMenu);
    glutAddMenuEntry("Azul", 1);
    glutAddMenuEntry("Rojo", 2);
    glutAddMenuEntry("Amarillo", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void manejadorMenu(int opcion) {
    switch (opcion) {
        case 1: // Color azul
            switch (getFiguraActual()){
                case 1:
                    lataSeleccionado = false;
                    bustoSeleccionado = false;
                    peonSeleccionado = false;
                    cocheSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = true;
                        opcionMenu2 = false;
                        opcionMenu3 = false;
                    }
                    break;
                case 2:
                    dadoSeleccionado = false;
                    bustoSeleccionado = false;
                    peonSeleccionado = false;
                    cocheSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = true;
                        opcionMenu2 = false;
                        opcionMenu3 = false;
                    }
                    break;
                case 3:
                    dadoSeleccionado = false;
                    lataSeleccionado = false;
                    peonSeleccionado = false;
                    cocheSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = true;
                        opcionMenu2 = false;
                        opcionMenu3 = false;
                    }
                    break;
                case 4:
                    dadoSeleccionado = false;
                    lataSeleccionado = false;
                    bustoSeleccionado = false;
                    cocheSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = true;
                        opcionMenu2 = false;
                        opcionMenu3 = false;
                    }
                    break;
                case 5:
                    dadoSeleccionado = false;
                    lataSeleccionado = false;
                    bustoSeleccionado = false;
                    peonSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = true;
                        opcionMenu2 = false;
                        opcionMenu3 = false;
                    }
                    break;
                case 6:
                    dadoSeleccionado = false;
                    lataSeleccionado = false;
                    bustoSeleccionado = false;
                    peonSeleccionado = false;
                    cocheSeleccionado = false;
                    if (esSeleccionado) {
                        opcionMenu1 = true;
                        opcionMenu2 = false;
                        opcionMenu3 = false;
                    }
                    gruaAzul = true;
                    gruaRojo = false;
                    gruaAmarillo = false;
                    break;
            }
            break;
        case 2: // Color rojo
            switch (getFiguraActual()){
                case 1:
                    lataSeleccionado = false;
                    bustoSeleccionado = false;
                    peonSeleccionado = false;
                    cocheSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = false;
                        opcionMenu2 = true;
                        opcionMenu3 = false;
                    }
                    break;
                case 2:
                    dadoSeleccionado = false;
                    bustoSeleccionado = false;
                    peonSeleccionado = false;
                    cocheSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = false;
                        opcionMenu2 = true;
                        opcionMenu3 = false;
                    }
                    break;
                case 3:
                    dadoSeleccionado = false;
                    lataSeleccionado = false;
                    peonSeleccionado = false;
                    cocheSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = false;
                        opcionMenu2 = true;
                        opcionMenu3 = false;
                    }
                    break;
                case 4:
                    dadoSeleccionado = false;
                    lataSeleccionado = false;
                    bustoSeleccionado = false;
                    cocheSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = false;
                        opcionMenu2 = true;
                        opcionMenu3 = false;
                    }
                    break;
                case 5:
                    dadoSeleccionado = false;
                    lataSeleccionado = false;
                    bustoSeleccionado = false;
                    peonSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = false;
                        opcionMenu2 = true;
                        opcionMenu3 = false;
                    }
                    break;
                case 6:
                    dadoSeleccionado = false;
                    lataSeleccionado = false;
                    bustoSeleccionado = false;
                    peonSeleccionado = false;
                    cocheSeleccionado = false;
                    if (esSeleccionado) {
                        opcionMenu1 = false;
                        opcionMenu2 = true;
                        opcionMenu3 = false;
                    }
                    gruaAzul = false;
                    gruaRojo = true;
                    gruaAmarillo = false;
                    break;
            }
            break;
        case 3: // Color amarillo
            switch (getFiguraActual()){
                case 1:
                    lataSeleccionado = false;
                    bustoSeleccionado = false;
                    peonSeleccionado = false;
                    cocheSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = false;
                        opcionMenu2 = false;
                        opcionMenu3 = true;
                    }
                    break;
                case 2:
                    dadoSeleccionado = false;
                    bustoSeleccionado = false;
                    peonSeleccionado = false;
                    cocheSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = false;
                        opcionMenu2 = false;
                        opcionMenu3 = true;
                    }
                    break;
                case 3:
                    dadoSeleccionado = false;
                    lataSeleccionado = false;
                    peonSeleccionado = false;
                    cocheSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = false;
                        opcionMenu2 = false;
                        opcionMenu3 = true;
                    }
                    break;
                case 4:
                    dadoSeleccionado = false;
                    lataSeleccionado = false;
                    bustoSeleccionado = false;
                    cocheSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = false;
                        opcionMenu2 = false;
                        opcionMenu3 = true;
                    }
                    break;
                case 5:
                    dadoSeleccionado = false;
                    lataSeleccionado = false;
                    bustoSeleccionado = false;
                    peonSeleccionado = false;
                    gruaSeleccionadoMenu = false;
                    if (esSeleccionado) {
                        opcionMenu1 = false;
                        opcionMenu2 = false;
                        opcionMenu3 = true;
                    }
                    break;
                case 6:
                    dadoSeleccionado = false;
                    lataSeleccionado = false;
                    bustoSeleccionado = false;
                    peonSeleccionado = false;
                    cocheSeleccionado = false;
                    if (esSeleccionado) {
                        opcionMenu1 = false;
                        opcionMenu2 = false;
                        opcionMenu3 = true;
                    }
                    gruaAzul = false;
                    gruaRojo = false;
                    gruaAmarillo = true;
                    break;
            }
            break;
    }
}


/**	void idle()
Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.
**/
void idle(int v) {
    glutPostRedisplay();        // Redibuja
    glutTimerFunc(30, idle, 0);    // Vuelve a activarse dentro de 30 ms
    if (animacionActivada)
        grua.animaciones();   //Anima las rotaciones de forma automáica
}