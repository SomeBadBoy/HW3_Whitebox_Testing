#include <iostream>
using namespace std;
#define num 200
int circle(int shifou[num])
{
    int j=0;
    for(int i=0; i<num; i++)
        if (shifou[i])
            j++;
    return j;
}
int picktrue(int tu[num][num],int node) //����-1��ʾû��
{
    int panduan=-1;
    for (int i=0; i<num; i++)
        if (tu[node][i]==1)
            panduan=i;
    return panduan;
}
int pickfalse(int tu[num][num],int node) //����-1��ʾû��
{
    int panduan=-1;
    for (int i=0; i<num; i++)
        if (tu[node][i]==2)
            panduan=i;
    return panduan;
}
int pickbase(int tu[num][num],int node)   //����-1��ʾû��
{
    int panduan=-1;
    for (int i=0; i<num; i++)
        if (tu[node][i]==0)
            panduan=i;
    return panduan;
}
int xunhuan(int path[num],int pathi)
{
    int chonfu=0;  //��ʾû��ѭ��
    for (int k=0; k<pathi-1; k++)
        if (path[k]==path[pathi-1])
            chonfu=1;  //����1��ʾ���ظ�
    return chonfu;
}

void search(int tu[num][num],int path[num],int pathi,int outpath[num][num])
{
    int rpathi=pathi;
    int bpathi=pathi;
    if (xunhuan(path,pathi)) //���ظ���Ԫ��
    {
        int temp=0;
        while(outpath[temp][0]!=-1)
            temp++;
        for (int j=0; j<pathi; j++)
        {
            outpath[temp][j]=path[j];
        }
        return;
    }
    else if (picktrue(tu,path[pathi-1])==-1 && pickfalse(tu,path[pathi-1])==-1 && pickbase(tu,path[pathi-1])==-1)
    {
        int temp=0;
        while(outpath[temp][0]!=-1)
            temp++;
        for (int j=0; j<pathi; j++)
        {
            outpath[temp][j]=path[j];
        }
        return;
    }
    if (pickfalse(tu,path[pathi-1])!=-1)
    {
        path[pathi++]=pickfalse(tu,path[pathi-1]);
        search(tu,path,pathi,outpath);
    }
    if (picktrue(tu,path[rpathi-1])!=-1)
    {
        path[rpathi++]=picktrue(tu,path[rpathi-1]);
        tu[path[rpathi-2]][path[rpathi-1]]=-1;
        search(tu,path,rpathi,outpath);
    }
    else if (pickbase(tu,path[bpathi-1])!=-1)
    {
        path[bpathi++]=pickbase(tu,path[bpathi-1]);
        search(tu,path,bpathi,outpath);
    }
}
void paixu(int outpath[num][num])
{
    int ilen,jlen;
    int temp[num]= {};
    int q;
    for (int i=0; i<num; i++) //ð������i��ǰ��ģ�j�Ǻ����
        for (int j=i+1; j<num; j++)
        {
            ilen=0;
            jlen=0;
            while(outpath[i][ilen++]!=-1);  //�����i�еĳ���
            while(outpath[j][jlen++]!=-1);  //�����j�еĳ���
            //    cout<<ilen<<" "<<jlen<<endl;
            if (ilen ==1 || jlen==1)
                break;
            else if (ilen<jlen)
                continue;
            else if (ilen>jlen)
            {
                for (q=0; q<num; q++)
                    temp[q]=outpath[i][q];
                for (q=0; q<num; q++)
                    outpath[i][q]=outpath[j][q];
                for (q=0; q<num; q++)
                    outpath[j][q]=temp[q];
            }
            else for (int k=0; k<num; k++)
                {
                    if( outpath[j][k] < outpath[i][k] )   //����С�ͽ���
                    {
                        for (q=0; q<num; q++)
                            temp[q]=outpath[i][q];
                        for (q=0; q<num; q++)
                            outpath[i][q]=outpath[j][q];
                        for (q=0; q<num; q++)
                            outpath[j][q]=temp[q];
                        break;
                    }
                }
        }
}

int main()
{
    int start;
    while (cin>>start)
    {
        int path[num];
        int pathi; //·���±�
        pathi=0;
        path[pathi++]=start;  //pathi�ĵ�����һ���������ռ�ݵ�λ��
        int tu[num][num]= {};   //100��ʾû�ã�0��ʾN�ǻ����ڵ㣬1��ʾT��֧�е���ȷ��һ·��2��ʾF��֧�еĴ��һ·
        int shifou[num]= {0};  //1�����Ƿ�֧�ڵ�,0�����ڵ��û�д˽ڵ�
        int i,j;
        for (i=0; i<num; i++)
            shifou[i]=0;
        for (i=0; i<num; i++)
            for (j=0; j<num; j++)
                tu[i][j]=-1;
        char line[10];

        int outpath[num][num]= {}; //�������·��,���±�Ϊ0��ʼ
        for (i=0; i<num; i++)
            for (j=0; j<num; j++)
                outpath[i][j]=-1;

        while (cin>>line)
        {
            if (line[0]=='E' && line[1]=='N' && line[2]=='D')
                break;
            int linei;
            linei=0;
            i=0;
            j=0;
            while(line[linei]<='9' && line[linei]>='0')
            {
                i=i*10+line[linei]-'0';
                linei++;
            }
            linei=linei+2;
            while(line[linei]<='9' && line[linei]>='0')
            {
                j=j*10+line[linei]-'0';
                linei++;
            }
            linei=linei+1;
            if (line[linei]=='T')
            {
                tu[i][j]=1;
                shifou[i]=1;
            }
            else if (line[linei]=='F')
            {
                tu[i][j]=2;
                shifou[i]=1;
            }
            else if (line[linei]=='N')
                tu[i][j]=0;
        }
        cout<<"CC="<<circle(shifou)+1<<endl;
        search(tu,path,pathi,outpath);
        paixu(outpath);
        i=0;
        while (outpath[i][0]!=-1)
        {
            j=0;
            if(outpath[i][j]!=-1)
                cout<<outpath[i][j++];
            while (outpath[i][j]!=-1)
                cout<<","<<outpath[i][j++];
            cout<<endl;
            i++;
        }
    }
    return 0;
}
