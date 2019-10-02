#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include <QObject>

class TestSuite : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void test();
};

#endif
