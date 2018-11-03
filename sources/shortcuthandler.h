/*

Copyright 2013, 2016 Adam Reichold

This file is part of qpdfview.

qpdfview is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

qpdfview is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with qpdfview.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef SHORTCUTHANDLER_H
#define SHORTCUTHANDLER_H

#include <QAbstractTableModel>
#include <QAction>
#include <QKeySequence>

class QSettings;

namespace qpdfview {

// The QAbstractTableModel class provides an abstract model that can be subclassed to create table models.
// QAbstractTableModel provides a standard interface for models that represent their
// data as a two-dimensional array of items. It is not used directly, but must be subclassed.
class ShortcutHandler : public QAbstractTableModel {
    Q_OBJECT

public:
    static ShortcutHandler* instance();
    ~ShortcutHandler();

    void registerAction(QAction* action);

    // When subclassing QAbstractTableModel, you must implement rowCount(),
    // columnCount(), and data().
    int columnCount(const QModelIndex& parent) const;
    int rowCount(const QModelIndex& parent) const;

    // Editable models need to implement setData(), and implement flags() to
    // return a value containing Qt::ItemIsEditable.
    Qt::ItemFlags flags(const QModelIndex& index) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QVariant data(const QModelIndex& index, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);

    bool matchesSkipBackward(const QKeySequence& keySequence) const;
    bool matchesSkipForward(const QKeySequence& keySequence) const;

    bool matchesMoveUp(const QKeySequence& keySequence) const;
    bool matchesMoveDown(const QKeySequence& keySequence) const;
    bool matchesMoveLeft(const QKeySequence& keySequence) const;
    bool matchesMoveRight(const QKeySequence& keySequence) const;

public slots:
    // [virtual slot] bool QAbstractItemModel::submit()
    // Lets the model know that it should submit cached information to permanent storage.
    // This function is typically used for row editing.
    bool submit();
    // [virtual slot] void QAbstractItemModel::revert()
    // Lets the model know that it should discard cached information. This function
    //is typically used for row editing.
    void revert();

    void reset();

private:
    Q_DISABLE_COPY(ShortcutHandler)

    static ShortcutHandler* s_instance;
    ShortcutHandler(QObject* parent = 0);

    QSettings* m_settings;

    // The QList class is a template class that provides lists.
    // QList<T> is one of Qt's generic container classes. It stores
    // items in a list that provides fast index-based access and index-based insertions and removals.
    QList<QAction*> m_actions;

    typedef QHash<QAction*, QList<QKeySequence> > Shortcuts;
    Shortcuts m_shortcuts;
    Shortcuts m_defaultShortcuts;

    QAction* m_skipBackwardAction;
    QAction* m_skipForwardAction;

    QAction* m_moveUpAction;
    QAction* m_moveDownAction;
    QAction* m_moveLeftAction;
    QAction* m_moveRightAction;

    QAction* createAction(const QString& text, const QString& objectName, const QList< QKeySequence >& shortcuts);

};

} // qpdfview

#endif // SHORTCUTHANDLER_H
