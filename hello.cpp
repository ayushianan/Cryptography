#include<bits/stdc++.h>
using namespace std;

string inputs();
void outputs(string);
string l(string,int);
int r(string,int);
string made(string);
string code(string,string);
string prepare(string,int);
string decode(string, string);
int main()
{
  cout<<"         ##########################           "<<"\n";
  cout<<"              Cuustomer cipher                "<<"\n";
  cout<<"         ##########################           "<<"\n";
  int c,lj,ind=0;
  string k;string normal="";
  string ct="";
  string matrix="";
  while(1)
  {
    cout<<"----------------------------------------------"<<"\n";
    cout<<"***Make a choice****"<<"\n";
    cout<<"1: **E/n/c/r/y/p/t**"<<"\n";
    cout<<"2: **D/e/c/r/y/p/t**"<<"\n";
    cout<<"3: **go back**"<<endl;
    cout<<"----------------------------------------------"<<"\n";
    cin>>c;
    switch(c)
        {
        case 1: k=inputs();
                matrix=made(k);
                normal=inputs();
                lj=normal.length();
                if(lj%2!=0)
                  ind=1;
                ct=code(normal,matrix);
                outputs(ct);
                break;
        case 2: k=inputs();
                matrix=made(k);
                ct=inputs();
                normal=decode(ct,matrix);
                if(ind==1)
                  normal.erase(lj);
                outputs(normal);
                ind=0;
                break;
        case 3: exit(0);
        default:cout<<"w*r*o*n*g"<<"\n";
        }
  }
  return 0;
}
string decode(string txtout,string matrix )
{
    int c[2];int a[2];int b[2];
    int s=0;
    int or1=0;
    string a1=txtout;
    int textlen=txtout.length();
    for (int l=0;l<textlen;l=l+2)
    {
        c[0] = 0;c[1] = 0;
        for(int i=0;i<26;i++)
        {
            if (a1[l] == matrix[i])
                c[0] = i;
            if (a1[l+1]==matrix[i])
                c[1] =i;
        }
        for (int m=0;m<2;m++)
        {
            if (c[m] < 5 )
                a[m] = 1;
            else if (c[m]<10&& c[m]>4)
                a[m] = 2;
            else if (c[m]<15 && c[m]>9)
                a[m] = 3;
            else if (c[m]<20 && c[m]>14)
                a[m] = 4;
            else
                a[m] = 5;
            if (c[m]%5==0)
                b[m] = 1;
            else if (c[m]%5==1)
                b[m] = 2;
            else if (c[m]%5==2)
                b[m] = 3;
            else if (c[m]%5==3)
                b[m] = 4;
            else
                b[m] = 5;
        }
        if (a[0]==a[1]||b[0]==b[1])
        {
            if (a[0]==a[1])
            {
                or1=a[0];
                c[0] = (c[0] - 1);
                c[1] = (c[1] - 1);
                for (int m=0;m<2;m++)
                {
                    if (c[m] < 5 )
                        a[m] = 1;
                    else if (c[m]<10&& c[m]>4)
                        a[m] = 2;
                    else if (c[m]<15 && c[m]>9)
                        a[m] = 3;
                    else if (c[m]<20 && c[m]>14)
                        a[m] = 4;
                    else
                        a[m] = 5;
                }
                if (a[0]!=or1||c[0]< 0)
                    c[0]=c[0] + 5;
                if (a[1]!=or1||c[1]< 0)
                    c[1]=c[1] + 5;
                a1[l] = matrix[c[0]];
                a1[l+1] = matrix[c[1]];
            }
            else if (b[0]==b[1])
            {
                if (c[0]>c[1])
                {
                    c[0]=(c[0] - 5) ;
                    c[1]= (c[1] - 5) ;
                    if(c[1] < 0)
                        c[1]=(c[1] + 25) ;
                }
                else if (c[0] < c[1] && c[0] < 4)
                {
                    c[0] = (c[0] + 5);c[1] = (c[1] - 5) ;
                }
                else
                {
                    if (c[1]-c[0] == 20)
                    {
                        c[0]=c[0] + 20;
                        c[1]=(c[1] - 5) ;
                    }
                    else
                    {
                        c[0]=(c[0] - 5) ;
                        c[1]=(c[1] - 5) ;
                        if (c[0] > 24)
                            c[0] = c[0] - 25;
                        if (c[1] > 24)
                            c[1] = c[1] - 25;
                    }
                }
                a1[l] = matrix[c[0]];
                a1[l+1] = matrix[c[1]];
            }
        }else if(b[0]<b[1])
        {
            s=abs(b[0] -b[1]);
            a1[l] = matrix[c[0]+s];
            a1[l+1] = matrix[c[1]-s];
        }

        else if (b[0] >b[1])
        {
            s= (b[0]-b[1]);
            a1[l] = matrix[c[0]-s];
            a1[l+1] = matrix[c[1]+s];
        }
    }return a1;
}
string l(string a,int p1)
{
    for (int i=0;i<p1;i++)
    {
        if(a[i]<91&&a[i]>64)
            a[i]+=32;
    }
    return a;
}
int r(string a,int p1)
{
    int k=0;
    for (int i=0;i<p1;i++)
    {
        if(a[i]!=' ')
            a[k++]=a[i];
    }
    a[k]='\0';
    return k;
}
string made(string temp)
{
    int h=temp.length();
    h--;
    string temp1;
    char t;
    for(int i=0;i<6;i++)
    {
      t=temp[h];
      temp1=temp1+t;
      h--;
    }
    string m=temp1;
    int len=temp1.length();
    len=r(temp1,len);
    m=l(temp1,len);string a;
    int i=0,k=0,v=0,c=0;
    bool flag = true;
    for (int p = 0;p<len;p++)
        if (m[p] == 'j')
            m[p] = 'i';
    for (int u=0;u<len;u++)
    {
        for (k=0;k<u;k++)
        {
            if (m[u]==m[k])
                flag= false;
        }
        if (flag == true)
        {
            char z=m[u];
            a = a +z;i++;
        }
        flag=true;
    }
    while(c<26)
    {
        for (k=0;k<len;k++)
        {
            if (v==m[k]-97)
            {
                flag=false;
            }
        }
        if (flag==true)
        {
            if (v!= 9)
            {
              char z=97+v;
                a = a+z; i++;
            }
        }
        v++;c++;k=0;flag=true;
    }
    return a;
}
string code(string textin1,string matrix)
{
  int e=textin1.length();
  e=r(textin1,e);
  string keyword=l(textin1, e);
  keyword=prepare(keyword,e);
  textin1=keyword;
  string ch= keyword;
  int c[2];int a[2];int b[2];
  int s= 0;
  int or1= 0;
  int textlen =e;
    for (int l= 0; l < textlen; l = l + 2)
    {
        for (int i = 0; i< 26; i++)
        {
            if (textin1[l] == matrix[i])
                c[0] = i;
            if (textin1[l+1] == matrix[i])
                c[1] =i;
        }
        for(int m=0;m<2;m++)
        {
            if(c[m]<5 )
                a[m] = 1;
            else if(c[m]<10&& c[m]>4)
                a[m] = 2;
            else if(c[m]<15 && c[m]>9 )
                a[m] = 3;
            else if(c[m]<20 && c[m]>14)
                a[m] = 4;
            else
                a[m] = 5;
            if (c[m]%5==0)
                b[m] = 1;
            else if(c[m]%5==1)
                b[m] = 2;
            else if(c[m]%5==2)
                b[m] = 3;
            else if (c[m]%5==3)
                b[m] = 4;
            else
                b[m] = 5;
        }
        if(a[0]==a[1]||b[0]==b[1])
        {
            if (a[0]==a[1])
            {
                or1= a[0];
                c[0] = (c[0] + 1);
                c[1] = (c[1] + 1);
                for (int m=0;m<2;m++)
                {
                    if (c[m]<5 )
                        a[m] = 1;
                    else if (c[m]<10&&c[m]>4)
                        a[m] = 2;
                    else if (c[m]<15 && c[m]>9)
                        a[m] = 3;
                    else if (c[m]<20 && c[m]>14)
                        a[m] = 4;
                    else
                        a[m] = 5;
                }
                if (a[0] != or1)
                    c[0] = c[0] - 5;
                if (a[1] != or1)
                    c[1] = c[1] - 5;
                ch[l] = matrix[c[0]];
                ch[l+1] = matrix[c[1]];
            }
            if (b[0] == b[1])
            {
                c[0] = (c[0] + 5) ;
                c[1] = (c[1] + 5) ;
                if (c[0] > 24)
                    c[0] = c[0]-25;
                if (c[1] > 24)
                    c[1] = c[1]-25;
                ch[l] = matrix[c[0]];
                ch[l+1] = matrix[c[1]];
            }
        }
        else if (b[0] < b[1])
        {
            s = abs(b[0] - b[1]);
            ch[l] = matrix[c[0]+s];
            ch[l+1] = matrix[c[1]-s];
        }
        else if (b[0] > b[1])
        {
            s= (b[0] - b[1]);
            ch[l] = matrix[c[0]-s];
            ch[l+1] = matrix[c[1]+s];
        }
    }
    return ch;
}
string prepare(string txtin,int n)
{
    for (int i=0;i<n;i++)
    {
        if (txtin[i]=='j')
            txtin[i]='i';
    }
    if (n%2!=0)
        txtin= txtin+ "x";
    n=txtin.length();
    for (int i=0;i<n;i=i+2)
    {
        if (txtin[i] == txtin[i+1])
        {
          txtin=txtin+" ";
          n= txtin.length();
          for (int j=n -1;j>i;j--)
            txtin[j]=txtin[j-1];
          txtin[i + 1] = 'x';
        }
    }return txtin;
}
string inputs()
{
    ifstream Inputs;string h,e;
    cout<<"Please enter filename"<<"\n";
    cin>> e;
    Inputs.open(e.c_str(),ios::in);
    if(!Inputs)
    {
        cout<<"error"<< "\n";
        return 0;
    }
    while(Inputs)
    {
        Inputs >> h;
    }
    Inputs.close();
    return h;
}
void outputs(string h)
{
    ofstream outs;string e;
    cout<<"enter file name"<<"\n";
    cin>>e;
    outs.open(e.c_str(), ios :: out);
    if(!outs)
        cout<<"error"<<"\n";
    if(outs.is_open())
    {
        outs<<h;
        outs.close();
    }
}
