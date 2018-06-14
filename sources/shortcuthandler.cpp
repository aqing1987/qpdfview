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

#include "shortcuthandler.h"

#include <QApplication>
#include <QSettings>

#include "documentview.h"

namespace {

// The QKeySequence class encapsulates a key sequence as used by shortcuts.
// In its most common form, a key sequence describes a combination of keys that
// must be used together to perform some action. Key sequences are used with
// QAction objects to specify which keyboard shortcuts can be used to trigger actions.
QList<QKeySequence> toShortcuts(const QStringList& stringList) {
    QList<QKeySequence> shortcuts;

    foreach (const QString& string, stringList) {
        QKeySequence shortcut(string.trimmed());

        if (!shortcut.isEmpty()) {
            shortcuts.append(shortcut);
        }
    }

    return shortcuts;
}

QStringList toStringList(const QList<QKeySequence>& shortcuts,
                         QKeySequence::SequenceFormat format = QKeySequence::PortableText) {
    QStringList stringList;

    foreach (const QKeySequence& shortcut, shortcuts) {
        stringList.append(shortcut.toString(format));
    }

    return stringList;
}

inline bool matches(const QKeySequence& keySequence, const QList<QKeySequence>& shortcuts) {
    foreach (const QKeySequence& shortcut, shortcuts) {
        if (keySequence.matches(shortcut) == QKeySequence::ExactMatch) {
            return true;
        }
    }

    return false;
}

} // anonymous

namespace qpdfview {

ShortcutHandler* ShortcutHandler::s_instance = 0;

ShortcutHandler* ShortcutHandler::instance() {
    if (s_instance == 0) {
        s_instance = new ShortcutHandler(qApp);
    }

    return s_instance;
}

ShortcutHandler::~ShortcutHandler() {
    s_instance = 0;
}

void ShortcutHandler::registerAction(QAction* action) {
    Q_ASSERT(!action->objectName().isEmpty());

    const QList<QKeySequence> defaultShortcuts = action->shortcuts();
    const QList<QKeySequence> shortcuts =
            toShortcuts(m_settings->value(action->objectName(),
                                          toStringList(defaultShortcuts)).toStringList());

    action->setShortcuts(shortcuts);

    m_actions.append(action);
    m_shortcuts.insert(action, shortcuts);
    m_defaultShortcuts.insert(action, defaultShortcuts);
}

int ShortcutHandler::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);

    return 2;
}

int ShortcutHandler::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);

    return m_actions.count();
}

Qt::ItemFlags ShortcutHandler::flags(const QModelIndex& index) const {
    switch (index.column()) {
    case 0:
        return Qt::ItemIsEnabled;
    case 1:
        return Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }

    return Qt::NoItemFlags;
}

QVariant ShortcutHandler::headerData(int section, Qt::Orientation orientation, int role) const {
    Q_UNUSED(orientation);

    if (role == Qt::DisplayRole) {
        switch(section) {
        case 0:
            return tr("Action");
        case 1:
            return tr("Key sequence");
        }
    }

    return QVariant();
}

// The QVariant class acts like a union for the most common Qt data types.
QVariant ShortcutHandler::data(const QModelIndex& index, int role) const {
    if ((role == Qt::DisplayRole || role == Qt::EditRole) &&
            index.row() >= 0 && index.row() < m_actions.count()) {

        QAction* action = m_actions.at(index.row());

        switch (index.column()) {
        case 0:
            return action->text().remove(QLatin1Char('&'));
        case 1:
            return toStringList(m_shortcuts.value(action), QKeySequence::NativeText).join(";");
        }
    }

    return QVariant();
}

bool ShortcutHandler::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (role == Qt::EditRole && index.column() == 1 &&
            index.row() >= 0 && index.row() < m_actions.count()) {

        QList<QKeySequence> shortcuts =
                toShortcuts(value.toString().split(";", QString::SkipEmptyParts));

        if (!shortcuts.isEmpty() || value.toString().isEmpty()) {
            m_shortcuts.insert(m_actions.at(index.row()), shortcuts);

            // This signal is emitted whenever the data in an existing item changes.
            emit dataChanged(index, index);

            return true;
        }
    }

    return false;
}

bool ShortcutHandler::matchesSkipBackward(const QKeySequence& keySequence) const {
    return matches(keySequence, m_skipBackwardAction->shortcuts());
}

