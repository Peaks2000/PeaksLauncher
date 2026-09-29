// SPDX-License-Identifier: GPL-3.0-only
#include "SyncingPage.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>

#include "Application.h"
#include "InstanceList.h"
#include "minecraft/MinecraftInstance.h"
#include "settings/SettingsObject.h"

SyncingPage::SyncingPage(QWidget* parent) : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);
    m_syncGameOptions = new QCheckBox(tr("Sync Minecraft game options between instances"), this);
    m_syncGameOptions->setChecked(APPLICATION->settings()->get("SyncGameOptions").toBool());
    layout->addWidget(m_syncGameOptions);

    layout->addWidget(new QLabel(tr("Inherit options.txt from:"), this));
    m_sourceInstance = new QComboBox(this);
    m_sourceInstance->setEnabled(m_syncGameOptions->isChecked());
    connect(m_syncGameOptions, &QCheckBox::toggled, m_sourceInstance, &QComboBox::setEnabled);
    layout->addWidget(m_sourceInstance);
    refreshInstances();

    auto* description = new QLabel(
        tr("Choose an instance to use its options.txt as the source for other instances. Changes in other instances "
           "will not replace the source file. If no source is chosen, options are shared after each game exits and "
           "the first launched instance supplies the initial file. Some options may differ between Minecraft versions."),
        this);
    description->setWordWrap(true);
    layout->addWidget(description);
    layout->addStretch();
}

bool SyncingPage::apply()
{
    APPLICATION->settings()->set("SyncGameOptions", m_syncGameOptions->isChecked());
    APPLICATION->settings()->set("SyncGameOptionsSourceInstance", m_sourceInstance->currentData().toString());
    return true;
}

void SyncingPage::openedImpl()
{
    refreshInstances();
}

void SyncingPage::refreshInstances()
{
    QString selectedId = m_sourceInstance->currentData().toString();
    if (m_sourceInstance->count() == 0)
        selectedId = APPLICATION->settings()->get("SyncGameOptionsSourceInstance").toString();

    m_sourceInstance->clear();
    m_sourceInstance->addItem(tr("No source (share changes between instances)"), QString());

    if (auto* instances = APPLICATION->instances()) {
        for (int i = 0; i < instances->count(); ++i) {
            const auto* instance = instances->at(i);
            m_sourceInstance->addItem(instance->name(), instance->uuid());
        }
    }

    if (!selectedId.isEmpty()) {
        int selectedIndex = m_sourceInstance->findData(selectedId);
        if (selectedIndex < 0 && APPLICATION->instances()) {
            // Older settings may contain an instance ID rather than a UUID.
            if (const auto* instance = APPLICATION->instances()->getInstanceById(selectedId))
                selectedIndex = m_sourceInstance->findData(instance->uuid());
        }
        if (selectedIndex < 0) {
            m_sourceInstance->addItem(tr("Missing instance (%1)").arg(selectedId), selectedId);
            selectedIndex = m_sourceInstance->count() - 1;
        }
        m_sourceInstance->setCurrentIndex(selectedIndex);
    }
}
