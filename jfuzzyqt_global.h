#ifndef JFUZZYQT_GLOBAL_H
#define JFUZZYQT_GLOBAL_H

#include <Qt/qglobal.h>

#ifdef JFUZZYQT_LIB
# define JFUZZYQT_EXPORT Q_DECL_EXPORT
#else
# define JFUZZYQT_EXPORT Q_DECL_IMPORT
#endif

#endif // JFUZZYQT_GLOBAL_H
