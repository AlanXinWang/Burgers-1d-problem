#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.141592

void originfunction(float delta_x,int x,int t,float u[t][x+1]) //赋值函数 
 {
 	int i=0;
 	for(i=0;i<x;i++)
 	{
 		u[0][i]=sin(PI*(delta_x*i));
	}
	u[0][x+1]=0; //边界条件修正 
 }
 
void myprint(int x,FILE *fp,int t,float u[t][x+1]) //输出到文件 
{
	int i=0,j=0;
	for(j=0;j<x+1;j++)
	{
		for(i=0;i<t;i=i+20)	//从行的数据开始写入 
		{
			fprintf(fp,"%f	",u[i][j]);  	 
			
		}
		fprintf(fp,"\n");  
	}
}

void myprint_2(int x,FILE *fp,int t,float u[t][x+1])
{
	int i=0;
	for(i=0;i<x+1;i++)
	{
		fprintf(fp,"%f\n",u[t-1][i]);
	}
}

void main_calculator(int x,int t,float u[t][x+1],int y,float delta_x,float delta_h) //主计算函数，负责计算u_j_n+1的值 
{
	int i=0,j=0,k=0;
	float round_ux=0,round_u2x=0; //定义当前计算点的一阶偏导数和二阶偏导数 
	for(i=0;i<x+1;i++)
	{
		if(i==0|i==x) 	//边界条件修正 
		{
			u[y][i]=0;
		}
		else
		{
			round_ux=(u[y-1][i+1]-u[y-1][i-1])/(2*delta_x);  //一阶偏导数采取两点的中心差分 
			round_u2x=(u[y-1][i+1]-2*u[y-1][i]+u[y-1][i-1])/(delta_x*delta_x);  //二阶偏导数采取三点的中心差分 
			u[y][i]=u[y-1][i]+delta_h*(0.02*round_u2x-u[y-1][i]*round_ux);  //时间项导数采取显式欧拉法 
		}
	}
} 
int main()
{
	FILE *fp;
	fp=fopen("D:\\data.txt","w");
	int L=2;		//空间长度 
	int x=20;		//网格数量
	int t=20;		//时间分割数量 
	float delta_x=0; 	//空间步长	 
	delta_x=L*1.0/x; 
	
	float h=0.2;
	float delta_h=0;	//时间步长
	delta_h=h/t; 
	float u[t][x+1];	//定义二维节点，行数据表示n个时间步长推进，列数据表示第n个节点 
	int i=0,j=0,k=0,p=0,q=0;
	
	originfunction(delta_x,x,t,u); //通过初始扰动对h=0时刻直接赋值 
	/*
	 for(i=0;i<x+1;i++)		//打印初始值 
	{
		fprintf(fp,"%f\n",u[0][i]);
	}
	*/
	for(i=1;i<t;i++)
	{
		main_calculator(x,t,u,i,delta_x,delta_h);
	}
	

	
			
	for(i=0;i<x+1;i++)  	//将0.2s的数据替换到0s的位置，即可求出0.4s的数据 
	{
		u[0][i]=u[t-1][i];
	}
	
	for(i=1;i<t;i++)
	{
		main_calculator(x,t,u,i,delta_x,delta_h);
	}
	
	 
	
		for(i=0;i<x+1;i++)  	//将0.4s的数据替换到0s的位置，即可求出0.6s的数据 
	{
		u[0][i]=u[t-1][i];
	}
	
	for(i=1;i<t;i++)
	{
		main_calculator(x,t,u,i,delta_x,delta_h);
	}
	
	for(i=0;i<x+1;i++)  	//将0.6s的数据替换到0s的位置，即可求出0.8s的数据 
	{
		u[0][i]=u[t-1][i];
	}
	
	for(i=1;i<t;i++)
	{
		main_calculator(x,t,u,i,delta_x,delta_h);
	}
	
	for(i=0;i<x+1;i++)  	//将0.8s的数据替换到0s的位置，即可求出1.0s的数据 
	{
		u[0][i]=u[t-1][i];
	}
	
	for(i=1;i<t;i++)
	{
		main_calculator(x,t,u,i,delta_x,delta_h);
	}
	
	myprint_2(x,fp,t,u);	//打印数据		
	
	if( fclose( fp ) ) 	/* 关闭文件 */
	{                        
        printf( "Can not close the file!\n" );
        exit(0);
    }
	return 0;
	
}
