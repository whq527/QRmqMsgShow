#include "CWListModel.h"

CWListModel::CWListModel(QObject *parent)
	:QAbstractListModel(parent)
{
}

CWListModel::~CWListModel()
{
}

int CWListModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	Q_UNUSED(parent);
	return m_data.count();
}

QVariant CWListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= m_data_size)
		return QVariant();

	if (role == Qt::DisplayRole)
		return m_data.at(index.row());
	else
		return QVariant();
}

//只会刷新一次画面
void CWListModel::appendData(const QList<QString>& _strlist)
{
	beginResetModel();
	for (int i = 0; i < _strlist.size(); i++)
	{
		m_data.push_front(_strlist.at(i));
		if (m_data.size() > 50)
		{
			m_data.pop_back();
		}
	}
	m_data_size = m_data.size();
	endResetModel();
}

//会刷新多次画面
void CWListModel::appendData(const QString& _strlist)
{
	beginResetModel();
	m_data.push_front(_strlist);
	if (m_data.size() > 50)
	{
		m_data.pop_back();
	}
	m_data_size = m_data.size();
	endResetModel();
}