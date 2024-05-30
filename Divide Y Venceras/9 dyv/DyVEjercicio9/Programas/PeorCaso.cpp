#include <iostream>

using namespace std;

void GeneradorPeorCaso(int n)
{
 for (int i=0 ; i<n ; i++)
        {
                cout<<"a";
        }
        cout<<endl;
        cout<<"aaa"<<endl;
        cout<<"aaa"<<endl;
        cout<<"aaa"<<endl;
}

int main()
{
     int n;
     cin>>n;
     GeneradorPeorCaso(n);
}
