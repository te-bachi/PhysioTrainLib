#ifndef __QUATERNION_H__
#define __QUATERNION_H__

class Quaternion;

class Quaternion {
    
    private:
        
    public:
        float         _x;
        float         _y;
        float         _z;
        float         _w;

        
                    Quaternion();
                    Quaternion(float x, float y, float z, float  w);
                    Quaternion(const Quaternion& q);
        virtual     ~Quaternion();

        static Quaternion     diff(const Quaternion &a, const Quaternion &b);
        static float          dot(const Quaternion &q1, const Quaternion &q2);
        
        void                  inverse();
        void                  conjugate();

        Quaternion operator* (const Quaternion &q);
        Quaternion operator/ (const float s);
        
};

#endif
