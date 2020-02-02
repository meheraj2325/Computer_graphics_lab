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

#include <stdlib.h>

static int slices = 16;
static int stacks = 16;

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

void drawLine_0(int x0, int y0,int x1, int y1)
{
    int dx= x1-x0,dy= y1-y0;
    int x=x0,y=y0,d=2*dy-dx,dE=2*dy,dNE=2*(dy-dx);
    glVertex2i(x,y);
    while(x<x1)
    {
        if(d<0)//E
        {
            x++,d+=dE;
        }
        else //NE
        {
            x++,y++,d+=dNE;
            glVertex2i(x,y);
        }
    }
}
void drawLine_1(int x0, int y0,int x1, int y1)
{
    int dx= x1-x0,dy= y1-y0;
    int x=x0,y=y0,d=dy-2*dx,dN=-2*dx,dNE=2*(dy-dx);
    glVertex2i(x,y);
    while(y<y1)
    {
        if(d<0)//NE
        {
            x++,y++,d+=dNE;
        }
        else //N
        {
            y++,d+=dN;
            glVertex2i(x,y);
        }
    }
}

void drawLine_2(int x0, int y0,int x1, int y1)
{
    int dx= x1-x0,dy= y1-y0;
    int x=x0,y=y0,d=-(2*dx+dy),dN=-2*dx,dWN=-2*(dx+dy);
    glVertex2i(x,y);
    while(y<y1)
    {
        if(d<0)//N
        {
            y++,d+=dN;
        }
        else //WN
        {
            x--,y++,d+=dWN;
            glVertex2i(x,y);
        }
    }
}

void drawLine_3(int x0, int y0,int x1, int y1)
{
    int dx= x1-x0,dy= y1-y0;
    int x=x0,y=y0,d=-(dx+2*dy),dW=-2*dy,dWN=-2*(dy+dx);
    glVertex2i(x,y);
    while(x>x1)
    {
        if(d<0)//WN
        {
            x--,y++,d+=dWN;
        }
        else //W
        {
            x--,d+=dW;
            glVertex2i(x,y);
        }
    }
}

void drawLine_4(int x0, int y0,int x1, int y1)
{
    int dx= x1-x0,dy= y1-y0;
    int x=x0,y=y0,d=dx-2*dy,dW=-2*dy,dSW=2*(dx-dy);
    glVertex2i(x,y);
    while(x>x1)
    {
        if(d<0)//SW
        {
            x--,y--,d+=dSW;
        }
        else //W
        {
            x--,d+=dW;
            glVertex2i(x,y);
        }
    }
}

void drawLine_5(int x0, int y0,int x1, int y1)
{
    int dx= x1-x0,dy= y1-y0;
    int x=x0,y=y0,d=2*dx-dy,dS=2*dx,dSW=2*(dx-dy);
    glVertex2i(x,y);
    while(y<y1)
    {
        if(d<0)//S
        {
            x--,d+=dS;
        }
        else //SW
        {
            x--,y--,d+=dSW;
            glVertex2i(x,y);
        }
    }
}

void drawLine_6(int x0, int y0,int x1, int y1)
{
    int dx= x1-x0,dy= y1-y0;
    int x=x0,y=y0,d=dy+2*dx,dS=2*dx,dSE=2*(dy+dx);
    glVertex2i(x,y);
    while(y<y1)
    {
        if(d<0)//SE
        {
            x++,y--,d+=dSE;
        }
        else //S
        {
            y--,d+=dS;
            glVertex2i(x,y);
        }
    }
}


void drawLine_7(int x0, int y0,int x1, int y1)
{
    int dx= x1-x0,dy= y1-y0;
    int x=x0,y=y0,d=2*dy+dx,dE=2*dy,dSE=2*(dy+dx);
    glVertex2i(x,y);
    while(x<x1)
    {
        if(d<0)//E
        {
            x++,d+=dE;
        }
        else //SE
        {
            x++,y--,d+=dSE;
            glVertex2i(x,y);
        }
    }
}

void findZone(int x0, int y0,int x1, int y1)
{
    int dx= x1-x0,dy= y1-y0;
    if(dx>=0 && dy>=0)
    {
        if(abs(dx)>abs(dy))drawLine_0(x0,y0,x1,y1);
        else drawLine_1(x0,y0,x1,y1);
    }
    else if(dx<=0 && dy>=0)
    {
        if(abs(dx)>abs(dy))drawLine_3(x0,y0,x1,y1);
        else drawLine_2(x0,y0,x1,y1);
    }
    else if(dx<=0 && dy<=0)
    {
        if(abs(dx)>abs(dy))drawLine_4(x0,y0,x1,y1);
        else drawLine_5(x0,y0,x1,y1);
    }
    else
    {
        if(abs(dx)>abs(dy))drawLine_7(x0,y0,x1,y1);
        else drawLine_6(x0,y0,x1,y1);
    }

}

void draw8way(int x, int y,int zone)
{
    switch(zone)
    {
        case 0: {glVertex2i(x,y); break;}
        case 1: {glVertex2i(y,x); break;}
        case 2: {glVertex2i(-y,x); break;}
        case 3: {glVertex2i(-x,y); break;}
        case 4: {glVertex2i(-x,-y); break;}
        case 5: {glVertex2i(-y,-x); break;}
        case 6: {glVertex2i(y,-x); break;}
        case 7: {glVertex2i(x,-y); break;}
    }

}

void drawLine_00(int x0, int y0,int x1, int y1, int zone)
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
            draw8way(x,y,zone);
        }
    }
}


void findZonee(int x0, int y0,int x1, int y1)
{
    int dx= x1-x0,dy= y1-y0;
    if(dx>=0 && dy>=0)
    {
        if(abs(dx)>abs(dy))drawLine_00(x0,y0,x1,y1,0);
        else drawLine_00(y0,x0,y1,x1,1);
    }
    else if(dx<=0 && dy>=0)
    {
        if(abs(dx)>abs(dy))drawLine_00(-x0,y0,-x1,y1,3);
        else drawLine_00(y0,-x0,y1,-x1,2);
    }
    else if(dx<=0 && dy<=0)
    {
        if(abs(dx)>abs(dy))drawLine_00(-x0,-y0,-x1,-y1,4);
        else drawLine_00(-y0,-x0,-y1,-x1,5);
    }
    else
    {
        if(abs(dx)>abs(dy))drawLine_00(x0,-y0,x1,-y1,7);
        else drawLine_00(-y0,x0,-y1,x1,6);
    }

}

void lineDraw(void)
{
    findZonee(-20,30,59,80);
    findZonee(-20,-30,100,-80);
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
    glBegin(GL_POINTS);
    glVertex2i(x, y+1);
    glVertex2i(x, y);
    lineDraw();
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
