#pragma execution_character_set("utf-8")
#pragma once
#include "CRmq.h"
#include "common.hpp"
#include <QDateTime>
#include <QStandardItemModel>

void append_info(QStandardItem * _item, st_m_cpack & _msg);
void update_info(QStandardItem* _item, st_m_cpack& _msg);
void append_head(QStandardItem* _item, st_m_cpack& _msg);
void update_head(QStandardItem* _item, st_m_cpack& _msg);
void append_pack(QStandardItem* _item, st_m_cpack& _msg);
void update_pack(QStandardItem* _item, st_m_cpack& _msg);

void Fun_Data(QStandardItemModel* _root, st_m_cpack& _msg)
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
		append_head(item_routekey, _msg);
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
				QStandardItem *item_pack_header = item_routekey->child(row++);
				update_head(item_pack_header, _msg);
				QStandardItem *item_pack_pack = item_routekey->child(row++);
				update_pack(item_pack_pack, _msg);
				return;
			}
		}

		// 添加新的routekey
		QStandardItem *item_routekey = new QStandardItem(routekey);
		append_info(item_routekey, _msg);
		append_head(item_routekey, _msg);
		append_pack(item_routekey, _msg);
		item_exchange->appendRow(item_routekey);
	}
}

void append_info(QStandardItem * _item, st_m_cpack & _msg)
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

void update_info(QStandardItem* _item, st_m_cpack& _msg)
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

void append_head(QStandardItem* _item, st_m_cpack& _msg)
{
	QStandardItem *item_pack_header = new QStandardItem("HEAD");
	_item->appendRow(item_pack_header);
	item_pack_header->appendRow(newItemValue("RequestType", _msg.pack.head.RequestType));
	item_pack_header->appendRow(newItemValue("firstflag", _msg.pack.head.firstflag));
	item_pack_header->appendRow(newItemValue("nextflag", _msg.pack.head.nextflag));
	item_pack_header->appendRow(newItemValue("recCount", _msg.pack.head.recCount));
	item_pack_header->appendRow(newItemValue("retCode", _msg.pack.head.retCode));
	item_pack_header->appendRow(newItemValue("userdata", _msg.pack.head.userdata));
	item_pack_header->appendRow(newItemValue("ParmBits", (const char*)_msg.pack.head.ParmBits));
}

void update_head(QStandardItem* _item, st_m_cpack& _msg)
{
	int row = 0;
	_item->child(row++)->setText(setItemValue("RequestType", _msg.pack.head.RequestType));
	_item->child(row++)->setText(setItemValue("firstflag", _msg.pack.head.firstflag));
	_item->child(row++)->setText(setItemValue("nextflag", _msg.pack.head.nextflag));
	_item->child(row++)->setText(setItemValue("recCount", _msg.pack.head.recCount));
	_item->child(row++)->setText(setItemValue("retCode", _msg.pack.head.retCode));
	_item->child(row++)->setText(setItemValue("userdata", _msg.pack.head.userdata));
	_item->child(row++)->setText(setItemValue("ParmBits", (const char*)_msg.pack.head.ParmBits));
}

void append_pack(QStandardItem* _item, st_m_cpack& _msg)
{
	QStandardItem *item_pack_pack = new QStandardItem("ST_CPACK");
	_item->appendRow(item_pack_pack);
	item_pack_pack->appendRow(newItemValue("vsvarstr0", _msg.pack.pack.vsvarstr0));
	item_pack_pack->appendRow(newItemValue("vsvarstr1", _msg.pack.pack.vsvarstr1));
}

void update_pack(QStandardItem* _item, st_m_cpack& _msg)
{
	int row = 0;
	_item->child(row++)->setText(setItemValue("vsvarstr0", _msg.pack.pack.vsvarstr0));
	_item->child(row++)->setText(setItemValue("vsvarstr1", _msg.pack.pack.vsvarstr1));
}