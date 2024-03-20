#ifndef VECTOR_H
#define VECTOR_H

#include "cstdlib"
#include "type_traits"
#include "algorithm"
#include "optional"

template <typename T>
class Vector
{
private:
    T* buf;
    size_t len;
    size_t cap;

    static constexpr size_t MIN_NON_ZERO_CAP = 8;

public:
    Vector() : buf(nullptr), len(0), cap(0) {}

    ~Vector()
    {
        delete[] buf;
    }

    // Reserves capacity for at least additional elements
    // After calling, capacity will be >= length + additional
    // Does nothing if capacity is sufficient
    void reserve(size_t additional)
    {
        if (additional > this->cap - this->len)
        {
            if (std::is_empty<T>())
            {
                // This shouldn't happen as we return std::numeric_limits<size_t>::max()
                // When sizeof(T) = 0, so if we reach this point
                // Something has gone terribly wrong
                std::abort();
            }

            // TODO: Check for overflow
            auto required_cap = this->len + additional;
            this->cap = std::max({this->cap * 2, required_cap, MIN_NON_ZERO_CAP});

            auto alloc = new T[cap];
            std::copy_n(this->buf, len, alloc);
            delete[] this->buf;
            this->buf = alloc;
        }
    }

    void push(T value)
    {
        if (this->len == this->cap)
        {
            reserve(1);
        }

        *(this->buf + this->len) = value;
        this->len += 1;
    }

    std::optional<T> pop_back()
    {
        if (this->len == 0)
        {
            return std::nullopt;
        }
        else
        {
            this->len -= 1;
            return *(this->buf + this->len);
        }
    }
};

#endif // VECTOR_H
