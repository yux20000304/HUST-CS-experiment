#include<stdio.h>
#include<string.h>
int main()
{
    char a[5000];
    strcpy(a,"１２３４５ＡＢＣＤＥＦＧａｂｃｄｅｆｇ轻轻的我走了，正如我轻轻的来；我轻轻的招手，作别西天的云彩。那河畔的金柳，是夕阳中的新娘；波光里的艳影，在我的心头荡漾。");
    int length=strlen(a);
    int i;
    for(i=0;i<length-1;i+=2)
        printf("%X%X ",(unsigned char)a[i],(unsigned char)a[i+1]);
    system("pause");
    return 0;
}
