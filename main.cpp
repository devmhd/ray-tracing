
#include<windows.h>
#include<GL/glut.h>
#include "consts.hpp"

#include "Camera.h"


#include "object.hpp"
#include "sphere.hpp"
#include "plane.hpp"

#include "bitmap_image.hpp"

//class Scene;
//############################ GLOBALS ########################
//typedef Vector Color;
Camera cam; // construct it
// construct it

int screenWidth = 512, screenHeight = 512;
int doRayTrace = 0;
float lightStrength = 1.0;
float amount = 1.0;
int blockSize = 1;


void drawAxes()
{
    //if(drawaxes==1)
    {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        {
            glVertex3f( 100,0,0);
            glVertex3f(-100,0,0);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(0,-100,0);
            glVertex3f(0, 100,0);
            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(0,0, 100);
            glVertex3f(0,0,-100);
        }
        glEnd();
    }
}

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
    //if(drawgrid==1)
    {
        glColor3f(0.6, 0.6, 0.6);	//grey
        glBegin(GL_LINES);
        {
            for(i=-8; i<=8; i++)
            {

                if(i==0)
                    continue;	//SKIP the MAIN axes

                //lines parallel to Y-axis
                glVertex3f(i*10, -90, 0);
                glVertex3f(i*10,  90, 0);

                //lines parallel to X-axis
                glVertex3f(-90, i*10, 0);
                glVertex3f( 90, i*10, 0);
            }
        }
        glEnd();
    }
}



// -----------------------------------------------------------
// Sphere primitive class definition
// -----------------------------------------------------------

// -----------------------------------------------------------
// Scene class definition
// -----------------------------------------------------------

