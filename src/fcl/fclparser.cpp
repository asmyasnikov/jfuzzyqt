/****************************************************************
Copyright (C) 2009 Marco Estanqueiro, Aleksey Myasnikov
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
in file LICENSE along with this program.  If not, see
<http://www.gnu.org/licenses/>
****************************************************************/
/*!
 * \file fclparser.cpp
 * \class FIXME
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.83
 * \brief FIXME
 */
#include "fclparser.h"
#include "../connection/ruleconnectionmethod.h"
#include "../connection/and/ruleconnectionmethodandmin.h"
#include "../connection/or/ruleconnectionmethodormax.h"
#include "../connection/and/ruleconnectionmethodandproduct.h"
#include "../connection/or/ruleconnectionmethodorprobor.h"
#include "../connection/and/ruleconnectionmethodandbdif.h"
#include "../connection/or/ruleconnectionmethodorbsum.h"
#include "fclruletree.h"
#include "../activation/ruleactivationmethodmin.h"
#include "../activation/ruleactivationmethodproduct.h"
#include "../accumulation/ruleaccumulationmethodmax.h"
#include "../accumulation/ruleaccumulationmethodbsum.h"
#include "../accumulation/ruleaccumulationmethodnsum.h"
#include "../accumulation/ruleaccumulationmethodsum.h"
#include "../accumulation/ruleaccumulationmethodprobor.h"
#include <QRegExp>

jfuzzyqt::FCLParser::FCLParser() : QObject ()
{
}

jfuzzyqt::FCLParser::FCLParser(QObject* parent) : QObject (parent)
{
}

jfuzzyqt::FCLParser::FCLParser(const FCLParser& parser) : QObject (parser.parent())
{
}

jfuzzyqt::FCLParser::~FCLParser()
{
}

QString jfuzzyqt::FCLParser::readLine(QTextStream &in)
{
    QRegExp rxIndent("^\\s+");///< empty line
    QString str = in.readLine();
    while(str!=NULL)
    {
        str = str.toLower();
        str.remove(QRegExp("//.*")); ///< remove comments
        str.replace(QRegExp("^\\s+"),""); ///< removes indentation
        str.replace(QRegExp("\\s+$"),""); ///< removes end line spaces or tabs
        str.replace(QRegExp("\\s+")," "); ///< convert tabs and multiple spaces to single space
        if ( str.isEmpty() )
        {
            str = in.readLine(); ///<Removes empty lines
        }else{
            break;
        }
    }
    return str;
}

void jfuzzyqt::FCLParser::loadVarInput(QTextStream& in, FunctBlock& funcBlock)
{
    QRegExp rxVar("(\\w+)\\s*:\\s*(\\w+)");
    QRegExp rxOut("end_var");
    QString line = readLine(in);
    while (!line.isNull()) {
        if (rxVar.indexIn(line) > -1)
        {
            Variable *v = new Variable(this, rxVar.cap(1) );
            funcBlock.addVariable(v->getName(),v);
        }else if (rxOut.indexIn(line) > -1){
            break;
        }
        line = readLine(in);
    }
}

void jfuzzyqt::FCLParser::loadVarOutput(QTextStream& in, FunctBlock& funcBlock)
{
    QRegExp rxVar("(\\w+)\\s*:\\s*(\\w+)");
    QRegExp rxOut("end_var");

    QString line = readLine(in);
    while (!line.isNull()) {
        if (rxVar.indexIn(line) > -1)
        {
            Variable *v = new Variable(this, rxVar.cap(1) );
            funcBlock.addVariable(v->getName(),v);
        }else if (rxOut.indexIn(line) > -1){
            break;
        }
        line = readLine(in);
    }
}

