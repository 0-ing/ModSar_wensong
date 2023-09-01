#ifndef COM_SERIALIZER_SERIALIZERREFPACK_HPP
#define COM_SERIALIZER_SERIALIZERREFPACK_HPP

#include <array>
#include <tuple>
//#include "ISerializer.hpp"

namespace com
{
namespace serializer
{
// TODO: Rewrite FTLs so make ISerializer a generic interface
class ISerializer
{
public:
    /** \brief Virtual destructor required to allow deleting via the interface */
    virtual ~ISerializer() = default;

    // In order to know how much shared memory we have to allocate we have to know how big the serialized object becomes
    virtual uint32_t computeSerializedSize(const void* objectp) = 0;

    // In order to serialize we have to know where to put the serialized data, how much data can be written there
    // and what to serialize; the return value is the success of the serialization (true = success, false = something
    // went wrong)
    virtual bool serialize(uint8_t* targetbuffer, uint32_t maxsize, const void* objectp) = 0;
};

template<size_t N>
class SerializerRefPack
{
public:
    /**
     * @brief Construct a SerializerRefPack out of a tuple with serializers.
     *
     * @tparam Types The types of the tuple.
     */
    template<typename... Types>
    constexpr SerializerRefPack(std::tuple<Types...>& serializers)
    {
        static_assert(sizeof...(Types) == N, "Tuple of serializers must be same size as SerializerPack.");
        init<0U>(serializers);
    }

    /**
     * @brief Compute the serialized size of the given tuple.
     *
     * @tparam Types The types of the tuple.
     * @param tuple The tuple used for calculating the serialized size.
     * @return uint32_t The returned total serialized size.
     */
    template<typename... Types>
    uint32_t computeSerializedSize(std::tuple<Types...>& tuple)
    {
        return computeSerializedSize<0>(tuple, 0U);
    }

    /**
     * @brief Serialize a byte stream into a tuple.
     *
     * @tparam Types The types of the tuple.
     * @param source The source pointer of the byte stream.
     * @param maxLength The maxLength of the byte stream.
     * @param dest The tuple to serialize the types into.
     * @return true if deserialization was successful.
     * @return false if deserialization was not successful.
     */
    template<typename... Types>
    bool serialize(const uint8_t* dest, uint32_t maxLength, std::tuple<Types...>& source)
    {
        uint32_t bytesRead;
        return serialize<0>(source, maxLength, bytesRead, source);
    }

private:
    /**
     * @brief Initialize the SerializerRefPack.
     *
     * @tparam I The current index.
     * @tparam T The type of the tuple.
     * @param serializers The tuple of serializers.
     */
    template<size_t I, typename T>
    typename std::enable_if<I != N, void>::type init(T& serializers)
    {
        serializers_[I] = &std::get<I>(serializers);
        init<I + 1>(serializers);
    }

    /**
     * @brief Initialize the SerializerRefPack.
     *
     * Template specialization for the end of initialization.
     */
    template<size_t I, typename T>
    typename std::enable_if<I == N, void>::type init(T&)
    {
    }

    template<size_t I, typename... Types>
    typename std::enable_if<I != N, uint32_t>::type computeSerializedSize(std::tuple<Types...>& tuple, uint32_t size)
    {
        ISerializer& serializer = *serializers_[I];
        auto& src               = std::get<I>(tuple);
        return size + serializer.computeSerializedSize(&src);
    }

    template<size_t I, typename... Types>
    typename std::enable_if<I == N, uint32_t>::type computeSerializedSize(std::tuple<Types...>& tuple, uint32_t size)
    {
        return size;
    }

    /**
     * @brief Serialize into the I-th element of the tuple.
     *
     * Template specialization for template unrolling.
     *
     * @tparam I The current index.
     * @tparam Types The types of the tuple.
     * @param source Source pointer.
     * @param maxLength The (remaining) maxLength of the byte stream.
     * @param bytesRead Pointer to the info how many bytes were read.
     * @param source Destination pointer.
     * @return std::enable_if<I != N, bool>::type
     */
    template<size_t I, typename... Types>
    typename std::enable_if<I != N, bool>::type serialize(const uint8_t* dest,
                                                          uint32_t maxLength,
                                                          std::tuple<Types...>& tuple)
    {
        ISerializer& serializer = *serializers_[I];
        auto& source            = std::get<I>(tuple);
        auto success            = serializer.serialize(dest, maxLength, &source);
        if (success)
        {
            // TODO: Shouldn't the serializer return how many bytes it had written?
            auto size = serializer.computeSerializedSize(&source);
            return serialize<I + 1>(dest + size, maxLength - size, tuple);
        }
        return false;
    }

    /**
     * @brief Serialize into the I-th element of the tuple.
     *
     * Template specialization for the end of template unrolling.
     */
    template<size_t I, typename... Types>
    typename std::enable_if<I == N, bool>::type serialize(const uint8_t* dest,
                                                          uint32_t maxLength,
                                                          std::tuple<Types...>& tuple)
    {
        return true;
    }

    /**
     * @brief The array with pointers to all referenced serializers.
     */
    std::array<ISerializer*, N> serializers_;
};

} // namespace serializer
} // namespace com

#endif // COM_SERIALIZER_SERIALIZERREFPACK_HPP
