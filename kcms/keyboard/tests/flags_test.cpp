/*
 *  Copyright (C) 2011 Andriy Rysin (rysin@kde.org)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <QIcon>
#include <QtTest>

#include "../flags.h"
#include "../keyboard_config.h"
#include "../xkb_rules.h"

class FlagsTest : public QObject
{
    Q_OBJECT

    Flags *flags;
    const Rules *rules;

private Q_SLOTS:
    void initTestCase()
    {
        flags = new Flags();
        rules = nullptr;
    }

    void cleanupTestCase()
    {
        delete flags;
        delete rules;
    }

    void testRules()
    {
        QVERIFY(flags != nullptr);

        const QIcon iconUs(flags->getIcon(QStringLiteral("us")));
        QVERIFY(!iconUs.isNull());
        QVERIFY(flags->getIcon("--").isNull());

        KeyboardConfig keyboardConfig;
        LayoutUnit layoutUnit(QStringLiteral("us"));
        LayoutUnit layoutUnit1(QStringLiteral("us"), QStringLiteral("intl"));
        layoutUnit1.setDisplayName(QStringLiteral("usi"));
        LayoutUnit layoutUnit2(QStringLiteral("us"), QStringLiteral("other"));

        keyboardConfig.layouts.append(layoutUnit1);
        QCOMPARE(flags->getShortText(layoutUnit, keyboardConfig), QString("us"));
        QCOMPARE(flags->getShortText(layoutUnit1, keyboardConfig), QString("usi"));
        QCOMPARE(flags->getShortText(layoutUnit2, keyboardConfig), QString("us"));

        const Rules *rules = Rules::readRules(Rules::NO_EXTRAS);
        QCOMPARE(flags->getLongText(layoutUnit, rules), QString("English (US)"));
        QCOMPARE(flags->getLongText(layoutUnit2, rules), QString("other"));

        rules = nullptr; // when no rules found
        QCOMPARE(flags->getLongText(layoutUnit1, rules), QString("us - intl"));
    }

    //    void loadRulesBenchmark() {
    //    	QBENCHMARK {
    //    		Flags* flags = new Flags();
    //    		delete flags;
    //    	}
    //    }
};

// need GUI for xkb protocol in xkb_rules.cpp
QTEST_MAIN(FlagsTest)

#include "flags_test.moc"
