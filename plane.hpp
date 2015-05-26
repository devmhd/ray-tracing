class Plane : public Object
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
