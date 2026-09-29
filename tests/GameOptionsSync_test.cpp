#include <QDir>
#include <QFile>
#include <QTemporaryDir>
#include <QTest>

#include "minecraft/launch/GameOptionsSync.h"

namespace {
bool writeFile(const QString& path, const QByteArray& contents)
{
    QFile file(path);
    return file.open(QIODevice::WriteOnly | QIODevice::Truncate) && file.write(contents) == contents.size();
}

QByteArray readFile(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return {};
    return file.readAll();
}
}  // namespace

class GameOptionsSyncTest : public QObject {
    Q_OBJECT

   private slots:
    void sharesChangesBetweenInstances()
    {
        QTemporaryDir root;
        QVERIFY(root.isValid());
        const auto first = root.filePath("first");
        const auto second = root.filePath("second");
        QVERIFY(QDir().mkpath(first));
        QVERIFY(QDir().mkpath(second));

        const auto firstOptions = QDir(first).filePath("options.txt");
        const auto secondOptions = QDir(second).filePath("options.txt");
        const auto sharedOptions = root.filePath("sync/options.txt");
        QVERIFY(writeFile(firstOptions, "music:0.5\n"));
        QVERIFY(writeFile(secondOptions, "music:1.0\n"));

        GameOptionsSync firstLaunch;
        QVERIFY2(firstLaunch.beforeLaunch(first, root.path()).isEmpty(), "Could not initialize options sync");
        QCOMPARE(readFile(sharedOptions), QByteArray("music:0.5\n"));

        QVERIFY(writeFile(firstOptions, "music:0.2\n"));
        QVERIFY(firstLaunch.afterExit().isEmpty());
        QCOMPARE(readFile(sharedOptions), QByteArray("music:0.2\n"));

        GameOptionsSync secondLaunch;
        QVERIFY(secondLaunch.beforeLaunch(second, root.path()).isEmpty());
        QCOMPARE(readFile(secondOptions), QByteArray("music:0.2\n"));

        // An unchanged instance must not publish its former options over the shared copy.
        QVERIFY(writeFile(sharedOptions, "music:0.3\n"));
        QVERIFY(secondLaunch.afterExit().isEmpty());
        QCOMPARE(readFile(sharedOptions), QByteArray("music:0.3\n"));
    }
};

QTEST_GUILESS_MAIN(GameOptionsSyncTest)
#include "GameOptionsSync_test.moc"
