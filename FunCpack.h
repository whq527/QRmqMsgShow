#pragma once
#include "QStandardItem"
#include "CRmq.h"

void appendCpack_head(QStandardItem* _item, st_m_cpack& _msg);
void updateCpack_head(QStandardItem* _item, st_m_cpack& _msg);
void appendCpack_pack(QStandardItem* _item, st_m_cpack& _msg);
void updateCpack_pack(QStandardItem* _item, st_m_cpack& _msg);