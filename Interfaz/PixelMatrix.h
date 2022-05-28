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
       free (&pPixelMatrix); // le puse el & porque me daba error antes
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

    void applySepiaFilter(){

        for(int i =0;i<matrixWidth;i++){
            for(int j=0;j<matrixHeight;j++){

                Pixel p = getPixel(i,j);
                int R = p.getR();
                int G = p.getG();
                int B = p.getB();

                int new_R = 0.393*R + 0.769*G + 0.189*B;
                int new_G = 0.349*R + 0.686*G + 0.168*B;
                int new_B = 0.272*R + 0.534*G + 0.131*B;

                if(new_R > 255){new_R = 255;}
                if(new_G >255){new_G = 255;}
                if(new_B >255){new_B = 255;}


                Pixel* pSepia = new Pixel(new_R,new_G,new_B,255);
                setPixel(i,j, *pSepia);

            }
        }
    }

    void applyDarkerFilter(){
        for(int i =0;i<matrixWidth;i++){
            for(int j=0;j<matrixHeight;j++){

                Pixel p = getPixel(i,j);
                int R = p.getR();
                int G = p.getG();
                int B = p.getB();

                int new_R = R - 3;
                int new_G = G - 3;
                int new_B = B - 3;

                if(new_R < 0){new_R = 0;}
                if(new_G < 0){new_G = 0;}
                if(new_B < 0){new_B = 0;}


                Pixel* pDarker = new Pixel(new_R,new_G,new_B,255);
                setPixel(i,j, *pDarker);

            }
        }

    }



    void drawWithLapiz(int x, int y, int grosor, int colorR, int colorB, int colorG){
        for(int i =0;i<matrixWidth;i++){
            for(int j=0;j<matrixHeight;j++){
                if(i==x && j==y){
                    int newR = colorR;
                    int newG = colorG;
                    int newB = colorB;
                    Pixel* newPix = new Pixel(newR,newG,newB,255);
                    setPixel(i,j, *newPix);

                }
            }
        }

    }

    int getWidth(){
        return this->matrixWidth;
    }

    int getHeight(){
        return this->matrixHeight;
    }

};
#endif // PIXELMATRIX_H
