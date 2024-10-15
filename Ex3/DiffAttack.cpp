#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
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
int char2int(char c){
    if(c>='0'&&c<='9')
        return c-'0';
    else 
        return c-'a'+10;
}
char int2char(int i){
    if(i>=0&&i<=9)
        return i+'0';
    else 
        return i+'a'-10;
}
int HexStr2int(string ss){//要保证这个十六进制字符串是两位
    char a=ss[0];
    char b=ss[1];
    int sum=0;
    sum+=char2int(a)*16;
    sum+=char2int(b);
    return sum;
}
string int2HexStr(int n){//把int转换成两位的十六进制字符串
    string s="";
    if(n==0){
        s="00";
        return s;
    }
    while(n>0){
        int t=n%16;
        s=int2char(t)+s;
        n/=16;
    }
    if(s.length()==1){
        s="0"+s;
    }
    return s;
}

int main()
{
    //输出文件
    ofstream fout("./222.txt");
    vector<string> S = {
        "d6","90","e9","fe","cc","e1","3d","b7","16","b6","14","c2","28","fb","2c","05",
                    "2b","67","9a","76","2a","be","04","c3","aa","44","13","26","49","86","06","99",
                    "9c","42","50","f4","91","ef","98","7a","33","54","0b","43","ed","cf","ac","62",
                    "e4","b3","1c","a9","c9","08","e8","95","80","df","94","fa","75","8f","3f","a6",
                    "47","07","a7","fc","f3","73","17","ba","83","59","3c","19","e6","85","4f","a8",
                    "68","6b","81","b2","71","64","da","8b","f8","eb","0f","4b","70","56","9d","35",
                    "1e","24","0e","5e","63","58","d1","a2","25","22","7c","3b","01","21","78","87",
                    "d4","00","46","57","9f","d3","27","52","4c","36","02","e7","a0","c4","c8","9e",
                    "ea","bf","8a","d2","40","c7","38","b5","a3","f7","f2","ce","f9","61","15","a1",
                    "e0","ae","5d","a4","9b","34","1a","55","ad","93","32","30","f5","8c","b1","e3",
                    "1d","f6","e2","2e","82","66","ca","60","c0","29","23","ab","0d","53","4e","6f",
                    "d5","db","37","45","de","fd","8e","2f","03","ff","6a","72","6d","6c","5b","51",
                    "8d","1b","af","92","bb","dd","bc","7f","11","d9","5c","41","1f","10","5a","d8",
                    "0a","c1","31","88","a5","cd","7b","bd","2d","74","d0","12","b8","e5","b4","b0",
                    "89","69","97","4a","0c","96","77","7e","65","b9","f1","09","c5","6e","c6","84",
                    "18","f0","7d","ec","3a","dc","4d","20","79","ee","5f","3e","d7","cb","39","48"
    };

    //最后构建出来的差分分布表应该是(2^8=256)*256的(因为输入是8个字节)
    //差分分布表初始化
    int diff[256][256]={0};

    
    for(int i=0;i<256;i++)//异或输入从0到255
    {
        for(int j=0;j<256;j++)//j:每一种输入明文x的可能
        {
          //有了异或输入和输入明文x，就可以计算x*=i^j
          int x_star=i^j;

          //y由x经过S盒变换得到
          int y=HexStr2int(S[j].c_str());

          //y*由x*经过S盒变换得到
          int y_star=HexStr2int(S[x_star].c_str());

          //最后输出异或由y*^y得到
          diff[i][y_star^y]++;
        }
    }
    // vector<vector<string>> diff_Str(256, vector<string>(256));
    // //初始化
    // for(int i=0;i<256;i++)
    // {
    //     for(int j=0;j<256;j++)
    //     {
    //         diff_Str[i][j]="";
    //     }
    // }
    // //转换成字符形式
    // for(int i=0;i<256;i++)
    // {
    //     for(int j=0;j<256;j++)
    //     {
    //         diff_Str[i][j]+=int2HexStr(diff[i][j]);
    //     }
    // }
    //输出差分分布表
    for(int i=0;i<256;i++)
    {
        for(int j=0;j<256;j++)
        {
            //cout<<diff_Str[i][j]<<" ";
            fout << int2HexStr(diff[i][j]) << " ";
        }
        //cout<<endl;
        fout<<endl;
    }
    fout.close();
}