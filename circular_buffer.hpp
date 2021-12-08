#pragma once

#include <cstdlib>
#include <cassert>
#include <cstring>

constexpr void inc(std::size_t& n, std::size_t m) {
    n = (n + 1) % m;
}

// Interface

template<typename T, std::size_t N>
class CircularBuffer {
public:
    CircularBuffer();

    void push(T const& elem, bool overwrite = true);
    T pop();

    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;
    bool full() const;

private:
    T m_buffer[N];
    std::size_t m_data_start;
    std::size_t m_data_end;
    std::size_t m_size;
};

// Implementation

template<typename T, std::size_t N>
inline CircularBuffer<T,N>::CircularBuffer()
    : m_data_start{0}
    , m_data_end{0}
    , m_size{0}
{
    memset(m_buffer, 0, sizeof(m_buffer));
}

template<typename T, std::size_t N>
void CircularBuffer<T, N>::push(T const &elem, bool overwrite) {
    if (m_size == N && !overwrite) {
        return;
    }
    m_buffer[m_data_end] = elem;
    inc(m_data_end, N);
    if (m_size == N) {
        inc(m_data_start, N);
    } else {
        ++m_size;
    }
}

template<typename T, std::size_t N>
T CircularBuffer<T, N>::pop() {
    assert(m_size > 0);
    T tmp = m_buffer[m_data_start];
    inc(m_data_start, N);
    --m_size;
    return tmp;
}

template<typename T, std::size_t N>
inline std::size_t CircularBuffer<T, N>::size() const {
    return m_size;
}

template<typename T, std::size_t N>
inline std::size_t CircularBuffer<T, N>::capacity() const {
    return N;
}

template<typename T, std::size_t N>
inline bool CircularBuffer<T, N>::empty() const {
    return m_size == 0;
}

template<typename T, std::size_t N>
inline bool CircularBuffer<T, N>::full() const {
    return m_size == N;
}
