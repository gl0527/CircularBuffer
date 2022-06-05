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

namespace lg {

/**
 * @brief Circular buffer implementation.
 * @tparam T Type of buffered elements.
 * @tparam N Size of the buffer.
 */
template<typename T, std::size_t N>
class CircularBuffer {
public:
    /**
     * @brief Adds an element to the buffer (after the last element).
     * @param[in] elem The element to be added to the buffer.
     * @param[in] overwrite A flag which determines what should happen if the buffer is full.
     *                      If true, subsequent elements will overwrite previously added ones.
     *                      If false, subsequent elements get ignored.
     */
    void push(T const& elem, bool overwrite = true) noexcept;

    /**
     * @brief Gives back the first element of the buffer, and also removes it from there.
     * @return The first element of the buffer.
     */
    T pop() noexcept;

    /**
     * @brief Resets the buffer to its initial state.
     *
     * This function only resets the indices and size variables, but does not alter the buffer.
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

template<typename T, std::size_t N>
void CircularBuffer<T, N>::push(T const &elem, bool overwrite) noexcept {
    if (m_size == N) {
        if (!overwrite) {
            return;
        }
        m_data_start = (m_data_start + 1) % N;
    } else {
        ++m_size;
    }
    m_buffer[m_data_end] = elem;
    m_data_end = (m_data_end + 1) % N;
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
inline void CircularBuffer<T, N>::reset() noexcept {
    m_data_start = 0;
    m_data_end = 0;
    m_size = 0;
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

}   // namespace lg

#endif  // #ifndef CIRCULAR_BUFFER_HPP
