#pragma once
#include "CRmq.h"
#include "common.hpp"
#include <QDateTime>

void appendCpack_info(QStandardItem * _item, st_m_cpack & _msg)
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

void updateCpack_info(QStandardItem* _item, st_m_cpack& _msg)
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

void appendCpack_head(QStandardItem* _item, st_m_cpack& _msg)
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

void updateCpack_head(QStandardItem* _item, st_m_cpack& _msg)
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

void appendCpack_pack(QStandardItem* _item, st_m_cpack& _msg)
{
	QStandardItem *item_pack_pack = new QStandardItem("ST_CPACK");
	_item->appendRow(item_pack_pack);
	item_pack_pack->appendRow(newItemValue("vsvarstr0", _msg.pack.pack.vsvarstr0));
	item_pack_pack->appendRow(newItemValue("vsvarstr1", _msg.pack.pack.vsvarstr1));
}

void updateCpack_pack(QStandardItem* _item, st_m_cpack& _msg)
{
	int row = 0;
	_item->child(row++)->setText(setItemValue("vsvarstr0", _msg.pack.pack.vsvarstr0));
	_item->child(row++)->setText(setItemValue("vsvarstr1", _msg.pack.pack.vsvarstr1));
}