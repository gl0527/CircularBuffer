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
#include <cstdlib>
#include <utility>

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
     * @brief Adds an element to the buffer (after the last element).
     * @param[in] elem The element to be added to the buffer.
     * @param[in] overwrite A flag which determines what should happen if the buffer is full.
     *                      If true, subsequent elements will overwrite previously added ones.
     *                      If false, subsequent elements get ignored.
     */
    void push(T &&elem, bool overwrite = true) noexcept;

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
    T buffer_[N]{};             ///< The array which contains all the elements.
    std::size_t head_{0};       ///< The index where the data starts.
    std::size_t tail_{0};       ///< The index after the last element of the data.
    bool full_{false};          ///< A flag which is true when the buffer is full.
};

template<typename T, std::size_t N>
void CircularBuffer<T, N>::push(T const &elem, bool overwrite) noexcept {
    if (full_) {
        if (!overwrite) {
            return;
        }
        head_ = (head_ + 1) % N;
    }
    buffer_[tail_] = elem;
    tail_ = (tail_ + 1) % N;
    full_ = head_ == tail_;
}

template<typename T, std::size_t N>
void CircularBuffer<T, N>::push(T &&elem, bool overwrite) noexcept {
    if (full_) {
        if (!overwrite) {
            return;
        }
        head_ = (head_ + 1) % N;
    }
    buffer_[tail_] = std::move(elem);
    tail_ = (tail_ + 1) % N;
    full_ = head_ == tail_;
}

template<typename T, std::size_t N>
T CircularBuffer<T, N>::pop() noexcept {
    assert(!empty());
    const auto old_head = head_;
    head_ = (head_ + 1) % N;
    full_ = false;
    return std::move(buffer_[old_head]);
}

template<typename T, std::size_t N>
inline void CircularBuffer<T, N>::reset() noexcept {
    head_ = 0;
    tail_ = 0;
    full_ = false;
}

template<typename T, std::size_t N>
inline std::size_t CircularBuffer<T, N>::size() const noexcept {
    if (full_) {
        return N;
    }

    if (tail_ >= head_) {
        return tail_ - head_;
    }

    return N + tail_ - head_;
}

template<typename T, std::size_t N>
constexpr std::size_t CircularBuffer<T, N>::capacity() const noexcept {
    return N;
}

template<typename T, std::size_t N>
inline bool CircularBuffer<T, N>::empty() const noexcept {
    return !full_ && head_ == tail_;
}

template<typename T, std::size_t N>
inline bool CircularBuffer<T, N>::full() const noexcept {
    return full_;
}

}   // namespace lg

#endif  // #ifndef CIRCULAR_BUFFER_HPP
