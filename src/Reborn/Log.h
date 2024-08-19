#pragma once
#include "easylogging++.h"

#define LOG_TRACE LOG(TRACE)
#define LOG_INFO  LOG(INFO)
#define LOG_DEBUG LOG(DEBUG) << __FILE__ << ":" << __LINE__ << " "
#define LOG_WARN  LOG(WARNING) << __FILE__ << ":" << __LINE__ << " " 
#define LOG_ERROR LOG(ERROR) << __FILE__ << ":" << __LINE__ << " "
#define LOG_FATAL LOG(FATAL) << __FILE__ << ":" << __LINE__ << " "