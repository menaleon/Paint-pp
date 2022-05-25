
#ifndef PRUEBABMP_PIXEL_H
#define PRUEBABMP_PIXEL_H


#include <cstdint>

class Pixel {

private:
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
public:

    Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha){
        red=R;
        green=G;
        blue=B;
        alpha=A;
    }
    int getR(){
        return R;
    }
    int getG(){
        return G;
    }
    int getB(){
        return B;
    }
    int getA(){
        return A;
    }
    /*
    int* getRGBA(){
        int arrayRGBA[4]={R,G,B,A};
        return arrayRGBA;
    }
     */
};


#endif //PRUEBABMP_PIXEL_H
