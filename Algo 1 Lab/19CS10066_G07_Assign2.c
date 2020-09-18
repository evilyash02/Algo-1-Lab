

#include "assign2.h"
#include <stdlib.h>

int finals;

Point* merge(Point* big, Point* small, int nb, int ns) // merges in linear time wrt nb+ns = 2*n
{
    
    int ib=0, is =0, i =0;
    Point* final = (Point*)malloc((nb+ns)*sizeof(Point));
    for( ib =0; ib<nb; ib++)
    {
        if(big[ib].y==0)
        {
            while(is<ns && small[is].x<big[ib].x) // finds point in small just before the current big point
                is++;
            if(is!=ns)
            {
                while (small[is].x>big[ib].x)       // deals with the case when x coordinates coincide
                    is--;
                Point inters;             // creates intersection point
                inters.x=big[ib].x;
                inters.y=small[is++].y;
                final[i++]=inters;     // adds intersection point to final
                
                if(ib+1!=nb){
                    while(is<ns && small[is].x<big[ib+1].x)       // copies all from small till the next big point arrives
                    {
                        final[i++]=small[is++];
                    }
                }
                else{
                    while(is<ns)       // copies all from small till the next big point arrives
                    {
                        final[i++]=small[is++];
                    }
                }
                
            }
            else
                final[i++]=big[ib];
            
        }
        else{
            if(big[ib].y!=final[i-1].y)
                final[i++]=big[ib]; // if big point's y is not zero, it copies the point as is
        }
    }
    finals=i;
    return final;
}


Point* findOutLine(Box boxes[], int size, int *outputsize){
    if (size==1)                //base case
    {
        Box b = boxes[0];
        Point* outline;
      if (b.left==0)
      {
          *outputsize=2;
        outline = (Point*)malloc(2*sizeof(Point));
        outline[0].x=0;
        outline[0].y=b.ht;
        outline[1].x=b.right;
        outline[1].y=0;
        }
      else
      {
        *outputsize=3;
          outline = (Point*)malloc(3*sizeof(Point));
          outline[0].x=0;
          outline[0].y=0;
          outline[1].x=b.left;
          outline[1].y=b.ht;
          outline[2].x=b.right;
          outline[2].y=0;

      }
      return outline;
    }
    
    int m = size/2;
        int nb,ns;
        Point* big = findOutLine(boxes+m, size-m, &nb);
        Point* small = findOutLine(boxes, m, &ns);
    Point* merged =merge(big,small, nb, ns);
    *outputsize=finals;
    return merged;
}


void Ymerge(Box boxes[], int l, int m, int r){
    //Merge
        int i, j, k;
        int a = m - l + 1;
        int b = r - m;

        Box L[a], R[b];

        for (i = 0; i < a; i++)
            L[i] = boxes[l + i];
            
        for (j = 0; j < b; j++)
            R[j] = boxes[m + 1 + j];
        
        i = 0;
        j = 0;
        k = l;
        while (i < a && j < b) {
            if (L[i].ht <= R[j].ht) {
                boxes[k] = L[i];
                i++;
            }
            else {
                boxes[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < a) {
            boxes[k] = L[i];
            i++;
            k++;
        }

        while (j < b) {
            boxes[k] = R[j];
            j++;
            k++;
        }
}


void Ysort(Box boxes[],int l, int r){
    if(l<r){
        int m=(l+r)/2;
        Ysort(boxes, l,m);
        Ysort(boxes, m+1,r);
        Ymerge(boxes,l,m,r);
    }
}





int main() {
    int n;
    printf(" ");
    scanf("%d", &n);
    Box boxes[n];
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d %d %d", &boxes[i].left , &boxes[i].right , &boxes[i].ht);
    }
    int outputsize;
    Ysort(boxes,0,n-1);

    Point* ptr = findOutLine(boxes, n, &outputsize);

    prettyPrint(ptr, outputsize);
}



