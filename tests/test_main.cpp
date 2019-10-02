#include <QCoreApplication>
#include <QTest>

#include "test_suite.h"

int main(int argc, char *argv[])
{
    QCoreApplication(argc, argv);

    TestSuite testSuite;

    return QTest::qExec(&testSuite, argc, argv);
}