class Scene
{
public:
    Scene() : m_Primitives( 0 ), m_Primitive( 0 ) {}
    ~Scene()
    {
        delete m_Primitive;
    }
    void InitScene()
    {
        m_Primitive = new Primitive*[500];

        /**/

        m_Primitive[0] = new Sphere( Vector( 40.0, 0.0f, 10.0f ), 10.0f );
        m_Primitive[0]->SetName( "big sphere" );
        m_Primitive[0]->SetReflection( 0.2f );
        m_Primitive[0]->SetDiffuse( .20f );
        m_Primitive[0]->SetSpecular(.2f);
        m_Primitive[0]->SetShininess(5);
        m_Primitive[0]->SetColor( Color( 0.0f, 1.0f, 0.0f ) );

        m_Primitive[1] = new Sphere( Vector( 30.0f,60.0f,20.0f), 20.0f );
        m_Primitive[1]->SetName( "small sphere" );
        m_Primitive[1]->SetReflection( 0.2f );
        m_Primitive[1]->SetRefraction( 0.8f );
        m_Primitive[1]->SetRefrIndex( 0.8f );
        m_Primitive[1]->SetDiffuse( 0.1f );
        m_Primitive[1]->SetSpecular(.3);
        m_Primitive[1]->SetShininess(20);
        m_Primitive[1]->SetColor( Color( 0.0, 0.0, 1.0) );

        m_Primitive[2] = new Sphere( Vector( 15.0f,15.0f,45.0f), 15.0f );
        m_Primitive[2]->SetName( "smal lsphere" );
        m_Primitive[2]->SetReflection( .2f );
        m_Primitive[2]->SetDiffuse( 0.3f );
        m_Primitive[2]->SetSpecular(.1);
        m_Primitive[2]->SetShininess(10);
        m_Primitive[2]->SetColor( Color( 1.0, 1.0, 0.0) );

        // light source 1
        m_Primitive[3] = new Sphere( Vector( 70, 70, 70 ), 2.0f );
        m_Primitive[3]->Light( true );
        m_Primitive[3]->SetColor( Color(1.0f,1.0f,1.0f ) );
        // light source 2
        m_Primitive[4] = new Sphere( Vector( -70,70,70), 2.0f );
        m_Primitive[4]->Light( true );
        m_Primitive[4]->SetColor( Color(1.0f,1.0f,1.0f )) ;

        //cube
        float h=30;

        m_Primitive[5] = new PlanePrim( Vector( 0, 1, 0 ), Vector(0,0,0 ));
        m_Primitive[5]->SetName( "plane" );
        m_Primitive[5]->SetReflection( .6 );
        m_Primitive[5]->SetDiffuse( .20f );
        m_Primitive[5]->SetSpecular(.1);
        m_Primitive[5]->SetShininess(5);
        m_Primitive[5]->SetColor( Color( 1.0f, 0.0f, 0.0f  ) );

        m_Primitive[6] = new PlanePrim( Vector( 0, -1, 0 ), Vector(0,h,0 ));
        m_Primitive[6]->SetName( "plane" );
        m_Primitive[6]->SetReflection( .6 );
        m_Primitive[6]->SetDiffuse( .20f );
        m_Primitive[6]->SetSpecular(.1);
        m_Primitive[6]->SetShininess(5);
        m_Primitive[6]->SetColor( Color( 1.0f, 0.0f, 0.0f  ) );

        m_Primitive[7] = new PlanePrim( Vector( 0, 0, -1 ), Vector(0,0,0 ));
        m_Primitive[7]->SetName( "plane" );
        m_Primitive[7]->SetReflection( .6 );
        m_Primitive[7]->SetDiffuse( .20f );
        m_Primitive[7]->SetSpecular(.1);
        m_Primitive[7]->SetShininess(5);
        m_Primitive[7]->SetColor( Color( 1.0f, 0.0f, 0.0f  ) );


        m_Primitive[8] = new PlanePrim( Vector( 0, 0, 1 ), Vector(0,0,h ));
        m_Primitive[8]->SetName( "plane" );
        m_Primitive[8]->SetReflection( .6 );
        m_Primitive[8]->SetDiffuse( .20f );
        m_Primitive[8]->SetSpecular(.1);
        m_Primitive[8]->SetShininess(5);
        m_Primitive[8]->SetColor( Color( 1.0f, 0.0f, 0.0f  ) );


        m_Primitive[9] = new PlanePrim( Vector( -1, 0, 0 ), Vector(0,0,0 ));
        m_Primitive[9]->SetName( "plane" );
        m_Primitive[9]->SetReflection( .6 );
        m_Primitive[9]->SetDiffuse( .20f );
        m_Primitive[9]->SetSpecular(.1);
        m_Primitive[9]->SetShininess(5);
        m_Primitive[9]->SetColor( Color( 1.0f, 0.0f, 0.0f  ) );


        m_Primitive[10] = new PlanePrim( Vector( 1, 0, 0 ), Vector(h,0,0 ));
        m_Primitive[10]->SetName( "plane" );
        m_Primitive[10]->SetReflection( .6 );
        m_Primitive[10]->SetDiffuse( .20f );
        m_Primitive[10]->SetSpecular(.1);
        m_Primitive[10]->SetShininess(5);
        m_Primitive[10]->SetColor( Color( 1.0f, 0.0f, 0.0f  ) );


//cube


        /*  m_Primitive[4] = new PlanePrim( Vector( 0, 0, 1 ), Vector(0,0,0 ));
          m_Primitive[4]->SetName( "plane" );
          m_Primitive[4]->SetReflection( 0 );
          m_Primitive[4]->SetDiffuse( 1.0f );
          m_Primitive[4]->SetColor( Color( 1.0f, 1.0f, 1.0f  ) );

          m_Primitive[5] = new PlanePrim( Vector( 0, 0, 1 ), Vector(0,20,0 ));
          m_Primitive[5]->SetName( "plane" );
          m_Primitive[5]->SetReflection( 0 );
          m_Primitive[5]->SetDiffuse( 1.0f );
          m_Primitive[5]->SetColor( Color( 0.0f, 0.0f, 0.0f ) );*/


        int p=11;
        for(int i=0,m=-5; i<10; i++,m++)
        {
            for(int j=0,n=-5; j<10; j++,n++)
            {
                m_Primitive[p+i*10+j] = new PlanePrim( Vector( 0, 0, 1 ), Vector(m*30,n*30,0 ));
                m_Primitive[p+i*10+j]->SetName( "plane" );
                m_Primitive[p+i*10+j]->SetReflection( 0 );
                m_Primitive[p+i*10+j]->SetDiffuse( 1.0f );
                if (i%2==0 && j%2==0)m_Primitive[p+i*10+j]->SetColor( Color( 0.0f, 0.0f, 0.0f ) );
                 else if(i%2==0 && j%2!=0) m_Primitive[p+i*10+j]->SetColor( Color( 1.0f, 1.0f, 1.0f ) );
               else if (i%2!=0 && j%2!=0) m_Primitive[p+i*10+j]->SetColor( Color( 0.0f, 0.0f, 0.0f ) );
                else if(i%2!=0 &&  j%2==0) m_Primitive[p+i*10+j]->SetColor( Color( 1.0f, 1.0f, 1.0f ) );
            }
        }


        // set number of primitives
        m_Primitives =p+100;
    }

