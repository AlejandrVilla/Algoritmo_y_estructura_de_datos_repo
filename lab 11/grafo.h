#ifndef GRAFO_H
#define GRAFO_H
#include <list>
#include <fstream>
#include <unordered_set>
#include <queue>

template<class V,class E>class Vertex;

template <class V, class E>
class Grafo
{
private:
    std::list<Vertex<V, E>> m_grafo;
public:
    Grafo(){}
    Vertex<V, E> *find_Vertex(V);
    void Insert_Vertex(V);
    void Insert_Arista(V , V , E );

    void delete_vertex(V);                
    void delete_Arista(V , V , E );      
    bool esVacio();             
    bool existeVertex(V);       
    bool sonAdyacentes(V ,V);   

    void verAdyacencias();

    void graficar(std::string);    

    void DFS();   
    void DFS_visit(Vertex<V,E>* ,std::unordered_set<V>& ,std::unordered_set<V>& ); 
    void BFS();

    void solve(std::pair<int,int>&);
};

template<class V,class E>
Vertex<V, E> *Grafo<V,E>::find_Vertex(V v)
{
    Vertex<V, E> *p = nullptr;
    for( auto it = m_grafo.begin() ; it!=m_grafo.end() ; ++it )
        if ( it->m_Dato == v )
            p = &(*it);
    return p;
}

template<class V,class E>
void Grafo<V,E>::Insert_Vertex(V dato)
{
    m_grafo.push_back(Vertex<V, E>(dato));
}

template<class V,class E>
void Grafo<V,E>::Insert_Arista(V v1, V v2, E Ar)
{
    Vertex<V, E> *p = find_Vertex(v1);
    Vertex<V, E> *q = find_Vertex(v2);

    if (p && q)
    {
        p->m_Aristas.push_back(Edge<V, E>(Ar, q));
        q->m_Aristas.push_back(Edge<V, E>(Ar, p));
    }
}

template<class V,class E>
void Grafo<V,E>::delete_vertex(V dato)
{
    Vertex<V,E>* p = find_Vertex(dato);
    for(auto it = m_grafo.begin(); it!=m_grafo.end() ; ++it)
    {
        for(auto it2 = it->m_Aristas.begin() ; it2!=it->m_Aristas.end() ; ++it2)
        {
            if(it2->m_pVertes->m_Dato == dato)
                it->m_Aristas.erase(it2);
        }
    }
    m_grafo.remove(*p);
}

template<class V,class E>
void Grafo<V,E>::delete_Arista(V v1, V v2, E dato)
{
    for(auto it = m_grafo.begin(); it!=m_grafo.end() ; ++it)
    {
        if(it->m_Dato == v1 || it->m_Dato == v2)
        {
            for(auto it2 = it->m_Aristas.begin() ; it2!=it->m_Aristas.end() ; ++it2)
            {
                if(it2->m_Dato == dato)
                    it->m_Aristas.erase(it2);
            }
        }
    }
}

template<class V,class E>
bool Grafo<V,E>::esVacio()
{   
    if( m_grafo.size() == 0 )
        return true;
    return false;
}

template<class V,class E>
bool Grafo<V,E>::existeVertex(V v)
{
    for( auto it = m_grafo.begin() ; it!=m_grafo.end() ; ++it)
        if( it->m_Dato == v )
            return true;
    return false;
}

template<class V,class E>
bool Grafo<V,E>::sonAdyacentes(V v1,V v2)
{
    Vertex<V,E>* p = find_Vertex(v1);
    Vertex<V,E>* q = find_Vertex(v2);
    if( p && q )
    {
        for( auto it = p->m_Aristas.begin() ; it!=p->m_Aristas.end() ; ++it )
        {
            if( it->m_pVertes == q )
                return true;
        }
    }
    return false;
}

template<class V,class E>
void Grafo<V,E>::verAdyacencias()
{
    for(auto it = m_grafo.begin(); it!=m_grafo.end() ; ++it)
    {
        std::cout<<it->m_Dato<<" -> ";
        for(auto it2 = it->m_Aristas.begin() ; it2!=it->m_Aristas.end() ; ++it2)
            std::cout<<"("<<(it2->m_pVertes)->m_Dato<<", "<<it2->m_Dato<<") -> ";
        std::cout<<"\n";
    }
}

