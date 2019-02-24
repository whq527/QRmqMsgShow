#pragma once
#include <qabstractitemmodel.h>
#include <QStringList>
class CWListModel :
	public QAbstractListModel
{
	Q_OBJECT
public:
	CWListModel(QObject *parent = 0);
	virtual ~CWListModel();
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role) const;
	//实现先进先出
	void appendData(const QList<QString>& _strlist);
	void appendData(const QString& _strlist);
private:
	QStringList m_data;
	int m_data_size = 0;
};
