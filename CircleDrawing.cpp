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
#include <stdio.h>
#include<math.h>

static int slices = 16;
static int stacks = 16;
int flag_pressed = 0, flag_release=0,x_initial,y_initial ,x_center,y_center,x_release,y_release,radius,increment_x1=1,increment_y1=1,increment_x2=-1,increment_y2=-1,mass1=1,mass2=1;
/* GLUT callback Handlers */

static void resize(int width, int height){
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 319, -240, 239, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

int calculateRadius(int x0,int y0,int x1,int y1){
    return sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0));
}

int calculateHypotenous(int dx,int dy){
    return sqrt((dx*dx + dy*dy));
}

void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        int mx = mousex;
        int my = mousey;
        //printf(" c1 %d %d\n",mx-320,-my+240);
        glutPostRedisplay();
        if(flag_pressed==0){
            flag_pressed=1;
            x_center = mx-320;
            y_center = -my+240;
            x_initial = x_center;
            y_initial = y_center;
        }
    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP){
        int mx = mousex;
        int my = mousey;
        if(flag_release==0){
            flag_release = 1;
            x_release = mx-320;
            y_release = -my+240;
            radius = calculateRadius(x_initial,y_initial,x_release,y_release);
            increment_x1 = (x_release - x_center);
            increment_y1 = (y_release - y_center);
            int d = calculateHypotenous(increment_x1,increment_y1);
            increment_x1 = 2*(increment_x1)/d;
            increment_y1 = 2*(increment_y1)/d;
        }
    }
}


void draw8way(int x,int y,int a, int b){
            glVertex2i(x+a, y+b);
            glVertex2i(y+a, x+b);
            glVertex2i(-y+a, x+b);
            glVertex2i(-x+a, y+b);
            glVertex2i(-x+a, -y+b);
            glVertex2i(-y+a, -x+b);
            glVertex2i(y+a, -x+b);
            glVertex2i(x+a, -y+b);
    }

void drawCircle1(int a,int b,int r){
    int x=0,y=r, d=5-4*r;
    draw8way(x,y,a,b);
    while(x<y){
        if(d<0){
            x++;
            d+= 8*x + 12;
        }
        else{
            x++,y--;
            d+= 8*x - 8*y + 20;
        }
        draw8way(x,y,a,b);
    }
}


static void display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(319, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 239);
    glEnd();
    glBegin(GL_POINTS);

    if(flag_pressed==1 && flag_release ==1){
        drawCircle1(x_center,y_center,radius);
        if(y_center + radius > 240)
            increment_y1 = -1;
        else if(y_center - radius < -240)
            increment_y1 = 1;
        else if(x_center + radius > 320)
            increment_x1 = -1;
        else if(x_center - radius < -320)
            increment_x1 = 1;

        x_center+=increment_x1, y_center+=increment_y1;
    }
    
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

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Experiment 01");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMainLoop();



    return EXIT_SUCCESS;
}