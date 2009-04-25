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
 * \file fclrulenode.cpp
 * \class FCLRuleNode
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.78
 * \brief FIXME
 */
#include "fclrulenode.h"
#include "fclruletree.h"
#include <QDebug>
#include <QRegExp>

FCLRuleNode::FCLRuleNode(QObject *parent, const QString& oper)
        : QObject(parent)
{
    left = NULL;
    right = NULL;
    this->oper = oper.toLower().contains("and") ? "and" : "or";
    if ( !this->oper.contains("and") )
    {
        priority = 0;
    }else{
        priority = 1;
    }
}

FCLRuleNode::~FCLRuleNode()
{
}
bool FCLRuleNode::isPriorThen(int priority)
{
    return (this->priority < priority);
}
void FCLRuleNode::setLeft(FCLRuleNode* node)
{
    left = node;
    if(left) left->setParent(this);
}
int FCLRuleNode::getPriority()
{
    return priority;
}
void FCLRuleNode::setRight(FCLRuleNode* node)
{
    right = node;
    if(right) right->setParent(this);
}
FCLRuleNode* FCLRuleNode::getRight()
{
    return right;
}
bool FCLRuleNode::hasRightMember()const
{
    return right;
}
QString FCLRuleNode::print()const
{
    QString str;
    str.append("(");
    if(!value1.isEmpty() || left)
    {
        if( left )
        {
            str.append(left->print());
        }else {
            str.append(value1);
        }
    }
    if(!value2.isEmpty() || right)
    {
        str.append(" ");
        str.append(oper.toUpper());
        str.append(" ");
        if(right)
        {
            str.append(right->print());
        }else{
            str.append(value2);
        }
    }
    str.append(")");
    return str;
}
void FCLRuleNode::insertLeaveValues(QList<QString>&values, FCLRuleTree*rt)
{
    if(values.size())
    {
        if( left )
        {
            left->insertLeaveValues(values, rt);
        }else{
            value1 = values.takeFirst();
            FCLRuleNode*node = rt->getRuleNode(value1);
            if(node)setLeft(node);
        }
    }
    if(values.size())
    {
        if( right )
        {
            right->insertLeaveValues(values, rt);
        }else{
            value2 = values.takeFirst();
            FCLRuleNode*node = rt->getRuleNode(value2);
            if(node) setRight(node);
        }
    }
}
const QString& FCLRuleNode::getOperator()const
{
    return oper;
}
RuleExpression* FCLRuleNode::toRuleExpression(FunctBlock &fb, const RuleConnectionMethod *AND, const RuleConnectionMethod *OR)const
{
    RuleExpression *re = new RuleExpression();
    if(left)
    {
        re->addTerm1Expression(left->toRuleExpression(fb,AND,OR));
    }else{
        re->addTerm1Rule(toRuleTermLeft(fb));
    }
    if( oper == "and" )//If the operator is 'and'
    {
        re->setRuleConnectionMethod(AND);
    }else{
        re->setRuleConnectionMethod(OR);
    }
    if(right)
    {
        re->addTerm2Expression(right->toRuleExpression(fb,AND,OR));
    }else{
        re->addTerm2Rule(toRuleTermRight(fb));
    }
    return re;
}
RuleTerm* FCLRuleNode::toRuleTermLeft(FunctBlock &fb)const
{
    QRegExp rxMember("(\\w+)\\s+(is not|is)\\s+(\\w+)");
    RuleTerm *rt = new RuleTerm();
    if(!value1.isEmpty())
    {
        if ( rxMember.indexIn(value1) > -1 )
        {
            rt->setName( rxMember.cap(3) );
            if(  rxMember.cap(2) == "is" )
            {
                rt->setNegated(false);
            }else{
                rt->setNegated(true);
            }
            QString varname = rxMember.cap(1);
            Variable *v = fb.getVariable( varname );
            if( !v )
            {
                qWarning()<< "[FCLRuleNode::toRuleTermLeft]:Variable " << varname << " is NULL!!";
            }else{
                rt->setVariable(v);
            }
        }else{
            qWarning() << "[FCLRuleNode::toRuleTermLeft]: Error reading regular expression";
        }
    }
    return rt;
}
RuleTerm* FCLRuleNode::toRuleTermRight(FunctBlock &fb)const
{
    QRegExp rxMember("(\\w+)\\s+(is not|is)\\s+(\\w+)");
    RuleTerm *rt = new RuleTerm();
    if(!value2.isEmpty())
    {
        if (rxMember.indexIn(value2) > -1 )
        {
            rt->setName( rxMember.cap(3) );
            if(  rxMember.cap(2) == "is" )
            {
                rt->setNegated(false);
            }else{
                rt->setNegated(true);
            }
            QString varname = rxMember.cap(1);
            Variable *v = fb.getVariable( varname );
            if( !v )
            {
                qWarning()<< "[FCLRuleNode::toRuleTermRight]:Variable " << varname << " is NULL!!";
            }
            rt->setVariable(v);
        }else{
            qWarning() << "[FCLRuleNode::toRuleTermRight]: Error reading regular expression";
        }
    }
    return rt;
}
