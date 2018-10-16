//
//  LinkedList.cpp
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList()
{
    this->head = new Node<string>();
    this->tail = new Node<string>();
    
    this->head->setNext(this->tail);
    this->head->setPrevious(NULL);

    this->tail->setNext(NULL);
    this->tail->setPrevious(this->head);

    this->quantity = 0;
}

LinkedList::~LinkedList()
{
    Node<string>* n = this->head;
    
    while(n != this->tail)
    {
        Node<string>* toDestroy = n;
        
        n = n->getNext();
        
        delete toDestroy;
    }
    
    delete this->tail;
}

Node<string>* LinkedList::getHead(void)
{
    return this->head;
}

Node<string>* LinkedList::getTail(void)
{
    return this->tail;
}

int LinkedList::getQuantity(void)
{
    return this->quantity;
}

bool LinkedList::isEmpty(void)
{
    return this->quantity == 0;
}

string LinkedList::get(int i)
{
    if( i < 1 || i > this->getQuantity())
    {
        throw invalid_argument("Valor do índice de busca deve estar entre [1, quantity].");
    }
    
    int counter = 1;
    
    string result;
    for(Node<string>* n = this->head->getNext(); n != this->tail; n = n->getNext())
    {
        if( i == counter )
        {
            result = n->getValue();
            break;
        }
        counter++;
    }
    
    return result;
}

int LinkedList::search(string s)
{
    int cont = 1;
    bool result = false;
    for(Node<string>* no = head->getNext();no->getNext()!=nullptr;no=no->getNext())
    {
        if(no->getValue() == s)
        {
            result = true;
            return cont;
        }
        
        if(result != true)
        {
            cont++;
        }
    }
    //Elemento nao encontrado
    return -1;

    //std::cout << "\tERRO - Método search ainda não foi implementado.\n";
    //return -1;
}

void LinkedList::print(void)
{
    for(Node<string>* n = this->head->getNext(); n != this->tail; n = n->getNext())
    {
        std::cout << n->getValue() << " ";
    }
    std::cout << std::endl;
}

ListStatus LinkedList::checkConsistency()
{
    if( this->head == NULL )
    {
        return HeadNull;
    }
    else if( this->head->getNext() == NULL )
    {
        return HeadNextNull;
    }
    else if( this->head->getNext()->getPrevious() != this->head )
    {
        return IncorrectLink;
    }
    else if( this->head->getPrevious() != NULL )
    {
        return HeadPrevious;
    }
    
    if( this->tail == NULL )
    {
        return TailNull;
    }
    else if( this->tail->getPrevious() == NULL )
    {
        return TailPreviousNull;
    }
    else if( this->tail->getPrevious()->getNext() != this->tail )
    {
        return IncorrectLink;
    }
    else if( this->tail->getNext() != NULL )
    {
        return TailNext;
    }
    
    if(this->isEmpty())
    {
        if( this->head->getNext() != this->tail )
        {
            return HeadTail;
        }
        
        if( this->head != this->tail->getPrevious() )
        {
            return HeadTail;
        }
    }
    else
    {
        // Verifica encadeamento dos elementos
        for(Node<string>* i = this->head->getNext(); i != this->tail; i=i->getNext())
        {
            if( i->getNext()->getPrevious() != i )
            {
                return IncorrectLink;
            }
            if( i->getPrevious()->getNext() != i )
            {
                return IncorrectLink;
            }
        }
    }
    
    return OK;
}

bool LinkedList::insertBegin(string s)
{
	//Criando no com a string passada
    Node<string>* no = new Node<string>(s);
    //Posicionando o novo no
    no->setPrevious(head);
    no->setNext(head->getNext());
    //Atualizando os vizinhos do no posicionado
    no->getNext()->setPrevious(no);
    no->getPrevious()->setNext(no);

    ++this->quantity;
    return true;
}

bool LinkedList::insertEnd(string s)
{
    //Criando no com a string passada
    Node<string>* no = new Node<string>(s);
    //Posicionando o novo no
    no->setNext(tail);
    no->setPrevious(tail->getPrevious());
    //Atualizando os vizinhos do no posicionado
    no->getNext()->setPrevious(no);
    no->getPrevious()->setNext(no);
    ++this->quantity;
    return true;
}

bool LinkedList::insert(int i, string s)
{
    return false;
}

void LinkedList::unlink(Node<string>* a)
{
    a->getPrevious()->setNext(a->getNext());
    a->getNext()->setPrevious(a->getPrevious());
}

bool LinkedList::insertOrdered(string s)
{
    Node<string>* aux = new Node<string>(s);
    if(this->isEmpty())
    {
        this->insertBegin(s);
        return true;
    }
    else
    {
        
        return false;
    }
}

Node<string>* LinkedList::searchCF(string s)
{
	for(Node<string>* no = head->getNext();no->getNext()!=nullptr;no=no->getNext())
    {
        if(no->getValue() == s)
        {
            searchMF(no->getValue());
            return head->getNext();
        }
    }
    //Não encontra e retorna ponteiro nulo
    return nullptr;
}

Node<string>* LinkedList::searchMF(string s)
{
    for(Node<string>* no = head->getNext();no->getNext()!=nullptr;no=no->getNext())
    {
        if(no->getValue() == s)
        {
            unlink(no);
            insertBegin(no->getValue());
            return head->getNext();
        }
    }
    //Não encontra e retorna ponteiro nulo
    return nullptr;
}

string LinkedList::removeEnd(void)
{
    //Criando um auxiliar com o nó que vem antes da cauda
    Node<string>* aux = tail->getPrevious();
    //Trocando os links dos anteriores e posteriores a aux
    unlink(aux);
    --this->quantity;
    return aux->getValue();
}

string LinkedList::removeBegin(void)
{
    //Criando um auxiliar com o nó que vem após a cabeca
    Node<string>* aux = head->getNext();
    //Trocando os links dos anteriores e posteriores a aux
    unlink(aux);
    --this->quantity;
    return aux->getValue();
}

string LinkedList::remove(int indice)
{
    return "";
}
