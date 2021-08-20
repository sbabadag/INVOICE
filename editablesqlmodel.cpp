/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtSql>

#include "editablesqlmodel.h"

EditableSqlModel::EditableSqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{
}

//! [0]
Qt::ItemFlags EditableSqlModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
//! [0]

//! [1]
bool EditableSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() < 1 || index.column() > 2)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    int id = data(primaryKeyIndex).toInt();

    clear();

    bool ok;

    switch (index.column()) {
          case 1:
                {
                 ok = setDescription(id, value.toString());

                }
    case 2:
          {
                  ok = setQuantity(id, value.toString().toDouble());

          }
    case 3:
          {
                 ok = setUnit(id, value.toString());

          }
    case 4:
          {
                 ok = setRate(id, value.toString().toDouble());

          }
    case 5:
          {
                 ok = setAmount(id, value.toString().toDouble());

          }
    }

    refresh();

    return ok;
}
//! [1]

void EditableSqlModel::refresh()
{
    setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("Description"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("Unit"));
    setHeaderData(3, Qt::Horizontal, QObject::tr("Quoted rate"));
    setHeaderData(4, Qt::Horizontal, QObject::tr("Quoted amount"));
}

//! [2]
bool EditableSqlModel::setDescription(int personId, const QString &description)
{
    QSqlQuery query;
    query.prepare("update orders set description = ? where ID = ?");
    query.addBindValue(description);
    query.addBindValue(personId);
    return query.exec();
}
//! [2]

bool EditableSqlModel::setQuantity(int personId, const double &quantity)
{
    QSqlQuery query;
    query.prepare("update person set quantity = ? where ID = ?");
    query.addBindValue(quantity);
    query.addBindValue(personId);
    return query.exec();
}

bool EditableSqlModel::setUnit(int personId, const QString &unit)
{
    QSqlQuery query;
    query.prepare("update person set unit = ? where ID = ?");
    query.addBindValue(unit);
    query.addBindValue(personId);
    return query.exec();
}

bool EditableSqlModel::setRate(int personId, const double &rate)
{
    QSqlQuery query;
    query.prepare("update person set rate = ? where ID = ?");
    query.addBindValue(rate);
    query.addBindValue(personId);
    return query.exec();
}

bool EditableSqlModel::setAmount(int personId, const double &amount)
{
    QSqlQuery query;
    query.prepare("update person set amount = ? where ID = ?");
    query.addBindValue(amount);
    query.addBindValue(personId);
    return query.exec();
}
