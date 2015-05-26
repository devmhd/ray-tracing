/*class Plane : public Object
{
public:

   Vector normal, position;
   float armlegth;
    Plane( const Vector& _normal, const Vector& _position, float _armlegth ){

        normal = _normal;
        position = _position;
        armlegth = _armlegth;
    };




    int intersect( Ray& ray, float& distance )
    {
        Vector intersectPoint;

        float d = normal.dot(ray.direction);
        if (d != 0)
        {
            float dist = (- normal.dot(ray.origin) + normal.dot(position)) / d;
            if (dist > 0)
            {
                intersectPoint = ray.origin + ray.direction * dist;

                if(intersectPoint.x>=position.x-1 && intersectPoint.x<=position.x+armlegth && intersectPoint.y>=position.y-1 && intersectPoint.y<=position.y+armlegth &&
                        intersectPoint.z>=position.z-1 && intersectPoint.z<=position.z+armlegth)
                {
                    if (dist < distance)
                    {
                        distance = dist;
                        return HIT;
                    }
                }

            }
        }
        return NOHIT;
    }


    Vector getNormal( Vector& position )
    {
        return normal;
    }

    Vector getNormal()
    {
        return normal;
    }
};
*/


class PlanePrim : public Primitive
{
public:

    Vector N,D;
    int GetType()
    {
        return PLANE;
    }
    PlanePrim( const Vector& a_Normal, const Vector& a_D ) : N(a_Normal), D(a_D ) {};
    Vector& getNormal()
    {
        return N;
    }
    Vector& GetD()
    {
        return D;
    }
    int intersect( Ray& a_Ray, float& a_Dist )
    {
        Vector pi;
        float h=30;
        float d = N.dot(a_Ray.direction) ;
        if (d != 0)
        {
            float dist = (-( N.dot( a_Ray.origin)) + N.dot(D)) / d;
            if (dist > 0)
            {
                pi = a_Ray.origin + a_Ray.direction * dist;

                if(pi.x>=D.x-1 && pi.x<=D.x+h && pi.y>=D.y-1 && pi.y<=D.y+h &&
                        pi.z>=D.z-1 && pi.z<=D.z+h)
                {
                    if (dist < a_Dist)
                    {
                        a_Dist = dist;
                        return HIT;
                    }
                }

            }
        }
        return MISS;
    }


    Vector getNormal( Vector& a_Pos )
    {
        return N;
    }


};
