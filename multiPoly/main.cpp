
#include <stdio.h>
#include <iostream>

using namespace std;
//设计函数分别求两个一元多项式的乘积与和。
//
//输入格式:
//输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。
//
//输出格式:
//输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。零多项式应输出0 0。
void addPolys(int p1[][2],int p2[][2],int n1,int n2);
void sortPoly(int p[][2],int left,int right);
void multiPoly(int p1[][2],int p2[][2],int n1,int n2);
int main()
{
    int n1=0,n2=0;
    int poly1[1001][2] = {0};
    int poly2[1001][2] = {0};
    cout<<"输入n1:"<<endl;
    cin>>n1;    //读入第一个单项式的非零项个数
    for (int i = 0; i < n1; ++i) {
        cout<<"输入"<<i<<endl;
        scanf("%d %d",&poly1[i][0],&poly1[i][1]);
    }
    cout<<"输入n2:"<<endl;
    cin>>n2;
    for (int i = 0; i < n2; ++i) {
        cout<<"输入"<<i<<endl;
        scanf("%d %d",&poly2[i][0],&poly2[i][1]);
    }
    sortPoly(poly1,0,n1-1);
    sortPoly(poly2,0,n2-1);
//    for(int i=0;i<n1;i++)
//        printf("%d %d ",poly1[i][0],poly1[i][1]);
//    printf("\n");
//    for(int i=0;i<n2;i++)
//        printf("%d %d ",poly2[i][0],poly2[i][1]);
//    printf("\n相加:");
//    addPolys(poly1,poly2,n1,n2);
    printf("\n相乘：");
    multiPoly(poly1,poly2,n1,n2);

    return 0;
}

void swap(int array [][2], int i, int j){
    int ti0 = array[i][0],ti1 = array[i][1];
    array[i][0]=array[j][0];
    array[i][1]=array[j][1];
    array[j][0]=ti0;
    array[j][1]=ti1;

}

void sortPoly(int p[][2],int left,int right)
{
        int i,j,temp0,temp1;
        if(left>right)
            return;
        temp1=p[left][1];        //temp存储基准数
        temp0=p[left][0];
        i=left;
        j=right;
        while (i!=j)
        {
            //注意顺序，先从右往左
            while(p[j][1]>=temp1 && i<j)
            {
                j--;
            }
            //再从左往右找
            while(p[i][1]<=temp1 && i<j)
                i++;

            //交换两个数在数组中的位置
            if(i<j)
            {
                swap(p,i,j);
            }

            //将基准数归位
            p[left][1] = p[i][1];
            p[left][0] = p[i][0];
            p[i][1] = temp1;
            p[i][0] = temp0;


            sortPoly(p,left,i-1);
            sortPoly(p,i+1,right);
            return;

        }

}

void addPolys(int p1[][2],int p2[][2],int n1,int n2)
{
    int resArr[1001][2]={0};
    int i=0,j=0,count=0;
    while(i<n1 && j<n2)
    {
        if(p1[i][1]==p2[j][1])
        {
            resArr[i][0]=p1[i][0]+p2[j][0];
            resArr[i][1]=p1[i][1];
            i++,j++,count++;
        }
        else if(p1[i][1]<p2[j][1])
        {
            resArr[i][0]=p1[i][0];
            resArr[i][1]=p1[i][1];
            i++,count++;
        }
        else
        {
            resArr[i][0]=p2[j][0];
            resArr[i][1]=p2[j][1];
            j++,count++;
        }
    }
    if(i<n1)
    {
        for(;i<n1;i++)
        {
            resArr[count][0]=p1[i][0];
            resArr[count][1]=p1[i][1];
            i++,count++;
        }
    }
    if(j<n2)
    {
        for(;j<n2;j++)
        {
            resArr[count][0]=p2[j][0];
            resArr[count][1]=p2[j][1];
            j++,count++;
        }
    }
    for(int i=0;i<count;i++)
    {
        printf("%d %d",resArr[i][0],resArr[i][1]);
    }


}

void multiPoly(int p1[][2],int p2[][2],int n1,int n2)
{
    int max=0;
    int count=0;
    int res[10000]={0};
    for(int i=0;i<n1;i++)
    {
        for(int j=0;j<n2;j++)
        {
            res[p1[i][1]+p2[j][1]] += p1[i][0]*p2[j][0];
            if(p1[i][1]+p2[j][1]>max)
                max = p1[i][1]+p2[j][1];
        }
    }
    int i=0;
    while(i<=max)
    {
        if(res[i]!=0)
        {
            printf("%d %d ",res[i],i);
        }

        i++;
    }
}