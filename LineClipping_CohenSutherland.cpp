/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<stdio.h>
#include<bits/stdc++.h>
#include <stdlib.h>

using namespace std;

#define TOP 8
#define RIGHT 2
#define BOTTOM 4
#define LEFT 1


static int slices = 16;
static int stacks = 16;

int posx0, posy0, posx1,posy1;
int cnt = 0;
bool flag =false;
int xmax= 160, xmin= -160, ymax= 160, ymin= -160;


/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 319, -240, 239, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

int calcX(int x){
    return x-320;
}
int calcY(int y){
    return 239-y;
}


void draw8way(int x, int y,int zone)
{
    switch(zone)
    {
        case 0: {
            glVertex2i(x,y);
            break;
        }
        case 1: {
            glVertex2i(y,x);
            break;
        }
        case 2: {
            glVertex2i(-y,x);
            break;
        }
        case 3: {
            glVertex2i(-x,y);
            break;
        }
        case 4: {
            glVertex2i(-x,-y);
            break;
        }
        case 5: {
            glVertex2i(-y,-x);
            break;
        }
        case 6: {
            glVertex2i(y,-x);
            break;
        }
        case 7: {
            glVertex2i(x,-y);
            break;
        }
    }

}

void drawLine_0(int x0, int y0,int x1, int y1, int zone)
{
    int dx= x1-x0,dy= y1-y0;
    int x=x0,y=y0,d=2*dy-dx,dE=2*dy,dNE=2*(dy-dx);
    draw8way(x,y,zone);
    while(x<x1)
    {
        if(d<0)//E
        {
            x++,d+=dE;
        }
        else //NE
        {
            x++,y++,d+=dNE;
        }
        draw8way(x,y,zone);
    }
}


int findZone(int x0, int y0,int x1, int y1)
{
    int dx= x1-x0,dy= y1-y0;
    if(dx>=0 && dy>=0)
    {
        if(abs(dx)>abs(dy))return 0;
        else return 1;
    }
    else if(dx<=0 && dy>=0)
    {
        if(abs(dx)>abs(dy))return 3;
        else return 2;
    }
    else if(dx<=0 && dy<=0)
    {
        if(abs(dx)>abs(dy))return 4;
        else return 5;
    }
    else
    {
        if(abs(dx)>abs(dy))return 7;
        else return 6;
    }

}

void lineDraw(int x0, int y0,int x1, int y1 )
{
    int zone = findZone(x0,y0,x1,y1);
    if(zone ==0 )
    {
        // glColor3d(1,1,1);
        drawLine_0(x0,y0,x1,y1,0);
    }
    else if(zone ==1 )
    {
        // glColor3d(1,0,0);
        drawLine_0(y0,x0,y1,x1,1);
    }
    else if(zone ==2 )
    {
        // glColor3d(0,1,0);
        drawLine_0(y0,-x0,y1,-x1,2);
    }
    else if(zone ==3 )
    {
        // glColor3d(0,0,1);
        drawLine_0(-x0,y0,-x1,y1,3);
    }
    else if(zone ==4 )
    {
        // glColor3d(1,1,1);
        drawLine_0(-x0,-y0,-x1,-y1,4);
    }
    else if(zone ==5 )
    {
        // glColor3d(1,1,1);
        drawLine_0(-y0,-x0,-y1,-x1,5);
    }
    else if(zone ==6 )
    {
        // glColor3d(1,0,6);
        drawLine_0(-y0,x0,-y1,x1,6);
    }
    else if(zone ==7 )
    {
        // glColor3d(6,0,1);
        drawLine_0(x0,-y0,x1,-y1,7);
    }
}


int makeCode(int x, int y){
    int code =0;
    if(y > ymax)code += 8;
    else if(y<ymin)code += 4;
    if(x > xmax)code += 2;
    else if(x<xmin)code += 1;
    return code;    
}

//this is cohen sutherland algo

void cohenSutherland(int x0, int y0, int x1, int y1){
    int code, code0, code1;
    int x,y;
    code0 = makeCode(x0,y0);
    code1 = makeCode(x1,y1);
    while(1){
        if(!(code0 | code1)){
            //completely accepted
            lineDraw(x0, y0, x1, y1);
            break;
        }
        else if(code0 & code1){
            //completeky rejected
            break;
        }
        else{
            //partially accepted
            if(code0)code = code0;
            else code = code1;
            if(code & TOP){
                y = ymax;
                x = x0 + round((x1-x0)*(ymax-y0)/(y1-y0));
            }
            else if(code & BOTTOM){
                y = ymin;
                x = x0 + round((x1-x0)*(ymin-y0)/(y1-y0));
            }
            else if(code & RIGHT){
                x = xmax;
                y = y0 + round((y1-y0)*(xmax-x0)/(x1-x0));
            }
            else{
                x = xmin;
                y = y0 + round((y1-y0)*(xmin-x0)/(x1-x0));
            }

            if(code == code0){
                x0 = x, y0 = y;
                code0 = makeCode(x0, y0);
            }
            else{
                x1 = x, y1 = y;
                code1 = makeCode(x1, y1);
            }
        }
    }
}

void mouse_button_callback(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(cnt==0) posx0 = calcX(x), posy0 = calcY(y), cnt++;
        else {
            posx1 = calcX(x), posy1 = calcY(y), cnt=0;
            cout <<"First point -> (" <<posx0 << "," << posy0<< ")" << endl;
            cout <<"Second point -> (" <<posx1 << "," << posy1<< ")" << endl;
          }
    }
}

static void display(void)
{
    int x = 10, y = 20;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(319, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 239);
    glEnd();

    glutMouseFunc(mouse_button_callback);

    glBegin(GL_POINTS);

    glVertex2i(x, y+1);
    glVertex2i(x, y);

    
    //make the line clapping grid
    glColor3d(1,0,0);//set color red
    lineDraw(xmax,239,xmax,-240);
    lineDraw(xmin,239,xmin,-240);
    lineDraw(-320,ymax,319,ymax);
    lineDraw(-320,ymin,319,ymin);

    //draw lies
    glColor3d(0,1,0);  

    if(cnt ==0)
    cohenSutherland(posx0,posy0,posx1,posy1);

    glEnd();


    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;

    case '+':
        slices++;
        stacks++;
        break;

    case '-':
        if (slices>3 && stacks>3)
        {
            slices--;
            stacks--;
        }
        break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Experiment 01");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
