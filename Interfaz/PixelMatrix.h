#ifndef PIXELMATRIX_H
#define PIXELMATRIX_H

#include "Pixel.h"
#include <stdlib.h>
#include <math.h>

class PixelMatrix {

private:
    int matrixHeight;
    int matrixWidth;
    Pixel* pPixelMatrix;

public:

PixelMatrix(int w, int h){
   matrixWidth = w;
   matrixHeight = h;
   pPixelMatrix =(Pixel*) malloc(w*h*sizeof(Pixel));
   for(int i=0;i<matrixHeight;i++){
     for(int j=0;j<matrixWidth;j++){
         Pixel* p = new Pixel(255,255,255,255);
         setPixel(j,i,*p);
     }
   }
}

~PixelMatrix(){
       free (&pPixelMatrix); // le puse el & porque me daba error antes
    }

PixelMatrix* clone(){
    PixelMatrix *pNew = new PixelMatrix(this->getWidth(), this->getHeight());
    for(int i=0;i<pNew->getHeight();i++){
      for(int j=0;j<pNew->getWidth();j++){
          Pixel p = this->getPixel(j,i);
          pNew->setPixel(j,i,p);
      }
    }
    return pNew;
}

PixelMatrix* rotate90(){
    PixelMatrix *pNew = new PixelMatrix(this->getHeight(),this->getWidth());
    for(int i=0;i<pNew->getHeight();i++){
      for(int j=0;j<pNew->getWidth();j++){
          Pixel p = this->getPixel(i,j);
          pNew->setPixel(pNew->getWidth()-j-1,i,p);
      }
    }
    return pNew;
}

PixelMatrix* flipX(){
    PixelMatrix *pNew = new PixelMatrix(this->getWidth(),this->getHeight());
    for(int i=0;i<pNew->getHeight();i++){
      for(int j=0;j<pNew->getWidth();j++){
          Pixel p = this->getPixel(j,i);
          pNew->setPixel(pNew->getWidth()-j-1,i,p);
      }
    }
    return pNew;
}

PixelMatrix* flipY(){
    PixelMatrix *pNew = new PixelMatrix(this->getWidth(),this->getHeight());
    for(int i=0;i<pNew->getHeight();i++){
      for(int j=0;j<pNew->getWidth();j++){
          Pixel p = this->getPixel(j,i);
          pNew->setPixel(j,pNew->getHeight()-i-1,p);
      }
    }
    return pNew;
}

PixelMatrix* zoom(){
    PixelMatrix *pNew = new PixelMatrix(this->getWidth()*2, this->getHeight()*2);
    for(int i=0;i<this->getHeight();i++){
      for(int j=0;j<this->getWidth();j++){
          Pixel p = this->getPixel(j,i);
          pNew->setPixel(2*j,2*i,p);
          pNew->setPixel(2*j,2*i+1,p);
          pNew->setPixel(2*j+1,2*i,p);
          pNew->setPixel(2*j+1,2*i+1,p);
      }
    }
    return pNew;
}


    Pixel getPixel(int x, int y){
        Pixel p = pPixelMatrix[matrixWidth*y+x];
        return p;
    }

    void setPixel(int x, int y, Pixel p){
        pPixelMatrix[matrixWidth*y+x].setR(p.getR());
        pPixelMatrix[matrixWidth*y+x].setG(p.getG());
        pPixelMatrix[matrixWidth*y+x].setB(p.getB());
        pPixelMatrix[matrixWidth*y+x].setA(p.getA());
    }

    void setPixelFill (int x, int y, Pixel p, Pixel base){
        if (x<0 || x>matrixWidth || y<0 || y>matrixHeight){
            return;
        }
        Pixel pixelActual = getPixel(x,y);
        if (pixelActual.getR() == base.getR() && pixelActual.getG() == base.getG() &&
            pixelActual.getB() == base.getB() && pixelActual.getA() == base.getA()){
            setPixel(x, y, p);
            setPixelFill(x-1,y,p,base);
            setPixelFill(x+1,y,p,base);
            setPixelFill(x,y-1,p,base);
            setPixelFill(x-1,y-1,p,base);
            setPixelFill(x+1,y-1,p,base);
            setPixelFill(x,y+1,p,base);
            setPixelFill(x-1,y+1,p,base);
            setPixelFill(x+1,y+1,p,base);
        }
    }

    void drawCircle(int x1, int y1, int r, Pixel p){
        for(int i=0; i<r; i++){
            int y = (int)sqrt(pow(r,2)-pow(i,2));
            setPixel(x1+i, y1+y, p);
            setPixel(x1+i, y1-y, p);
            setPixel(x1-i, y1+y, p);
            setPixel(x1-i, y1-y, p);
            setPixel(x1+y, y1+i, p);
            setPixel(x1+y, y1-i, p);
            setPixel(x1-y, y1+i, p);
            setPixel(x1-y, y1-i, p);
        }
    }

