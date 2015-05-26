/*
class Sphere : public Object
{
public:

    Vector center;
    float sqRadius, radius, rRadius;

    Sphere( const Vector& a_Centre, float a_Radius ){

        center = a_Centre;
        sqRadius =a_Radius * a_Radius;
        radius = a_Radius;
        rRadius = 1.0f / a_Radius;

        type = SPHERE;

        }


    int intersect( Ray& ray, float& distance )
    {
        Vector v = ray.origin - center;
        float b = - v.dot(ray.direction);
        float det = (b * b) - v.dot(v) + sqRadius;


        int retval = NOHIT;

        if (det > 0)
        {
            det = sqrtf( det );
            float i1 = b - det;
            float i2 = b + det;
            if (i2 > 0)
            {
                if (i1 < 0)
                {
                    if (i2 < distance)
                    {
                        distance = i2;
                        retval = INSIDE_OBJECT;
                    }
                }
                else
                {
                    if (i1 < distance)
                    {
                        distance = i1;
                        retval = HIT;
                    }
                }
            }
        }
        return retval;
    }

    Vector getNormal( Vector& position )
    {
        return (position - center) * rRadius;
    }


};

*/


class Sphere : public Primitive
{
public:
    int GetType()
    {
        return SPHERE;
    }
    Sphere( const Vector& a_Centre, float a_Radius ) :
        m_Centre( a_Centre ), m_SqRadius( a_Radius * a_Radius ),
        m_Radius( a_Radius ), m_RRadius( 1.0f / a_Radius ) {}
    Vector& GetCentre()
    {
        return m_Centre;
    }
    float GetSqRadius()
    {
        return m_SqRadius;
    }
    int intersect( Ray& a_Ray, float& a_Dist )
    {
        Vector v = a_Ray.origin - m_Centre;
        float b = -v.dot( a_Ray.direction );
        float det = (b * b) - v.dot(v) + m_SqRadius;
        int retval = MISS;
        if (det > 0)
        {
            det = sqrtf( det );
            float i1 = b - det;
            float i2 = b + det;
            if (i2 > 0)
            {
                if (i1 < 0)
                {
                    if (i2 < a_Dist)
                    {
                        a_Dist = i2;
                        retval = INSIDE_OBJ;
                    }
                }
                else
                {
                    if (i1 < a_Dist)
                    {
                        a_Dist = i1;
                        retval = HIT;
                    }
                }
            }
        }
        return retval;
    }

    Vector getNormal( Vector& a_Pos )
    {
        return (a_Pos - m_Centre) * m_RRadius;
    }
private:
    Vector m_Centre;
    float m_SqRadius, m_Radius, m_RRadius;
};


