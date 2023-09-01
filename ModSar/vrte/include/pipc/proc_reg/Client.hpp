#ifndef PIPC_PROC_REG_CLIENT_HPP
#define PIPC_PROC_REG_CLIENT_HPP

#ifdef __QNX__
#    include "qnx/Client.hpp"
#else
#    include "linux/Client.hpp"
#endif

#endif // PIPC_PROC_REG_CLIENT_HPP
