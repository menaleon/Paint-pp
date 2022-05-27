#ifndef PIXELMATRIX_H
#define PIXELMATRIX_H

#include "Pixel.h"
#include <stdlib.h>

class PixelMatrix {
private:
    int matrixHeight;
    int matrixWidth;
    Pixel* pPixelMatrix;
public:
    PixelMatrix(int h, int w){
        matrixHeight = h;
        matrixWidth = w;
        pPixelMatrix =(Pixel*) malloc(h*w*sizeof (Pixel));
        for(int i =0;i<matrixWidth;i++){
            for(int j=0;j<matrixHeight;j++){
                Pixel* p = new Pixel(255,0,0,255);
                setPixel(i,j, *p);
            }
        }
    }

    ~PixelMatrix(){
       free (pPixelMatrix);
    }

    Pixel getPixel(int x, int y){
        Pixel p = pPixelMatrix[matrixWidth*x+y];
        return p;
    }
    void setPixel(int x, int y, Pixel p){
        pPixelMatrix[matrixWidth*x+y].setR(p.getR());
        pPixelMatrix[matrixWidth*x+y].setG(p.getG());
        pPixelMatrix[matrixWidth*x+y].setB(p.getB());
        pPixelMatrix[matrixWidth*x+y].setA(p.getA());
    }

    void applyGrayFilter(){
            for(int i =0;i<matrixWidth;i++){
                for(int j=0;j<matrixHeight;j++){
                    Pixel p = getPixel(i,j);
                    int R = p.getR();
                    int G = p.getG();
                    int B = p.getB();
                    int gray = (R+G+B)/3;
                    Pixel* pGray = new Pixel(gray,gray,gray,255);
                    setPixel(i,j, *pGray);
                }
            }
        }
    void applyNegativeFilter(){
            for(int i =0;i<matrixWidth;i++){
                for(int j=0;j<matrixHeight;j++){
                    Pixel p = getPixel(i,j);
                    int R=p.getR();
                    int negativeR = 255-R;
                    int G = p.getG();
                    int negativeG = 255-G;
                    int B = p.getB();
                    int negativeB = 255-B;
                    Pixel* pNegative = new Pixel(negativeR,negativeG,negativeB,255);
                    setPixel(i,j, *pNegative);
                }
            }
        }

};

#endif //PRUEBABMP_PIXELMATRIX_H
