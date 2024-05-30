#include <iostream>
#include <string>
#include <list>

using namespace std;

string s1;
string s2;
string s3;
string s4;

list<int> SolucionDirecta(int in,int final) {
    list <int> salida;
    if(final-in<5){return salida;}
    else{
        string sub1=s1.substr(in,3);
        string sub2=s1.substr(in+3,3);
        if((sub1 == s2 && sub2 == s3) || (sub1 == s2 && sub2 == s4) || (sub1 == s3 && sub2 == s2) || (sub1 == s3 && sub2 == s4) || (sub1 == s4 && sub2 == s2) || (sub1 == s4 && sub2 == s3))
        {   
            salida.push_back(in+1);
        }
    }
    return salida;
}

list<int> Combinar(int in1,int final1,int in2,int final2,list<int> sa1,list<int> sa2)
{   
    list<int> sa3;
    sa3.merge(sa2);
    sa3.merge(sa1);
    for(int i=final1;i<final1+5;i++)
    {   
        if( i-4 >= in1  && i+1 <= final2) {
            sa3.merge(SolucionDirecta(i-4,i+1));
        }
    }
    return sa3;
}

list<int> dyv(int in,int final)
{   list<int> sa2;
    list<int> sa1;
    if((final-in)<=5)
    {
        return SolucionDirecta(in,final);
    }
    else
    {
        int m=(final-in+1)/2;
        list<int> sa2=dyv(in,in+m);
        list<int> sa1=dyv(in+m+1,final);
        return Combinar(in,in+m,in+m+1,final,sa1,sa2);
    }
}

int main()
{
    cin>>s1>>s2>>s3>>s4;
    list<int>sal= dyv(0,s1.length()-1);
    cout<<"La solucion es : "<<sal.size()<<endl;
    for(int salida:sal)
    {
        cout<<salida<<" ";
    }
    return 0;
}