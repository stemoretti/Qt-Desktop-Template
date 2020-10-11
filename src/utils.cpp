#include "utils.h"

#include <QCoreApplication>
#include <QDir>
#include <QRegularExpression>

#include "config.h"

namespace Utils
{

QString resourcePath(const QString &path)
{
    QDir directory(QCoreApplication::applicationDirPath());

    if (directory.cd(path) // when run on Windows
        || directory.cd(QDir(path).dirName()) // when run inside the build directory
        || (directory.cdUp() && directory.cd(path))) // when run on Linux
        return directory.absolutePath();

    return QString();
}

QStringList languages()
{
    QDir translationsDir(resourcePath(TRANSLATIONS_PATH));
    QStringList languages("en_US");

    if (translationsDir.exists()) {
        QStringList translations = translationsDir.entryList({ PROJECT_NAME "*.qm" });
        translations.replaceInStrings(QRegularExpression("[^_]+_(\\w+)\\.qm"), "\\1");
        languages.append(translations);
        languages.sort();
    }

    return languages;
}

}
