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

#ifndef __KATE_VI_CMDS_H__
#define __KATE_VI_CMDS_H__

#include <ktexteditor/commandinterface.h>
#include "kateviglobal.h"
#include "kateregexpsearch.h"
#include <katesedcmd.h>

#include <QStringList>

namespace KTextEditor { class DocumentPrivate; }
class KCompletion;

/**
 * The KateCommands namespace collects subclasses of KTextEditor::Command
 * for specific use in kate.
 */
namespace KateViCommands
{

/**
 * This KTextEditor::Command provides access to a lot of the core functionality
 * of kate part, settings, utilities, navigation etc.
 * it needs to get a kateview pointer, it will cast the kate::view pointer
 * hard to kateview
 */
class CoreCommands : public KTextEditor::Command, public KTextEditor::CommandExtension,
    public KTextEditor::RangeCommand
{
    CoreCommands() { }
    static CoreCommands *m_instance;

public:
    ~CoreCommands()
    {
        m_instance = 0;
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
     * @param rangeStart first line in range
     * @param rangeEnd last line in range
     * @return success
     */
    bool exec(class KTextEditor::View *view, const QString &cmd, QString &errorMsg,
              const KTextEditor::Range &range = KTextEditor::Range(-1, -0, -1, 0));

    bool supportsRange(const QString &range);

    /** This command does not have help. @see KTextEditor::Command::help */
    bool help(class KTextEditor::View *, const QString &, QString &);

    /**
     * supported commands as prefixes
     * @return prefix list
     */
    const QStringList &cmds();

    /**
    * override completionObject from interfaces/document.h .
    */
    KCompletion *completionObject(KTextEditor::View *, const QString &);

    virtual void flagCompletions(QStringList &) {}
    virtual bool wantsToProcessText(const QString &)
    {
        return false;
    }
    virtual void processText(KTextEditor::View *, const QString &) {}

    static CoreCommands *self()
    {
        if (m_instance == 0) {
            m_instance = new CoreCommands();
        }
        return m_instance;
    }
};

/**
 * This KTextEditor::Command provides vi 'ex' commands
 */
class ViCommands : public KTextEditor::Command, public KTextEditor::CommandExtension,
    public KTextEditor::RangeCommand
{
    ViCommands() { }
    static ViCommands *m_instance;

public:
    ~ViCommands()
    {
        m_instance = 0;
    }

    /**
     * execute command
     * @param view view to use for execution
     * @param cmd cmd string
     * @param msg message returned from running the command
     * @return success
     */
    bool exec(class KTextEditor::View *view, const QString &cmd, QString &msg);

    /**
     * execute command on given range
     * @param view view to use for execution
     * @param cmd cmd string
     * @param msg message returned from running the command
     * @param rangeStart first line in range
     * @param rangeEnd last line in range
     * @return success
     */
    bool exec(class KTextEditor::View *view, const QString &cmd, QString &msg,
              const KTextEditor::Range &range = KTextEditor::Range(-1, -0, -1, 0));

    bool supportsRange(const QString &range);

    /** This command does not have help. @see KTextEditor::Command::help */
    bool help(class KTextEditor::View *, const QString &, QString &)
    {
        return false;
    }

    /**
     * supported commands as prefixes
     * @return prefix list
     */
    const QStringList &cmds();

    /**
    * override completionObject from interfaces/document.h .
    */
    KCompletion *completionObject(KTextEditor::View *, const QString &);

    virtual void flagCompletions(QStringList &) {}
    virtual bool wantsToProcessText(const QString &)
    {
        return false;
    }
    virtual void processText(KTextEditor::View *, const QString &) {}

    static ViCommands *self()
    {
        if (m_instance == 0) {
            m_instance = new ViCommands();
        }
        return m_instance;
    }
private:
    const QStringList &mappingCommands();
    KateViGlobal::MappingMode modeForMapCommand(const QString &mapCommand);
    bool isMapCommandRecursive(const QString &mapCommand);
};

/**
 * This KTextEditor::Command provides vi commands for the application
 */
class AppCommands : public KTextEditor::Command
{
    AppCommands();
    static AppCommands *m_instance;

public:
    ~AppCommands()
    {
        m_instance = 0;
    }

    /**
     * execute command
     * @param view view to use for execution
     * @param cmd cmd string
     * @param msg message returned from running the command
     * @return success
     */
    bool exec(class KTextEditor::View *view, const QString &cmd, QString &msg);

    /** Help for AppCommands */
    bool help(class KTextEditor::View *, const QString &, QString &);

    /**
     * supported commands as prefixes
     * @return prefix list
     */
    const QStringList &cmds();

    static AppCommands *self()
    {
        if (m_instance == 0) {
            m_instance = new AppCommands();
        }
        return m_instance;
    }

private:
    QRegExp re_write;
    /*QRegExp re_quit;
    QRegExp re_exit;
    QRegExp re_changeBuffer;
    QRegExp re_edit;
    QRegExp re_new;*/
};
/**
 * Support vim/sed style search and replace
 * @author Charles Samuels <charles@kde.org>
 **/
class SedReplace : public KateCommands::SedReplace
{
    SedReplace() { }
    static SedReplace *m_instance;

public:
    ~SedReplace()
    {
        m_instance = 0;
    }

    static SedReplace *self()
    {
        if (m_instance == 0) {
            m_instance = new SedReplace();
        }
        return m_instance;
    }

protected:
    virtual bool interactiveSedReplace(KTextEditor::ViewPrivate *kateView, QSharedPointer<InteractiveSedReplacer> interactiveSedReplace);
};

} // namespace KateViCommands
#endif
