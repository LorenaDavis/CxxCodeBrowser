#include <QApplication>
#include <QTextCodec>

#include "Application.h"
#include "Misc.h"
#include "Project.h"

int main(int argc, char *argv[])
{
    Nav::Application a(argc, argv);

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    // For Qt4, set the default codec for C strings to UTF-8.  With Qt5, the
    // codec for C strings is already UTF-8, and there is no
    // QTextCodec::setCodecForCStrings function to call.
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif

    Nav::hackSwitchIconThemeToTheOneWithIcons();
    int result = a.exec();
    Nav::theProject.reset();
    return result;
}
