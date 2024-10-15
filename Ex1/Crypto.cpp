#include<iostream>
#include<string.h>
using namespace std;


int main(){

    string Secret= "IYMYSILONRFNCQXQJEDSHBUIBCJUZBOLFQYSCHATPEQGQJEJNGNXZWHHGWFSUKULJQACZKKJOAAHGKEMTAFGMKVRDOPXNEHEKZNKFSKIFRQVHHOVXINPHMRTJPYWQGJWPUUVKFPOAWPMRKKQZWLQDYAZDRMLPBJKJOBWIWPSEPVVQMBCRYVCRUZAAOUMBCHDAGDIEMSZFZHALIGKEMJJFPCIWKRMLMPINAYOFIREAOLDTHITDVRMSE";
    int len=strlen(Secret.c_str());
    cout<<len<<endl;
    double P[26]={0.082,0.015,0.028,0.043,0.127,0.022,0.020,0.061,0.070,0.002,0.008,0.040,0.024,0.067,0.075,0.019,0.001,0.060,0.063,0.091,0.028,0.010,0.023,0.001,0.020,0.001};

    for(int m=5;m<6;m++){

        cout<<"m="<<m<<endl;
        ///首先对原字符串进行分割
        string Secretarr[m];
        for(int i=0;i<m;i++)
            Secretarr[i]="";

        for(int i=1;i<len+1;i++){
            int t= (i%m);
            Secretarr[t]+=Secret[i-1];
        }
        
        cout<<"移位前:"<<endl;
        for(int i=0;i<m;i++)
            cout<<Secretarr[i]<<endl;
        ///分割完毕后开始进行移位
        //////这里要注意保证移位后仍然在‘A-Z’之间
        for(int i=0;i<m;i++){
            for(int j=1;j<strlen(Secretarr[i].c_str())+1;j++){
                Secretarr[i][j-1]-=((j%26)-1+26)%26;
                if(Secretarr[i][j-1]<65)Secretarr[i][j-1]+=26;
            }
            
        }
        cout<<"移位后:"<<endl;
        for(int i=0;i<m;i++)
            cout<<Secretarr[i]<<endl;
        //////统计频数
        double f[m][26];
        for(int i=0;i<m;i++)
            for(int j=0;j<26;j++)
                f[i][j]=0;

        for(int i=0;i<m;i++){
            for(int j=0;j<strlen(Secretarr[i].c_str());j++)
            {
                f[i][Secretarr[i][j]-'A']+=1;
        }
        }
        for(int i=0;i<m;i++)
         {
             for(int j=0;j<26;j++)
             cout<<f[i][j]<<" ";
            cout<<endl<<endl;;
        }
        ////////计算频率
        double ff[m][26];
        for(int i=0;i<m;i++)
            for(int j=0;j<26;j++)
                ff[i][j]=f[i][j]/strlen(Secretarr[i].c_str());

         for(int i=0;i<m;i++)
         {
             for(int j=0;j<26;j++)
             cout<<ff[i][j]<<" ";
            cout<<endl<<endl;;
        }
            
                
        double p[m];

        for(int i=0;i<m;i++)
        {
            p[i]=0;
            for(int j=0;j<26;j++)
            {
                p[i]+=f[i][j]*(f[i][j]-1);
            }
            p[i]/=strlen(Secretarr[i].c_str())*(strlen(Secretarr[i].c_str())-1);
            cout<<p[i]<<endl;
        }

        cout<<endl<<endl;
        
    /////////有m个密钥
    int key[m];
    for(int i=0;i<m;i++){
        key[i]=0;
     }
      key[1]=15;
      key[2]=17;
      key[3]=8;
      key[4]=12;
      key[0]=4;

    
        for(int k=0;k<m;k++){
        /////计算第i个密钥
    
        ////定义数值Mg,计算26种情况下的Mg
        for(int i=0;i<26;i++){
            double Mg=0;
            for(int j=0;j<26;j++){
                int t= i+j;
                if(t>25)t-=26;
                //cout<<"P[i]*ff[k][t]="<<P[i]*ff[k][t]<<endl;
                Mg+=(P[j]*ff[k][t]);///strlen(Secretarr[k].c_str());
                //Mg+=(ff[k][t]*ff[k][t]);
            }
            cout<<Mg<<" ";
        }
        cout<<endl<<endl;
     }


    for(int i=0;i<m;i++){
        for(int j=0;j<strlen(Secretarr[i].c_str());j++){
            Secretarr[i][j]-=key[i];
            if(Secretarr[i][j]>90)Secretarr[i][j]-=26;
            if(Secretarr[i][j]<65)Secretarr[i][j]+=26;
    }
    }

    for(int i=0;i<m;i++)
            cout<<Secretarr[i]<<endl;

      string finalresult="";
    
        int recorder=0;
        while(true){
            if(Secretarr[1][recorder]){
                finalresult+=Secretarr[1][recorder];
            }
            else break;
            if(Secretarr[2][recorder]){
                finalresult+=Secretarr[2][recorder];
            }
            else break;
            if(Secretarr[3][recorder]){
                finalresult+=Secretarr[3][recorder];
            }
            else break;
            if(Secretarr[4][recorder]){
                finalresult+=Secretarr[4][recorder];
            }
            else break;
            if(Secretarr[0][recorder]){
                finalresult+=Secretarr[0][recorder];
            }
            else break;
            recorder++;
        }
      cout<<"HAAH"<<endl;           
     cout<<finalresult<<endl;
    }
}