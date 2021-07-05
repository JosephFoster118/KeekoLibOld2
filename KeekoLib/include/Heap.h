#pragma once
#include <vector>
#include <utility>
#include <functional>
#include <exception>
#include <iostream>




struct HeapEmptyException : public std::exception
{
	const char * what () const throw ()
    {
    	return "Heap Empty: tried poping/peaking empty heap";
    }
};


template<class T1, class T2>
class Heap
{
public:
    typedef std::function<bool(T1,T1)> CompareFunction;

    

    Heap<T1,T2>(CompareFunction comp = [](T1 a, T1 b)->bool
    {
        return a >= b;
    })
    {
        comp_lambda = comp;
    };

    std::pair<T1,T2> peak();
    std::pair<T1,T2> pop();
    void insert(T1,T2);

private:
    std::vector<std::pair<T1,T2>> data;
    CompareFunction comp_lambda;
    void swapElements(uint32_t a, uint32_t b);

};

template<class T1, class T2>
void Heap<T1,T2>::swapElements(uint32_t a, uint32_t b)
{
    std::pair<T1,T2> temp = data[a];
    data[a] = data[b];
    data[b] = temp;
}

template<class T1, class T2>
std::pair<T1,T2> Heap<T1,T2>::peak()
{
    if(data.empty())
    {
        throw HeapEmptyException{};
    }
    return data[0];
}

template<class T1, class T2>
std::pair<T1,T2> Heap<T1,T2>::pop()
{
    if(data.empty())
    {
        throw HeapEmptyException{};
    }
    std::pair<T1,T2> result = data[0];

    //reform heap
    data[0] = data[data.size() - 1];
    data.pop_back();
    for(uint32_t current_index = 1; current_index <= data.size()/2;)
    {
        //std::cout << current_index << std::endl;
        uint32_t left = current_index*2 - 1;
        uint32_t right = current_index*2;
        uint32_t current = current_index - 1;

        uint swap_index = !comp_lambda(data[left].first,data[right].first) ? right:left;

        if(comp_lambda(data[current].first,data[swap_index].first))
        {
            break;
        }

        swapElements(swap_index, current);

        current_index = swap_index + 1;

        


    }



    return result;
}


template<class T1, class T2>
void Heap<T1,T2>::insert(T1 key,T2 value)
{
    data.push_back(std::pair<T1,T2>{key,value});
    for(uint32_t current_index = data.size(); current_index > 1; current_index/=2)
    {
        if(comp_lambda(data[current_index - 1].first, data[(current_index/2) - 1].first))
        {
            std::pair<T1,T2> temp = data[current_index - 1];
            data[current_index - 1] = data[(current_index/2) - 1];
            data[(current_index/2) - 1] = temp;
        }
        else
        {
            break;
        }
    }
}