template<class V,class E>
void Grafo<V,E>::graficar(std::string dir)
{
    std::ofstream f;
    std::unordered_set<V> vertices;
    f.open(dir);
    f<<"graph G{\n";
    for(auto it = m_grafo.begin(); it!=m_grafo.end() ; ++it)
    {
        vertices.insert( it->m_Dato );
        f<<it->m_Dato<<";\n";
        for(auto it2 = it->m_Aristas.begin() ; it2!=it->m_Aristas.end() ; ++it2)
        {
            if( vertices.find( (it2->m_pVertes)->m_Dato ) == vertices.end() )
            {
                f<<it->m_Dato<<" -- ";
                f<<(it2->m_pVertes)->m_Dato<<"[label="<<it2->m_Dato<<"];\n";
            }
        }
    }
    f<<"}";
    f.close();
}

template<class V,class E>
void Grafo<V,E>::DFS()
{
    std::unordered_set< V > gray;
    std::unordered_set< V > black;
    for( auto it=m_grafo.begin() ; it!=m_grafo.end() ; ++it )
    {
        if( gray.find(it->m_Dato) == gray.end() && black.find(it->m_Dato) == black.end() )
        {
            gray.insert(it->m_Dato);
            std::cout<<it->m_Dato<<"->";
            DFS_visit(&(*it),gray,black);
        }
    }
}

template<class V,class E>
void Grafo<V,E>::DFS_visit(Vertex<V,E>* vertice,std::unordered_set<V>& gray,std::unordered_set<V>& black)
{
    for( auto it2=vertice->m_Aristas.begin() ; it2!=vertice->m_Aristas.end() ; ++it2 )
    {
        if( gray.find((it2->m_pVertes)->m_Dato) == gray.end() && black.find((it2->m_pVertes)->m_Dato) == black.end() )
        {
            gray.insert((it2->m_pVertes)->m_Dato);
            std::cout<<it2->m_pVertes->m_Dato<<"->";
            DFS_visit(it2->m_pVertes,gray,black);
        }
    }
    black.insert(vertice->m_Dato);
}

template<class V,class E>
void Grafo<V,E>::BFS()
{
    std::queue< Vertex<V,E>* > vertices;
    std::unordered_set< V > enCola;
    std::unordered_set< V > visitados;
    Vertex<V,E>* ver = &(*m_grafo.begin());
    vertices.push( ver );
    enCola.insert(ver->m_Dato);
    while( !vertices.empty() )
    {
        for( auto it2=ver->m_Aristas.begin() ; it2!=ver->m_Aristas.end(); ++it2 )
        {
            if( enCola.find( ( it2->m_pVertes)->m_Dato ) == enCola.end() && visitados.find( ( it2->m_pVertes)->m_Dato ) == visitados.end() )
            {
                vertices.push(it2->m_pVertes);
                enCola.insert((it2->m_pVertes)->m_Dato);
            }
        }
        vertices.pop();
        enCola.erase(ver->m_Dato);
        visitados.insert(ver->m_Dato);
        std::cout<<ver->m_Dato<<"->";
        if(!vertices.empty())
            ver = vertices.front();
    }
    std::cout<<'\n';
}   

template<class V,class E>
void Grafo<V,E>::solve(std::pair<int,int>& v)
{
    std::queue< Vertex<V,E>* > vertices;
    std::unordered_set< V* > enCola;
    std::unordered_set< V* > visitados;
    Vertex<V,E>* ver = find_Vertex(v);
    vertices.push( ver );
    enCola.insert( &(ver->m_Dato) );
    while( !vertices.empty() )
    {
        for( auto it2=ver->m_Aristas.begin() ; it2!=ver->m_Aristas.end(); ++it2 )
        {
            if( enCola.find( ( &(it2->m_pVertes)->m_Dato) ) == enCola.end() && visitados.find( &(( it2->m_pVertes)->m_Dato) ) == visitados.end() )
            {
                if( it2->m_Dato == 't' )
                {
                    std::cout<<"yes\n";
                    return;
                }
                vertices.push(it2->m_pVertes);
                enCola.insert( &((it2->m_pVertes)->m_Dato) );
            }
        }
        vertices.pop();
        enCola.erase( &(ver->m_Dato) );
        visitados.insert( &(ver->m_Dato) );
        // std::cout<<ver->m_Dato.first<<' '<<ver->m_Dato.second<<"->";
        if(!vertices.empty())
            ver = vertices.front();
    }
    std::cout<<"no\n";
}   

#endif