bool ShortcutHandler::matchesSkipForward(const QKeySequence& keySequence) const {
    return matches(keySequence, m_skipForwardAction->shortcuts());
}

bool ShortcutHandler::matchesMoveUp(const QKeySequence& keySequence) const {
    return matches(keySequence, m_moveUpAction->shortcuts());
}

bool ShortcutHandler::matchesMoveDown(const QKeySequence& keySequence) const {
    return matches(keySequence, m_moveDownAction->shortcuts());
}

bool ShortcutHandler::matchesMoveLeft(const QKeySequence& keySequence) const {
    return matches(keySequence, m_moveLeftAction->shortcuts());
}

bool ShortcutHandler::matchesMoveRight(const QKeySequence& keySequence) const {
    return matches(keySequence, m_moveRightAction->shortcuts());
}

bool ShortcutHandler::submit() {
    for (Shortcuts::iterator iterator = m_shortcuts.begin();
         iterator != m_shortcuts.end(); ++iterator) {
        iterator.key()->setShortcuts(iterator.value());
    }

    foreach (const QAction* action, m_actions) {
        m_settings->setValue(action->objectName(), toStringList(action->shortcuts()));
    }

    return true;
}

void ShortcutHandler::revert() {
    for (Shortcuts::iterator iterator = m_shortcuts.begin();
         iterator != m_shortcuts.end(); ++iterator) {
        iterator.value() = iterator.key()->shortcuts();
    }
}

void ShortcutHandler::reset() {
    for (Shortcuts::iterator iterator = m_defaultShortcuts.begin();
         iterator != m_defaultShortcuts.end(); ++iterator) {
        m_shortcuts.insert(iterator.key(), iterator.value());
    }

    emit dataChanged(createIndex(0, 1), createIndex(m_actions.count(), 1));
}

// .config/qpdfview/shortcuts.conf
ShortcutHandler::ShortcutHandler(QObject* parent) : QAbstractTableModel(parent),
    m_settings(new QSettings("qpdfview", "shortcuts", this)),
    m_actions(),
    m_shortcuts(),
    m_defaultShortcuts() {

    m_skipBackwardAction = createAction(
                tr("Skip backward"), QLatin1String("skipBackward"),
                QList< QKeySequence >() << QKeySequence(Qt::Key_PageUp) << QKeySequence(Qt::KeypadModifier + Qt::Key_PageUp));

    m_skipForwardAction = createAction(
                tr("Skip forward"), QLatin1String("skipForward"),
                QList< QKeySequence >() << QKeySequence(Qt::Key_PageDown) << QKeySequence(Qt::KeypadModifier + Qt::Key_PageDown));

    m_moveUpAction = createAction(
                tr("Move up"), QLatin1String("moveUp"),
                QList< QKeySequence >() << QKeySequence(Qt::Key_Up) << QKeySequence(Qt::KeypadModifier + Qt::Key_Up));

    m_moveDownAction = createAction(
                tr("Move down"), QLatin1String("moveDown"),
                QList< QKeySequence >() << QKeySequence(Qt::Key_Down) << QKeySequence(Qt::KeypadModifier + Qt::Key_Down));

    m_moveLeftAction = createAction(
                tr("Move left"), QLatin1String("moveLeft"),
                QList< QKeySequence >() << QKeySequence(Qt::Key_Left) << QKeySequence(Qt::KeypadModifier + Qt::Key_Left));

    m_moveRightAction = createAction(
                tr("Move right"), QLatin1String("moveRight"),
                QList< QKeySequence >() << QKeySequence(Qt::Key_Right) << QKeySequence(Qt::KeypadModifier + Qt::Key_Right));
}

QAction* ShortcutHandler::createAction(const QString& text,
                                       const QString& objectName,
                                       const QList<QKeySequence>& shortcuts) {

    // The QAction class provides an abstract user interface action that can be inserted into widgets.
    // In applications many common commands can be invoked via menus, toolbar buttons, and keyboard
    // shortcuts. Since the user expects each command to be performed in the same way, regardless
    // of the user interface used, it is useful to represent each command as an action.
    QAction* action = new QAction(text, this);
    action->setObjectName(objectName);
    action->setShortcuts(shortcuts);

    registerAction(action);

    return action;
}

} // qpdfview
