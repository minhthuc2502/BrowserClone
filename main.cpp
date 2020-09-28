#include <mainWindow.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    mainWindow w_browser;
    w_browser.setWindowState(Qt::WindowMaximized);

    w_browser.show();
    return app.exec();
}
