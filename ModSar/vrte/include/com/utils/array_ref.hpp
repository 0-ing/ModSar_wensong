#ifndef COM_UTILS_ARRAY_REF_HPP
#define COM_UTILS_ARRAY_REF_HPP

#include <cstddef>
#include <stddef.h>
#include <stdint.h>
namespace com
{
namespace utils
{
/**
 * \brief Reference to a mutable array with fixed size
 *
 * This class is designed for safely using fixed size arrays while
 * staying independent from the array size in the class type.
 *
 * \remark Since the class points to a mutable array, it will
 * always return non-const references.
 */
template<typename T>
class array_ref
{
public:
    /** \brief Default constructor */
    array_ref() = default;

    /** \brief Constructor for a C-style fixed-size array */
    template<size_t N>
    array_ref(T (&vals)[N]) : m_values(vals), m_size(N)
    {
    }

    /** \brief Constructor for a pointer with separate size argument */
    array_ref(T* vals, size_t size) : m_values(vals), m_size(size)
    {
    }

    /** \brief No move operations, as there is no ownership */
    array_ref(array_ref&& other) = delete;

    /** \brief No move operations, as there is no ownership */
    array_ref& operator=(array_ref&& other) = delete;

    /** \brief Copy constructor */
    array_ref(const array_ref& other) = default;

    /** \brief Copy assignment */
    array_ref& operator=(const array_ref& other) = default;

    /** \brief Begin iterator */
    T* begin() const
    {
        return &m_values[0];
    }

    /** \brief End iterator */
    T* end() const
    {
        return &m_values[m_size];
    }

    /** \brief Returns the size of the array */
    size_t size() const
    {
        return m_size;
    }

    /** \brief Dereference operator */
    constexpr T& operator[](size_t idx) const
    {
        return m_values[idx];
    }

private:
    T* m_values;
    size_t m_size;
};

/**
 * \brief Reference to an immutable array with fixed size
 *
 * This class is designed for safely using fixed size arrays while
 * staying independent from the array size in the class type.
 *
 * \remark Since the class points to an immutable array, it will
 * always return const references.
 */
template<typename T>
class const_array_ref
{
public:
    /**
     * @brief Default constructor.
     */
    constexpr const_array_ref() : m_values(nullptr), m_size(0)
    {
    }

    /** @brief Constructor with explicit nullptr assignment. */
    constexpr const_array_ref(std::nullptr_t) : const_array_ref()
    {
    }

    /** \brief Constructor for a C-style empty array */
    constexpr const_array_ref(const T(vals)[0]) : const_array_ref()
    {
        static_cast<void>(vals);
    }

    /** \brief Constructor for a C-style fixed-size array */
    template<size_t N>
    const_array_ref(const T (&vals)[N]) : m_values(vals), m_size(N)
    {
    }

    /** \brief Constructor for a pointer with separate size argument */
    const_array_ref(const T* vals, size_t size) : m_values(vals), m_size(size)
    {
    }

    // /** \brief No move operations, as there is no ownership */
    // // TODO: We need this for the empty initializer use case !?
    // const_array_ref(const_array_ref&& other) = default;

    // /** \brief No move operations, as there is no ownership */
    // const_array_ref& operator=(const_array_ref&& other) = default;

    // /** \brief Copy constructor */
    // const_array_ref(const const_array_ref& other) = default;

    // /** \brief Copy assignment */
    // const_array_ref& operator=(const const_array_ref& other) = default;

    /** \brief Begin iterator */
    const T* begin() const
    {
        return &m_values[0];
    }

    /** \brief End iterator */
    const T* end() const
    {
        return &m_values[m_size];
    }

    /** \brief Returns the size of the array */
    size_t size() const
    {
        return m_size;
    }

    /** \brief Dereference operator */
    constexpr const T& operator[](size_t idx) const
    {
        return m_values[idx];
    }

private:
    const T* m_values;
    size_t m_size;
};

} // namespace utils
} // namespace com

#endif // COM_UTILS_ARRAY_REF_HPP
