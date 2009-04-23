LANGUAGE = C++
QT -= gui
CONFIG += plugin \
    release
UI_DIR = ./src.gen/ui
MOC_DIR = ./src.gen/moc
OBJECTS_DIR = ./src.gen/obj
DESTDIR = ./build
TEMPLATE = lib
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
    src/membership/value.h \
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
    src/membership/continuous/membershipfunctionsigm.h
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
    src/membership/value.cpp \
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
    src/membership/continuous/membershipfunctionsigm.cpp
OTHER_FILES += fcl/tipper.fcl \
    fcl/singletone.fcl \
    fcl/mamdani.fcl \
    fcl/tsukamoto.fcl \
    TODO \
    LICENSE \
    PROBLEMS \
    fcl/gauss.fcl \
    fcl/brackets.fcl
