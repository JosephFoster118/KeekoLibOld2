#include "Span.h"


template<class T>
Span<T>::Span(const std::initializer_list<T> &lst)
{
    data(new T[lst.size()]);
    for(unsigned int i = 0; i < lst.size(); i++)
    {
        data[i] = lst[i];
    }
}

