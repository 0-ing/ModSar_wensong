#ifndef PIPC_PROG_REG_SERVER_HPP
#define PIPC_PROG_REG_SERVER_HPP

#ifdef __QNX__
#    include "qnx/Server.hpp"
#else
#    include "linux/Server.hpp"
#endif

#endif // PIPC_PROG_REG_SERVER_HPP
