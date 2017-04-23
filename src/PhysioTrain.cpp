

#ifndef ARDUINO

#include <stdio.h>

#include "Quaternion.h"

void
print_q(const char *str, Quaternion &q)
{
    printf("%s = %0.4f %0.4f %0.4f %0.4f\n", str, q.getW(), q.getX(), q.getY(), q.getZ());
}

void
print_rot(const char *str, RotationMatrix &rot)
{
    printf("%s = [\n", str);
    printf("  %8.4f %8.4f %8.4f\n", rot.getElement(0, 0), rot.getElement(0, 1), rot.getElement(0, 2));
    printf("  %8.4f %8.4f %8.4f\n", rot.getElement(1, 0), rot.getElement(1, 1), rot.getElement(1, 2));
    printf("  %8.4f %8.4f %8.4f\n", rot.getElement(2, 0), rot.getElement(2, 1), rot.getElement(2, 2));
    printf("]\n");
}

int
main(int argc, char *argv[])
{
    Quaternion q1 = Quaternion(   1.0f,    0.0f,    0.0f,    0.0f);
    Quaternion q2 = Quaternion(   0.0f, 0.7071f,    0.0f, 0.7071f);
    Quaternion q3 = Quaternion(0.7071f, 0.7071f,    0.0f,    0.0f);
    Quaternion q4 = q2 * q3;
    Quaternion q5 = q2;
    q5.inverse();

    print_q("q4", q4);
    print_q("q5", q5);

    RotationMatrix rot4 = q4.getRotationMatrix();
    RotationMatrix rot5 = q5.getRotationMatrix();

    print_rot("rot4", rot4);
    print_rot("rot5", rot5);
    
    return 0;
}

#endif

