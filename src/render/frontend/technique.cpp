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

#include "technique.h"
#include "parameter.h"
#include <QDebug>

QT_BEGIN_NAMESPACE

namespace Qt3D {

Technique::Technique(Node *parent)
    : QAbstractTechnique(parent)
{
}

void Technique::addCriterion(TechniqueCriterion *criterion)
{
    if (!m_criteriaList.contains(criterion))
        m_criteriaList.append(criterion);
}

void Technique::removeCriterion(TechniqueCriterion *criterion)
{
    m_criteriaList.removeOne(criterion);
}

QVariant Technique::criterionValue(const QString &customTypeName) const
{
    Q_FOREACH (TechniqueCriterion *criterion, m_criteriaList)
        if (criterion->criterionCustomType() == customTypeName)
            return criterion->criterionValue();
    return QVariant();
}

QVariant Technique::criterionValue(TechniqueCriterion::CriterionType type)
{
    Q_FOREACH (TechniqueCriterion *criterion, m_criteriaList)
        if (criterion->criterionType() == type)
            return criterion->criterionValue();
    return QVariant();
}

QList<TechniqueCriterion *> Technique::criteria() const
{
    return m_criteriaList;
}

void Technique::clearCriteria()
{
    m_criteriaList.clear();
}

bool Technique::containsCriterion(const QString &customTypeName) const
{
    Q_FOREACH (TechniqueCriterion *criterion, m_criteriaList)
        if (criterion->criterionCustomType() == customTypeName)
            return true;
    return false;
}

bool Technique::containsCriterion(TechniqueCriterion::CriterionType type) const
{
    Q_FOREACH (TechniqueCriterion *criterion, m_criteriaList)
        if (criterion->criterionType() == type)
            return true;
    return false;
}

void Technique::addPass(QAbstractRenderPass *pass)
{
    Q_CHECK_PTR(pass);
    pass->setParent(this);
    QAbstractTechnique::addPass(pass);
}

void Technique::addParameter(Parameter *p)
{
    Q_CHECK_PTR(p);
    m_parameters.append(p);
}

void Technique::removeParameter(Parameter *p)
{
    m_parameters.removeOne(p);
}

Parameter *Technique::parameterByName(QString name) const
{
    foreach (Parameter* p, m_parameters) {
        if (p->name() == name)
            return p;
    }
    return NULL;
}

} // of namespace Qt3D

QT_END_NAMESPACE
