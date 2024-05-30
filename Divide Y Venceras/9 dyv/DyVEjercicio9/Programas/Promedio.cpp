#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void GeneradorCasoPromedio(int n)
{
 for (int i=0 ; i<n ; i++)
        {
        	char c= 'a'+ rand() % 26;
                cout<<c;
        }
        cout<<endl;
        string cadena1;
        string cadena2;
        string cadena3;
        for(int i=0; i<3 ; i++)
        {
        char c= 'a'+ rand() % 26;
        cadena1+=c;
        }
        for(int i=0; i<3 ; i++)
        {
        char c= 'a'+ rand() % 26;
        cadena2+=c;
        }
        for(int i=0; i<3 ; i++)
        {
        char c= 'a'+ rand() % 26;
        cadena3+=c;
        }
        cout<<cadena1<<endl;
        cout<<cadena2<<endl;
        cout<<cadena3<<endl;
}

int main()
{
     int n;
     cin>>n;
     GeneradorCasoPromedio(n);
}
