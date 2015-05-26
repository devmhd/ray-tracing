#include "Ray.hpp"





/*
class Object
{
public:



    int type;

    Color color;
    float reflection, diffuse, ambient, specular, shininess;
    bool isLight;


    Object(){};


    virtual int intersect( Ray& ray, float& distance ) = 0;
    virtual Vector getNormal( Vector& position ) = 0;




};

*/



class Primitive
{
public:
    static const int SPHERE = 1;
    static const int PLANE = 0;

    static const int HIT	=	 1;
    static const int MISS  =	 0;
    static const int INSIDE_OBJ = -1;

    bool isLight;
    int type;
    Color color;
    float coeff_reflection, coeff_diff, coeff_amb, coeff_spec,shininess;

    Primitive() {
        isLight = false;
    }

   
    virtual int intersect( Ray& a_Ray, float& a_Dist ) = 0;
    virtual Vector getNormal( Vector& a_Pos ) = 0;


};

