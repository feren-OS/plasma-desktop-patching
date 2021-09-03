/*
 *  Copyright (C) 2018 <furkantokac34@gmail.com>
 *  Copyright (c) 2019 Cyril Rossi <cyril.rossi@enioka.com>
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

#ifndef _KCM_LANDINGPAGE_H
#define _KCM_LANDINGPAGE_H

#include "config-landingpage.h"

#include <KPackage/Package>
#include <KQuickAddons/ManagedConfigModule>
#include <QJsonArray>
#include <QJsonValue>

class QStandardItemModel;

class LandingPageData;
class LandingPageGlobalsSettings;

class FeedbackSettings;

namespace KActivities
{
namespace Stats
{
class ResultModel;
}
}

class MostUsedModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    enum Roles { KcmPluginRole = Qt::UserRole + 1000 };

    explicit MostUsedModel(QObject *parent = nullptr);
    void setResultModel(KActivities::Stats::ResultModel *model);
    QHash<int, QByteArray> roleNames() const override;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    // Model when there is nothing from kactivities-stat
    QStandardItemModel *m_defaultModel;
    // Model fed by kactivities-stats
    KActivities::Stats::ResultModel *m_resultModel;
};

class LookAndFeelGroup : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString thumbnail READ thumbnail CONSTANT)

public:
    LookAndFeelGroup(QObject *parent = nullptr);
    QString id() const;
    QString name() const;
    QString thumbnail() const;

    KPackage::Package m_package;
};

class KCMLandingPage : public KQuickAddons::ManagedConfigModule
{
    Q_OBJECT
    Q_PROPERTY(MostUsedModel *mostUsedModel READ mostUsedModel CONSTANT)
    Q_PROPERTY(LandingPageGlobalsSettings *globalsSettings READ globalsSettings CONSTANT)
#if HAVE_KUSERFEEDBACK
    Q_PROPERTY(bool feedbackEnabled READ feedbackEnabled CONSTANT)
    Q_PROPERTY(FeedbackSettings *feedbackSettings READ feedbackSettings CONSTANT)
    Q_PROPERTY(QJsonArray feedbackSources MEMBER m_feedbackSources NOTIFY feedbackSourcesChanged)
#endif
    Q_PROPERTY(LookAndFeelGroup *defaultLightLookAndFeel READ defaultLightLookAndFeel CONSTANT)
    Q_PROPERTY(LookAndFeelGroup *defaultMixedLookAndFeel READ defaultMixedLookAndFeel CONSTANT)
    Q_PROPERTY(LookAndFeelGroup *defaultDarkLookAndFeel READ defaultDarkLookAndFeel CONSTANT)

public:
    KCMLandingPage(QObject *parent, const QVariantList &args);
    ~KCMLandingPage() override
    {
    }

    MostUsedModel *mostUsedModel() const;

    LandingPageGlobalsSettings *globalsSettings() const;
#if HAVE_KUSERFEEDBACK
    void programFinished(int exitCode);
    bool feedbackEnabled() const;
    FeedbackSettings *feedbackSettings() const;
#endif

    LookAndFeelGroup *defaultLightLookAndFeel() const;
    LookAndFeelGroup *defaultMixedLookAndFeel() const;
    LookAndFeelGroup *defaultDarkLookAndFeel() const;

    Q_INVOKABLE void openWallpaperDialog();
    Q_INVOKABLE void openKCM(const QString &kcm);

public Q_SLOTS:
    void save() override;

#if HAVE_KUSERFEEDBACK
Q_SIGNALS:
    void feedbackSourcesChanged();
#endif

private:
    LandingPageData *m_data;

    LookAndFeelGroup *m_defaultLightLookAndFeel = nullptr;
    LookAndFeelGroup *m_defaultMixedLookAndFeel = nullptr;
    LookAndFeelGroup *m_defaultDarkLookAndFeel = nullptr;

    MostUsedModel *m_mostUsedModel = nullptr;

    QHash<int, QHash<QString, QJsonArray>> m_uses;
#if HAVE_KUSERFEEDBACK
    QJsonArray m_feedbackSources;
#endif
    bool m_lnfDirty = false;
};

#endif // _KCM_LANDINGPAGE_H
