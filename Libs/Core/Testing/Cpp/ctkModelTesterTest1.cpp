/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc. 
  All rights reserved.
  Distributed under a BSD License. See LICENSE.txt file.

  This software is distributed "AS IS" WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the above copyright notice for more information.

=========================================================================*/

// Qt includes
#include <QAbstractItemModel>
#include <QApplication>
#include <QList>
#include <QModelIndex>
#include <QTreeWidget>

// CTK includes
#include "ctkModelTester.h"

// STL includes
#include <stdlib.h>
#include <iostream>

//-----------------------------------------------------------------------------
class QAbstractItemModelHelper : public QAbstractItemModel
{
public:
  virtual QModelIndex index(int, int, const QModelIndex&) const { return QModelIndex(); }
  virtual QModelIndex parent(const QModelIndex&) const { return QModelIndex(); }
  virtual int rowCount(const QModelIndex&) const { return 0; }
  virtual int columnCount(const QModelIndex&) const { return 0; }
  virtual QVariant data(const QModelIndex&, int) const { return QVariant(); }
};

//-----------------------------------------------------------------------------
int ctkModelTesterTest1(int argc, char * argv [] )
{
  QApplication app(argc, argv);

  QAbstractItemModelHelper * item = new QAbstractItemModelHelper;
  QObject * object = new QObject; 

  ctkModelTester ctkTester( item, object );

  delete item;

  try
    {
    // as we can infer that QTreeWidget is correct, ctkModelTester shall not fail
    // for any of the actions on QTreeWidget.
    QTreeWidget treeWidget(0);
    ctkModelTester treeModelTester(treeWidget.model());
    treeWidget.setColumnCount(1);
    QList<QTreeWidgetItem *> items;
    for (int i = 0; i < 10; ++i)
      {
      items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
      }
    treeWidget.addTopLevelItems(items);
    treeWidget.takeTopLevelItem(0);
    treeWidget.takeTopLevelItem(treeWidget.topLevelItemCount() / 2 );
    treeWidget.takeTopLevelItem(treeWidget.topLevelItemCount() - 1);
    treeWidget.insertTopLevelItem(0, new QTreeWidgetItem(&treeWidget, QStringList("new item 0")));
    treeWidget.insertTopLevelItem(treeWidget.topLevelItemCount() / 2, 
                                  new QTreeWidgetItem((QTreeWidget*)0, QStringList("new item 1")));
    treeWidget.insertTopLevelItem(treeWidget.topLevelItemCount(), 
                                  new QTreeWidgetItem((QTreeWidget*)0, QStringList("new item 2")));
    new QTreeWidgetItem(treeWidget.topLevelItem(0), QStringList("new item 3"));
    QAbstractItemModel* model = treeWidget.model();
    model->setData(model->index(0,0),QString("foo"));
    treeWidget.sortItems(0, Qt::DescendingOrder);
    }
  catch (const char* error)
    {
    std::cerr << error << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

