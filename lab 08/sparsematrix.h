#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include "cell.h"
#include <iostream>

//Insertar, eliminar, buscar mayor, buscar menor , mostrar
template <typename T, const int n_Fil = 10, const int n_Col=10>
class SparseMatrix
{
private:
    Cell<T> *m_Fil[n_Fil];
    Cell<T> *m_Col[n_Col];

public:
    SparseMatrix();
    bool find_col(int,int,Cell<T>**&);
    bool find_fil(int,int,Cell<T>**&);
    void insert(T,int,int);
    void eliminar(int,int);
    T buscarMayor(T);
    T buscarMenor(T);
    void mostrar();
};

template<typename T,const int n_Fil,const int n_Col>
SparseMatrix<T,n_Fil,n_Col>::SparseMatrix()
{
    for (int i = 0; i < n_Fil; i++)
         m_Fil[i] = 0;
      for (int i = 0; i < n_Col; i++)
         m_Col[i] = 0;
}

template<typename T,const int n_Fil,const int n_Col>
bool SparseMatrix<T,n_Fil,n_Col>::find_col(int f, int c, Cell<T> **&q)  // busca en el array de filas
{
    q = &m_Fil[f];
    while (*q)
    {
        if ((*q)->m_Col == c)
        return true;
        if ((*q)->m_Col > c)
        return false;
        q = &((*q)->m_SigCol);
    }
    return false;
}

template<typename T,const int n_Fil,const int n_Col>
bool SparseMatrix<T,n_Fil,n_Col>::find_fil(int f, int c, Cell<T> **&p) // busca en el array de columnas
{
    p = &m_Col[c];
    while (*p)
    {
        if ((*p)->m_Fil == f)
        return true;
        if ((*p)->m_Fil > f)
        return false;
        p = &((*p)->m_SigFil);
    }
    return false;
}

template<typename T,const int n_Fil,const int n_Col>
void SparseMatrix<T,n_Fil,n_Col>::insert(T d, int f, int c)
{
    Cell<T> **p;
    Cell<T> **q;
    bool a = find_fil(f, c, p);
    bool b = find_col(f, c, q);
    if (!a && !b)
    {
        Cell<T> *pNuevo = new Cell<T>(d, f, c);
        pNuevo->m_SigFil = *p;
        pNuevo->m_SigCol = *q;
        *p = *q = pNuevo;
    }
}

template<typename T,const int n_Fil,const int n_Col>
void SparseMatrix<T,n_Fil,n_Col>::eliminar(int f, int c)
{
    Cell<T>** p;
    Cell<T>** q;
    bool a = find_fil(f, c, p);
    bool b = find_col(f, c, q);
    if(a && b)
    {
        Cell<T>* aux = *p;
        *p = (*p)->m_SigFil;
        *q = (*p)->m_SigCol;
        delete aux;
    }
}


template<typename T,const int n_Fil,const int n_Col>
T SparseMatrix<T,n_Fil,n_Col>::buscarMayor( T d )
{
    T max = d;
    Cell<T>* tmp = nullptr;
    for( int i = 0 ; i < n_Fil ; i++ )
    {
        tmp = m_Fil[i];
        for( ; tmp != nullptr ; tmp = tmp->m_SigCol )
            if( tmp->m_Dato > max )
                max = tmp->m_Dato;
    }
    return max;
}

template<typename T,const int n_Fil,const int n_Col>
T SparseMatrix<T,n_Fil,n_Col>::buscarMenor( T d )
{
    T min = d;
    Cell<T>* tmp = m_Fil[0];
    for( int i = 0 ; i < n_Fil ; i++ )
    {
        for( ; tmp != nullptr ; tmp = tmp->m_SigCol )
            if( tmp->m_Dato < min )
                min = tmp->m_Dato;
    }
    return min;
}

template<typename T,const int n_Fil,const int n_Col>
void SparseMatrix<T,n_Fil,n_Col>::mostrar()
{
    Cell<int> **q;
    for (int i = 0 ; i < n_Fil ; i++)
    {
        for (int j = 0 ; j < n_Col ; j++)
        {
            if (find_fil(i, j, q))
                std::cout << (*q)->m_Dato << " ";
            else
                std::cout << "0 ";
        }
        std::cout << '\n';
    }
}


#endif