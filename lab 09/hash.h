#ifndef HASH_H
#define HASH_H
#include <iostream>
#include <list>

template <class O, class K, int (*fd)(std::string, int), const int size = 11>
class Hash
{
private:
    std::list<O> m_list[size];

public:
    Hash(){}
    void Add(O, K);             // O = pos del genoma, clave string
    void Delete(K);             // ingresa string del genoma a eliminar
    O find(K);                  // busca genoma 
};

template <class O, class K, int (*fd)(std::string, int), const int size>
void Hash<O, K, fd, size>::Add(O obj, K key)
{
    int pos = fd(key, size);
    std::cout << "Se insertó elemento en la posición:" << pos << '\n';
    m_list[pos].push_back(obj);
}

#endif