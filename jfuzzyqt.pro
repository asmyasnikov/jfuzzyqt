LANGUAGE = C++
QT -= gui
CONFIG += plugin release
DEFINES += J_FUZZY_QT_LIBRARY
UI_DIR = ./src.gen/ui
MOC_DIR = ./src.gen/moc
OBJECTS_DIR = ./src.gen/obj
DESTDIR = ./build
win32-msvc|win32-msvc.net|win32-msvc2002|win32-msvc2003|win32-msvc2005|win32-msvc2008:TEMPLATE = vclib
else:TEMPLATE = lib
TARGET = jfuzzyqt
INCLUDEPATH += . \
    include \
    src \
    src\accumulation \
    src\activation \
    src\connection \
    src\defuzzifier \
    src\fcl \
    src\membership \
    src\rule \
    src\connection\and \
    src\connection\or \
    src\membership\continuous \
    src\membership\discrete
DEPENDPATH += . \
    include \
    src \
    src\accumulation \
    src\activation \
    src\connection \
    src\defuzzifier \
    src\fcl \
    src\membership \
    src\rule \
    src\connection\and \
    src\connection\or \
    src\membership\continuous \
    src\membership\discrete

# Input
HEADERS += include/jfuzzyqt.h \
    src/common.h \
    src/functblock.h \
    src/accumulation/ruleaccumulationmethod.h \
    src/accumulation/ruleaccumulationmethodbsum.h \
    src/accumulation/ruleaccumulationmethodmax.h \
    src/accumulation/ruleaccumulationmethodnsum.h \
    src/accumulation/ruleaccumulationmethodprobor.h \
    src/accumulation/ruleaccumulationmethodsum.h \
    src/activation/ruleactivationmethod.h \
    src/activation/ruleactivationmethodmin.h \
    src/activation/ruleactivationmethodproduct.h \
    src/connection/ruleconnectionmethod.h \
    src/defuzzifier/defuzzifier.h \
    src/defuzzifier/defuzzifiercenterofgravity.h \
    src/defuzzifier/defuzzifiercenterofgravitysingletons.h \
    src/defuzzifier/defuzzifiercontinuous.h \
    src/defuzzifier/defuzzifierdiscrete.h \
    src/fcl/fclparser.h \
    src/fcl/fclrulenode.h \
    src/fcl/fclruletree.h \
    src/membership/membershipfunction.h \
    src/rule/rule.h \
    src/rule/ruleblock.h \
    src/rule/ruleexpression.h \
    src/rule/ruleterm.h \
    src/rule/variable.h \
    src/rule/linguisticterm.h \
    src/connection/and/ruleconnectionmethodandbdif.h \
    src/connection/and/ruleconnectionmethodandmin.h \
    src/connection/and/ruleconnectionmethodandproduct.h \
    src/connection/or/ruleconnectionmethodorbsum.h \
    src/connection/or/ruleconnectionmethodormax.h \
    src/connection/or/ruleconnectionmethodorprobor.h \
    src/membership/discrete/membershipfunctionsingleton.h \
    src/membership/discrete/membershipfunctiondiscrete.h \
    src/membership/continuous/membershipfunctioncontinuous.h \
    src/membership/continuous/membershipfunctionpiecewiselinear.h \
    src/membership/continuous/membershipfunctiongauss.h \
    src/membership/continuous/membershipfunctionsigm.h \
    src/membership/continuous/membershipfunctiontrian.h \
    src/membership/continuous/membershipfunctiontrap.h \
    src/membership/discrete/membershipfunctiongenericsingleton.h \
    src/membership/continuous/membershipfunctiongbell.h \
    src/optimization/optimizationparameters.h \
    src/optimization/value.h \
    src/optimization/errorfunction.h \
    src/optimization/optimizationdeltajump.h \
    src/optimization/optimizationgradient.h \
    src/optimization/optimizationpartialderivate.h
SOURCES += src/jfuzzyqt.cpp \
    src/functblock.cpp \
    src/accumulation/ruleaccumulationmethod.cpp \
    src/accumulation/ruleaccumulationmethodbsum.cpp \
    src/accumulation/ruleaccumulationmethodmax.cpp \
    src/accumulation/ruleaccumulationmethodnsum.cpp \
    src/accumulation/ruleaccumulationmethodprobor.cpp \
    src/accumulation/ruleaccumulationmethodsum.cpp \
    src/activation/ruleactivationmethod.cpp \
    src/activation/ruleactivationmethodmin.cpp \
    src/activation/ruleactivationmethodproduct.cpp \
    src/connection/ruleconnectionmethod.cpp \
    src/defuzzifier/defuzzifier.cpp \
    src/defuzzifier/defuzzifiercenterofgravity.cpp \
    src/defuzzifier/defuzzifiercenterofgravitysingletons.cpp \
    src/defuzzifier/defuzzifiercontinuous.cpp \
    src/defuzzifier/defuzzifierdiscrete.cpp \
    src/fcl/fclparser.cpp \
    src/fcl/fclrulenode.cpp \
    src/fcl/fclruletree.cpp \
    src/membership/membershipfunction.cpp \
    src/rule/rule.cpp \
    src/rule/ruleblock.cpp \
    src/rule/ruleexpression.cpp \
    src/rule/ruleterm.cpp \
    src/rule/variable.cpp \
    src/rule/linguisticterm.cpp \
    src/connection/and/ruleconnectionmethodandbdif.cpp \
    src/connection/and/ruleconnectionmethodandmin.cpp \
    src/connection/and/ruleconnectionmethodandproduct.cpp \
    src/connection/or/ruleconnectionmethodorbsum.cpp \
    src/connection/or/ruleconnectionmethodormax.cpp \
    src/connection/or/ruleconnectionmethodorprobor.cpp \
    src/membership/discrete/membershipfunctionsingleton.cpp \
    src/membership/discrete/membershipfunctiondiscrete.cpp \
    src/membership/continuous/membershipfunctioncontinuous.cpp \
    src/membership/continuous/membershipfunctionpiecewiselinear.cpp \
    src/membership/continuous/membershipfunctiongauss.cpp \
    src/membership/continuous/membershipfunctionsigm.cpp \
    src/membership/continuous/membershipfunctiontrian.cpp \
    src/membership/continuous/membershipfunctiontrap.cpp \
    src/membership/discrete/membershipfunctiongenericsingleton.cpp \
    src/membership/continuous/membershipfunctiongbell.cpp \
    src/optimization/optimizationparameters.cpp \
    src/optimization/value.cpp \
    src/optimization/errorfunction.cpp \
    src/optimization/optimizationdeltajump.cpp \
    src/optimization/optimizationgradient.cpp \
    src/optimization/optimizationpartialderivate.cpp
