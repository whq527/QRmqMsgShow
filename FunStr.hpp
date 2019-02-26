#pragma execution_character_set("utf-8")
#pragma once
#include "CRmq.h"
#include "common.hpp"
#include <QDateTime>
#include <QStandardItemModel>

void append_info(QStandardItem * _item, st_m_str & _msg);
void update_info(QStandardItem* _item, st_m_str& _msg);
void append_pack(QStandardItem* _item, st_m_str& _msg);
void update_pack(QStandardItem* _item, st_m_str& _msg);

void Fun_Data(QStandardItemModel* _root, st_m_str& _msg)
{
	QString exchange = QString::fromStdString(_msg.header.exchange);
	QString routekey = QString::fromStdString(_msg.header.routekey);
	QList<QStandardItem*> plist = _root->findItems(exchange, Qt::MatchExactly, 0);
	if (plist.empty())
	{
		QStandardItem *item_exchange = new QStandardItem(exchange);
		QStandardItem *item_routekey = new QStandardItem(routekey);
		item_exchange->appendRow(item_routekey);
		append_info(item_routekey, _msg);
		append_pack(item_routekey, _msg);
		_root->appendRow(item_exchange);
	}
	else//找到exchange
	{
		QStandardItem *item_exchange = plist.at(0);
		for (int i = 0; i < item_exchange->rowCount(); i++)//找routekey更新
		{
			QStandardItem *item_routekey = item_exchange->child(i);
			if (routekey == item_routekey->text())
			{
				int row = 0;
				QStandardItem *item_pack_info = item_routekey->child(row++);
				update_info(item_pack_info, _msg);
				QStandardItem *item_pack_pack = item_routekey->child(row++);
				update_pack(item_pack_pack, _msg);
				return;
			}
		}

		// 添加新的routekey
		QStandardItem *item_routekey = new QStandardItem(routekey);
		append_info(item_routekey, _msg);
		append_pack(item_routekey, _msg);
		item_exchange->appendRow(item_routekey);
	}
}

void append_info(QStandardItem * _item, st_m_str & _msg)
{
	QStandardItem *item_pack_info = new QStandardItem("INFO");
	_item->appendRow(item_pack_info);
	item_pack_info->appendRow(newItemValue("exchange", _msg.header.exchange));
	item_pack_info->appendRow(newItemValue("routekey", _msg.header.routekey));
	item_pack_info->appendRow(newItemValue("queue", _msg.header.queue));
	item_pack_info->appendRow(newItemValue("zlib", _msg.header.zlib ? "True" : "False"));
	item_pack_info->appendRow(newItemValue("src_size", _msg.header.src_size));
	item_pack_info->appendRow(newItemValue("type", _msg.header.type));
	item_pack_info->appendRow(newItemValue("id", _msg.header.id));
	item_pack_info->appendRow(newItemValue("struct_name", _msg.header.struct_name));
	item_pack_info->appendRow(newItemValue("timestamp", QDateTime::fromTime_t(_msg.header.timestamp).toString("yyyy-MM-dd hh:mm:ss")));
}

void update_info(QStandardItem* _item, st_m_str& _msg)
{
	int row = 0;
	_item->child(row++)->setText(setItemValue("exchange", _msg.header.exchange));
	_item->child(row++)->setText(setItemValue("routekey", _msg.header.routekey));
	_item->child(row++)->setText(setItemValue("queue", _msg.header.queue));
	_item->child(row++)->setText(setItemValue("zlib", _msg.header.zlib ? "True" : "False"));
	_item->child(row++)->setText(setItemValue("src_size", _msg.header.src_size));
	_item->child(row++)->setText(setItemValue("type", _msg.header.type));
	_item->child(row++)->setText(setItemValue("id", _msg.header.id));
	_item->child(row++)->setText(setItemValue("struct_name", _msg.header.struct_name));
	_item->child(row++)->setText(setItemValue("timestamp", QDateTime::fromTime_t(_msg.header.timestamp).toString("yyyy-MM-dd hh:mm:ss")));
}

void append_pack(QStandardItem* _item, st_m_str& _msg)
{
	QStandardItem *item_pack_pack = new QStandardItem("String");
	_item->appendRow(item_pack_pack);
	item_pack_pack->appendRow(newItemValue("MSG", _msg.pack));
}

void update_pack(QStandardItem* _item, st_m_str& _msg)
{
	int row = 0;
	_item->child(row++)->setText(setItemValue("MSG", _msg.pack));
}