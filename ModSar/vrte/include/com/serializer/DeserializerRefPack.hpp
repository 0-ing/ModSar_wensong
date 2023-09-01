#ifndef COM_SERIALIZER_DESERIALIZERREFPACK_HPP
#define COM_SERIALIZER_DESERIALIZERREFPACK_HPP

#include <array>
#include <tuple>
//#include "IDeserializer.hpp"

namespace com
{
namespace serializer
{
// TODO: Rewrite FTLs so make IDeserializer a generic interface
class IDeserializer
{
public:
    /** \brief Virtual destructor required to allow deleting via the interface */
    virtual ~IDeserializer() = default;

    // In order to deserialize we have to know where to put the deserialized object and
    // how much data can be read from which buffer
    // the return value is the success of the deserialization (true = success, false = something went wrong)
    // additionally the number of read bytes is written into the uint32_t pointed to by readbytes
    virtual bool deserialize(const uint8_t* receivebuffer, uint32_t length, void* objectp, uint32_t* readbytes) = 0;
};

template<size_t N>
class DeserializerRefPack
{
public:
    /**
     * @brief Construct a DeserializerRefPack out of a tuple with deserializers.
     *
     * @tparam Types The types of the tuple.
     */
    template<typename... Types>
    constexpr DeserializerRefPack(std::tuple<Types...>& deserializers)
    {
        static_assert(sizeof...(Types) == N, "Tuple of deserializers must be same size as DeserializerPack.");
        init<0U>(deserializers);
    }

    /**
     * @brief Deserialize a byte stream into a tuple.
     *
     * @tparam Types The types of the tuple.
     * @param source The source pointer of the byte stream.
     * @param length The length of the byte stream.
     * @param tuple The tuple to deserialize the types into.
     * @return true if deserialization was successful.
     * @return false if deserialization was not successful.
     */
    template<typename... Types>
    bool deserialize(const uint8_t* source, uint32_t length, std::tuple<Types...>& tuple)
    {
        uint32_t bytesRead;
        return deserialize<0>(source, length, bytesRead, tuple);
    }

private:
    /**
     * @brief Initialize the DeserializerRefPack.
     *
     * @tparam I The current index.
     * @tparam T The type of the tuple.
     * @param deserializers The tuple of deserializers.
     */
    template<size_t I, typename T>
    typename std::enable_if<I != N, void>::type init(T& deserializers)
    {
        deserializers_[I] = &std::get<I>(deserializers);
        init<I + 1>(deserializers);
    }

    /**
     * @brief Initialize the DeserializerRefPack.
     *
     * Template specialization for the end of initialization.
     */
    template<size_t I, typename T>
    typename std::enable_if<I == N, void>::type init(T&)
    {
    }

    /**
     * @brief Deserialize into the I-th element of the tuple.
     *
     * Template specialization for template unrolling.
     *
     * @tparam I The current index.
     * @tparam Types The types of the tuple.
     * @param source Source pointer.
     * @param length The (remaining) length of the byte stream.
     * @param bytesRead Pointer to the info how many bytes were read.
     * @param tuple The tuple to deserialize into.
     * @return std::enable_if<I != N, bool>::type
     */
    template<size_t I, typename... Types>
    typename std::enable_if<I != N, bool>::type deserialize(const uint8_t* source,
                                                            uint32_t length,
                                                            uint32_t* bytesRead,
                                                            std::tuple<Types...>& tuple)
    {
        IDeserializer& deserializer = *deserializers_[I];
        auto& dst                   = std::get<I>(tuple);
        auto success                = deserializer.deserialize(source, length, &dst, &bytesRead);
        if (success)
        {
            return deserialize<I + 1>(source + *bytesRead, length - *bytesRead, bytesRead, tuple);
        }
        return false;
    }

    /**
     * @brief Deserialize into the I-th element of the tuple.
     *
     * Template specialization for the end of template unrolling.
     */
    template<size_t I, typename... Types>
    typename std::enable_if<I == N, bool>::type deserialize(const uint8_t* source,
                                                            uint32_t length,
                                                            uint32_t* bytesRead,
                                                            std::tuple<Types...>& dest)
    {
        return true;
    }

    /**
     * @brief The array with pointers to all referenced deserializers.
     */
    std::array<IDeserializer*, N> deserializers_;
};

} // namespace serializer
} // namespace com

#endif // COM_SERIALIZER_DESERIALIZERREFPACK_HPP
