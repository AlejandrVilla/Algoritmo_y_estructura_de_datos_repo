#include <iostream>
#include <ostream>
#include <vector>
#include "vertex.h"
#include "edge.h"
#include "grafo.h"
using namespace std;

int main()
{
    int n,m;cin>>n>>m;
    vector<string> filas(n);
    for(int i=0;i<n;i++)
        cin>>filas[i];
    int r,c;cin>>r>>c;

    Grafo<pair<int,int>,char> caminos;
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;j++)
        {
            if( filas[i][j] != 'X' )
            {
                caminos.Insert_Vertex( make_pair( i,j ) );
                if( i!=0 )
                    caminos.Insert_Arista( make_pair(i,j), make_pair(i-1,j), filas[i][j] );
                if( j!=0 )    
                    caminos.Insert_Arista( make_pair(i,j), make_pair(i,j-1), filas[i][j] ); 
            }
        }
    }
    pair<int,int> v=make_pair(r-1,c-1);
    caminos.solve( v );
}