#include<iostream>
#include<map>
#include<fstream>
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
string KeyGen(int i){
    string result="";

    while(i){
        int temp=i%2;
        if(temp==0)
            result='0'+result;
        else
            result='1'+result;
        i>>=1;
    }
    while(result.length()<8){
            result='0'+result;
        }
    return result;
}
int SevenBitXOR(char a,char b,char c,char d,char e,char f,char g){
    a-='0';
    b-='0';
    c-='0';
    d-='0';
    e-='0';
    f-='0';
    g-='0';
    return (a^b^c^d^e^f^g);

}
int main()
{
    map<char,char> S_RE;
    S_RE['0']='E';
    S_RE['1']='3';
    S_RE['2']='4';
    S_RE['3']='8';
    S_RE['4']='1';
    S_RE['5']='C';
    S_RE['6']='A';
    S_RE['7']='F';
    S_RE['8']='7';
    S_RE['9']='D';
    S_RE['A']='9';
    S_RE['B']='6'; 
    S_RE['C']='B';
    S_RE['D']='2';
    S_RE['E']='0';
    S_RE['F']='5';
    //候选子密钥有2^8=256个
    int countnumber[256]={0};
    //产生这256个候选子密钥
    string key[256];
    for(int i=0;i<256;i++){
        key[i]=KeyGen(i);
    }
    //文件操作
    ifstream infile;
    infile.open("./MC.txt");
    
    int recorder=0;
/////这里是计算K5相关的内容
    while((recorder++)<8000){
        
        string Message,Ciphertext;
        getline(infile,Message);
        getline(infile,Ciphertext);
        //256个候选子密钥依次来
        for(int i=0;i<256;i++){
        //对密钥的处理    
            //这一次的密钥是(8位)
            string _Key=key[i];
            //给他拆成4位，4位
            char * Key1=&_Key[0];
            char * Key2=&_Key[4];
            //接下来转换为对应的int
            int Key1int=charpointerToint(Key1,4);
            int Key2int=charpointerToint(Key2,4);

        //接下来对本轮密文处理
            char * Ciphertext1=&Ciphertext[4];
            char * Ciphertext2=&Ciphertext[12];
            //同样转换为对应的int
            int Ciphertext1int=charpointerToint(Ciphertext1,4);
            int Ciphertext2int=charpointerToint(Ciphertext2,4);
        //接下来进行异或，异或分别得到v24和v44
            int temp1=Key1int^Ciphertext1int;
            int temp2=Key2int^Ciphertext2int;
        //进行S盒的逆代换，得到u24和u44
            char v24=S_RE[int2char(temp1)];
            char v44=S_RE[int2char(temp2)];
        //将u24和u44转换为二进制bit串
            string v24bit=charToBytes(v24);
            //长度可能不够
            while(v24bit.length()<4){
                v24bit='0'+v24bit;
            }
            string v44bit=charToBytes(v44);
            //长度可能不够
            while(v44bit.length()<4){
                v44bit='0'+v44bit;
            }
            
        //接下来就可以计算随机变量x5 XOR x7 XOR x8 XOR u6 XOR u8 XOR u14 XOR u16了
            if(SevenBitXOR(Message[4],Message[6],Message[7],v24bit[1],v24bit[3],v44bit[1],v44bit[3])==0){
                countnumber[i]++;
            }
        }
    }
    
    //countnumber中存储的是随机变量等于0的次数
    //接下来计算其偏差
    for(int i=0;i<256;i++){
        countnumber[i]-=8000/2;
        //然后取绝对值
        countnumber[i]=abs(countnumber[i]);
    }
    //获取countnumber中最大的值的索引
    int maxindex=0;
    for(int i=1;i<256;i++){
        if(countnumber[i]>countnumber[maxindex])
            maxindex=i;
    }
    //输出这个索引对应的子密钥，这是对16位真实密钥(第五轮，K25和K45)的第5-8和第13-16位的预测结果
    cout<<key[maxindex]<<endl;

}