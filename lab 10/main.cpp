#include <iostream>
#include <list>
#include <ostream>
#include "vertex.h"
#include "edge.h"
#include "grafo.h"
using namespace std;

int main()
{
    cout<<"CREANDO GRAFO VACIO\n";
    Grafo<string, int> G;

    cout<<"\nNSERTANDO VERTICES\n";
    G.Insert_Vertex("Arequipa");
    G.Insert_Vertex("Lima");
    G.Insert_Vertex("Cuzco");
    G.Insert_Vertex("Puno");
    G.Insert_Vertex("Ica");
    G.Insert_Vertex("Tacna");
    G.Insert_Vertex("Moquegua");

    cout<<"\nINSERTANDO ARISTAS\n";
    G.Insert_Arista("Arequipa", "Cuzco", 250);
    G.Insert_Arista("Arequipa", "Puno", 200);
    G.Insert_Arista("Lima", "Ica", 100);
    G.Insert_Arista("Lima", "Arequipa", 160);
    G.Insert_Arista("Tacna", "Moquegua", 160);
    G.Insert_Arista("Moquegua", "Arequipa", 160);
    G.Insert_Arista("Moquegua", "Puno", 160);

    cout<<"\nMOSTRANDO LISTA DE ADYACENCIA\n";
    G.verAdyacencias();

    cout<<"\nBUSCANDO VERTICE AREQUIPA\n";
    cout<<G.existeVertex("Arequipa");
    cout<<"\nBUSCANDO VERTICE PIURA\n";
    cout<<G.existeVertex("Piura");

    cout<<"\nCOMPROBANDO SI AREQUIPA Y LIMA SON ADYACENTES\n";
    cout<<G.sonAdyacentes("Lima","Arequipa");
    cout<<"\nCOMPROBANDO SI LIMA Y PUNO SON ADYACENTES\n";
    cout<<G.sonAdyacentes("Lima","Puno");

    cout<<"\nGRAFICANDO GRAFO INICIAL\n";
    G.graficar("grafoAntes1.dot");
    system("dot grafoAntes1.dot -o grafoAntes1.png -Tpng");           //dot grafo.dot -o grafo.png -Tpng
    system("grafoAntes1.png");

    cout<<"\nELIMINANDO ARISTA (Arequipa, Lima, 160)\n";
    G.delete_Arista("Arequipa","Lima",160);

    cout<<"\nMOSTRANDO LISTA DE ADYACENCIA\n";
    G.verAdyacencias();

    cout<<"\nGRAFICANDO DESPUES DE ELIMINAR ARISTA\n";
    G.graficar("grafoAntes2.dot");
    system("dot grafoAntes2.dot -o grafoAntes2.png -Tpng");           //dot grafo.dot -o grafo.png -Tpng
    system("grafoAntes2.png");

    cout<<"\nELIMINANDO VERTICE Arequipa\n";
    G.delete_vertex("Arequipa");

    cout<<"\nMOSTRANDO LISTA DE ADYACENCIA\n";
    G.verAdyacencias();

    cout<<"\nGRAFICANDO DESPUES DE ELIMINAR VERTICE";
    G.graficar("grafoDespues.dot");
    system("dot grafoDespues.dot -o grafoDespues.png -Tpng");           //dot grafo.dot -o grafo.png -Tpng
    system("grafoDespues.png");


    return 1;
}