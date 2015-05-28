#include<windows.h>
#include<GL/glut.h>
#include "consts.hpp"

#include "Camera.h"

#include "object.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "cube.hpp"
#include "world.hpp"

#include "bitmap_image.hpp"

#include "Tracer.h"

Camera cam;


int traceFlag = 0;

void drawSquare(float a)
{
    glBegin(GL_QUADS);
    {
        glVertex3f( a, a,0);
        glVertex3f( a,-a,0);
        glVertex3f(-a,-a,0);
        glVertex3f(-a, a,0);
    }
    glEnd();
}



void drawGrid()
{
    int i;

    {
        glColor3f(0.6, 0.6, 0.6);
        glBegin(GL_LINES);
        {
            for(i=-8; i<=8; i++)
            {

                if(i==0)
                    continue;


                glVertex3f(i*10, -90, 0);
                glVertex3f(i*10,  90, 0);


                glVertex3f(-90, i*10, 0);
                glVertex3f( 90, i*10, 0);
            }
        }
        glEnd();
    }
}




void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {

    case '4':

        cam.yaw(.8);
        break;
    case '6':

        cam.yaw(-.8);
        break;
    case '8':

        cam.pitch(-.8);
        break;
    case '2':

        cam.pitch(.8);
        break;

    case '+':
        cam.slide(0,0,-.8);
        break;
    case '-':
        cam.slide(0,0,.8);
        break;

    default:
        break;
    }

}


void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_DOWN:
        cam.slide(0,-.8,0);

        break;
    case GLUT_KEY_UP:
        cam.slide(0,.8,0);
        break;

    case GLUT_KEY_RIGHT:
        cam.slide(.8,0,0);
        break;
    case GLUT_KEY_LEFT:
        cam.slide(-.8,0,0);
        break;

    case GLUT_KEY_PAGE_UP:
        cam.roll(.8);
        break;
    case GLUT_KEY_PAGE_DOWN:
        cam.roll(-.8);
        break;



    case GLUT_KEY_INSERT:
        break;

    case GLUT_KEY_F5:
        traceFlag=1;
        break;
    case GLUT_KEY_END:
        break;

    default:
        break;
    }

}

void animate()
{
    glutPostRedisplay();
}


//<<<<<<<<<<<<<<<<<<<<<<< display >>>>>>>>>>>>>>>>>>>>>>>>>>
void display(void)
{
    // glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_NORMALIZE);

    glClearColor(0,0,0,0);


    glMatrixMode(GL_MODELVIEW);
    //  glLoadIdentity();
    cam.setModelViewMatrix(); // for this camera set up
    cam.setProjectionMatrix();



    for(int i=0; i<world.nCubes; i++)
    {
        Cube c = world.allCubes[i];

        glPushMatrix();
        {
            glTranslatef( c.lowPoint.x + c.armLength/2.0 , c.lowPoint.y + c.armLength/2.0 , c.lowPoint.z + c.armLength/2.0 );
            glColor3f(c.color.x, c.color.y, c.color.z);
            glutSolidCube(c.armLength);

        }
        glPopMatrix();

    }


    for(int i=0,m=-5; i<10; i++,m++)
    {
        for(int j=0,n=-5; j<10; j++,n++)
        {
            glPushMatrix();
            {
                glTranslatef(m*30+15,n*30+15,0 );
                if (i%2==0 && j%2==0)glColor3f( 0.0f, 0.0f, 0.0f );
                else if(i%2==0 && j%2!=0)glColor3f( 1.0f, 1.0f, 1.0f  );
                else if (i%2!=0 && j%2!=0)glColor3f( 0.0f, 0.0f, 0.0f );
                else if(i%2!=0 &&  j%2==0)glColor3f( 1.0f, 1.0f, 1.0f  );


                drawSquare(15);
            }
            glPopMatrix();
        }
    }




    for(int i=0; i<world.nObjects; i++)
    {

        Object* ob = world.allObjects[i];

        if(ob->type == Object::SPHERE)
        {

            Sphere* sp = (Sphere*) ob;

            glPushMatrix();
            {
                glTranslatef( sp->center.x, sp->center.y, sp->center.z );
                glColor3f(sp->color.x, sp->color.y, sp->color.z );
                glutSolidSphere(sp->radius,20,20);

            }
            glPopMatrix();

        }

    }

    if(traceFlag)
    {
        initTracing(cam);
        traceFlag = 0;
    }
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    freopen("input.txt","r",stdin);
    world.loadFromFile();

    glutInit(&argc,argv);
    glutInitWindowSize(nPixel, nPixel);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

    glutCreateWindow("Awesome Tracer");

    glColor3f(0.0f,0.0f,0.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    traceFlag=0;
    glEnable(GL_DEPTH_TEST);	//enable Depth Testing
    glDisable(GL_LIGHTING);
    glViewport(0, 0, nPixel, nPixel);
    cam.sett(50.0f,-80.0f,100.0, 0,0.25f,0, 0,0,1);

    cam.setShape(80.0,1.0,1.0, 10000.0);

    cam.setDisplay(nPixel, nPixel);
    glutDisplayFunc(display);
    glutIdleFunc(animate);

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);

    glutMainLoop();

    return 0;
}
