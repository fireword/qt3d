/****************************************************************************
**
** Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtTest/QTest>
#include <Qt3DCore/private/qnode_p.h>
#include <Qt3DCore/private/qscene_p.h>

#include <Qt3DRender/QObjectPicker>
#include <Qt3DRender/QAttribute>

#include "testpostmanarbiter.h"

class MyObjectPicker : public Qt3DRender::QObjectPicker
{
    Q_OBJECT
public:
    MyObjectPicker(Qt3DCore::QNode *parent = Q_NULLPTR)
        : Qt3DRender::QObjectPicker(parent)
    {}

private:
    friend class tst_ObjectPicker;
};

// We need to call QNode::clone which is protected
// So we sublcass QNode instead of QObject
class tst_QObjectPicker : public Qt3DCore::QNode
{
    Q_OBJECT
public:
    tst_QObjectPicker()
    {
        qRegisterMetaType<Qt3DRender::QAttribute*>("Qt3DRender::QAttribute*");
    }

    ~tst_QObjectPicker()
    {
        QNode::cleanup();
    }

private Q_SLOTS:

    void checkCloning_data()
    {
        QTest::addColumn<Qt3DRender::QObjectPicker *>("objectPicker");

        Qt3DRender::QObjectPicker *objectPicker = new Qt3DRender::QObjectPicker();
        QTest::newRow("empty objectPicker") << objectPicker;
        objectPicker = new Qt3DRender::QObjectPicker();
        objectPicker->setHoverEnabled(true);
        QTest::newRow("objectPicker_all_true") << objectPicker;
        objectPicker = new Qt3DRender::QObjectPicker();
        Qt3DRender::QAttribute *attr = new Qt3DRender::QAttribute();
        objectPicker->setPickAttribute(attr);
        QTest::newRow("objectPicker_withAttribute") << objectPicker;

    }

    void checkCloning()
    {
        // GIVEN
        QFETCH(Qt3DRender::QObjectPicker *, objectPicker);

        // WHEN
        Qt3DRender::QObjectPicker *clone = static_cast<Qt3DRender::QObjectPicker *>(QNode::clone(objectPicker));
        QCoreApplication::processEvents();

        // THEN
        QVERIFY(clone != Q_NULLPTR);
        QCOMPARE(objectPicker->id(), clone->id());
        QCOMPARE(objectPicker->hoverEnabled(), clone->hoverEnabled());
        QCOMPARE(objectPicker->isPressed(), clone->isPressed());
        QCOMPARE(objectPicker->containsMouse(), clone->containsMouse());

        if (objectPicker->pickAttribute()) {
            QVERIFY(clone->pickAttribute());
            QCOMPARE(clone->pickAttribute()->id(), objectPicker->pickAttribute()->id());
        }
    }

    void checkPropertyUpdates()
    {
        // GIVEN
        QScopedPointer<Qt3DRender::QObjectPicker> objectPicker(new Qt3DRender::QObjectPicker());
        TestArbiter arbiter(objectPicker.data());

        // WHEN
        Qt3DRender::QAttribute *attr = new Qt3DRender::QAttribute();
        objectPicker->setPickAttribute(attr);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.events.size(), 1);
        Qt3DCore::QScenePropertyChangePtr change = arbiter.events.first().staticCast<Qt3DCore::QScenePropertyChange>();
        QCOMPARE(change->propertyName(), "pickAttribute");
        QCOMPARE(change->value().value<Qt3DCore::QNodeId>(), attr->id());
        QCOMPARE(change->type(), Qt3DCore::NodeUpdated);

        arbiter.events.clear();

        // WHEN
        objectPicker->setHoverEnabled(true);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.events.size(), 1);
        change = arbiter.events.last().staticCast<Qt3DCore::QScenePropertyChange>();
        QCOMPARE(change->propertyName(), "hoverEnabled");
        QCOMPARE(change->value().toBool(), true);
        QCOMPARE(change->type(), Qt3DCore::NodeUpdated);

        arbiter.events.clear();

    }

    void checkBackendUpdates()
    {
        // GIVEN
        //QScopedPointer<MyObjectPicker> objectPicker(new MyObjectPicker());

        // TO DO: Complete
        // WHEN
        // Create Backend Change and distribute it to frontend node
        // objectPicker->sceneChangeEvent();

        // THEN
        // Check that the QOjectPicker triggers the expected signal
    }


protected:
    Qt3DCore::QNode *doClone() const Q_DECL_OVERRIDE
    {
        return Q_NULLPTR;
    }

};

QTEST_MAIN(tst_QObjectPicker)

#include "tst_qobjectpicker.moc"
