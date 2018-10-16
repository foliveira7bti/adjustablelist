//
//  TestList.cpp
//
//  Created by Eiji Adachi Medeiros Barbosa 
//

#include "TestList.h"
#include "LinkedList.h"
#include <string>
#include <iostream>

using namespace std;

bool test_InsertOrdered()
{
    cout << "INÍCIO: Test InsertOrdered" << endl;
    
    bool resultado = true;
    
    LinkedList* lista = new LinkedList();
    
    string v[] = {"delta","echo","bravo","charlie","alpha","fox","juliet","hotel","india","golf"};
    
    for(int i = 0; i < 10; i++)
    {
        int tamanhoAntes = lista->getQuantity();
        
        string valorInserido = v[i];
        
        bool inseriu = lista->insertOrdered(valorInserido);
        if( !inseriu )
        {
            cerr << "\tERRO - Teste InsertOrdered: não inseriu elemento na lista corretamente." << endl;
            resultado = false;
            break;
        }
        
        ListStatus verificada = lista->checkConsistency();
        if( verificada != OK )
        {
            cerr << "\tERRO - Teste InsertOrdered: alguma invariante da lista foi quebrada. Código do erro: " << verificada << endl;
            resultado = false;
            break;
        }
        
        int tamanhoDepois = lista->getQuantity();
        
        if( tamanhoDepois != tamanhoAntes + 1 )
        {
            cerr << "\tERRO - Teste InsertOrdered: tamanho da lista não foi incrementado corretamente." << endl;
            resultado = false;
            break;
        }
        
        // Verifica se está ordenado
        for( Node<string>* no = lista->getHead()->getNext(); no != lista->getTail()->getPrevious(); no = no->getNext() )
        {
            string valor = no->getValue();
            string valorProximo = no->getNext()->getValue();
            if( valor > valorProximo )
            {
                cerr << "\tERRO - Teste InsertOrdered: lista não está ordenada corretamente." << endl;
                resultado = false;
                break;
            }
        }
    }
    
    delete lista;
    
    cout << "FIM: Teste InsertOrdered" << endl << endl;
    
    return resultado;
}

bool test_SearchCF()
{
    cout << "INÍCIO: Teste SearchCF" << endl;
    
    bool resultado = true;
    
    LinkedList* lista = new LinkedList();
    
    string v[] = {"alpha","bravo","charlie","delta","echo","fox","golf","hotel","india","juliet"};
    
    for(int i = 0; i < 10; i++)
    {
        string valorInserido = v[i];
        lista->insertEnd(valorInserido);
    }
    
    for(int i = 0; i < 10; i++)
    {
        string valorBuscado = v[9-i];
        
        Node<string>* noRetornado = lista->searchCF(valorBuscado);
        
        string valorRetornado = noRetornado->getValue();
        
        if( valorRetornado != valorBuscado )
        {
            cerr << "\tERRO - Teste SearchCF: buscou a chave " << valorBuscado << ", mas retornou nó com conteúdo igual a " << valorRetornado << endl;
            resultado = false;
            break;
        }
        
        for( Node<string>* no = lista->getHead()->getNext(); no->getNext() != lista->getTail(); no = no->getNext() )
        {
            if( no->getCount() < no->getNext()->getCount() )
            {
                cerr << "\tERRO - Teste SearchCF: a lista não está ordenada pelo contador de acessos." << endl;
                resultado = false;
                break;
            }
        }
        
        ListStatus verificada = lista->checkConsistency();
        if( verificada != OK )
        {
            cerr << "\tERRO - Teste SearchCF: alguma invariante da lista foi quebrada. Código do erro: " << verificada << endl;
            resultado = false;
            break;
        }
    }
    
    if(!resultado)
    {
        return resultado;
    }
    
    string inexistentes[] = {"0", "50", "100", "200"};
    
    for(int i = 0; i < 4; i++)
    {
        int indiceRetornado = lista->search(inexistentes[i]);
        if( indiceRetornado != -1 )
        {
            cerr << "\tERRO - Teste SearchCF: buscou chave inexistente e não retornou -1." << endl;
            resultado = false;
            break;
        }
        
        ListStatus verificada = lista->checkConsistency();
        if( verificada != OK )
        {
            cerr << "\tERRO - Teste SearchCF: alguma invariante da lista foi quebrada. Código do erro: " << verificada << endl;
            resultado = false;
            break;
        }
    }
    
    delete lista;
    
    cout << "FIM: Teste SearchCF" << endl << endl;
    
    return resultado;
}

bool test_SearchMF()
{
    cout << "INÍCIO: Teste SearchMF" << endl;
    
    bool resultado = true;
    
    LinkedList* lista = new LinkedList();;
    
    string v[] = {"alpha","bravo","charlie","delta","echo","fox","golf","hotel","india","juliet"};
    
    for(int i = 0; i < 10; i++)
    {
        string valorInserido = v[i];
        lista->insertEnd(valorInserido);
    }
    
    for(int i = 0; i < 10; i++)
    {
        string valorBuscado = v[9-i];
        
        Node<string>* noRetornado = lista->searchMF(valorBuscado);
        
        ListStatus verificada = lista->checkConsistency();
        if( verificada != OK )
        {
            cerr << "\tERRO - Teste SearchMF: alguma invariante da lista foi quebrada. Código do erro: " << verificada << endl;
            resultado = false;
            break;
        }
        
        string valorRetornado = noRetornado->getValue();
        
        if( valorRetornado != valorBuscado )
        {
            cerr << "\tERRO - Teste SearchMF: buscou a chave " << valorBuscado << ", mas retornou nó com conteúdo igual a " << valorRetornado << endl;
            resultado = false;
            break;
        }
        
        if( lista->getHead()->getNext() != noRetornado )
        {
            cerr << "\tERRO - Teste SearchMF: o nó retornado não foi movido para o início da lista." << endl;
            resultado = false;
            break;
        }
    }
    
    if(!resultado)
    {
        return resultado;
    }
    
    string inexistentes[] = {"0", "50", "100", "200"};
    
    for(int i = 0; i < 4; i++)
    {
        int indiceRetornado = lista->search(inexistentes[i]);
        if( indiceRetornado != -1 )
        {
            cerr << "\tERRO - Teste SearchMF: buscou chave inexistente e não retornou -1." << endl;
            resultado = false;
            break;
        }
        
        ListStatus verificada = lista->checkConsistency();
        if( verificada != OK )
        {
            cerr << "\tERRO - Teste SearchMF: alguma invariante da lista foi quebrada. Código do erro: " << verificada << endl;
            resultado = false;
            break;
        }
    }
    
    delete lista;
    
    cout << "FIM: Teste SearchMF" << endl << endl;
    
    return resultado;
}
