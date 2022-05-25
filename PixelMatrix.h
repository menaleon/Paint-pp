
#ifndef PRUEBABMP_PIXELMATRIX_H
#define PRUEBABMP_PIXELMATRIX_H
#include "Pixel.h"

class PixelMatrix {
private:
    int matrixHeight;
    int matrixWidth;
    Pixel** pPixelMatrix;
public:
    PixelMatrix(int h, int w){
        h = matrixHeight;
        w = matrixWidth;
        pPixelMatrix = (Pixel**) malloc(h*w*sizeof (Pixel*));
    }

    ~PixelMatrix(){
        free (pPixelMatrix);
    }

    Pixel getPixel(int x, int y){
        Pixel p = pPixelMatrix[x][y];
        return p;
    }
    void setPixel(int x, int y, Pixel p){
        pPixelMatrix[x][y] = p;
    }

};

#endif //PRUEBABMP_PIXELMATRIX_H
