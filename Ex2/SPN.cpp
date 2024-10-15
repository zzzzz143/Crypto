#include<iostream>
#include<map>
using namespace std;
int char2int(char c){
    if(c>='0'&&c<='9')
        return c-'0';
    else 
        return c-'A'+10;
}
char int2char(int i){
    if(i>=0&&i<=9)
        return i+'0';
    else 
        return i+'A'-10;
}
int charpointerToint(char* c,int n){
    
    int t=0;
    for(int i=0;i<n;i++){
        if(i!=0)t*=2;
        if(c[i]=='0')
        {
            t+=0;
        }
        else{
            t+=1;
        }
    }
    return t;
}
string charToBytes(char c){
    int t=char2int(c);
    string s="";
    while(t){
        if(t%2==0)
            s='0'+s;
        else
            s='1'+s;
        t/=2;
    }
    
    return s;
}
int main()

{
    //cout<<charToBytes('A')<<endl;
    int l,m,Nr;
    l=m=Nr=4;
    map<char,char> dict1;
    dict1['0']='E';
    dict1['1']='4';
    dict1['2']='D';
    dict1['3']='1';
    dict1['4']='2';
    dict1['5']='F';
    dict1['6']='B';
    dict1['7']='8';
    dict1['8']='3';
    dict1['9']='A';
    dict1['A']='6';
    dict1['B']='C'; 
    dict1['C']='5';
    dict1['D']='9';
    dict1['E']='0';
    dict1['F']='7';
    map<int,int> dict2;
    dict2[1]=1;
    dict2[2]=5;
    dict2[3]=9;
    dict2[4]=13;
    dict2[5]=2;
    dict2[6]=6;
    dict2[7]=10;
    dict2[8]=14;
    dict2[9]=3;
    dict2[10]=7;
    dict2[11]=11;
    dict2[12]=15;
    dict2[13]=4;
    dict2[14]=8;   
    dict2[15]=12;
    dict2[16]=16;
    
    char message[l*m];
    string Key;
    //Nr=4,加密四轮
    //Keyarray使用[1]到[5]表示第1到第5轮的密钥
    ///////虽然都是用于异或，但是前四轮和第五轮不太一样
    char Keyarray[Nr+2][l*m];
    cin>>message;
    cin>>Key;
    //同样的，Key第一个字母给它设置成空格
    //这样就可以直接使用K(4r-3)
    Key=' '+Key;
    //初始化每轮的密钥
    for(int i=1;i<=5;i++){
        //计算4r-3
        int t=4*i-3;
        for(int j=0;j<l*m;j++){
            Keyarray[i][j]=Key[t+j];
        }
    }
////打印一下密钥
    for(int i=1;i<=5;i++){
        
        for(int j=0;j<l*m;j++){
           // printf("%c ",Keyarray[i][j]);
        }
        //cout<<endl;
    }
///////////OK到这里基本信息就获取的差不多了
///定义一个应该就够了，后面会覆盖
//string w=message;
char w[l*m];
for(int i=0;i<l*m;i++){
    w[i]=message[i];
}
//cout<<"message:"<<message<<endl;
//cout<<"w:"<<w<<endl;

char u[l*m];
char v[l*m];
for(int i=1;i<=Nr-1;i++){

    //这里是异或。注意字符'0'和数字0的差别
    for(int j=0;j<l*m;j++){
        int t1=w[j]-48;
        //cout<<"t1:"<<t1<<" ";
        int t2=Keyarray[i][j]-48;
        //cout<<"t2:"<<t2<<" ";   
        int t3=t1^t2;
        //cout<<"t3:"<<t3<<" ";   
        u[j]=t3+'0';
    }
    //cout<<"u"<<i<<":"<<u<<endl;
    //这里是S盒代换
    for(int j=0;j<m;j++){
        int t=charpointerToint(&u[j*l],l);
        char s=int2char(t);
        char s2=dict1[s];
        string ss=charToBytes(s2);
        //可能不够长
        while(ss.length()<l){
            ss='0'+ss;
        }
        for(int k=0;k<l;k++){
            v[j*l+k]=ss[k];
        }
    }
    //cout<<"v"<<i<<":"<<v<<endl;
    //这里是P置换
    for(int j=0;j<l*m;j++){
        w[j]=v[dict2[j+1]-1];
    }
    //cout<<"w"<<i<<":"<<w<<endl;
}
////最后进行最后一次特殊的密钥处理
char u2[l*m];
for(int i=0;i<l*m;i++){
    int t1=w[i]-48;
    int t2=Keyarray[Nr][i]-48;
    int t3=t1^t2;
    u2[i]=t3+'0';
    }

for(int j=0;j<m;j++){
        int t=charpointerToint(&u2[j*l],l);
        char s=int2char(t);
        char s2=dict1[s];
        string ss=charToBytes(s2);
        //可能不够长
        while(ss.length()<l){
            ss='0'+ss;
        }
        for(int k=0;k<l;k++){
            v[j*l+k]=ss[k];
        }
    }
char y[l*m];
for(int i=0;i<l*m;i++){
    int t1=v[i]-48;
    int t2=Keyarray[Nr+1][i]-48;
    int t3=t1^t2;
    y[i]=t3+'0';
    }
for(int i=0;i<l*m;i++){
    printf("%c",y[i]);
}


}
