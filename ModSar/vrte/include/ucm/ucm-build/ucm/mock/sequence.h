//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file         src/ucm/mock/mock_sequence.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_BUILD_UCM_MOCK_SEQUENCE_H_
#define UCM_AAP_BUILD_UCM_MOCK_SEQUENCE_H_

#include "ucm/mock/any.h"

#include <deque>
#include <memory>
#include <string>
#include <iostream>
#include <stdexcept>

namespace bosch    {
namespace vrte     {
namespace ucm      {
namespace mock     {

struct Sequence
{
protected:
    Sequence() = default;
    ~Sequence() = default;
private:
    struct Fifo final
        : protected std::deque<Any>
    {
        ~Fifo()
        {
            if (not empty())
                std::cout << "Warning: mock sequence not empty on destruction\n";
        }
        std::deque<Any>& deque() {return *this;}
    };
public:
    static std::deque<Any>& fifo()
    {
        static Fifo value;
        return value.deque();
    }

    static void clear()
    {
        fifo().clear();
    }

    template<typename T>
    static void push()
    {
        fifo().push_back(Any::make<T>());
    }

    template<typename T>
    static void push(T&& t)
    {
        fifo().push_back(Any::make<T>(static_cast<T&&>(t)));
    }

    template<typename T, typename... U>
    static void emplace(U&&... u)
    {
        fifo().push_back(Any::make<T>(static_cast<U&&>(u)...));
    }

    template<typename T, typename... U>
    static void unique(U&&... u)
    {
        fifo().push_back(Any::make<std::unique_ptr<T>>(
                    std::make_unique<T>(static_cast<U&&>(u)...)));
    }

    template<typename T, typename... U>
    static void shared(U&&... u)
    {
        fifo().push_back(Any::make<std::shared_ptr<T>>(
                    std::make_shared<T>(static_cast<U&&>(u)...)));
    }

    template<typename T>
    static void push_exception(T&& t)
    {
        fifo().push_back(Any::make_exception<T>(static_cast<T&&>(t)));
    }

    template<typename T, typename... U>
    static void emplace_exception(U&&... u)
    {
        fifo().push_back(Any::make_exception<T>(static_cast<U&&>(u)...));
    }

    template<typename T>
    static T pop()
    {
        if (fifo().empty()) {
            std::cout << (std::string(__PRETTY_FUNCTION__) + " empty fifo");
            std::exit(1);
        }

        Any tmp = static_cast<Any&&>(fifo().front());
        fifo().pop_front();
        return tmp.get<T>();
    }
};

} // namespace mock
} // namespace ucm
} // namespace vrte
} // namespace bosch

#endif // UCM_AAP_BUILD_UCM_MOCK_SEQUENCE_H_
