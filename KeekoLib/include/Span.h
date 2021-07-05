#pragma once
#include <memory>

template<class T>
class Span
{
public:
    Span() = delete;
    Span<T>(const std::initializer_list<T> &lst);

private:
    std::unique_ptr<T> data;
};

