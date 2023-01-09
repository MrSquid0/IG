/*	Prácticas de Informática Gráfica
	Grupo C					Curso 2022-23

	Codigo base para la realización de las practicas de IG

	Estudiante: Gonzalo José López Castilla
=======================================================
	Gvel. Arroyo, J.C. Torres
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
modulo entradaTeclado.c
	Gestion de eventos de teclado
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"

/**
Imprime en la consola las instrucciones del programa
**/
void printHelp ()
{

    printf ("\n\n     Prácticas de Informática Gráfica	Curso 2022-2023");
    printf ("\n\n Dpto. Lenguajes y Sistemas Informaticos");
    printf ("\n E.T.S.I. Informatica		Univ. de Granada ");
    printf ("\n");
    printf ("\n Opciones: \n\n");
    printf ("h, H: Imprime informacion de ayuda \n");
    printf ("PgUp, PgDn: avanza y retrocede la cámara \n\n");
    printf ("+,-: avanza y retrocede la cámara \n\n");
    printf ("Teclas de movimiento de cursor: giran la camara\n");
    // Anyade la informacion de las opciones que introduzcas aqui !!

    printf ("\n Escape: Salir");
    printf ("\n\n\n");
}




/* @teclado ---------------------------------------------------------------- */

/** 		void letra (unsigned char k, int x, int y)
Este procedimiento es llamado por el sistema cuando se pulsa una tecla normal
El codigo k es el ascii de la letra
Para anyadir nuevas ordenes de teclado coloca el correspondiente case.
Parametros de entrada:
k: codigo del caracter pulsado
x:
y:
**/

float rotxCamara = 30, rotyCamara = 45;
float dCamara = 10;

void letra (unsigned char k, int x, int y)
{

    switch (k)
    {
        case 'p': //Cambia la visualización a puntos
            setModo(GL_POINT);
            break;
        case 'l': //Cambia la visualización a líneas
            setModo(GL_LINE);
            break;
        case 'f': //Cambia la visualización a relleno
            setModo(GL_FILL);
            break;
        case 'i': //Activa o desactiva la iluminación de la figura
            iluminacionON();
            break;
        case 'h':
        case 'H':
            printHelp ();		// H y h imprimen ayuda
            break;
        case '+':			// acerca la cámara
            dCamara -= 5.0;
            break;
        case '-':			// aleja la cámara
            dCamara += 5.0;
            break;
        case 'B':
            setAnguloR1(getAnguloR1()+1);
            if (getAnguloR1()>360)
                setAnguloR1(getAnguloR1()-360);
            break;
        case 'b':
            setAnguloR1(getAnguloR1()-1);
            if (getAnguloR1()<0)
                setAnguloR1(getAnguloR1()+360);
            break;
        case 'C':
            setAnguloR2(getAnguloR2()+1);
            if (getAnguloR2()>90)
                setAnguloR2(90);
            break;
        case 'c':
            setAnguloR2(getAnguloR2()-1);
            if (getAnguloR2()<-90)
                setAnguloR2(-90);
            break;
        case 'M':
            setAnguloR3(getAnguloR3()+1);
            if (getAnguloR3()>360)
                setAnguloR3(getAnguloR3()-360);
            break;
        case 'm':
            setAnguloR3(getAnguloR3()-1);
            if (getAnguloR3()<0)
                setAnguloR3(getAnguloR3()+360);
            break;
        case 'F':
            setF();
            break;
        case 'G':
            setG();
            break;
        case 'A':
            activarDesactivarAnimacion();
            break;
        case 27:			// Escape  Terminar
            exit (0);
        default:
            return;
    }
    setCamara (rotxCamara, rotyCamara, dCamara);
    glutPostRedisplay ();		// Algunas de las opciones cambian paramentros
}				// de la camara. Es necesario actualziar la imagen

/**		void especial(int k, int x, int y)
Este procedimiento es llamado por el sistema cuando se pulsa una tecla
especial. El codigo k esta definido en glut mediante constantes
Parametros de entrada:
k: codigo del caracter pulsado (definido en glut mediante constantes).
x:
y:
**/
void especial (int k, int x, int y)
{

    switch (k)
    {
        case GLUT_KEY_UP:
            rotxCamara += 5.0;	// Cursor arriba + rotacion x
            if (rotxCamara > 360)
                rotxCamara -= 360;
            break;
        case GLUT_KEY_DOWN:
            rotxCamara -= 5.0;
            if (rotxCamara < 0)
                rotxCamara += 360;
            break;
        case GLUT_KEY_LEFT:
            rotyCamara += 5.0;
            if (rotyCamara > 360)
                rotyCamara -= 360;
            break;
        case GLUT_KEY_RIGHT:
            rotyCamara -= 5.0;
            if (rotyCamara < 0)
                rotyCamara += 360;
            break;
        case GLUT_KEY_PAGE_DOWN:	// acerca la cámara
            dCamara -= 5.0;
            break;
        case GLUT_KEY_PAGE_UP:	// aleja la cámara
            dCamara += 5.0;
            break;
        default:
            return;
    }
    setCamara (rotxCamara, rotyCamara, dCamara);
    glutPostRedisplay ();		// Actualiza la imagen (ver proc. letra)
}