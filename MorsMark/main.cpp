#include "MorsMainWindow.h"
#include <MorsApp.h>

int main(int argc, char *argv[])
{
    MorsApp app(argc,argv);


//#ifdef MORS_WINDOWS_PLATFORM
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
//#else
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
//#endif // MORS_WINDOWS_PLATFORM

    MorsMainWindow window;

    if(argc > 1)
    {
       //window.openMarkdownFile(QString::fromLocal8Bit(argv[1]));
    }
    window.show();

    return app.exec();
}
