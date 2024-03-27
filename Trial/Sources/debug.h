//
//  Trial Program
//  Lawicel SLCAN Protocol
//  Bart Simpson didn't do it
//
#ifndef DEBUG_H_INCLUDED 
#define DEBUG_H_INCLUDED 
#include "logger.h"
#if (OPTION_SERIAL_DEBUG_LEVEL > 0) || (OPTION_SLCAN_DEBUG_LEVEL > 0)
#define LOGGER_INIT(fn) log_init(fn)
#define LOGGER_EXIT()   log_exit()
#else
#define LOGGER_INIT(fn) do {} while(0)
#define LOGGER_EXIT()   do {} while(0)
#endif 
#endif 
