// SPDX-License-Identifier: GPL-3.0-only
#include "SyncingPage.h"

#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>

#include "Application.h"
#include "settings/SettingsObject.h"

SyncingPage::SyncingPage(QWidget* parent) : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);
    m_syncGameOptions = new QCheckBox(tr("Sync Minecraft game options between instances"), this);
    m_syncGameOptions->setChecked(APPLICATION->settings()->get("SyncGameOptions").toBool());
    layout->addWidget(m_syncGameOptions);

    auto* description = new QLabel(
        tr("When enabled, options.txt is copied into an instance before launch and shared after the game exits. "
           "The first launched instance supplies the initial options. Some options may differ between Minecraft versions."),
        this);
    description->setWordWrap(true);
    layout->addWidget(description);
    layout->addStretch();
}

bool SyncingPage::apply()
{
    APPLICATION->settings()->set("SyncGameOptions", m_syncGameOptions->isChecked());
    return true;
}