    int GetNrPrimitives()
    {
        return m_Primitives;
    }
    Primitive* GetPrimitive( int a_Idx )
    {
        return m_Primitive[a_Idx];
    }
private:
    int m_Primitives;
    Primitive** m_Primitive;
} scn;


void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {

    case '1':
        //drawgrid=1-drawgrid;
        cam.yaw(.8);
        break;
    case '2':
        //drawgrid=1-drawgrid;
        cam.yaw(-.8);
        break;
    case '3':
        //drawgrid=1-drawgrid;
        cam.pitch(.8);
        break;
    case '4':
        //drawgrid=1-drawgrid;
        cam.pitch(-.8);
        break;
    case '5':
        cam.roll(.8);
        break;
    case '6':
        cam.roll(-.8);
        break;

    default:
        break;
    }
    //// glutPostRedisplay();
}


void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_DOWN:		//move backward
        cam.slide(0,0,.8);
       //cout<<"ereer";
        break;
    case GLUT_KEY_UP:		//move forward
        cam.slide(0,0,-.8);
        break;

    case GLUT_KEY_RIGHT:   //move right
        cam.slide(.8,0,0);
        break;
    case GLUT_KEY_LEFT:    //move left
        cam.slide(-.8,0,0);
        break;

    case GLUT_KEY_PAGE_UP:  //move upward
        cam.slide(0,.8,0);
        break;
    case GLUT_KEY_PAGE_DOWN:  //move downward
        cam.slide(0,-.8,0);
        break;

    case GLUT_KEY_INSERT:
        break;

    case GLUT_KEY_HOME:
        doRayTrace=1;
        break;
    case GLUT_KEY_END:
        break;

    default:
        break;
    }
    // glutPostRedisplay();
}

void animate()
{
//	angle+=0.05;
    //codes for any changes in Models, Camera
    glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<< myReshape >>>>>>>>>>>>>>>>>>>
void myReshape(int width, int height)
{
    // adjust the camera aspect ratio to match that of the viewport
    /* students do here: update screenWidth and screenHeight;
       update nCols, nRows in camera;
       update camera's shape */
    if(height == 0)
        height = 1;

    float ratio = 1.0*width/height;

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, width, height);

    // Set the correct perspective.
    gluPerspective(45,ratio,1.0,10000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,5.0,
              0.0,0.0,-1.0,
              0.0f,1.0f,0.0f);

    screenWidth=width;
    screenHeight=height;
    //to update nCols nRows camera's shape
    cam.setShape(20.0,screenWidth/(float)screenHeight,1.0, 10000.0); // match it to viewport
    cam.setDisplay(screenHeight, screenWidth); //sets nRows, nCols in camera

    //glViewport(0, 0, screenWidth, screenHeight); // update viewport
}

