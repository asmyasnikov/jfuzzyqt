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
 * \file fclruletree.cpp
 * \class FIXME
 * \author Marco Estanqueiro
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#include "fclruletree.h"
#include <QDebug>
#include <QRegExp>

FCLRuleTree::FCLRuleTree(QObject *parent)
    : QObject(parent)
{
    root = NULL;
}

FCLRuleTree::~FCLRuleTree()
{
}

void FCLRuleTree::insertNode(FCLRuleNode* node)
{
    node->setParent(this);
    if (!root)
    {
        root = node;
    }else{
        root = insertNode(root, node);
    }
    Q_ASSERT(root);
}
FCLRuleNode* FCLRuleTree::insertNode(FCLRuleNode* root, FCLRuleNode* node)
{
    if(node->isPriorThen( root->getPriority()))
    {
        insertRight(root, node);
        return root;
    }else{
        node->setLeft(root);
        return node;
    }
}
void FCLRuleTree::insertRight(FCLRuleNode* root, FCLRuleNode* node)
{
    Q_ASSERT(root);
    Q_ASSERT(node);
    if ( root->hasRightMember() )
    {
        insertRight(root->getRight(), node);
    }else{
        root->setRight(node);
    }
}

QString FCLRuleTree::print()const
{
    Q_ASSERT(root);
    return root->print();
}
void FCLRuleTree::insertLeaveValues(QList<QString> &values)
{
    Q_ASSERT(root);
    root->insertLeaveValues(values);
}
void FCLRuleTree::addExpression(const QString& exp)
{
    QList<QString> list;
    QRegExp rx("(and|or)");
    QRegExp rxMember("(\\w+)\\s+(is not|is)\\s+(\\w+)");
    int pos = 0;
    if((pos = rx.indexIn(exp, pos)) == -1 && !exp.isEmpty())
    {
        insertNode( new FCLRuleNode(this, exp ) );
    }else{
        while ((pos = rx.indexIn(exp, pos)) != -1)
        {
            insertNode( new FCLRuleNode(this, rx.cap(1) ) );
            pos += rx.matchedLength();
        }
    }
    pos = 0;
    while ((pos = rxMember.indexIn(exp, pos)) != -1)
    {
        QString condition(rxMember.cap(0));
        if(!condition.isEmpty())
        {
            list.append( condition );
        }
        pos += rxMember.matchedLength();
    }
    insertLeaveValues(list);
}

RuleExpression* FCLRuleTree::getRuleExpression(FunctBlock &fb, const RuleConnectionMethod *AND, const RuleConnectionMethod *OR)const
{
    Q_ASSERT(root);
    return root->toRuleExpression(fb, AND, OR);
}
