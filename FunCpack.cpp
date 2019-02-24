#include "FunCpack.h"
#include "common.hpp"

void appendCpack_head(QStandardItem* _item, st_m_cpack& _msg)
{
	QStandardItem *item_pack_header = new QStandardItem("head");
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
	QStandardItem *item_pack_pack = new QStandardItem("pack");
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