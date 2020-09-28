#include <helpPage.h>

helpPage::helpPage() : QTextBrowser() {
    QString htmlText = "<!DOCTYPE html>"
                       "<html>"
                       "<body>"
                       "<h1>My browser</h1>"
                       "<p>This browser is reated by Qt framework. I used qt widgets and webkitwidget to build it.<br><br>"
                       "I do it project to learn the most used widgets in Qt widgets.<br><br>"
                       "This is the version 0.1.</p>"
                       "</body>"
                       "</html>";
    setHtml(htmlText);
    setFrameStyle(QFrame::NoFrame);
}
