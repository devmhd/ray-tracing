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

    Primitive() : m_Name( 0 ), m_Light( false ) {};

    virtual int GetType() = 0;
    virtual int Intersect( Ray& a_Ray, float& a_Dist ) = 0;
    virtual Vector GetNormal( Vector& a_Pos ) = 0;
    virtual Color GetColor( Vector& )
    {
        return m_Color;
    }
    virtual void Light( bool a_Light )
    {
        m_Light = a_Light;
    }
    bool IsLight()
    {
        return m_Light;
    }
    void SetName( char* a_Name )
    {
        delete m_Name;
        m_Name = new char[strlen( a_Name ) + 1];
        strcpy( m_Name, a_Name );
    }
    char* GetName()
    {
        return m_Name;
    }

    void SetColor( Color a_Color )
    {
        m_Color = a_Color;
    }
    Color GetColor()
    {
        return m_Color;
    }
    void SetAmbient( float a_Amb )
    {
        m_Amb= a_Amb;
    }
    void SetDiffuse( float a_Diff )
    {
        m_Diff = a_Diff;
    }
    void SetSpecular( float a_Spc )
    {
        m_Spc = a_Spc;
    }
    void SetReflection( float a_Refl )
    {
        m_Refl = a_Refl;
    }
    void SetShininess(float a_shine)
    {
        m_shine=a_shine;
    }
    float GetSpecular()
    {
        return  m_Spc;
    }
    float GetDiffuse()
    {
        return m_Diff;
    }
    float GetAmbient(  )
    {
        return m_Amb;
    }
    float GetReflection()
    {
        return m_Refl;
    }
    float GetShininess()
    {
        return m_shine;
    }
    void SetRefraction( float a_Refr )
    {
        m_Refr = a_Refr;
    }

    float GetRefraction()
    {
        return m_Refr;
    }
    void SetRefrIndex( float a_Refr )
    {
        m_RIndex = a_Refr;
    }
    float GetRefrIndex()
    {
        return m_RIndex;
    }

protected:

    char* m_Name;
    bool m_Light;

    Color m_Color;
    float m_Refl,m_Refr,m_RIndex;
    float m_Diff, m_Amb, m_Spc,m_shine;
};

