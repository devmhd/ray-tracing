#include <stdio.h>

class World
{
public:
    World() : nObjects( 0 ), allObjects( 0 ) {}
    ~World()
    {
        delete allObjects;
    }



    void addCube(Vector lowPoint, float armLength, Color color, float amb, float diff, float spec, float refl, float shin){

        allObjects[nObjects     ] = new PlanePrim( Vector( 0, 1, 0 ), Vector(0,0,0 ), 10);
        allObjects[nObjects + 1 ] = new PlanePrim( Vector( 0, -1, 0 ), Vector(0,armLength,0 ), armLength);
        allObjects[nObjects + 2 ] = new PlanePrim( Vector( 0, 0, -1 ), Vector(0,0,0 ), 10);
        allObjects[nObjects + 3 ] = new PlanePrim( Vector( 0, 0, 1 ), Vector(0,0,armLength ), armLength);
        allObjects[nObjects + 4 ] = new PlanePrim( Vector( -1, 0, 0 ), Vector(0,0,0 ), 10);
        allObjects[nObjects + 5 ] = new PlanePrim( Vector( 1, 0, 0 ), Vector(armLength,0,0 ), armLength);

        for(int i=0; i<6; ++i,nObjects++){

            allObjects[nObjects]->coeff_reflection =  refl ;
            allObjects[nObjects]->coeff_diff =  diff ;
            allObjects[nObjects]->coeff_spec = spec;
            allObjects[nObjects]->shininess = shin;
            allObjects[nObjects]->color = color;

        }

    }


