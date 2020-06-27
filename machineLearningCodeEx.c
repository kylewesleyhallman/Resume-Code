#include <stdio.h>

int main(void)
{
   
    
    for (int m =0; m <= 1 ; m++)
    {
        for (int n =0; n <= 1 ; n++)
        {
            for (int p =0; p <= 1 ; p++)
            {     
                 for (int q =0; q <= 1 ; q++)
                 {
                     for (int r =0; r <= 1 ; r++)
                    {
            
                    if ((p == 1 || q == 0) && 
                        (m == 1 || n == 0 || q == 1 || r == 1) && 
                        (m == 0 || n == 0 || p == 1 || r == 0) &&
                        (n == 0 || q == 0 || r == 0))
                        {
                            printf("%d %d %d %d %d\n",m,n,p,q,r);
                        }
                            
                
                    }    
                } 
            }
        }
    }
}  