void jfuzzyqt::FCLParser::loadDefuzzify(QTextStream& in, FunctBlock& funcBlock, const QString& varName)
{
    QString defuzzificationMethodType = "cog";

    QRegExp rxOut("end_defuzzify");
    QRegExp rxMethod("method\\s*:\\s*(\\w+)");
    QRegExp rxDefault("default\\s*:=\\s*(\\w+)");
    QRegExp rxExtra("term\\s+(\\w+)\\s*:=(.+);");

    QString line = readLine(in);

    while ( !line.isNull() )
    {
        if ( rxExtra.indexIn(line) > -1)
        {
            Variable *v = new Variable(this, varName );
            funcBlock.addVariable( v->getName() , v );

            LinguisticTerm* lt = new LinguisticTerm(this);
            lt->setTermName( rxExtra.cap(1) );
            lt->loadFrom( rxExtra.cap(2) );
            funcBlock.setVariable( varName , lt );
        }else if (rxOut.indexIn(line) > -1){
            break;
        }else if ( rxMethod.indexIn(line) > -1){
            Defuzzifier* d = funcBlock.createDefuzzifier( rxMethod.cap(1) );
            funcBlock.setDefuzzifier(varName, d);
        }else if ( rxDefault.indexIn(line) > -1){
            QString str = rxDefault.cap(1);
            funcBlock.setDefaultValue(varName, str.toDouble() );
        }
        line = readLine(in);
    }
}

void jfuzzyqt::FCLParser::loadFuzzify(QTextStream& in, FunctBlock& funcBlock, const QString& name)
{
    QRegExp rxOut("end_fuzzify");
    QRegExp rxExtra("term\\s+(\\w+)\\s*:=(.+);");

    QString line = readLine(in);
    while (!line.isNull())
    {
        if ( rxExtra.indexIn(line) > -1)
        {
            Variable *v = new Variable(this, name );
            funcBlock.addVariable( v->getName() , v );

            LinguisticTerm* lt = new LinguisticTerm(this);
            lt->setTermName( rxExtra.cap(1) );
            lt->loadFrom( rxExtra.cap(2) );

            funcBlock.setVariable( name , lt );
        }else if (rxOut.indexIn(line) > -1){
            break;
        }else{
            qWarning() << "[jfuzzyqt::FCLParser::loadFuzzify] term unimplemented : " << line;
        }
        line = readLine(in);
    }
}