    void loadFromFile()
    {
        allObjects = new Object*[500];

        nObjects = 0;


        int nShapes;

        scanf("%d", &nBumps);

        scanf("%d", &nPixel);

        scanf("%d", &nShapes);

        printf("Bumps: %d\n Number of things: %d\n Resolution: %d x %d\n", nBumps, nShapes, nPixel, nPixel);


        float x,y,z,r,cr,cg,cb;
        float amb, diff, spec, refl, shin;
        for(int i=0; i<nShapes; i++)
        {

            int type;
            scanf("%d", &type);



            if(type == 1)   //Sphere
            {


                printf("%d: Sphere\n", i);
                scanf("%f %f %f", &x, &y, &z);
                scanf("%f", &r);

                allObjects[nObjects] = new Sphere( Vector( x, y, z ), r );


                scanf("%f %f %f", &x, &y, &z);
                allObjects[nObjects]->color = ( Color( x, y, z ) );

                scanf("%f", &x);
      //          spheres[nSpheres].setambient(x);


                scanf("%f", &x);
                allObjects[nObjects]->coeff_diff =  x ;

                scanf("%f", &x);
                allObjects[nObjects]->coeff_spec =  x ;

                scanf("%f", &x);
                allObjects[nObjects]->coeff_reflection =  x ;

                scanf("%f", &x);
                allObjects[nObjects]->shininess =  x ;


                nObjects++;


            }
            else            //Cube
            {



                scanf("%f %f %f", &x, &y, &z);
                scanf("%f", &r);

 //               cubes[nCubes] = Cube(Point(x,y,z),r);

                scanf("%f %f %f", &cr, &cg, &cb);

  //              cubes[nCubes].setColor(Color(x,y,z));

                scanf("%f", &amb);
  //              cubes[nCubes].setambient(x);

                scanf("%f", &diff);
  //              cubes[nCubes].setdiffuse(x);

                scanf("%f", &spec);
  //              cubes[nCubes].setspecular(x);

                scanf("%f", &refl);
   //             cubes[nCubes].setreflection(x);

                scanf("%f", &shin);
    //            cubes[nCubes].setshininess(x);

     //           nCubes++;

                addCube(Vector(x,y,z), r, Color(cr,cg,cb), amb, diff, spec, refl, shin);

            }
        }

        int nLightSources;
        scanf("%d", &nLightSources);

        for(int i=0; i<nLightSources; ++i)
        {


            scanf("%f %f %f", &x, &y, &z);

            allObjects[nObjects] = new Sphere( Vector( x, y, z ), 3.0f );
            allObjects[nObjects]->isLight = true ;
            allObjects[nObjects]->color = Color(1.0f,1.0f,1.0f );

            ++nObjects;


        }

        printf("Lights sources: %d\n", nLightSources);





        /*
                allObjects[0] = new Sphere( Vector( 40.0, 0.0f, 10.0f ), 10.0f );

                allObjects[0]->coeff_reflection =  0.2f ;
                allObjects[0]->coeff_diff =  .20f ;
                allObjects[0]->coeff_spec = .2f;
                allObjects[0]->shininess = 5;
                allObjects[0]->color = ( Color( 0.0f, 1.0f, 0.0f ) );

                allObjects[1] = new Sphere( Vector( 30.0f,60.0f,20.0f), 20.0f );

                allObjects[1]->coeff_reflection =  0.2f ;

                allObjects[1]->coeff_diff =  0.1f ;
                allObjects[1]->coeff_spec = .3;
                allObjects[1]->shininess = 10000;
                allObjects[1]->color = ( Color( 0.0, 0.0, 1.0) );

                allObjects[2] = new Sphere( Vector( 15.0f,15.0f,45.0f), 15.0f );

                allObjects[2]->coeff_reflection =  .2f ;
                allObjects[2]->coeff_diff =  0.3f ;
                allObjects[2]->coeff_spec = .1;
                allObjects[2]->shininess = 10;
                allObjects[2]->color = ( Color( 1.0, 1.0, 0.0) );

                // light source 1
                allObjects[3] = new Sphere( Vector( 70, 70, 70 ), 2.0f );
                allObjects[3]->isLight = ( true );
                allObjects[3]->color = ( Color(1.0f,1.0f,1.0f ) );
                // light source 2
                allObjects[4] = new Sphere( Vector( -70,70,70), 2.0f );
                allObjects[4]->isLight = ( true );
                allObjects[4]->color = ( Color(1.0f,1.0f,1.0f )) ;

                //cube
                float h=10;

                allObjects[5] = new PlanePrim( Vector( 0, 1, 0 ), Vector(0,0,0 ), 10);

                allObjects[5]->coeff_reflection =  .6 ;
                allObjects[5]->coeff_diff =  .20f ;
                allObjects[5]->coeff_spec = .1;
                allObjects[5]->shininess = 5;
                allObjects[5]->color = ( Color( 1.0f, 0.0f, 0.0f  ) );

                allObjects[6] = new PlanePrim( Vector( 0, -1, 0 ), Vector(0,h,0 ), 10);

                allObjects[6]->coeff_reflection =  .6 ;
                allObjects[6]->coeff_diff =  .20f ;
                allObjects[6]->coeff_spec = .1;
                allObjects[6]->shininess = 5;
                allObjects[6]->color = ( Color( 1.0f, 0.0f, 0.0f  ) );

                allObjects[7] = new PlanePrim( Vector( 0, 0, -1 ), Vector(0,0,0 ), 10);

                allObjects[7]->coeff_reflection =  .6 ;
                allObjects[7]->coeff_diff =  .20f ;
                allObjects[7]->coeff_spec = .1;
                allObjects[7]->shininess = 5;
                allObjects[7]->color = ( Color( 1.0f, 0.0f, 0.0f  ) );


                allObjects[8] = new PlanePrim( Vector( 0, 0, 1 ), Vector(0,0,h ), 10);

                allObjects[8]->coeff_reflection =  .6 ;
                allObjects[8]->coeff_diff =  .20f ;
                allObjects[8]->coeff_spec = .1;
                allObjects[8]->shininess = 5;
                allObjects[8]->color = ( Color( 1.0f, 0.0f, 0.0f  ) );


                allObjects[9] = new PlanePrim( Vector( -1, 0, 0 ), Vector(0,0,0 ), 10);

                allObjects[9]->coeff_reflection =  .6 ;
                allObjects[9]->coeff_diff =  .20f ;
                allObjects[9]->coeff_spec = .1;
                allObjects[9]->shininess = 5;
                allObjects[9]->color = ( Color( 1.0f, 0.0f, 0.0f  ) );


                allObjects[10] = new PlanePrim( Vector( 1, 0, 0 ), Vector(h,0,0 ), 10);

                allObjects[10]->coeff_reflection =  .6 ;
                allObjects[10]->coeff_diff =  .20f ;
                allObjects[10]->coeff_spec = .1;
                allObjects[10]->shininess = 5;
                allObjects[10]->color = ( Color( 1.0f, 0.0f, 0.0f  ) );


        //cube







                  allObjects[4] = new PlanePrim( Vector( 0, 0, 1 ), Vector(0,0,0 ));

                  allObjects[4]->coeff_reflection =  0 ;
                  allObjects[4]->coeff_diff =  1.0f ;
                  allObjects[4]->color = ( Color( 1.0f, 1.0f, 1.0f  ) );

                  allObjects[5] = new PlanePrim( Vector( 0, 0, 1 ), Vector(0,20,0 ));

                  allObjects[5]->coeff_reflection =  0 ;
                  allObjects[5]->coeff_diff =  1.0f ;
                  allObjects[5]->color = ( Color( 0.0f, 0.0f, 0.0f ) );*/


        int p=nObjects;
        for(int i=0,m=-5; i<10; i++,m++)
        {
            for(int j=0,n=-5; j<10; j++,n++)
            {
                allObjects[p+i*10+j] = new PlanePrim( Vector( 0, 0, 1 ), Vector(m*30,n*30,0 ), 30);

                allObjects[p+i*10+j]->coeff_reflection =  0 ;
                allObjects[p+i*10+j]->coeff_diff =  1.0f ;
                if (i%2==0 && j%2==0)allObjects[p+i*10+j]->color = ( Color( 0.0f, 0.0f, 0.0f ) );
                else if(i%2==0 && j%2!=0) allObjects[p+i*10+j]->color = ( Color( 1.0f, 1.0f, 1.0f ) );
                else if (i%2!=0 && j%2!=0) allObjects[p+i*10+j]->color = ( Color( 0.0f, 0.0f, 0.0f ) );
                else if(i%2!=0 &&  j%2==0) allObjects[p+i*10+j]->color = ( Color( 1.0f, 1.0f, 1.0f ) );
            }
        }


        // set number of primitives
        nObjects =p+100;
    }

    int GetNrObjects()
    {
        return nObjects;
    }
    Object* GetObject( int a_Idx )
    {
        return allObjects[a_Idx];
    }
private:
    int nObjects;
    Object** allObjects;
} scn;
