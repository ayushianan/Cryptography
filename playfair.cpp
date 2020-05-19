#include<bits/stdc++.h>
using namespace std;
int main()
{
  cout<<"##############################################"<<endl;
  cout<<"         ##########################           "<<endl;
  cout<<"      Playfair cypher Encrypt/Decrypt         "<<endl;
  cout<<"         ##########################           "<<endl;
  cout<<"##############################################"<<endl;

  int c=0;
  while(c!=10)
  {
    cout<<"----------------------------------------------"<<endl;
    cout<<"Make a choice"<<endl;
    cout<<"1: Encrypt the message"<<endl;
    cout<<"2: Decrypt the message"<<endl;
    cout<<"3: Quit"<<endl;
    cout<<"----------------------------------------------"<<endl;
    cin>>c;
    switch(choice)
        {
        case 1: key = getkey();
                matrix = Create_Matrix(key);
                plaintext = inputfile();
                plaintext = format(plaintext);
                ciphertext = encrypt(plaintext, matrix);//Submit data to encryption function
                method = outputmethod();
        case 2:
        case 3:
        default:
        }
  }


  return 0;
}
