#include "Ray.hpp"


class Object
{
public:
    static const int SPHERE = 1;
    static const int PLANE = 0;

    static const int HIT = 0;
    static const int NOHIT = 1;
    static const int INSIDE_OBJECT = 2;


    int type;

    Color color;
    float reflection, diffuse, ambient, specular, shininess;
    bool isLight;


    Object(){};


    virtual int intersect( Ray& ray, float& distance ) = 0;
    virtual Vector getNormal( Vector& position ) = 0;




};
