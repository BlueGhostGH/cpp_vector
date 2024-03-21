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
    Vector() noexcept : buf(nullptr), len(0), cap(0) {}

    Vector(std::initializer_list<T> init_list) : buf(nullptr), len(0), cap(0)
    {
        reserve(next_power_of_two(init_list.size()));

        for (const auto& elem : init_list)
        {
            push(elem);
        }
    }

    Vector(size_t len) : buf(nullptr), len(0), cap(0)
    {
        reserve(next_power_of_two(len));

        for (size_t i = 0; i < len; i++)
        {
            push(T());
        }
    }

    Vector(size_t len, const T& elem) : buf(nullptr), len(0), cap(0)
    {
        reserve(next_power_of_two(len));

        for (size_t i = 0; i < len; i++)
        {
            push(elem);
        }
    }

    Vector(const Vector& other) : buf(nullptr), len(0), cap(0)
    {
        reserve(other.cap);

        for (size_t i = 0; i < other.len; i++)
        {
            push(other[i]);
        }
    }

    Vector(Vector&& other) noexcept : buf(other.buf), len(other.len), cap(other.cap)
    {
        other.buf = nullptr;
        other.len = 0;
        other.cap = 0;
    }

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

    size_t length() const noexcept
    {
        return this->len;
    }

    size_t capacity() const noexcept
    {
        return this->capacity();
    }

    bool is_empty() const noexcept
    {
        return this->len == 0;
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

    std::optional<T> pop_back() noexcept
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

    void clear() noexcept
    {
        this->len = 0;
    }

    std::optional<T&> operator[](size_t idx)
    {
        if (idx >= this->len)
        {
            return std::nullopt;
        }
        else
        {
            return *(this->buf + idx);
        }
    }
};

// This MAY overflow
size_t next_power_of_two(size_t number)
{
    if (number <= 1)
    {
        return 1;
    }

    return std::numeric_limits<size_t>::max() >> std::countl_zero(number - 1) + 1;
}

#endif // VECTOR_H
