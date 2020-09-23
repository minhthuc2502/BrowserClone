#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtWebKitWidgets>

class mainWindow : public QMainWindow {
    Q_OBJECT
private:
    QAction *w_previous;
    QAction *w_next;
    QAction *w_stop;
    QAction *w_refresh;
    QAction *w_home;
    QAction *w_changeTab;
    QLineEdit *searchBar;

    QMenu *fileMenu;
    QMenu *ActionsMenu;
    QMenu *helpMenu;
    QAction *helpAction;

    QWebView *w_webpage;
public:
    mainWindow();
    void addWindowActions();
    void addWindowMenu();
    void addCentralWindow();
public slots:
    void returnHome();
    void updateURL(QUrl);
    void applySearchText(); // this slot will take content in search bar and apply to web page
};

#endif // MAINWINDOW_H
