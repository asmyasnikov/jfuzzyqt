/*!
* \file linguisticterm.h
* \class LinguisticTerm
* \author Marco Estanqueiro
* \date 2009/03
* \version 0.1
* \brief A linguistic term is an asociation between a termName and a membership function
*
* From pcingola@users.sourceforge.net jFuzzyLogic project
*/
#ifndef LINGUISTICTERM_H
#define LINGUISTICTERM_H

#include <QString>
#include <QObject>

class MembershipFunction;

class LinguisticTerm : public QObject
{
	Q_OBJECT

public:
	LinguisticTerm(QObject* parent=NULL);
	LinguisticTerm(QObject* parent,QString& termName, MembershipFunction* membershipFunction);
	~LinguisticTerm();
	
	QString getTermName() const;
	void setTermName(const QString& name);
	const MembershipFunction* getMembershipFunction();
	bool loadFrom(QString qString);
	void debug(QString tbs) const;

private:
	QString termName;///<Terms's name
	MembershipFunction* membershipFunction;///< Membership function 

};

#endif // LINGUISTICTERM_H
