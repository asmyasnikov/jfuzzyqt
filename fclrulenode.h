#ifndef FCLRULENODE_H
#define FCLRULENODE_H

#include <QString>
#include <QObject>

class FCLRuleNode : public QObject
{
public:
	FCLRuleNode(QObject *parent, QString oper);
	~FCLRuleNode();
	bool isPriorThen(int priority);
	int getPriority();
	void setLeft(FCLRuleNode* node);
	bool hasRightMember();
	FCLRuleNode* getRight();
	void setRight(FCLRuleNode* node);
	QString print();
	void insertLeaveValues(QList<QString> &values);
	const QString getOperator()const;
private:
	int priority;
	QString value1;
	QString value2;
	QString oper;
	FCLRuleNode* left;
	FCLRuleNode* right;
};

#endif // FCLRULENODE_H
