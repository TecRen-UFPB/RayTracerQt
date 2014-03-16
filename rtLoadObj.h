#ifndef RTLOADOBJ_H
#define RTLOADOBJ_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    float Ka, Kd, Ks;
}COEFICIENTE;

typedef struct{
    int TotalMTL;
    COEFICIENTE *CO;
}MTL;

typedef struct {
    float x,y,z;
}VERT;

typedef struct{
    float nx,ny,nz;
}NORMAL;

typedef struct{
    int nv;
    int v1, v2, v3;
    int n1, n2, n3;
}FACE;

typedef struct{
   int f;
}P;

typedef struct{
    int totalV;
    int totalF;
    int totalN;
    P *a;
    VERT *vertexs;
    NORMAL *normais;
    FACE *faces;
    MTL *mtl;
}OBJ;

OBJ *loadObj(const char *, const char *);

#endif // RTLOADOBJ_H
