#include<stdio.h>
#include<string.h>
int main()
{
    char a[5000];
    strcpy(a,"�������������£ãģţƣǣ�����������������ˣ��������������������������֣�����������Ʋʡ��Ǻ��ϵĽ�������Ϧ���е�������������Ӱ�����ҵ���ͷ������");
    int length=strlen(a);
    int i;
    for(i=0;i<length-1;i+=2)
        printf("%X%X ",(unsigned char)a[i],(unsigned char)a[i+1]);
    system("pause");
    return 0;
}
