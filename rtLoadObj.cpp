#include "rtLoadObj.h"

using namespace std;

MTL *mtl = NULL;
OBJ *object = NULL;
FILE *file = NULL;
char aux[50];
int countV = 0;
int countN = 0;

OBJ *loadObj(const char *nameOBJ, const char *nameMTL){

/////////////////////////////////////////////////////////////////////////
    //Abre o arquivo .mtl
    file = fopen(nameMTL, "r");
    if(!file){
        cout << "Arquivo MTL nao pode ser aberto" << endl;
        exit(1);
    }
    mtl = (MTL *)malloc(sizeof(MTL));
    if(!mtl){
        cout << "Problema na alocacao de memoria" << endl;
        exit(1);
    }

    mtl->TotalMTL = 0;
    while(!feof(file)){
        fgets(aux, 50, file);
        if(!strncmp(aux, "newmtl", 6)){
            mtl->TotalMTL++;
        }
    }

    if(mtl->TotalMTL){
        mtl->CO = (COEFICIENTE *)malloc(sizeof(COEFICIENTE)*mtl->TotalMTL);
        if(!mtl->CO){
            cout << "Problema na alocacao dos coeficiates" << endl;
            exit(1);
     }

        rewind(file);
        int i=0;
        while(!feof(file)){
            fgets(aux, 50, file);
            if(!strncmp(aux, "Ka ", 3)){
                cout << aux;
                sscanf(aux, "Ka %f", &mtl->CO[i].Ka);
                cout << "Ka " << mtl->CO[i].Ka << endl;
            }
            if(!strncmp(aux, "Kd %f", 3)){
                cout << aux;
                sscanf(aux, "Kd %f", &mtl->CO[i].Kd);
                cout << "Kd " << mtl->CO[i].Kd << endl;
            }
            if(!strncmp(aux, "Ks ", 3)){
                cout << aux;
                sscanf(aux, "Ks %f", &mtl->CO[i].Ks);
                cout << "Ks " << mtl->CO[i].Ks << endl;
                i++;
            }
            //cout << "Ka " << mtl->CO[i].Ka << " Kd " << mtl->CO[i].Kd << " Ks " << mtl->CO[i].Ks << endl;

        }
    }
    else
        cout << "arquivo mtl sem coeficientes de iluminacao" << endl;

    free(file);

////////////////////////////////////////////////////////////////////////////

    //Abre o arquivo .obj
    file = fopen(nameOBJ, "r");
    if(!file){
        cout << "Arquivo OBJ nao pode ser aberto" << endl;
        exit(1);
    }
    //Aloca espaço para a estrutura OBJ
    object = (OBJ *)malloc(sizeof(OBJ));
    if(!object){
        cout << "Problema de alocacao de memoria" << endl;
        exit(1);
    }

    //Inicializa todos os campos
    object->totalV = 0;
    object->totalN = 0;
    object->totalF = 0;
    object->vertexs = NULL;
    object->normais = NULL;
    object->faces = NULL;
    object->mtl = NULL;
    object->a = (P *)malloc(sizeof(P)*mtl->TotalMTL);
    if(!object->a){
        cout << "Problema na alocacao" << endl;
        exit(1);
    }
    for(int i = 0 ; i < mtl->TotalMTL ; i++)
        object->a[i].f = 0;

    //Varre todo o arquivo .obj em busca do total de
    //vértices, normais e faces
    object->mtl = mtl;
    int i = 0;
    while(!feof(file)){
        fgets(aux, 50, file);
        if(!strncmp(aux, "v ", 2))
            object->totalV++;
        if(!strncmp(aux, "vn ", 3))
            object->totalN++;
        if(!strncmp(aux, "f ", 2))
            object->totalF++;
        if(!strncmp(aux, "usemtl", 6)){
            object->a[i].f = object->totalF;
            cout << object->a[i].f << endl;
            i++;
        }

    }

    cout << "Total Vertice = " << object->totalV << endl;
    cout << "Total Normais = " << object->totalN << endl;
    cout << "Total face = " << object->totalF << endl;

    //Alocamos espaço para  os vértices
    object->vertexs = (VERT *)malloc(sizeof(VERT)*object->totalV);
    if(!object->vertexs){
        cout <<"Problema de alocacao de memoria para os vértices"<< endl;
        exit(1);
    }

    rewind(file);
    //Varre todo o arquivo .obj pegando cada vértice
    while(!feof(file)){
        fgets(aux, 50, file);
        if(!strncmp(aux, "v ", 2)){
            sscanf(aux, "v %f %f %f", &object->vertexs[countV].x, &object->vertexs[countV].y, &object->vertexs[countV].z);
            countV++;
        }
    }

    //Aloca espaço na memoria para as normais
    rewind(file);
    object->normais = (NORMAL *)malloc(sizeof(NORMAL)*object->totalN);
    if(!object->vertexs){
        cout << "Problema de alocacao de memoria para as normais" << endl;
        exit(1);
    }

    //Varre todo o arquivo .obj pegando cada normal
    while(!feof(file)){
        fgets(aux, 50, file);
        if(!strncmp(aux, "vn ", 3)){
            sscanf(aux, "vn %f %f %f", &object->normais[countN].nx, &object->normais[countN].ny, &object->normais[countN].nz);
            countN++;
        }
    }

    rewind(file);
    countV=0;
    countN=0;
    int a;  //Apenas auxiliar
    object->faces = (FACE *)malloc(sizeof(FACE)*object->totalF);
    if(!object->faces){
        cout<<"Problema de alocacao de memoria para as faces"<< endl;
        exit(1);
    }

    int check =0;
    while(!feof(file)){
        fgets(aux, 50, file);
        if(!strncmp(aux, "f ", 2)){
            check = sscanf(aux, "f %d/%d/%d %d/%d/%d %d/%d/%d", &object->faces[countV].v1,&a,&object->faces[countV].n1,
                                                                &object->faces[countV].v2,&a,&object->faces[countV].n2,
                                                                &object->faces[countV].v3,&a,&object->faces[countV].n3);
            countV++;
        }
    }

    rewind(file);
    countV=0;
    countN=0;
    //Neste caso o objeto não possui coordenadas de textura
    if(check != 9){
        while(!feof(file)){
            fgets(aux, 50, file);
            if(!strncmp(aux, "f ", 2)){
                check = sscanf(aux, "f %d//%d %d//%d %d//%d", &object->faces[countV].v1,&object->faces[countV].n1,
                                                              &object->faces[countV].v2,&object->faces[countV].n2,
                                                              &object->faces[countV].v3,&object->faces[countV].n3);
                countV++;
            }
        }
    }

    cout << "Objeto carregado" << endl;

    return object;
}
