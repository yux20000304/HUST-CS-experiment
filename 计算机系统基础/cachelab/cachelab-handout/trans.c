/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int i ,j, x , y;
    int x1,x2,x3,x4,x5,x6,x7,x8;
    
    if(N==32&&M==32){       //如果输入的是32*32的矩阵
        for(j=0;j<N;j+=8){  //行坐标
            for(i=0;i<M;i++){      //列坐标         
                        x1=A[i][j];
                        x2=A[i][j+1];
                        x3=A[i][j+2];
                        x4=A[i][j+3];
                        x5=A[i][j+4];
                        x6=A[i][j+5];
                        x7=A[i][j+6];
                        x8=A[i][j+7];

                        B[j][i]=x1;
                        B[j+1][i]=x2;
                        B[j+2][i]=x3;
                        B[j+3][i]=x4;
                        B[j+4][i]=x5;
                        B[j+5][i]=x6;
                        B[j+6][i]=x7;
                        B[j+7][i]=x8;
            }
        }
    }
    else if(N==64&&M==64){
        for(i=0;i<N;i+=8){
            for(j=0;j<M;j+=8){  //针对8*8的块
                for(x=i;x<i+4;x++){     //把8*8分解成上半部分一个4*8和下半部分一个4*8分别进行操作
                    x1=A[x][j];
                    x2=A[x][j+1];
                    x3=A[x][j+2];
                    x4=A[x][j+3];
                    x5=A[x][j+4];
                    x6=A[x][j+5];
                    x7=A[x][j+6];
                    x8=A[x][j+7];

                    B[j][x]=x1;         //注意到这里同样是转置，但是只有前4个完成了真正的转置，这里为了减少conflict miss先把后四个暂存
                    B[j+1][x]=x2;
                    B[j+2][x]=x3;
                    B[j+3][x]=x4;
                    B[j][x+4]=x5;
                    B[j+1][x+4]=x6;
                    B[j+2][x+4]=x7;
                    B[j+3][x+4]=x8;
                }
                for(y=j;y<j+4;y++){     //处理左下角的矩阵
                    x1=A[i+4][y];
                    x2=A[i+5][y];
                    x3=A[i+6][y];
                    x4=A[i+7][y];
                    x5=B[y][i+4];       //这里是会把之前放在错误位置的右上角矩阵和左下角矩阵进行交换
                    x6=B[y][i+5];
                    x7=B[y][i+6];
                    x8=B[y][i+7];

                    B[y][i+4]=x1;
                    B[y][i+5]=x2;
                    B[y][i+6]=x3;
                    B[y][i+7]=x4;
                    B[y+4][i]=x5;       //这里继续把原来右上角的矩阵挪到左下角
                    B[y+4][i+1]=x6;
                    B[y+4][i+2]=x7;
                    B[y+4][i+3]=x8;
                }
                for(x=i+4;x<i+8;x++){   //处理右下角的矩阵
                    x1=A[x][j+4];
                    x2=A[x][j+5];
                    x3=A[x][j+6];
                    x4=A[x][j+7];
                    B[j+4][x]=x1;
                    B[j+5][x]=x2;
                    B[j+6][x]=x3;
                    B[j+7][x]=x4;
                }
            }
        }
    }
    else if(N==67&&M==61){
        for(i=0;i<N;i+=16){
            for(j=0;j<M;j+=16){
                for(x=i;x<N&&x<i+16;x++){
                    for(y=j;y<M&&y<j+16;y++){
                        B[y][x]=A[x][y];
                    }
                }
            }
        }
        
    }
}

    /*
     * You can define additional transpose functions below. We've defined
     * a simple one below to help you get started.
     */

    /*
     * trans - A simple baseline transpose function, not optimized for the cache.
     */
    char trans_desc[] = "Simple row-wise scan transpose";
    void trans(int M, int N, int A[N][M], int B[M][N])
    {
        int i, j, tmp;

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < M; j++)
            {
                tmp = A[i][j];
                B[j][i] = tmp;
            }
        }

    }

    /*
     * registerFunctions - This function registers your transpose
     *     functions with the driver.  At runtime, the driver will
     *     evaluate each of the registered functions and summarize their
     *     performance. This is a handy way to experiment with different
     *     transpose strategies.
     */
    void registerFunctions()
    {
        /* Register your solution function */
        registerTransFunction(transpose_submit, transpose_submit_desc);

        /* Register any additional transpose functions */
        registerTransFunction(trans, trans_desc);

    }

    /*
     * is_transpose - This helper function checks if B is the transpose of
     *     A. You can check the correctness of your transpose by calling
     *     it before returning from the transpose function.
     */
    int is_transpose(int M, int N, int A[N][M], int B[M][N])
    {
        int i, j;

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < M; ++j)
            {
                if (A[i][j] != B[j][i])
                {
                    return 0;
                }
            }
        }
        return 1;
    }

