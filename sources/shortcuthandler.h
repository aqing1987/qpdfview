/*

Copyright 2013 Adam Reichold

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
#include <QKeySequence>

class QAction;
class QSettings;

class ShortcutHandler : public QAbstractTableModel
{
    Q_OBJECT

public:
    static ShortcutHandler* instance();
    ~ShortcutHandler();

    void registerAction(QAction* action);

    int columnCount(const QModelIndex& parent) const;
    int rowCount(const QModelIndex& parent) const;

    Qt::ItemFlags flags(const QModelIndex& index) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QVariant data(const QModelIndex& index, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);

    QKeySequence skipBackwardShortcut() const;
    QKeySequence skipForwardShortcut() const;

    QKeySequence moveUpShortcut() const;
    QKeySequence moveDownShortcut() const;
    QKeySequence moveLeftShortcut() const;
    QKeySequence moveRightShortcut() const;

public slots:
    bool submit();
    void revert();

    void reset();

private:
    static ShortcutHandler* s_instance;
    ShortcutHandler(QObject* parent = 0);

    QSettings* m_settings;

    QList< QAction* > m_actions;

    QMap< QAction*, QKeySequence > m_shortcuts;
    QMap< QAction*, QKeySequence > m_defaultShortcuts;

    QAction* m_skipBackwardAction;
    QAction* m_skipForwardAction;

    QAction* m_moveUpAction;
    QAction* m_moveDownAction;
    QAction* m_moveLeftAction;
    QAction* m_moveRightAction;

};

#endif // SHORTCUTHANDLER_H
