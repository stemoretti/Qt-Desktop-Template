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

    if (directory.cd(path) || directory.cd(QDir(path).dirName()) ||
        (directory.cdUp() && directory.cd(path)))
        return directory.absolutePath();

    return QString();
}

QStringList languages()
{
    QDir translationsDir(resourcePath(TRANSLATIONS_PATH));
    QStringList languages("en_US");

    if (translationsDir.exists()) {
        QStringList translations = translationsDir.entryList({"*.qm"});
        translations.replaceInStrings(QRegularExpression("[^_]+_(\\w+)\\.qm"), "\\1");
        languages.append(translations);
        languages.sort();
    }

    return languages;
}

}
