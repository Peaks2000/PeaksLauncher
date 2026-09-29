// SPDX-License-Identifier: GPL-3.0-only
#include "GameOptionsSync.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSaveFile>

namespace {
bool readOptions(const QString& path, QByteArray& contents, QString& error)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        error = file.errorString();
        return false;
    }
    contents = file.readAll();
    if (file.error() != QFileDevice::NoError) {
        error = file.errorString();
        return false;
    }
    return true;
}

bool writeOptions(const QString& path, const QByteArray& contents, QString& error)
{
    if (!QDir().mkpath(QFileInfo(path).absolutePath())) {
        error = QStringLiteral("Could not create the options directory");
        return false;
    }
    QSaveFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        error = file.errorString();
        return false;
    }
    if (file.write(contents) != contents.size() || !file.commit()) {
        error = file.errorString();
        return false;
    }
    return true;
}
}  // namespace

QString GameOptionsSync::beforeLaunch(const QString& gameRoot, const QString& dataRoot)
{
    m_localPath = QDir(gameRoot).filePath(QStringLiteral("options.txt"));
    m_sharedPath = QDir(dataRoot).filePath(QStringLiteral("sync/options.txt"));
    m_initialOptions.clear();
    m_active = false;

    QString error;
    if (QFileInfo::exists(m_sharedPath)) {
        if (!readOptions(m_sharedPath, m_initialOptions, error))
            return error;

        QByteArray localOptions;
        if (QFileInfo::exists(m_localPath) && !readOptions(m_localPath, localOptions, error))
            return error;
        if (!QFileInfo::exists(m_localPath) || localOptions != m_initialOptions) {
            if (!writeOptions(m_localPath, m_initialOptions, error))
                return error;
        }
    } else if (QFileInfo::exists(m_localPath)) {
        if (!readOptions(m_localPath, m_initialOptions, error) || !writeOptions(m_sharedPath, m_initialOptions, error))
            return error;
    }
    m_active = true;
    return {};
}

QString GameOptionsSync::afterExit()
{
    if (!m_active || !QFileInfo::exists(m_localPath))
        return {};

    QByteArray currentOptions;
    QString error;
    if (!readOptions(m_localPath, currentOptions, error))
        return error;
    if ((!QFileInfo::exists(m_sharedPath) || currentOptions != m_initialOptions) &&
        !writeOptions(m_sharedPath, currentOptions, error))
        return error;
    return {};
}
