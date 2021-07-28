#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LINEDRAWER_LIB)
#  define LINEDRAWER_EXPORT Q_DECL_EXPORT
# else
#  define LINEDRAWER_EXPORT Q_DECL_IMPORT
# endif
#else
# define LINEDRAWER_EXPORT
#endif
