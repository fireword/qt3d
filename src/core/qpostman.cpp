/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qpostman_p.h"
#include <private/qobject_p.h>
#include <Qt3DCore/qscenepropertychange.h>
#include <Qt3DCore/qscene.h>

QT_BEGIN_NAMESPACE

namespace Qt3D {

class QPostmanPrivate : public QObjectPrivate
{
public:
    QPostmanPrivate(QPostman *qq)
        : QObjectPrivate()
        , m_sceneLookup(Q_NULLPTR)
    {
        q_ptr = qq;
    }

    Q_DECLARE_PUBLIC(QPostman)
    QScene *m_sceneLookup;
};

QPostman::QPostman(QObject *parent)
    : QObject(*new QPostmanPrivate(this), parent)
{
    qRegisterMetaType<QSharedPointer<QSceneChange> >("QSharedPointer<QSceneChanged>");
}

void QPostman::setSceneLookup(QScene *scene)
{
    Q_D(QPostman);
    d->m_sceneLookup = scene;
}

void QPostman::sceneChangeEvent(const QSceneChangePtr &)
{

}

//void QPostman::sceneNodeUpdated(QSceneChangePtr &e)
//{
//    QMetaObject::invokeMethod(this,
//                              "notifyFrontendNode",
//                              Q_ARG(QSharedPointer<QSceneChange>, e));
//}

void QPostman::notifyFrontendNode(QSceneChangePtr &)
{
    // TO DO: Lookup in the engine's table if a node for the current
}

} //Qt3D

QT_END_NAMESPACE
