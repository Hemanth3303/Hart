/*
 * Logging functions with different severity levels and colored output
 */

 // Temp to prevent all the logger missing compile errors
#define HART_ENGINE_TRACE(message, ...)
#define HART_ENGINE_LOG(message, ...)
#define HART_ENGINE_WARNING(message, ...)
#define HART_ENGINE_ERROR(message, ...)
#define HART_ENGINE_FATAL(message, ...)

#define HART_CLIENT_TRACE(message, ...)
#define HART_CLIENT_LOG(message, ...)
#define HART_CLIENT_WARNING(message, ...)
#define HART_CLIENT_ERROR(message, ...)
#define HART_CLIENT_FATAL(message, ...)
