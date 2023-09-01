#ifndef UTILS_COMMAND_HPP
#define UTILS_COMMAND_HPP

#include <cstddef>
#include <utility>

namespace pipc
{
/**
 * @brief Callable command.
 *
 * Commands are functors with configurable state (see Command Pattern).
 * They are like a minimal heap-free implementation of a combination of
 * std::function and std::bind.
 *
 * They consist of the following variables:
 * Mandatory:
 * - A pointer to a function with selectable signature
 * Optional:
 * - A fixed no. of typed parameters
 *
 * @remark
 * No good idea to have a straight-forward implementation with nice API without
 * writing the code out. For now we will have classes Command_0, Command_1 and
 * Command_2 manually written for the respective no. of parameters.
 *
 * @todo
 * Currently only call-by-value supported for function's arguments.
 *
 * @todo
 * Maybe we can improve the API, especially with the manual wrapper functions.
 * Check out std::mem_fn:
 * https://en.cppreference.com/w/cpp/utility/functional/mem_fn
 */

namespace utils
{
/** @brief Command without any parameters. */
template<typename Ret, typename... Args>
class Command_0
{
public:
    constexpr Command_0() : function_(nullptr)
    {
    }

    /** @brief Check if a command is stored. */
    explicit operator bool() const noexcept
    {
        return function_ != nullptr;
    }

    /** @brief Set the function to a static function. */
    inline void set(Ret (*fnc)(Args... args))
    {
        function_ = reinterpret_cast<Ret (*)(Args... args)>(fnc);
    }

    /** @brief Call operator. */
    inline Ret operator()(Args... args)
    {
        return (*function_)(std::forward<Args>(args)...);
    }

private:
    /** @brief Callback pointer, can be any static function. */
    Ret (*function_)(Args... args);
};

/** @brief Command with one parameter of type Param. */
template<typename Param, typename Ret = void, typename... Args>
class Command_1
{
public:
    /** @brief Default constructor without valid command. */
    constexpr Command_1() : function_(nullptr), param_()
    {
    }

    /** @brief Constructor for function to a member function wrapper. */
    template<typename T, typename P>
    inline Command_1(Ret (*fnc)(T*, Args... args), P* param) : param_()
    {
        set(fnc, param);
    }

    /** @brief Check if a command is stored. */
    explicit operator bool() const noexcept
    {
        return function_ != nullptr;
    }

    /** @brief Set the function to a static function with one param. */
    inline void set(Ret (*fnc)(Param, Args... args), Param param)
    {
        function_ = fnc;
        param_    = param;
    }

    /**
     * @brief Set the function to a member function wrapper.
     */
    template<typename T, typename P>
    inline void set(Ret (*fnc)(T*, Args... args), P* param)
    {
        // TODO: This might be too restrictive if we want to allow only one class.
        static_assert((std::is_same<void*, Param>::value),
                      "Param must be a void pointer type to instantiate "
                      "a member function wrapper.");
        static_assert(((std::is_base_of<T, P>::value) || (std::is_same<void*, Param>::value)),
                      "Function argument and given pointer must belong to the same class.");
        function_ = reinterpret_cast<Ret (*)(Param, Args... args)>(reinterpret_cast<void*>(fnc));
        param_    = param;
    }

    /** @brief Call operator. */
    inline Ret operator()(Args... args)
    {
        return (*function_)(param_, std::forward<Args>(args)...);
    }

private:
    /** @brief Callback pointer, can be any static function. */
    Ret (*function_)(Param, Args... args);
    /** @brief Context, can be a pointer to an object or anything with size_t. */
    Param param_;
};

/**
 * @brief Command with one parameter of type Param0 and the other of type
 * Param1. */
template<typename Param0, typename Param1, typename Ret = void, typename... Args>
class Command_2
{
public:
    constexpr Command_2() : function_(nullptr), param0_(), param1_()
    {
    }

    /** @brief Check if a command is stored. */
    explicit operator bool() const noexcept
    {
        return function_ != nullptr;
    }

    /** @brief Set the function to a static function with one param. */
    inline void set(Ret (*fnc)(Param0, Param1, Args... args), Param0 param0, Param1 param1)
    {
        function_ = fnc;
        param0_   = param0;
        param1_   = param1;
    }

    /** @brief Set the function to a member function wrapper. */
    template<typename T>
    inline void set(Ret (*fnc)(T*, Param1, Args... args), T* param0, Param1 param1)
    {
        static_assert((std::is_same<void*, Param0>::value),
                      "Param must be size_t or a pointer type to instantiate "
                      "a member function wrapper.");
        function_ = reinterpret_cast<Ret (*)(Param0, Param1, Args... args)>(reinterpret_cast<void*>(fnc));
        param0_   = param0;
        param1_   = param1;
    }

    /** @brief Call operator. */
    inline Ret operator()(Args... args)
    {
        return (*function_)(param0_, param1_, std::forward<Args>(args)...);
    }

private:
    /** @brief Callback pointer, can be any static function. */
    Ret (*function_)(Param0, Param1, Args... args);
    /** @brief Context, can be a pointer to an object or anything with size_t. */
    Param0 param0_;
    Param1 param1_;
};

} // namespace utils
} // namespace pipc

#endif // UTILS_COMMAND_HPP