    void drawLine(int x1, int y1, int x2, int y2, Pixel p){
        if (abs(x2-x1)>abs(y2-y1)){
            if (x2>x1){
                for(int i=x1; i<x2; i++){
                    float m = (y2*1.0-y1)/(x2-x1);
                    setPixel(i, y1 + m*(i-x1), p);
                    setPixel(i+1, y1 + m*(i-x1), p);
                    setPixel(i-1, y1 + m*(i-x1), p);
                    setPixel(i, y1 + m*(i-x1)-1, p);
                    setPixel(i-1, y1 + m*(i-x1)-1, p);
                    setPixel(i+1, y1 + m*(i-x1)-1, p);
                    setPixel(i, y1 + m*(i-x1)+1, p);
                    setPixel(i-1, y1 + m*(i-x1)+1, p);
                    setPixel(i+1, y1 + m*(i-x1)+1, p);
                }
            }
            else
            {
                for(int i=x2; i<x1; i++){
                    float m = (y2*1.0-y1)/(x2-x1);
                    setPixel(i, y1 + m*(i-x1), p);
                    setPixel(i+1, y1 + m*(i-x1), p);
                    setPixel(i-1, y1 + m*(i-x1), p);
                    setPixel(i, y1 + m*(i-x1)-1, p);
                    setPixel(i-1, y1 + m*(i-x1)-1, p);
                    setPixel(i+1, y1 + m*(i-x1)-1, p);
                    setPixel(i, y1 + m*(i-x1)+1, p);
                    setPixel(i-1, y1 + m*(i-x1)+1, p);
                    setPixel(i+1, y1 + m*(i-x1)+1, p);
                }
            }
        }
        else {
            if (y2>y1) {
                for(int j=y1; j<y2; j++){
                    float m = (x2*1.0-x1)/(y2-y1);
                    setPixel(x1 + m*(j-y1),j, p);
                    setPixel(x1 + m*(j-y1)+1,j, p);
                    setPixel(x1 + m*(j-y1)-1,j, p);
                    setPixel(x1 + m*(j-y1),j-1, p);
                    setPixel(x1 + m*(j-y1)-1,j-1, p);
                    setPixel(x1 + m*(j-y1)+1,j-1, p);
                    setPixel(x1 + m*(j-y1),j+1, p);
                    setPixel(x1 + m*(j-y1)-1,j+1, p);
                    setPixel(x1 + m*(j-y1)+1,j+1, p);
                }
            }
            else {
                for(int j=y2; j<y1; j++){
                    float m = (x2*1.0-x1)/(y2-y1);
                    setPixel(x1 + m*(j-y1),j, p);
                    setPixel(x1 + m*(j-y1)-1,j, p);
                    setPixel(x1 + m*(j-y1)+1,j, p);
                    setPixel(x1 + m*(j-y1),j-1, p);
                    setPixel(x1 + m*(j-y1)-1,j-1, p);
                    setPixel(x1 + m*(j-y1)+1,j-1, p);
                    setPixel(x1 + m*(j-y1),j+1, p);
                    setPixel(x1 + m*(j-y1)-1,j+1, p);
                    setPixel(x1 + m*(j-y1)+1,j+1, p);
                }
            }
        }

    }


    void applyGrayFilter(){
            for(int i =0;i<matrixHeight;i++){
                for(int j=0;j<matrixWidth;j++){
                    Pixel p = getPixel(j,i);
                    int R = p.getR();
                    int G = p.getG();
                    int B = p.getB();
                    int gray = (R+G+B)/3;
                    Pixel* pGray = new Pixel(gray,gray,gray,255);
                    setPixel(j,i,*pGray);
                }
            }
    }

    void applyNegativeFilter(){
            for(int i =0;i<matrixHeight;i++){
                for(int j=0;j<matrixWidth;j++){
                    Pixel p = getPixel(j,i);
                    int R=p.getR();
                    int negativeR = 255-R;
                    int G = p.getG();
                    int negativeG = 255-G;
                    int B = p.getB();
                    int negativeB = 255-B;
                    Pixel* pNegative = new Pixel(negativeR,negativeG,negativeB,255);
                    setPixel(j,i,*pNegative);
                }
            }
    }

    void applySepiaFilter(){

        for(int i =0;i<matrixHeight;i++){
            for(int j=0;j<matrixWidth;j++){
                Pixel p = getPixel(j,i);
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
                setPixel(j,i,*pSepia);
            }
        }
    }

    void applyDarkerFilter(){
        for(int i =0;i<matrixHeight;i++){
            for(int j=0;j<matrixWidth;j++){
                Pixel p = getPixel(j,i);
                int R = p.getR();
                int G = p.getG();
                int B = p.getB();
                int new_R = R - 25;
                int new_G = G - 25;
                int new_B = B - 25;
                if(new_R < 0){new_R = 0;}
                if(new_G < 0){new_G = 0;}
                if(new_B < 0){new_B = 0;}
                Pixel* pDarker = new Pixel(new_R,new_G,new_B,255);
                setPixel(j,i,*pDarker);
            }
        }
    }

    void drawWithLapiz(int x, int y, int colorR, int colorG, int colorB){
        for(int i =0;i<matrixHeight;i++){
            for(int j=0;j<matrixWidth;j++){
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
