// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include <QWidget>
#include "ui/pages/BasePage.h"

class QCheckBox;
class QComboBox;

class SyncingPage : public QWidget, public BasePage {
    Q_OBJECT

   public:
    explicit SyncingPage(QWidget* parent = nullptr);

    QString displayName() const override { return tr("Syncing"); }
    QIcon icon() const override { return QIcon::fromTheme("refresh"); }
    QString id() const override { return "syncing-settings"; }
    bool apply() override;
    void openedImpl() override;

   private:
    void refreshInstances();

    QCheckBox* m_syncGameOptions;
    QComboBox* m_sourceInstance;
};