void saveBitmap()
{
    const unsigned int dim = 300;
    bitmap_image image(dim,dim);

    for (unsigned int x = 0; x < dim; ++x)
    {
        for (unsigned int y = 0; y < dim; ++y)
        {
            rgb_store col = jet_colormap[(x + y) % dim];
            image.set_pixel(x,y,col.red,col.green,col.blue);
        }
    }

    image.save_image("test09_color_map_image.bmp");
}
Primitive* Raytrace( Ray& a_Ray, Color& a_Acc, int a_Depth, float a_RIndex, float& a_Dist )
{
    if (a_Depth > TRACEDEPTH) return 0;
    // trace primary ray
    a_Dist = 1000000.0f;
    Vector pi;//point of intersection

    Primitive* prim = 0;
    //a_Acc = Color( 0, 0, 0);
    int result;
    float n= 1000005.0f;
    // find the nearest intersection
    for ( int s = 0; s < scn.GetNrPrimitives(); s++ )
    {
        Primitive* pr = scn.GetPrimitive( s );
        int res;
        res = pr->Intersect( a_Ray, a_Dist );
        if (res)
        {
            //if(a_Dist<n)
            {
                prim = pr;
                result = res; // 0 = miss, 1 = hit, -1 = hit from inside primitive
            }
        }
    }
    // no hit, terminate ray
    if (!prim)
    {
        a_Acc = Color( 0, 0, 0);
        return 0;
    }

    // handle intersection
    if (prim->IsLight())
    {
        // we hit a light, stop tracing
        a_Acc = Color( 1.0f, 1.0f, 1.0f );
    }
    else
    {
        // determine color at point of intersection
        a_Ray.direction.normalize() ;
        pi = a_Ray.origin + a_Ray.direction * a_Dist;
        // trace lights
        a_Acc += 0.4*prim->GetColor();
        for ( int l = 0; l < scn.GetNrPrimitives(); l++ )
        {
            Primitive* p = scn.GetPrimitive( l );
            if (p->IsLight())
            {
                Primitive* light = p;

                float shade = 1.0f;
                if (light->GetType() == Primitive::SPHERE)
                {
                    Vector L = ((Sphere*)light)->GetCentre() - pi;
                    float tdist = L.length();
                    L *= (1.0f / tdist);
                    Ray r = Ray( pi + L * EPSILON, L );
                    for ( int s = 0; s < scn.GetNrPrimitives(); s++ )
                    {
                        Primitive* pr = scn.GetPrimitive( s );
                        if ((pr != light) && (pr->Intersect( r, tdist )))
                        {
                            shade = 0;
                            break;
                        }
                    }
                }


                // calculate diffuse shading
                Vector L = ((Sphere*)light)->GetCentre() - pi;
                L.normalize();
                Vector N = prim->GetNormal( pi );
                if (prim->GetDiffuse() > 0)
                {
                    float dot = N.dot(L);
                    if (dot > 0)
                    {
                        float diff = dot * prim->GetDiffuse()* shade;
                        // add diffuse component to ray color
                        a_Acc += diff *( prim->GetColor() * light->GetColor());
                    }
                }

                if (prim->GetSpecular() > 0)
                {
                    // point light source: sample once for specular highlight
                    Vector V = a_Ray.direction;
                    Vector R = L - 2.0f * L.dot(N) * N;
                    float dot = V.dot(R);
                    if (dot > 0)
                    {
                        float spec = powf( dot, 20 ) * prim->GetSpecular()* shade ;
                        // add specular component to ray color
                        a_Acc += spec * light->GetColor();
                    }
                }
            }


        }
        float refl = prim->GetReflection();
        if (refl > 0.0f)
        {
            Vector N = prim->GetNormal( pi );
            Vector R = a_Ray.direction - 2.0f * a_Ray.direction.dot(N) * N;
            if (a_Depth < TRACEDEPTH)
            {
                Color rc( 0, 0, 0 );
                float dist;
                Ray ray( pi + R * EPSILON, R );
                // ray.SetOrigin(pi+ R * EPSILON);
                Raytrace( ray, rc, a_Depth + 1, a_RIndex, dist );
                a_Acc += refl * rc * prim->GetColor();
            }
        }


// calculate refraction
       /* float refr = prim->GetRefraction();
        if ((refr > 0) && (a_Depth < TRACEDEPTH))
        {
            float rindex = prim->GetRefrIndex();
            float n = a_RIndex / rindex;
            Vector N = prim->GetNormal( pi ) * (float)result;
            float cosI = -DOT( N, a_Ray.GetDirection() );
            float cosT2 = 1.0f - n * n * (1.0f - cosI * cosI);
            if (cosT2 > 0.0f)
            {
                Vector T = (n * a_Ray.GetDirection()) + (n * cosI - sqrtf( cosT2 )) * N;
                Color rco( 0, 0, 0 );
                float dis;
                Ray  r( pi + T * EPSILON, T );
                Raytrace( r, rco, a_Depth + 1, rindex, dis );
                // apply Beer's law
                Color absorbance = prim->GetColor() * 0.15f * -dis;
                //Color transparency = Color( expf( absorbance.r ), expf( absorbance.g ), expf( absorbance.b ) );
                a_Acc += refr * rco * prim->GetColor();
            }
        }*/
    }
    // return pointer to primitive hit by primary ray
    return prim;
}


