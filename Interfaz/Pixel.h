#ifndef PIXEL_H
#define PIXEL_H

#include <cstdint>

class Pixel {

private:
    uint8_t R=0;
    uint8_t G=0;
    uint8_t B=0;
    uint8_t A=0;

public:
    Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha){
        R=red;
        G=green;
        B=blue;
        A=alpha;
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

    void setR(int red){
            R = red;
        }
    void setG(int green){
            G = green;
        }
    void setB(int blue){
            B = blue;
        }
    void setA(int alpha){
            A = alpha;
        }

    /*
    int* getRGBA(){
        int arrayRGBA[4]={R,G,B,A};
        return arrayRGBA;
    }
     */
};

#endif // PIXEL_H
