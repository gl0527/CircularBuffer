#pragma once

#include <cassert>

template<typename T, std::size_t N>
class CircularBuffer {
public:
    void push(T const& elem, bool overwrite = true) noexcept;
    T pop() noexcept;

    std::size_t size() const noexcept;
    constexpr std::size_t capacity() const noexcept;
    bool empty() const noexcept;
    bool full() const noexcept;

private:
    T m_buffer[N]{};
    std::size_t m_data_start{0};
    std::size_t m_data_end{0};
    std::size_t m_size{0};
};

template<typename T, std::size_t N>
void CircularBuffer<T, N>::push(T const &elem, bool overwrite) noexcept {
    if (m_size == N && !overwrite) {
        return;
    }
    m_buffer[m_data_end] = elem;
    m_data_end = (m_data_end + 1) % N;
    if (m_size == N) {
        m_data_start = (m_data_start + 1) % N;
    } else {
        ++m_size;
    }
}

template<typename T, std::size_t N>
T CircularBuffer<T, N>::pop() noexcept {
    assert(m_size > 0);
    T tmp = m_buffer[m_data_start];
    m_data_start = (m_data_start + 1) % N;
    --m_size;
    return tmp;
}

template<typename T, std::size_t N>
inline std::size_t CircularBuffer<T, N>::size() const noexcept {
    return m_size;
}

template<typename T, std::size_t N>
constexpr std::size_t CircularBuffer<T, N>::capacity() const noexcept {
    return N;
}

template<typename T, std::size_t N>
inline bool CircularBuffer<T, N>::empty() const noexcept {
    return m_size == 0;
}

template<typename T, std::size_t N>
inline bool CircularBuffer<T, N>::full() const noexcept {
    return m_size == N;
}
