#ifndef LISTE1_H
#define LISTE1_H

#include <iostream>
#include "Task.h"

using namespace std;

template <typename T>
struct list_elem
{
    T info;
    list_elem<T>* next;
    list_elem<T>* prev;
};

template <typename T>
class LinkedList
{
public:
    list_elem<T>* pfirst;
    list_elem<T>* plast;

    void addFirst(T x)
    {
        list_elem<T>* paux = new list_elem<T>;
        paux->info = x;

        paux->prev = NULL;
        paux->next = pfirst;

        if (pfirst != NULL)
            pfirst->prev = paux;

        pfirst = paux;

        if (plast == NULL)
            plast = pfirst;
    }

    void addLast(T x)
    {
        list_elem<T>* paux = new list_elem<T>;
        paux->info = x;
        paux->prev = plast;

        paux->next = NULL;

        if (plast != NULL)
            plast->next = paux;

        plast = paux;

        if (pfirst == NULL)
            pfirst = plast;
    }

    T getInfo(list_elem<T>* p)
    {
        return p->info;
    }

    void removeFirst()
    {
        list_elem<T>* paux;

        if (pfirst != NULL)
        {
            paux = pfirst->next;

            if (pfirst == plast)
                plast = NULL;

            delete pfirst;

            pfirst = paux;

            if (pfirst != NULL)
                pfirst->prev = NULL;
        }
        else
            cout << "The list is empty" << endl;
    }

    void removeLast()
    {
        list_elem<T>* paux;

        if (plast != NULL)
        {
            paux = plast->prev;

            if (pfirst == plast)
                pfirst = NULL;

            delete plast;

            plast = paux;

            if (plast != NULL)
                plast->next = NULL;
        }
        else
            cout << "The list is empty" << endl;
    }

    list_elem<T>* findFirstOccurrence(T x)
    {
        list_elem<T>* paux;

        paux = pfirst;

        while (paux != NULL)
        {
            if (paux->info == x)
                return paux;

            paux = paux->next;
        }

        return NULL;
    }

    list_elem<T>* findLastOccurrence(T x)
    {
        list_elem<T>* paux;

        paux = plast;

        while (paux != NULL)
        {
            if (paux->info == x)
                return paux;

            paux = paux->prev;
        }

        return NULL;
    }

    void removeFirstOccurrence(T x)
    {
        list_elem<T>* px;

        px = findFirstOccurrence(x);

        if (px != NULL)
        {
            if (px->prev != NULL)
                px->prev->next = px->next;

            if (px->next != NULL)
                px->next->prev = px->prev;

            if (px->prev == NULL)
                pfirst = px->next;

            if (px->next == NULL)
                plast = px->prev;

            delete px;
        }
    }

    void removeLastOccurrence(T x)
    {
        list_elem<T>* px;

        px = findLastOccurrence(x);

        if (px != NULL)
        {
            if (px->prev != NULL)
                px->prev->next = px->next;

            if (px->next != NULL)
                px->next->prev = px->prev;

            if (px->prev == NULL)
                pfirst = px->next;

            if (px->next == NULL)
                plast = px->prev;

            delete px;
        }
    }

    bool isEmpty()
    {
        // returns 1 if the list is empty and 0 if the list is not empty
        return (pfirst == NULL);
    }

    LinkedList()
    {
        pfirst = plast = NULL;
    }

    ~LinkedList() {
        while (!isEmpty()) {
            removeFirst();
        }
    }
};

#endif