RuleBlock* jfuzzyqt::FCLParser::loadRuleBlock(QTextStream& in, FunctBlock& funcBlock, const QString& name)
{
    QRegExp rxRule("(rule\\s+(\\w+)\\s*:\\s*)(if\\s+.*\\s+then\\s+.*\\s*;)?");
    QRegExp rxOut ("end_ruleblock");
    QRegExp rxAND ("and\\s*:\\s*(\\w+)");
    QRegExp rxOR  ("or\\s*:\\s*(\\w+)");
    QRegExp rxACT ("act\\s*:\\s*(\\w+)");
    QRegExp rxACCU("accu\\s*:\\s*(\\w+)");

    RuleConnectionMethod *AND = NULL;
    RuleConnectionMethod *OR = NULL;
    QString ruleAccumulationMethodType = "sum";
    QString type;
    RuleBlock *ruleBlock = new RuleBlock(name);
    QString line = readLine(in);
    while (!line.isNull())
    {
        if (rxRule.indexIn(line) > -1)
        {
            if(AND && !OR)
            {
                // Which 'OR' method to use? (Note: We also set 'OR' method accordingly to fulfill DeMorgan's law
                if(AND->toQString().contains(QRegExp(" : min$"))){
                    OR = new RuleConnectionMethodOrMax();
                }else if(AND->toQString().contains(QRegExp(" : prod$"))){
                    OR = new RuleConnectionMethodOrProbOr();
                }else if(AND->toQString().contains(QRegExp(" : bdif$"))){
                    OR = new RuleConnectionMethodOrBoundedSum();
                }else{
                    qWarning()<<"Unknown (or unimplemented) 'AND' method: " << AND->toQString();
                }
            }else if(!AND && OR){
                // Which 'AND' method to use? (Note: We also set 'OR' method accordingly to fulfill DeMorgan's law
                if(OR->toQString().contains(QRegExp(" : max$"))){
                    AND = new RuleConnectionMethodAndMin();
                }else if(OR->toQString().contains(QRegExp(" : asum$"))){
                    AND = new RuleConnectionMethodAndProduct();
                }else if(OR->toQString().contains(QRegExp(" : bsum$"))){
                    AND = new RuleConnectionMethodAndBoundedDif();
                }else{
                    qWarning()<<"Unknown (or unimplemented) 'OR' method: " << OR->toQString();
                }
            }
            Q_ASSERT(AND && OR);
            Rule *r = loadRule(funcBlock, rxRule.cap(3), rxRule.cap(2),AND,OR);
            if ( r == NULL )
            {
                qWarning() << "[jfuzzyqt::FCLParser::loadRuleBlock]: Error loading rule" << rxRule.cap(2);
            }else{
                ruleBlock->addRule( *r );
            }
        }else if (rxOut.indexIn(line) > -1){
            RuleAccumulationMethod* ram = createAccumulationMethod(ruleAccumulationMethodType);
            if ( ram == NULL )
            {
                qWarning() << "[jfuzzyqt::FCLParser::loadRuleBlock]: No rule acumulation method created.";
            }else{
                ruleBlock->addRuleAccumulationMethod( ram );
                ruleBlock->setRuleConnectionMethodAnd(AND);
                ruleBlock->setRuleConnectionMethodOr(OR);
            }
            break;
        }else if (rxAND.indexIn(line) > -1){
            type = rxAND.cap(1);
            if( type == "min"){
                AND = new RuleConnectionMethodAndMin();
            }else if( type == "prod" ){
                AND = new RuleConnectionMethodAndProduct();
            }else if( type == "bdif" ){
                AND = new RuleConnectionMethodAndBoundedDif();
            }else{
                qWarning()<<"Unknown (or unimplemented) 'AND' method: "<<type;
            }
        }else if (rxACT.indexIn(line) > -1){
            type = rxACT.cap(1);
            if( type == "min")
            {
                ruleBlock->addRuleActivationMethod (new RuleActivationMethodMin(this));
            }else if( type=="prod" ){
                ruleBlock->addRuleActivationMethod (new RuleActivationMethodProduct(this));
            }else{
                qWarning()<<"Unknown (or unimplemented) 'ACT' method: "<<type;
            }
        }else if (rxACCU.indexIn(line) > -1){
            ruleAccumulationMethodType = rxACCU.cap(1);
        }else if ( rxOR.indexIn(line)> -1 ){
            type = rxOR.cap(1);
            if( type == "max" ) {
                OR = new RuleConnectionMethodOrMax();
            }else if( type == "asum" ){
                OR = new RuleConnectionMethodOrProbOr();
            }else if( type == "bsum" ){
                OR = new RuleConnectionMethodOrBoundedSum();
            }else{
                qWarning()<<"Unknown (or unimplemented) 'OR' method: "<<type;
            }
        }else if(!line.isEmpty()){
            qWarning()<<"Unknown line: " << line;
        }
        line = readLine(in);
    }
    return ruleBlock;
}

