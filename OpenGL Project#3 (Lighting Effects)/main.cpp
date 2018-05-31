//
//  main.cpp
//  OpenGL Project#3 (Lighting Effects)
//
//  Created by mac on 5/29/18.
//  Copyright © 2018 mac. All rights reserved.
//

// For MacOs users
#include <GLUT/glut.h>
#include <OPENGL/gl.h>
#include <OPENGL/glu.h>


/*
 
 // For Windows users
 #include <GL/glut.h>
 #include <GL/gl.h>
 #include <GL/glu.h>
 
 */


#include <iostream>

GLfloat mat_diffuse[] = { 0.25, 0.25, 1., 0. };
GLfloat mat_specular[] = { 1., 1., 1., 0. };
GLfloat light_position[] = { 10., 10., 20., 1. };
GLfloat ref_plane[] = { 1.5, 1.5, 1.5, 0. };
GLUquadricObj* qobj;
unsigned int MyTextureObject;

#define SImageWidth 32

GLubyte SImage[4*SImageWidth];


void MyStripeImage()
{
    for(int i=0;i<SImageWidth;i++)
    {
        SImage[4*i]=255;
        SImage[4*i+1]=(i<8)?0:255;
        SImage[4*i+2]=(i<8)?0:255;
        SImage[4*i+3]=0;
    }
    
    
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_1D, MyTextureObject);
    gluSphere(qobj, 1.5, 40, 40);
    glutSwapBuffers();
}

void Init() {
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    
    MyStripeImage();
    glGenTextures(1, &MyTextureObject); // generate texture
    glBindTexture(GL_TEXTURE_1D, MyTextureObject); // bind
    glTexImage1D(GL_TEXTURE_1D, 0, 4, SImageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, SImage); // only level 0 exists
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenfv(GL_S, GL_OBJECT_PLANE, ref_plane);
    
    // Wrapping
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    
    // filtering
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_1D);
    

    
}

void MyReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40., (GLfloat)w / (GLfloat)h, 1., 10.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.);
    glTranslatef(0., 0., -1.);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("openGL sample program");
    glutReshapeFunc(MyReshape);
    glutDisplayFunc(MyDisplay);
    Init();
    glutMainLoop();
    
    return 0;
}
