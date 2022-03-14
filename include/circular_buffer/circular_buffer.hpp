/**
 * @file circular_buffer.hpp
 * @brief Simple circular buffer implementation.
 *
 * @author gl0527 <gurzolajos27@gmail.com>
 * @date 02 Jan 2022
 */

#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP

#include <cassert>
#include <type_traits>

namespace lg {

template<std::size_t N>
struct is_pow2 {
    static constexpr bool value = N > 0 && ((N & (N - 1)) == 0);
};

template<std::size_t N>
constexpr bool is_pow2_v = is_pow2<N>::value;

/**
 * @brief Circular buffer implementation.
 * @tparam T Type of buffered elements.
 * @tparam N Size of the buffer.
 * @tparam Overwrite A flag which determines what should happen if the buffer is full.
 *                   If true, subsequent elements will overwrite previously added ones.
 *                   If false, subsequent elements get ignored.
 */
template<typename T, std::size_t N, bool Overwrite = true>
class CircularBuffer {
public:
    /**
     * @brief Adds an element to the buffer (after the last element).
     * @param[in] elem The element to be added to the buffer.
     * @return Void.
     */
    // Note: 2 implementations are provided because of modulo optimization,
    // 1 for power-of-2 numbers, and 1 for the rest.
    template<std::size_t U = N, std::enable_if_t<is_pow2_v<U>>* = nullptr>
    void push(T const& elem) noexcept;

    template<std::size_t U = N, std::enable_if_t<!is_pow2_v<U>>* = nullptr>
    void push(T const& elem) noexcept;

    /**
     * @brief Gives back the first element of the buffer, and also removes it from there.
     * @return The first element of the buffer.
     */
    // Note: 2 implementations are provided because of modulo optimization,
    // 1 for power-of-2 numbers, and 1 for the rest.
    template<std::size_t U = N, std::enable_if_t<is_pow2_v<U>>* = nullptr>
    T pop() noexcept;

    template<std::size_t U = N, std::enable_if_t<!is_pow2_v<U>>* = nullptr>
    T pop() noexcept;

    /**
     * @brief Resets the buffer to its initial state.
     * This function only resets the indices and size variables, but does not alter the buffer.
     * @return Void.
     */
    void reset() noexcept;

    /**
     * @brief Gives back the number of elements in the buffer.
     * @return The number of elements in the buffer.
     */
    std::size_t size() const noexcept;

    /**
     * @brief Gives back the maximum number of elements in the buffer.
     * @return The maximum number of elements in the buffer.
     */
    constexpr std::size_t capacity() const noexcept;

    /**
     * @brief Checks if the buffer is empty.
     * @return True if the buffer is empty, false otherwise.
     */
    bool empty() const noexcept;

    /**
     * @brief Checks if the buffer is full.
     * @return True if the buffer is full, false otherwise.
     */
    bool full() const noexcept;

private:
    T m_buffer[N]{};                ///< The array which contains all the elements.
    std::size_t m_data_start{0};    ///< The index where the data starts.
    std::size_t m_data_end{0};      ///< The index after the last element of the data.
    std::size_t m_size{0};          ///< The number of elements in the array.
};

template<typename T, std::size_t N, bool Overwrite>
template<std::size_t U, std::enable_if_t<is_pow2_v<U>>*>
void CircularBuffer<T, N, Overwrite>::push(T const &elem) noexcept {
    if (m_size == N) {
        if constexpr (!Overwrite) {
            return;
        }
        m_data_start = (m_data_start + 1) & (N - 1);
    } else {
        ++m_size;
    }
    m_buffer[m_data_end] = elem;
    m_data_end = (m_data_end + 1) & (N - 1);
}

template<typename T, std::size_t N, bool Overwrite>
template<std::size_t U, std::enable_if_t<!is_pow2_v<U>>*>
void CircularBuffer<T, N, Overwrite>::push(T const &elem) noexcept {
    if (m_size == N) {
        if constexpr (!Overwrite) {
            return;
        }
        if (++m_data_start == N) {
            m_data_start = 0;
        }
    } else {
        ++m_size;
    }
    m_buffer[m_data_end] = elem;
    if (++m_data_end == N) {
        m_data_end = 0;
    }
}

template<typename T, std::size_t N, bool Overwrite>
template<std::size_t U, std::enable_if_t<is_pow2_v<U>>*>
T CircularBuffer<T, N, Overwrite>::pop() noexcept {
    assert(m_size > 0);
    T tmp = m_buffer[m_data_start];
    m_data_start = (m_data_start + 1) & (N - 1);
    --m_size;
    return tmp;
}

template<typename T, std::size_t N, bool Overwrite>
template<std::size_t U, std::enable_if_t<!is_pow2_v<U>>*>
T CircularBuffer<T,N, Overwrite>::pop() noexcept {
    assert(m_size > 0);
    T tmp = m_buffer[m_data_start];
    if (++m_data_start == N) {
        m_data_start = 0;
    }
    --m_size;
    return tmp;
}

template<typename T, std::size_t N, bool Overwrite>
inline void CircularBuffer<T, N, Overwrite>::reset() noexcept {
    m_data_start = 0;
    m_data_end = 0;
    m_size = 0;
}

template<typename T, std::size_t N, bool Overwrite>
inline std::size_t CircularBuffer<T, N, Overwrite>::size() const noexcept {
    return m_size;
}

template<typename T, std::size_t N, bool Overwrite>
constexpr std::size_t CircularBuffer<T, N, Overwrite>::capacity() const noexcept {
    return N;
}

template<typename T, std::size_t N, bool Overwrite>
inline bool CircularBuffer<T, N, Overwrite>::empty() const noexcept {
    return m_size == 0;
}

template<typename T, std::size_t N, bool Overwrite>
inline bool CircularBuffer<T, N, Overwrite>::full() const noexcept {
    return m_size == N;
}

}   // namespace lg

#endif  // #ifndef CIRCULAR_BUFFER_HPP