Rule* jfuzzyqt::FCLParser::loadRule( FunctBlock& funcBlock,
                           const QString &rule,
                           const QString &name,
                           const RuleConnectionMethod *AND,
                           const RuleConnectionMethod *OR )
{
    QRegExp rxIF("if\\s+(.*)?\\s+then");
    QRegExp rxTHEN ("then\\s+((\\w+)?.*)?\\s+is\\s+((\\w+)?.*)?\\s*;");
    Rule* fuzzyRule = new Rule(NULL,name);
    if ( rxIF.indexIn(rule) > -1 && rxTHEN.indexIn(rule) > -1)
    {
        RuleExpression *antecedents = loadRuleIf(funcBlock,rxIF.cap(1),AND,OR);
        if (!antecedents)
        {
            qWarning() << "[jfuzzyqt::FCLParser::loadRule]:antecedents are NULL.";
        }
        fuzzyRule->addAntecedents( antecedents );
        Variable *v = funcBlock.getVariable(rxTHEN.cap(2));
        RuleTerm* rt = new RuleTerm(NULL, v, rxTHEN.cap(3), false);
        fuzzyRule->addConsequent(rt);
    }else{
        qWarning()<<"[jfuzzyqt::FCLParser::loadRule]:Unknown rule " << rule;
        return NULL;
    }
    return fuzzyRule;
}

RuleExpression* jfuzzyqt::FCLParser::loadRuleIf( FunctBlock& funcBlock,
                                       QString ruleif,
                                       const RuleConnectionMethod *AND,
                                       const RuleConnectionMethod *OR )
{
    FCLRuleTree tree(this);
    tree.addExpression(ruleif);
    return tree.getRuleExpression(funcBlock, AND, OR);
}

void jfuzzyqt::FCLParser::loadFunctBlock(QTextStream &in,FunctBlock& funcBlock)
{
    QRegExp rxFunctionBlockEnd("end_function_block");
    QRegExp rxVarInput("var_input");
    QRegExp rxVarOutput("var_output");
    QRegExp rxFuziffy("fuzzify\\s+(\\w+)");
    QRegExp rxDefuzzify("defuzzify\\s+(\\w+)");
    QRegExp rxRulleBlock("ruleblock\\s+(\\w+)");

    QString line = readLine(in);
    while (!line.isNull())
    {
        if (rxVarInput.indexIn(line) > -1)
        {
            loadVarInput(in,funcBlock);///< Input variable block
        }
        else if ( rxVarOutput.indexIn(line) > -1 )
        {
            loadVarOutput(in,funcBlock);///< Output Variable block
        }
        else if (rxDefuzzify.indexIn(line) > -1)
        {
            loadDefuzzify(in,funcBlock,rxDefuzzify.cap(1));///< Defuzzify block
        }
        else if (rxFuziffy.indexIn(line) > -1)
        {
            loadFuzzify(in, funcBlock, rxFuziffy.cap(1));///< Fuzzify block
        }
        else if (rxRulleBlock.indexIn(line) > -1)
        {
            RuleBlock *rb = loadRuleBlock(in, funcBlock, rxRulleBlock.cap(1));
            if ( rb == NULL )
            {
                qWarning() << "[jfuzzyqt::FCLParser::loadFunctBlock]: Error loading RuleBlock" << rxRulleBlock.cap(1);
            }else{
                    funcBlock.addRuleBlock ( rb );///< Rule block
            }
        }else if (rxFunctionBlockEnd.indexIn(line) > -1){
            return;///< End of Function block
        }
        line = readLine(in);
    }
}

RuleAccumulationMethod* jfuzzyqt::FCLParser::createAccumulationMethod(const QString& type)
{
    RuleAccumulationMethod* ruleAccumulationMethod = NULL;
    if( type == "max" )
    {
        ruleAccumulationMethod = new RuleAccumulationMethodMax();
    }else if( type == "bsum" ){
        ruleAccumulationMethod = new RuleAccumulationMethodBoundedSum();
    }else if( type == "nsum" ){
        ruleAccumulationMethod = new RuleAccumulationMethodNormalisedSum();
    }else if( type == "probor" ){
        ruleAccumulationMethod = new RuleAccumulationMethodProbOr();
    }else if( type == "sum" ){
        ruleAccumulationMethod = new RuleAccumulationMethodSum();
    }else{
        qWarning()<<"Unknown/Unimplemented Rule accumulation method "<<type;
    }
    return ruleAccumulationMethod;
}
