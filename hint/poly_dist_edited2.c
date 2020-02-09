#include <stdio.h>
#include <math.h>

struct PolyStruct {
    double d2;
    double d1;
    double d0;
} PolyDefault = {0.0, 0.0, 0.0};

typedef struct PolyStruct Poly;

Poly xs, ys, xp, yp;
Poly xsp, ysp;
Poly pxsp, pysp;
Poly ppxysp;

void printPoly (char var[], Poly p) {
    printf("%s = ", var);
    if(p.d2 != 0) printf("%+.0lft^2", p.d2);
    if(p.d1 != 0) printf("%+.0lft", p.d1);
    if(p.d0 != 0) printf("%+.0lf", p.d0);
    printf("\n");
}

int main () {

    double xs1, ys1, xs2, ys2;
    double xp1, yp1, xp2, yp2;
    double min, max;
    double spp;

    scanf("%lf%lf%lf%lf", &xs1, &ys1, &xs2, &ys2); 
    scanf("%lf%lf%lf%lf", &xp1, &yp1, &xp2, &yp2); 

    // xs = (1-t) * xs1 + xs2 * (t)
    // xs = xs1  - xs1 * (t) + xs2 * (t)
    // xs = {0, xs2 - xs1, xs1}
    xs.d2 = 0;
    xs.d1 = xs2 - xs1;
    xs.d0 = xs1;

    printPoly("xs", xs);

    // ys = (1-t) * ys1 + ys2 * (t)
    // ys = ys1  - ys1 * (t) + ys2 * (t)
    // ys = {0, ys2 - ys1, ys1}
    ys.d2 = 0;
    ys.d1 = ys2 - ys1;
    ys.d0 = ys1;

    printPoly("ys", ys);

    // xp = (1-t) * xp1 + xp2 * (t)
    // xp = xp1  - xp1 * (t) + xp2 * (t)
    // xp = {0, xp2 - xp1, xp1}
    xp.d2 = 0;
    xp.d1 = xp2 - xp1;
    xp.d0 = xp1;

    printPoly("xp", xp);

    // yp = (1-t) * yp1 + yp2 * (t)
    // yp = yp1  - yp1 * (t) + yp2 * (t)
    // yp = {0, yp2 - yp1, yp1}
    yp.d2 = 0;
    yp.d1 = yp2 - yp1;
    yp.d0 = yp1;

    printPoly("yp", yp);

    // xsp = xs - xp
    xsp.d2 = xs.d2 - xp.d2;
    xsp.d1 = xs.d1 - xp.d1;
    xsp.d0 = xs.d0 - xp.d0;

    printPoly("xsp", xsp);

    // ysp = ys - yp
    ysp.d2 = ys.d2 - yp.d2;
    ysp.d1 = ys.d1 - yp.d1;
    ysp.d0 = ys.d0 - yp.d0;

    printPoly("ysp", ysp);
    
    // pxsp = xsp * xsp
    pxsp.d2 += xsp.d1 * xsp.d1;
    pxsp.d1 += xsp.d1 * xsp.d0;
    pxsp.d1 += xsp.d0 * xsp.d1;
    pxsp.d0 += xsp.d0 * xsp.d0;

    printPoly("pxsp", pxsp);

    // pysp = ysp * ysp

    pysp.d2 += ysp.d1 * ysp.d1;
    pysp.d1 += ysp.d1 * ysp.d0;
    pysp.d1 += ysp.d0 * ysp.d1;
    pysp.d0 += ysp.d0 * ysp.d0;

    printPoly("pysp", pysp);

    // sqrt( (xsp * xsp) + (ysp * ysp) ) <= 10
    // (xsp * xsp) + (ysp * ysp) <= 100
    // (pxsp) + (pysp) <= 100

    ppxysp.d2 = pxsp.d2 + pysp.d2;
    ppxysp.d1 = pxsp.d1 + pysp.d1;
    ppxysp.d0 = pxsp.d0 + pysp.d0;

    printPoly("ppxysp", ppxysp);

    // (pxsp) + (pysp) - 100 <= 0

    ppxysp.d0 = ppxysp.d0 - 100;

    printPoly("ppxysp", ppxysp);

    // (b * b - 4 * a * c) > 0

    spp = ppxysp.d1 * ppxysp.d1 - 4 * ppxysp.d2 * ppxysp.d0;

    if (spp >= 0) {
        
        // min = (- b - sqrt( b * b - 4 a c ) ) / (2 a)
        // min = (- ppxysp.d1 - sqrt( ppxysp.d1 * ppxysp.d1 - 4 * ppxysp.d2 * ppxysp.d0 ) ) / ( 2 * ppxysp.d2 )

        min = ( 0 - ppxysp.d1 - sqrt( spp ) ) / ( 2 * ppxysp.d2 );

        // max = (- b + sqrt( b * b - 4 a c ) ) / (2 a)
        // max = (- ppxysp.d1 + sqrt( ppxysp.d1 * ppxysp.d1 - 4 * ppxysp.d2 * ppxysp.d0 ) ) / ( 2 * ppxysp.d2 )

        max = ( 0 - ppxysp.d1 + sqrt( spp ) ) / ( 2 * ppxysp.d2 );

        printf("min = %lf\n", min);
        printf("max = %lf\n", max);

        if(max >= 0 && min <= 1) {
            printf("yes\n");
        }else{
            printf("no\n");
        }

    }else{
        printf("error\n");
    }

    return 0;
}