#pragma once
#include "QStandardItem"

QStandardItem* newItemValue(QString _entry, QString _str)
{
	return new QStandardItem(QString("%1=%2").arg(_entry).arg(_str));
}

QString setItemValue(QString _entry, QString _str)
{
	return QString("%1=%2").arg(_entry).arg(_str);
}

QStandardItem* newItemValue(QString _entry, const char* _str)
{
	return new QStandardItem(QString("%1=%2").arg(_entry).arg(QString::fromLocal8Bit(_str)));
}

QString setItemValue(QString _entry, const char* _str)
{
	return QString("%1=%2").arg(_entry).arg(QString::fromLocal8Bit(_str));
}

QStandardItem* newItemValue(QString _entry, std::string _str)
{
	return new QStandardItem(QString("%1=%2").arg(_entry).arg(QString::fromLocal8Bit(_str.c_str())));
}

QString setItemValue(QString _entry, std::string _str)
{
	return QString("%1=%2").arg(_entry).arg(QString::fromLocal8Bit(_str.c_str()));
}

QStandardItem* newItemValue(QString _entry, int _num)
{
	return new QStandardItem(QString("%1=%2").arg(_entry).arg(QString::number(_num)));
}

QString setItemValue(QString _entry, int _num)
{
	return QString("%1=%2").arg(_entry).arg(QString::number(_num));
}

QStandardItem* newItemValue(QString _entry, unsigned int _num)
{
	return new QStandardItem(QString("%1=%2").arg(_entry).arg(QString::number(_num)));
}

QString setItemValue(QString _entry, unsigned int _num)
{
	return QString("%1=%2").arg(_entry).arg(QString::number(_num));
}

QStandardItem* newItemValue(QString _entry, long _num)
{
	return new QStandardItem(QString("%1=%2").arg(_entry).arg(QString::number(_num)));
}

QString setItemValue(QString _entry, long _num)
{
	return QString("%1=%2").arg(_entry).arg(QString::number(_num));
}

QStandardItem* newItemValue(QString _entry, long long _num)
{
	return new QStandardItem(QString("%1=%2").arg(_entry).arg(QString::number(_num)));
}

QString setItemValue(QString _entry, long long _num)
{
	return QString("%1=%2").arg(_entry).arg(QString::number(_num));
}

QStandardItem* newItemValue(QString _entry, unsigned long _num)
{
	return new QStandardItem(QString("%1=%2").arg(_entry).arg(QString::number(_num)));
}

QString setItemValue(QString _entry, unsigned long _num)
{
	return QString("%1=%2").arg(_entry).arg(QString::number(_num));
}

QStandardItem* newItemValue(QString _entry, double _num)
{
	return new QStandardItem(QString("%1=%2").arg(_entry).arg(QString::number(_num)));
}

QString setItemValue(QString _entry, double _num)
{
	return QString("%1=%2").arg(_entry).arg(QString::number(_num));
}