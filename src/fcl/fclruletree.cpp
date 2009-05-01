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
 * \class FCLRuleTree
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.95
 * \brief FIXME
 */
#include "fclruletree.h"
#include <QDebug>
#include <QRegExp>

jfuzzyqt::FCLRuleTree::FCLRuleTree(QObject *parent)
    : QObject(parent),
      parentTree(dynamic_cast<FCLRuleTree*>(parent))
{
    root = NULL;
}

jfuzzyqt::FCLRuleTree::~FCLRuleTree()
{
}

void jfuzzyqt::FCLRuleTree::insertNode(FCLRuleNode* node)
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
FCLRuleNode* jfuzzyqt::FCLRuleTree::insertNode(FCLRuleNode* root, FCLRuleNode* node)
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
void jfuzzyqt::FCLRuleTree::insertRight(FCLRuleNode* root, FCLRuleNode* node)
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

QString jfuzzyqt::FCLRuleTree::print()const
{
    Q_ASSERT(root);
    return root->print();
}
void jfuzzyqt::FCLRuleTree::insertLeaveValues(QList<QString>&values)
{
    Q_ASSERT(root);
    root->insertLeaveValues(values, this);
}
void jfuzzyqt::FCLRuleTree::addExpression(QString exp)
{
    QList<QString> list;
    QRegExp rxBrackets("\\([^(\\(|\\))]*\\)");
    int pos = 0;
    while((pos = rxBrackets.indexIn(exp)) != -1)
    {
        static int brackets = 0;
        FCLRuleTree tree(this);
        tree.addExpression(rxBrackets.cap(0).mid(1,rxBrackets.cap(0).size()-2));
        QString replacement = QString("generic%1 is value").arg(brackets);
        exp = exp.replace(pos, rxBrackets.cap(0).size(), QString(" %1 ").arg(replacement));
        subtrees.insert(replacement,tree.root);
        if(tree.root && tree.root->parent()) tree.root->setParent(this);
        brackets++;
    }
    if(!exp.contains("(") && !exp.contains(")"))
    {
        QRegExp rx("(and|or)");
        QRegExp rxMember("(\\w+)\\s+(is not|is)\\s+(\\w+)");
        pos = 0;
        if((pos = rx.indexIn(exp, pos)) == -1 && !exp.isEmpty())
        {
            insertNode( (subtrees.find(exp) != subtrees.end()) ?
                        (subtrees[exp]) :
                        new FCLRuleNode(this, exp ) );
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
        if(root) insertLeaveValues(list);
    }else{
        qCritical("[jfuzzyqt::FCLRuleTree::addExpression] : unnecessary bracket '(' or ')'");
        Q_ASSERT(!exp.contains( '(' ));
        Q_ASSERT(!exp.contains( ')' ));
    }
}

RuleExpression* jfuzzyqt::FCLRuleTree::getRuleExpression(FunctBlock &fb, const RuleConnectionMethod *AND, const RuleConnectionMethod *OR)const
{
    return root ?
           root->toRuleExpression(fb, AND, OR) :
           NULL;
}
FCLRuleNode* jfuzzyqt::FCLRuleTree::getRuleNode(const QString& exp)const
{
    return (subtrees.find(exp) != subtrees.end()) ?
           (subtrees[exp]) :
           (parentTree ? parentTree->getRuleNode(exp) : NULL);
}
