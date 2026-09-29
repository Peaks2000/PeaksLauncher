// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include <QByteArray>
#include <QString>

class GameOptionsSync {
   public:
    // Returns an error for logging; a sync failure must not prevent launching Minecraft.
    QString beforeLaunch(const QString& gameRoot, const QString& dataRoot, const QString& sourceGameRoot = {});
    QString afterExit();

   private:
    QString m_localPath;
    QString m_sharedPath;
    QByteArray m_initialOptions;
    bool m_active = false;
};