void plot_pixel_display(int x,int y,float r,float g,float b)
{
    glBegin(GL_POINTS);
    glColor3f(((float)r)/256.f,((float)g)/256.f,((float)b)/256.f);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}
void raytracer(Scene& scn, int blockSize)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //set to identity
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,cam.nCols,0,cam.nRows); // whole screen is the window
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING); // so glColor3f() will work

    Ray theRay;
    theRay.origin = (Vector(cam.eye.x,cam.eye.y,cam.eye.z));
    float blockWidth  = 2 *cam.W / (float)cam.nCols;
    float blockHeight = 2 *cam.H / (float)cam.nRows;


    float x, y;
    const unsigned int dim = 300;
    bitmap_image image(cam.nRows,cam.nCols);

    for(int row = 0; row < cam.nRows; row += blockSize)
    {
        for(int col = 0; col < cam.nCols; col += blockSize)
        {
            Color clr(0,0,0);

            x = -cam.W + col * blockWidth;
            y = -cam.H + row * blockHeight;
            theRay.direction =  Vector(-cam.nearDist * cam.n.x + x * cam.u.x + y *cam.v.x,
                                         -cam.nearDist * cam.n.y + x * cam.u.y + y * cam.v.y,
                                         -cam.nearDist * cam.n.z + x * cam.u.z + y * cam.v.z);
            theRay.direction.normalize();

            //	clr.sett(scn.shade(theRay)); // get color of this ray
            //clr.add(scn.ambient);//add ambient light
            //glColor3f(clr.red,clr.green,clr.blue); // set current color
            //glRecti(col,row,col+blockSize, row + blockSize);
            int a_Depth=1;
            float a_RIndex=1 ,a_Dist=10 ;
            Raytrace( theRay,clr,  a_Depth, a_RIndex,  a_Dist );

            //

            //   cout<<clr.x<<" "<<clr.y<<" "<<clr.z<<endl;
            glColor3f(clr.x,clr.y,clr.z);
            glRecti(col,row,col+blockSize, row + blockSize);
            //glRecti(row,col,row+blockSize, col + blockSize);

            float r=clr.x*256.0,g=clr.y*256.0,b=clr.z*256.0;
            if(r>255) r=255;
            if(g>255) g=255;
            if(b>255) b=255;


            image.set_pixel(row,col,r,g,b);
        }
    }
    image.save_image("test09.bmp");

}
//<<<<<<<<<<<<<<<<<<<<<<< display >>>>>>>>>>>>>>>>>>>>>>>>>>
void display(void)
{
    // glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_NORMALIZE);

    glClearColor(0,0,0,0);

    //	glMatrixMode(GL_PROJECTION);
    //	glLoadIdentity();

    //glDisable(GL_DEPTH_TEST);

    //glEnable(GL_DEPTH_TEST);
    // cam.drawOpenGL(scn);
    glMatrixMode(GL_MODELVIEW);
    //  glLoadIdentity();
      cam.setModelViewMatrix(); // for this camera set up
     cam.setProjectionMatrix();




    //  gluOrtho2D(0,cam.nCols,0,cam.nRows); // whole screen is the window

    //  drawGrid();
    /**/
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
               // else if(i%2!=0 && j%2==0)glColor3f( 1.0f, 1.0f, 1.0f  );
                //else if(i%2!=0 && j%2!=0)  glColor3f( 0.0f, 0.0f, 0.0f  );
               // glColor3f( 1.0f, 1.0f, 1.0f  );

                drawSquare(15);
            }
            glPopMatrix();
        }
    }
    drawAxes();

    glPushMatrix();
    {
        glTranslatef( 15.0 ,15.0 ,15.0 );
        glColor3f(1.0, 0.0, 0.0 );
        glutSolidCube(30);

    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef( 15.0f,15.0f ,45.0f );
        glColor3f(1.0, 1.0, 0.0 );
        GLUquadricObj * quadric;
        quadric = gluNewQuadric();
        glutSolidSphere(10.0,20,20);

    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef( 40.0, 0.0, 10.0 );
        glColor3f(0.0, 1.0, 0.0 );
        GLUquadricObj * quadric;
        quadric = gluNewQuadric();
        glutSolidSphere(10.0,20,20);

    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef( 30.0 ,60.0 ,20.0 );
        glColor3f(0.0, 0.0, 1.0 );
        GLUquadricObj * quadric;
        quadric = gluNewQuadric();
        glutSolidSphere(20.0,20,20);

    }
    glPopMatrix();

    if(doRayTrace)
    {
        raytracer(scn,blockSize);
        doRayTrace = 0;
    }
    glutSwapBuffers();
} // end of display
//<<<<<<<<<<<<<<<<<<<<<<<<<<< myinit >>>>>>>>>>>>>>>>>>>>>>>>>>>.
void myInit(void)
{

    glColor3f(0.0f,0.0f,0.0f);
    glShadeModel(GL_SMOOTH); // or could be GL_FLAT
    glEnable(GL_NORMALIZE);

    scn.InitScene();
    doRayTrace=0;



} // end of myInit

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
     /*glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_RGB |GLUT_DEPTH);
     glutInitWindowSize(screenWidth, screenHeight);
     glutInitWindowPosition(10, 10);
     glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
     glutCreateWindow("my ECE661 raytracer");
     glutKeyboardFunc(keyboardListener);
     glutSpecialFunc(specialKeyListener);
     myInit();

     glutReshapeFunc(myReshape);
     glutDisplayFunc(display);

     glutMainLoop();*/

    ///////////////
    glutInit(&argc,argv);
    glutInitWindowSize(screenHeight, screenWidth);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

    glutCreateWindow("My OpenGL Program");

    myInit();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing
    glDisable(GL_LIGHTING);
    glViewport(0, 0, screenWidth, screenHeight);
    cam.sett(50.0f,80.0f,100.0, 0,0.25f,0, 0,0,1);
    // cam.sett(80, 20, 90, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    cam.setShape(80.0,screenWidth/(float)screenHeight,1.0, 10000.0);
    // cam.setShape(80.0, 1, 1, 10000.0);
    cam.setDisplay(screenHeight, screenWidth);
    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)
// glutReshapeFunc(myReshape);
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
//	glutMouseFunc(mouseListener);

    glutMainLoop();		//The main loop of OpenGL

    return 0;
}
