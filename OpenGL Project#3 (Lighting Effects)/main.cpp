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

#define MAXZ 8.0
#define MINZ -8.0
#define ZINC 0.4
static float solidZ = MAXZ;
static float transparentZ = MINZ;

static GLuint sphereList, lightList;
static int spin = 0;

void init(void)
{
    glClearColor (0.2,0.2,0.2, 0.0); // slightly dark, not black
    GLfloat light_ambient[] = { 0.133, 0.545, 0.133, 1.0 }; //forest green
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, .0, .0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    
    glShadeModel (GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    
    sphereList = glGenLists(1);
    glNewList(sphereList, GL_COMPILE);
    glutSolidSphere (1.0, 300, 16);
    glEndList();
    
    lightList = glGenLists(1);
    glNewList(lightList, GL_COMPILE);
    glutSolidSphere (.05, 300, 16);
    glEndList();

    
}


void display(void)
{
    
    GLfloat mat_solid[] = { 0.75, 0.075, 0.0, 1.0 };
    GLfloat mat_zero[] = { .0, .0, .0, 1.0 };
    GLfloat mat_transparent[] = { 0.6, 0.6, 0.6, 0.8 };
    GLfloat mat_emission[] = { 0.0, 0.3, 0.3, 0.6 };
    
    
    GLfloat position[] = { 0.0, 0.0, 1.5, 1.0 };
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix ();
    glTranslatef (0.0, 0.0, -5.0);
    
    glPushMatrix ();
    glRotated ((GLdouble) spin, 1.0, 0.0, 0.0);
    glLightfv (GL_LIGHT0, GL_POSITION, position);
    
    glTranslated (0.0, 0.0, 1.5);
    glDisable (GL_LIGHTING);
    glColor3f (1.0, 1.0, 1.0);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
    glCallList (lightList);
    glEnable (GL_LIGHTING);
    glPopMatrix ();
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
    glEnable (GL_BLEND);
    glDepthMask (GL_FALSE);
    glBlendFunc (GL_SRC_ALPHA, GL_SRC_ALPHA);
    glCallList (sphereList);
    glDepthMask (GL_TRUE);
    glDisable (GL_BLEND);
    glPopMatrix ();
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                spin = (spin + 30) % 360;
                glutPostRedisplay();
            }
            break;
        default:
            break;
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
