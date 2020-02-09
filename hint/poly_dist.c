#include <stdio.h>
#include <math.h>

struct PolyStruct {
    double d2;
    double d1;
    double d0;
} PolyDefault = {0.0, 0.0, 0.0};

typedef struct PolyStruct Poly;

Poly xs, ys, xr, yr;
Poly xsr, ysr;
Poly pxsr, pysr;
Poly ppxysr;

void printPoly (char var[], Poly p) {
    printf("%s = ", var);
    if(p.d2 != 0) printf("%+.0lft^2", p.d2);
    if(p.d1 != 0) printf("%+.0lft", p.d1);
    if(p.d0 != 0) printf("%+.0lf", p.d0);
    printf("\n");
}

int main () {

    double sx1, sy1, sx2, sy2;
    double px1, py1, px2, py2;
    double min, max;
    double spp;

    scanf("%lf%lf%lf%lf", &sx1, &sy1, &sx2, &sy2); 
    scanf("%lf%lf%lf%lf", &px1, &py1, &px2, &py2); 

    // xs = (1-t) * sx1 + sx2 * (t)
    // xs = sx1  - sx1 * (t) + sx2 * (t)
    // xs = {0, sx2 - sx1, sx1}
    xs.d2 = 0;
    xs.d1 = sx2 - sx1;
    xs.d0 = sx1;

    printPoly("xs", xs);

    // ys = (1-t) * sy1 + sy2 * (t)
    // ys = sy1  - sy1 * (t) + sy2 * (t)
    // ys = {0, sy2 - sy1, sy1}
    ys.d2 = 0;
    ys.d1 = sy2 - sy1;
    ys.d0 = sy1;

    printPoly("ys", ys);

    // xr = (1-t) * px1 + px2 * (t)
    // xr = px1  - px1 * (t) + px2 * (t)
    // xr = {0, px2 - px1, px1}
    xr.d2 = 0;
    xr.d1 = px2 - px1;
    xr.d0 = px1;

    printf("xr = ");
    if(xr.d2 != 0) printf("%+.0lft^2", xr.d2);
    if(xr.d1 != 0) printf("%+.0lft", xr.d1);
    if(xr.d0 != 0) printf("%+.0lf", xr.d0);
    printf("\n");

    // yr = (1-t) * py1 + py2 * (t)
    // yr = py1  - py1 * (t) + py2 * (t)
    // yr = {0, py2 - py1, py1}
    yr.d2 = 0;
    yr.d1 = py2 - py1;
    yr.d0 = py1;

    printPoly("yr", yr);

    // xsr = xs - xr
    xsr.d2 = xs.d2 - xr.d2;
    xsr.d1 = xs.d1 - xr.d1;
    xsr.d0 = xs.d0 - xr.d0;

    printPoly("xsr", xsr);

    // ysr = ys - yr
    ysr.d2 = ys.d2 - yr.d2;
    ysr.d1 = ys.d1 - yr.d1;
    ysr.d0 = ys.d0 - yr.d0;

    printPoly("ysr", ysr);
    
    // pxsr = xsr * xsr
    pxsr.d2 += xsr.d1 * xsr.d1;
    pxsr.d1 += xsr.d1 * xsr.d0;
    pxsr.d1 += xsr.d0 * xsr.d1;
    pxsr.d0 += xsr.d0 * xsr.d0;

    printPoly("pxsr", pxsr);

    // pysr = ysr * ysr

    pysr.d2 += ysr.d1 * ysr.d1;
    pysr.d1 += ysr.d1 * ysr.d0;
    pysr.d1 += ysr.d0 * ysr.d1;
    pysr.d0 += ysr.d0 * ysr.d0;

    printPoly("pysr", pysr);

    // sqrt( (xsr * xsr) + (ysr * ysr) ) <= 10
    // (xsr * xsr) + (ysr * ysr) <= 100
    // (pxsr) + (pysr) <= 100

    ppxysr.d2 = pxsr.d2 + pysr.d2;
    ppxysr.d1 = pxsr.d1 + pysr.d1;
    ppxysr.d0 = pxsr.d0 + pysr.d0;

    printPoly("ppxysr", ppxysr);

    // (pxsr) + (pysr) - 100 <= 0

    ppxysr.d0 = ppxysr.d0 - 100;

    printPoly("ppxysr", ppxysr);

    // (b * b - 4 * a * c) > 0

    spp = ppxysr.d1 * ppxysr.d1 - 4 * ppxysr.d2 * ppxysr.d0;

    if (spp >= 0) {
        
        // min = (- b - sqrt( b * b - 4 a c ) ) / (2 a)
        // min = (- ppxysr.d1 - sqrt( ppxysr.d1 * ppxysr.d1 - 4 * ppxysr.d2 * ppxysr.d0 ) ) / ( 2 * ppxysr.d2 )

        min = ( 0 - ppxysr.d1 - sqrt( spp ) ) / ( 2 * ppxysr.d2 );

        // max = (- b + sqrt( b * b - 4 a c ) ) / (2 a)
        // max = (- ppxysr.d1 + sqrt( ppxysr.d1 * ppxysr.d1 - 4 * ppxysr.d2 * ppxysr.d0 ) ) / ( 2 * ppxysr.d2 )

        max = ( 0 - ppxysr.d1 + sqrt( spp ) ) / ( 2 * ppxysr.d2 );

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