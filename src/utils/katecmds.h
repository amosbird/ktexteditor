/*  This file is part of the KDE libraries and the Kate part.
 *
 *  Copyright (C) 2003-2005 Anders Lund <anders@alweb.dk>
 *  Copyright (C) 2001-2010 Christoph Cullmann <cullmann@kde.org>
 *  Copyright (C) 2001 Charles Samuels <charles@kde.org>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */

#ifndef __KATE_CMDS_H__
#define __KATE_CMDS_H__

#include <KTextEditor/Command>

#include <QStringList>

class KCompletion;

/**
 * The KateCommands namespace collects subclasses of KTextEditor::Command
 * for specific use in kate.
 */
namespace KateCommands
{

/**
 * This KTextEditor::Command provides access to a lot of the core functionality
 * of kate part, settings, utilities, navigation etc.
 * it needs to get a kateview pointer, it will cast the kate::view pointer
 * hard to kateview
 */
class CoreCommands : public KTextEditor::Command
{
    CoreCommands()
        : KTextEditor::Command(QStringList() << QStringLiteral("indent") << QStringLiteral("unindent") << QStringLiteral("cleanindent") << QStringLiteral("fold") << QStringLiteral("tfold") << QStringLiteral("unfold")
          << QStringLiteral("comment") << QStringLiteral("uncomment") << QStringLiteral("goto") << QStringLiteral("kill-line")
          << QStringLiteral("set-tab-width") << QStringLiteral("set-replace-tabs") << QStringLiteral("set-show-tabs")
          << QStringLiteral("set-indent-width")
          << QStringLiteral("set-indent-mode") << QStringLiteral("set-auto-indent")
          << QStringLiteral("set-line-numbers") << QStringLiteral("set-folding-markers") << QStringLiteral("set-icon-border")
          << QStringLiteral("set-indent-pasted-text") << QStringLiteral("set-word-wrap") << QStringLiteral("set-word-wrap-column")
          << QStringLiteral("set-replace-tabs-save") << QStringLiteral("set-remove-trailing-spaces")
          << QStringLiteral("set-highlight") << QStringLiteral("set-mode") << QStringLiteral("set-show-indent")
          << QStringLiteral("print"))
    {
    }
    
    static CoreCommands *m_instance;

public:
    ~CoreCommands()
    {
        m_instance = nullptr;
    }

    /**
     * execute command
     * @param view view to use for execution
     * @param cmd cmd string
     * @param errorMsg error to return if no success
     * @return success
     */
    bool exec(class KTextEditor::View *view, const QString &cmd, QString &errorMsg);

    /**
     * execute command on given range
     * @param view view to use for execution
     * @param cmd cmd string
     * @param errorMsg error to return if no success
     * @param range range to execute command on
     * @return success
     */
    bool exec(class KTextEditor::View *view, const QString &cmd, QString &errorMsg,
              const KTextEditor::Range &range = KTextEditor::Range(-1, -0, -1, 0)) Q_DECL_OVERRIDE;

    bool supportsRange(const QString &range) Q_DECL_OVERRIDE;

    /** This command does not have help. @see KTextEditor::Command::help */
    bool help(class KTextEditor::View *, const QString &, QString &) Q_DECL_OVERRIDE;

    /** override from KTextEditor::Command */
    KCompletion *completionObject(KTextEditor::View *, const QString &) Q_DECL_OVERRIDE;

    static CoreCommands *self()
    {
        if (m_instance == nullptr) {
            m_instance = new CoreCommands();
        }
        return m_instance;
    }
};

/**
 * insert a unicode or ascii character
 * base 9+1: 1234
 * hex: 0x1234 or x1234
 * octal: 01231
 *
 * prefixed with "char:"
 **/
class Character : public KTextEditor::Command
{
    Character()
        : KTextEditor::Command(QStringList() << QStringLiteral("char"))
    {
    }

    static Character *m_instance;

public:
    ~Character()
    {
        m_instance = nullptr;
    }

    /**
     * execute command
     * @param view view to use for execution
     * @param cmd cmd string
     * @param errorMsg error to return if no success
     * @return success
     */
    bool exec(class KTextEditor::View *view, const QString &cmd, QString &errorMsg,
              const KTextEditor::Range &range = KTextEditor::Range(-1, -0, -1, 0)) Q_DECL_OVERRIDE;

    /** This command does not have help. @see KTextEditor::Command::help */
    bool help(class KTextEditor::View *, const QString &, QString &) Q_DECL_OVERRIDE;

    static Character *self()
    {
        if (m_instance == nullptr) {
            m_instance = new Character();
        }
        return m_instance;
    }
};

/**
 * insert the current date/time in the given format
 */
class Date : public KTextEditor::Command
{
    Date()
        : KTextEditor::Command(QStringList() << QStringLiteral("date"))
    {
    }

    static Date *m_instance;

public:
    ~Date()
    {
        m_instance = nullptr;
    }

    /**
     * execute command
     * @param view view to use for execution
     * @param cmd cmd string
     * @param errorMsg error to return if no success
     * @return success
     */
    bool exec(class KTextEditor::View *view, const QString &cmd, QString &errorMsg,
              const KTextEditor::Range &range = KTextEditor::Range(-1, -0, -1, 0)) Q_DECL_OVERRIDE;

    /** This command does not have help. @see KTextEditor::Command::help */
    bool help(class KTextEditor::View *, const QString &, QString &) Q_DECL_OVERRIDE;

    static Date *self()
    {
        if (m_instance == nullptr) {
            m_instance = new Date();
        }
        return m_instance;
    }
};

} // namespace KateCommands
#endif

