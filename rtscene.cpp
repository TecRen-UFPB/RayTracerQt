#include "rtscene.h"
#include "rtfilm.h"
#include "rtraytracer.h"
#include "rtlight.h"

RTScene::RTScene()
{
}

RTScene::RTScene(RTCamera cam, std::vector<RTObject*> &primitives, int maxDepth)
{
    this->cam=cam;
    this->primitives=primitives;
    this->maxDepth=maxDepth;
    hasFog=false;
}

RTScene::RTScene(RTCamera cam, std::vector<RTObject*> &primitives, int maxDepth,double z_start,double z_end,RTColor fogColor)
    :fog(z_start,z_end,fogColor)
{
    this->cam=cam;
    this->primitives=primitives;
    this->maxDepth=maxDepth;
    hasFog=true;
}




void RTScene::render(int samples){

    int w=RTFilm::getInstance()->getWidth();
    int h=RTFilm::getInstance()->getHeight();

    RTRayTracer raytracer;
    raytracer.setScene(*this);

    // TODO parameterize the light source.
    double ia = 1.0, ip = 1.0;
    RTColor light_color(255,255,255);
    RTPoint light_pos(200,200,300); //300,200,300
    RTLight light(light_pos, ia, ip, light_color);

    #pragma omp parallel for
    for(int i=0;i<w;i++){
      #pragma omp parallel for
        for(int j=0;j<h;j++){

            int count = 1;
            double sr=0.0, sg=0.0, sb=0.0;

            RTRay ray;
            RTColor color;

            srand (time(NULL));
            double offseti = 0, offsetj = 0;

            do {
                ray =  cam.generateRay(i, j, offseti, offsetj);
                color = raytracer.traceRay(ray, 1, light);

                sr += color.getR();
                sg += color.getG();
                sb += color.getB();

                offseti = rand()/float(RAND_MAX+1);
                offsetj = rand()/float(RAND_MAX+1);
            } while(count++ < samples);

            // mean
            sr = sr/count;
            sg = sg/count;
            sb = sb/count;

            color = RTColor(sr, sg, sb);

            RTFilm::getInstance()->commit(i, j, color);
        }
    }




}
RTCamera RTScene::getCam() const
{
    return cam;
}

void RTScene::setCam(const RTCamera &value)
{
    cam = value;
}
std::vector<RTObject *> RTScene::getPrimitives() const
{
    return primitives;
}

void RTScene::setPrimitives(const std::vector<RTObject *> &value)
{
    primitives = value;
}
int RTScene::getMaxDepth() const
{
    return maxDepth;
}

void RTScene::setMaxDepth(int value)
{
    maxDepth = value;
}
bool RTScene::getHasFog() const
{
    return hasFog;
}

void RTScene::setHasFog(bool value)
{
    hasFog = value;
}
RTFog RTScene::getFog() const
{
    return fog;
}

void RTScene::setFog(const RTFog &value)
{
    fog = value;
}





