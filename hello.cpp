#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<stdlib.h>
#include <limits>
using namespace std;

string inputfile();
void outputfile(string);
string toLowerCase(string,int);
int removeSpaces(string,int);
string Create(string);
string encrypt(string,string);
string prepare(string,int);
string decrypt(string, string);
int main()
{
  cout<<"##############################################"<<endl;
  cout<<"         ##########################           "<<endl;
  cout<<"      Playfair cypher Encrypt/Decrypt         "<<endl;
  cout<<"         ##########################           "<<endl;
  cout<<"##############################################"<<endl;

  int c;
  string filename;
  string key;
  int method = 0;
  string plaintext = "";
  string ciphertext = "";
  string matrix = "";
  while(1)
  {
    cout<<"----------------------------------------------"<<endl;
    cout<<"Make a choice"<<endl;
    cout<<"1: Encrypt the message"<<endl;
    cout<<"2: Decrypt the message"<<endl;
    cout<<"3: Quit"<<endl;
    cout<<"----------------------------------------------"<<endl;
    cin>>c;
    switch(c)
        {
        case 1: key = inputfile();
                matrix = Create(key);
                //cout<<matrix;
                plaintext = inputfile();
                ciphertext = encrypt(plaintext, matrix);
                //cout<<ciphertext;
                outputfile(ciphertext);
                break;
        case 2: key = inputfile();
                matrix = Create(key);
                ciphertext=inputfile();
                plaintext=decrypt(ciphertext,matrix);
                //cout<<plaintext;
                outputfile(plaintext);
                break;
        case 3: exit(0);
        default:cout<<"invalid choice"<<endl;
        }
  }
  return 0;
}
string decrypt(string cipher, string matrix )
{
    string plain = cipher;
    int loc[2];
    int row[2];
    int col[2];
    int shift = 0;
    int original_row = 0;
    int n = 0;
    int m = 0;
    int textlen = cipher.length();
    for (n = 0; n < textlen; n = n + 2)
    {
        loc[0] = 0;loc[1] = 0;
        for (int temp = 0; temp < 26; temp++)
        {
            if (plain[n] == matrix[temp])
            {
                loc[0] = temp;
            }
            if (plain[n+1] == matrix[temp])
            {
                loc[1] = temp;
            }
        }
        for (m = 0; m < 2; m++)
        {
            if (loc[m] < 5 )
            {
                row[m] = 1;
            }
            else if (loc[m] > 4 && loc[m] < 10)
            {
                row[m] = 2;
            }
            else if (loc[m] > 9 && loc[m] < 15 )
            {
                row[m] = 3;
            }
            else if (loc[m] > 14 && loc[m] < 20)
            {
                row[m] = 4;
            }
            else
            {
                row[m] = 5;
            }
            if (loc[m] == 0 || loc[m] == 5 || loc[m] == 10 || loc[m] == 15 || loc[m] == 20)
            {
                col[m] = 1;
            }
            else if (loc[m] == 1 || loc[m] == 6 || loc[m] == 11 || loc[m] == 16 || loc[m] == 21)
            {
                col[m] = 2;
            }
            else if (loc[m] == 2 || loc[m] == 7 || loc[m] == 12 || loc[m] == 17 || loc[m] == 22)
            {
                col[m] = 3;
            }
            else if (loc[m] == 3 || loc[m] == 8 || loc[m] == 13 || loc[m] == 18 || loc[m] == 23)
            {
                col[m] = 4;
            }
            else
            {
                col[m] = 5;
            }
        }
        if (row[0] == row[1] || col[0] == col[1])
        {
            if (row[0] == row[1])
            {
                original_row = row[0];
                loc[0] = (loc[0] - 1);
                loc[1] = (loc[1] - 1);
                for (m = 0; m < 2; m++)
                {
                    if (loc[m] < 5 )
                    {
                        row[m] = 1;
                    }
                    else if (loc[m] > 4 && loc[m] < 10)
                    {
                        row[m] = 2;
                    }
                    else if (loc[m] > 9 && loc[m] < 15 )
                    {
                        row[m] = 3;
                    }
                    else if (loc[m] > 14 && loc[m] < 20)
                    {
                        row[m] = 4;
                    }
                    else
                    {
                        row[m] = 5;
                    }
                }

                if (row[0] != original_row || loc[0] < 0)
                {
                    loc[0] = loc[0] + 5;
                }
                if (row[1] != original_row || loc[1] < 0)
                {
                    loc[1] = loc[1] + 5;
                }
                plain[n] = matrix[loc[0]];
                plain[n+1] = matrix[loc[1]];

            }
            else if (col[0] == col[1]) //same column
            {
                if (loc[0] > loc[1]) //account for upper rollover
                {
                    loc[0] = (loc[0] - 5) ;
                    loc[1] = (loc[1] - 5) ;
                    if (loc[1] < 0)
                    {
                        loc[1] = (loc[1] + 25) ;
                    }
                }
                else if (loc[0] < loc[1] && loc[0] < 4) //account for lower rollover
                {
                    loc[0] = (loc[0] + 5) ; //Inverse of encryption shift
                    loc[1] = (loc[1] - 5) ; //Inverse of encryption shift
                }
                else
                {
                    if (loc[1] - loc[0] == 20) //account for adjacent column special case
                    {
                        loc[0] = loc[0] + 20; //Inverse of encryption shift
                        loc[1] = (loc[1] - 5) ; //Inverse of encryption shift
                    }

                    else //normal cases
                    {
                        loc[0] = (loc[0] - 5) ; //Inverse of encryption shift
                        loc[1] = (loc[1] - 5) ; //Inverse of encryption shift
                        if (loc[0] > 24)
                        {
                            loc[0] = loc[0] - 25; //account for wraparound
                        }
                        if (loc[1] > 24)
                        {
                            loc[1] = loc[1] - 25; //account for wraparound
                        }
                    }
                }
                plain[n] = matrix[loc[0]]; //assign the result location to be cipher char
                plain[n+1] = matrix[loc[1]]; //assign the result location to be cipher char
            }
        }
        else if (col[0] < col[1]) //if the second letter has a higher column
        {
            shift = abs(col[0] - col[1]);//col difference between char 1 - char 2
            loc[0] = loc[0] + shift;//location point right after shift
            loc[1] = loc[1] - shift;//location point right after shift
            plain[n] = matrix[loc[0]]; //assign the result location to be cipher char
            plain[n+1] = matrix[loc[1]]; //assign the result location to be cipher char
        }

        else if (col[0] > col[1]) //if the first letter has a higher column
        {
            shift = (col[0] - col[1]); //col difference between char 1 - char 2
            loc[0] = loc[0] - shift;//location point right after shift
            loc[1] = loc[1] + shift;//location point right after shift
            plain[n] = matrix[loc[0]]; //assign the result location to be cipher char
            plain[n+1] = matrix[loc[1]]; //assign the result location to be cipher char
        }
    }
    return plain;
}
string toLowerCase(string plain, int ps)
{
    int i;
    for (i = 0; i < ps; i++) {
        if (plain[i] > 64 && plain[i] < 91)
            plain[i] += 32;
    }
    return plain;
}
int removeSpaces(string plain, int ps)
{
    int i, count = 0;
    for (i = 0; i < ps; i++)
        if (plain[i] != ' ')
            plain[count++] = plain[i];
    plain[count] = '\0';
    return count;
}
string Create(string temp)
{
    string keyword=temp;
    int len = temp.length();
    len= removeSpaces(temp,len);
    keyword=toLowerCase(temp, len);
    string array;

    int i = 0;
    bool unique = true;
    int run = 1;

    int k = 0;
    int value = 0;
    int count = 0;


    for (int tmp = 0; tmp < len; tmp++)
    {
        if (keyword[tmp] == 'j')
        {
            keyword[tmp] = 'i';
        }
    }
    /**********************************/
    for (run = 0; run < len; run++) //run loop once for each letter of key
    {
        for (k = 0; k < run; k++)
        {
            if (keyword[run] == keyword[k])
            {
                unique = false;
            }
        }
        if (unique == true) //Letter has not been used in table
        {
            char z=keyword[run];
            array = array +z; //give the location the correct ascii value
            i++;//increment matrix since it has been filled
        }
        unique = true;
    }
    /*** put the rest of the characters in **/
    while (count < 26)
    {
        for (k = 0; k < len; k++)
        {
            if (value == keyword[k] - 97)
            {
                unique = false;
            }
        }
        if (unique == true) //Letter has not been used in table
        {
            if (value != 9) //not j since it is being bunched with i
            {
              char z=97+value;
                array = array+z; //give the location the correct ascii value
                i++;//increment matrix since it has been filled
            }
        }
        value++;
        count++;
        k = 0;
        unique = true;
    }
    return array;
}
string encrypt(string plain, string matrix)
{
  string keyword="";
  int len = plain.length();
  len= removeSpaces(plain,len);
  keyword=toLowerCase(plain, len);
  keyword=prepare(keyword,len);
  plain=keyword;
  string ciphertxt = keyword;
  int loc[2];
  int row[2];
  int col[2];
  int shift = 0;
  int original_row = 0;
  int n = 0;
  int textlen = len;
    for (n = 0; n < textlen; n = n + 2) //run half the length (diagrams)
    {
        //Assign letters to their locations in matrix
        for (int temp = 0; temp < 26; temp++)
        {
            if (plain[n] == matrix[temp])
            {
                loc[0] = temp; //location of the first letter in pair
            }
            if (plain[n+1] == matrix[temp])
            {
                loc[1] = temp; //location of the second letter in pair
            }
        }
        /* Find Row and Column Numbers */
        for (int m = 0; m < 2; m++)
        {
            if (loc[m] < 5 ) // Location second row
            {
                row[m] = 1;
            }
            else if (loc[m] > 4 && loc[m] < 10) // Location second row
            {
                row[m] = 2;
            }
            else if (loc[m] > 9 && loc[m] < 15 ) // Location third row
            {
                row[m] = 3;
            }
            else if (loc[m] > 14 && loc[m] < 20) // Location fourth row
            {
                row[m] = 4;
            }
            else // Location fifth row
            {
                row[m] = 5;
            }
            if (loc[m] == 0 || loc[m] == 5 || loc[m] == 10 || loc[m] == 15 || loc[m] == 20)
            {
                // Location first column
                col[m] = 1;
            }
            else if (loc[m] == 1 || loc[m] == 6 || loc[m] == 11 || loc[m] == 16 || loc[m] == 21)
            {
                // Location second column
                col[m] = 2;
            }
            else if (loc[m] == 2 || loc[m] == 7 || loc[m] == 12 || loc[m] == 17 || loc[m] == 22)
            {
                // Location third column
                col[m] = 3;
            }
            else if (loc[m] == 3 || loc[m] == 8 || loc[m] == 13 || loc[m] == 18 || loc[m] == 23)
            {
                // Location fourth column
                col[m] = 4;
            }
            else
            {
                // Location fifth column
                col[m] = 5;
            }
        }
        //Start that encryption and shifting :-)
        if (row[0] == row[1] || col[0] == col[1]) //same row or same column: special case
        {
            if (row[0] == row[1]) //same row
            {
                original_row = row[0]; //sets a baseline for starting row
                loc[0] = (loc[0] + 1);
                loc[1] = (loc[1] + 1);
                /* Find Row after shift */
                for (int m = 0; m < 2; m++)
                {
                    if (loc[m] < 5 )
                    {
                        row[m] = 1;
                    }
                    else if (loc[m] > 4 && loc[m] < 10)
                    {
                        row[m] = 2;
                    }
                    else if (loc[m] > 9 && loc[m] < 15 )
                    {
                        row[m] = 3;
                    }
                    else if (loc[m] > 14 && loc[m] < 20)
                    {
                        row[m] = 4;
                    }
                    else
                    {
                        row[m] = 5;
                    }
                }
                if (row[0] != original_row)
                {
                    loc[0] = loc[0] - 5;
                }
                if (row[1] != original_row)
                {
                    loc[1] = loc[1] - 5;
                }
                ciphertxt[n] = matrix[loc[0]]; //assign the resultant location to be cipher char
                ciphertxt[n+1] = matrix[loc[1]];
            }
            if (col[0] == col[1]) //same column
            {
                loc[0] = (loc[0] + 5) ;
                loc[1] = (loc[1] + 5) ;
                if (loc[0] > 24)
                {
                    loc[0] = loc[0] - 25;
                }
                if (loc[1] > 24)
                {
                    loc[1] = loc[1] - 25;
                }
                ciphertxt[n] = matrix[loc[0]]; //assign the result location to be cipher char
                ciphertxt[n+1] = matrix[loc[1]];
            }
        }
        else if (col[0] < col[1]) //if the second letter has a higher column
        {
            shift = abs(col[0] - col[1]); //col difference between char 1 - char 2
            loc[0] = loc[0] + shift;//location point right after shift
            loc[1] = loc[1] - shift;
            ciphertxt[n] = matrix[loc[0]]; //assign the result location to be cipher char
            ciphertxt[n+1] = matrix[loc[1]];
        }
        else if (col[0] > col[1]) //if the first letter has a higher column
        {
            shift = (col[0] - col[1]); //col difference between char 1 - char 2
            loc[0] = loc[0] - shift;//location point right after shift
            loc[1] = loc[1] + shift;
            ciphertxt[n] = matrix[loc[0]];
            ciphertxt[n+1] = matrix[loc[1]];
        }
    }
    return ciphertxt;
}
string prepare(string text,int len)
{
    int i = 0;
    int j = 0;
    /*** Change all j's into i's *****/
    for (int tmp = 0; tmp < len; tmp++)
    {
        if (text[tmp] == 'j')
        {
            text[tmp] = 'i';
        }
    }
    /**********************************/
    if (len % 2 == 0)
    {
        cout<<"plaintext is even"<<endl;
    }
    else
    {
        cout<< "plaintext is odd"<<endl;
        text = text + "x"; //add x as a filler to the end
    }
    len = text.length();
    for (i = 0; i < len; i = i + 2) //run for half of string length
    {
        if (text[i+1] == text[i]) //if char = previous char
        {
            text = text + " ";//increase length
            len = text.length();
            for (j = len -1; j > i; j--) //j starts a top len, will run till it hits i
            {
                text[j] = text[j-1]; //last letter = previous letter
            }
            text[i + 1] = 'x';
        }
        else //not a repeat character, move along
        {}
    }
    return text;
}
string inputfile()
{
    ifstream Inputfile;
    string text;
    string filename;
    int i = 0;
    cout<<"Please enter filename for input (ex C://plain.txt)"<<endl;
    cin>> filename;
    Inputfile.open(filename.c_str(), ios :: in);
    if ( !Inputfile )
    {
        cout << "PROBLEM! " << endl;
        return 0;
    }
    while ( Inputfile )
    {
        Inputfile >> text;
    }
    Inputfile.close();
    return text;
}
void outputfile(string info)
{
    ofstream outfile;
    string filename;
    int i = 0;
    cout<<"Please enter filename for output (ex C://plain.txt)"<<endl;
    cin>> filename;
    outfile.open(filename.c_str(), ios :: out);
    if ( !outfile )
    {
        cout << "PROBLEM! " << endl;
    }
    if (outfile.is_open())
    {
        outfile << info;
        outfile.close();
    }
}
