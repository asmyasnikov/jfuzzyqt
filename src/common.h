/****************************************************************
Copyright (C) 2009 Marco Estanqueiro, Aleksey Myasnikov
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser GPL as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser GPL for more details.
You should have received a copy of the GNU Lesser GPL
in file LICENSE along with this program.  If not, see
<http://www.gnu.org/licenses/>
****************************************************************/
/*!
 * \file common.h
 * \brief Common defines of JFuzzyQt.
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \date 2011/07
 * \version 1.08
 */
#ifndef JFUZZYQT_H_COMMON
#define JFUZZYQT_H_COMMON

#include <QtCore/QtGlobal>

#if defined(J_FUZZY_QT_LIBRARY)
#  define J_FUZZY_QT_EXPORT Q_DECL_EXPORT
#else
#  define J_FUZZY_QT_EXPORT Q_DECL_IMPORT
#endif

#endif // JFUZZYQT_H_COMMON
