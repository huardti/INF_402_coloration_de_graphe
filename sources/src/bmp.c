#include "bmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLANC (Color){255,255,255}

Image* NouvelleImage(int w,int h)
{
	Image* I = malloc(sizeof(Image));
	Color p = {255,255,255};

	I->width = w;
	I->height = h;

	I->dat = malloc(w*h*sizeof(Color*));

    /* initialisation de l'image a BLANC */
	for (size_t i = 0; i < w; i++) {
		for (size_t j = 0; j < h; j++) {
			SetPixel(I, i ,j , BLANC);
		}
	}
	return I;
}

void DelImage(Image* I) {
	if (I) {
		free(I->dat);
		free(I);
	}
}

void SetPixel(Image* I, int x, int y, Color p) {
	if ((I && x>=0 && x<I->width && y>=0 && y<I->height)) {
		I->dat[I->width*y+x] = p;
	}
}

Color GetPixel(Image* I,int x,int y) {
    if (I && x>=0 && x<I->width && y>=0 && y<I->height) {
	    return I->dat[I->width*y+x];   
    }
    fprintf(stderr, "GetPixel: le pixel %d %d n'est pas dans l'image", x, y);
    exit(1);
}

void tracerRond(Image *I, int r, int i, int j, Color p){
	
	for (int y = -r; y < r + 1; y++)  {
        for (int x = -r; x < r + 1; x++) {            
            if((x * x) + (y * y)-((r) * (r)) <= (r)) {                     
                SetPixel(I, i + x, j + y, p);
            }
		}
	}	
}

void traceDroite(Image * I, int x1, int y1, int x2, int y2, int e, Color p){
/* pour tracer une droite a partir de 2 points : (xa,ya) et (xb,yb) */

 int x,y,dx,dy,incrmX,incrmY,dp,NE,SE;

 dx = x2-x1;
 dy = y2-y1;

 if (dx>0)
  incrmX = 1;
 else {
  incrmX = -1;
  dx *= -1;
 }

 if (dy>0)
  incrmY = 1;
 else {
  incrmY = -1;
  dy *= -1;
 }

 if (dx>=dy) {
  dp=2*dy-dx;
  SE=2*dy;
  NE=2*(dy-dx);

  y=y1;
  for(x=x1;x!=x2;x+=incrmX) {
   /* affichePixel(x,y,couleur) */
   for (size_t s = y-e; s < y+e; s++) {
   	SetPixel(I, x, s,p); 
   }
   if (dp<=0) /* on choisit le pixel E */
    dp += SE;
   else {
    dp += NE;
    y+=incrmY;
   }
  }
 }
 else if (dx<dy) {
  dp=2*dx-dy;
  SE=2*dx;
  NE=2*(dx-dy);

  x=x1;
  for(y=y1;y!=y2;y+=incrmY) {
   /* affichePixel(x,y,couleur) */
   for (size_t s = x-e; s < x+e; s++) {
   	SetPixel(I, s,y,p); 
   }

   if (dp<=0) /* on choisit le pixel E */
    dp += SE;
   else {
    dp += NE;
    x+=incrmX;
   }
  }
 }
}
// -------------------------------------------

#pragma pack(1)  // desative l'alignement mémoire

struct BMPImHead
{
	int32 size_imhead;
	int32 width;
	int32 height;
	int16 nbplans; // toujours 1
	int16 bpp;
	int32 compression;
	int32 sizeim;
	int32 hres;
	int32 vres;
	int32 cpalette;
	int32 cIpalette;
};

struct BMPHead
{
	char signature[2];
	int32 taille;
	int32 rsv;
	int32 offsetim;
	struct BMPImHead imhead;
};

int Sauver(Image* I,const char* fichier)
{
	struct BMPHead head;
	Color p;
	int i,j,tailledata,pitch;
	uint_8 bgrpix[3];
	char corrpitch[4] = {0,3,2,1};
	FILE* F = fopen(fichier,"wb");
	if (!F){
		return -1;
    }
	memset(&head,0,sizeof(struct BMPHead));
	head.signature[0] = 'B';
	head.signature[1] = 'M';
	head.offsetim = sizeof(struct BMPHead);
	head.imhead.size_imhead = sizeof(struct BMPImHead);
	head.imhead.width = I->width;
	head.imhead.height = I->height;
	head.imhead.nbplans = 1;
	head.imhead.bpp = 24;
	pitch = corrpitch[(3*head.imhead.width)%4];
	tailledata = 3*head.imhead.height*head.imhead.width + head.imhead.height*pitch;
	head.imhead.sizeim = tailledata;
	head.taille = head.offsetim + head.imhead.sizeim;
	fwrite(&head,sizeof(struct BMPHead),1,F);


	for(j=0;j<I->height;j++)
	{
		for(i=0;i<I->width;i++)
		{
			p = GetPixel(I,i,I->height-j-1);
			bgrpix[0] = p.b;
			bgrpix[1] = p.g;
			bgrpix[2] = p.r;
			fwrite(&bgrpix,1,3,F);
		}
		bgrpix[0] = bgrpix[1] = bgrpix[2] = 0;
		fwrite(&bgrpix,1,pitch,F);
	}
	fclose(F);
	return 0;
}