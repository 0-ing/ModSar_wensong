#ifndef PIPC_HPP
#define PIPC_HPP

namespace pipc
{
/**
 * @brief Namespace for the Runtime Environment.
 *
 * Contains interfaces for the 2 main components IApp & IRuntime.
 * These two interfaces define the main interaction between service components and a runtime
 * to enable dynamic behavior like service discovery and shared memory management.
 */
namespace rte
{
}

/**
 * @brief Namespace for daemon implementation.
 *
 * Contains the implementation for a SD daemon process, handling Service Discovery
 * & Shared Memory Management.
 */
namespace daemon
{
}

/**
 * @brief Namespace for loan implementation.
 *
 * Contains all implementations needed to provide a loan abstraction.
 * Loans are like shared pointers in shared memory, that can be shared across multiple processes.
 */
namespace loan
{
}

/**
 * @brief Namespace for pimp implementation.
 *
 * Contains the network layer functionality in PIPC, consisting mainly of the PIMP sockets.
 */
namespace pimp
{
}

/**
 * @brief Namespace for queue implementations.
 *
 * Contains all queues which are used within PIPC.
 */
namespace queue
{
}

/**
 * @brief Namespace for Publisher & Subscriber implementation.
 *
 * Contains everything required to implement Pub/Sub, with & without zero copy.
 */
namespace pub_sub
{
}

/**
 * @brief Namespace for RPC implementation.
 *
 * Contains everything required to implement RPC, with & without zero copy.
 */
namespace rpc
{
}

/**
 * @brief Namespace for Service Discovery implementation.
 *
 * Contains everything required provide Service Discovery functionality for service components.
 */
namespace sd
{
}

/**
 * @brief Namespace for session implementation.
 *
 * Contains the session layer functionality in PIPC, which provides stateful connection between
 * service providers & users.
 */
namespace session
{
}

/**
 * @brief Namespace for shmem implementations.
 *
 * Contains classes which facilitate shared memory handling, like a Mapping abstraction and
 * a Smart Pointer for Shared Memory Access.
 */
namespace shmem
{
}

/**
 * @brief Namespace for stack implementations.
 *
 * Contains classes which provide stack implementations (currently not used).
 */
namespace stack
{
}

/**
 * @brief Namespace for transport implementation.
 *
 * Contains the transport layer functionality in PIPC, which introduces ports to provide a demultiplexing
 * mechanism to address multiple endpoints through a single socket / in a single node.
 */
namespace transport
{
}

/**
 * @brief Namespace for utils classes.
 *
 * Contains all kinds of different utility functionalities, which are used throughout PIPC.
 */
namespace utils
{
}

} // namespace pipc

#endif // PIPC_HPP
