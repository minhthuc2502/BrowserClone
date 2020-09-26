#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtWebKitWidgets>
#include <QTextBrowser>
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

    QTabWidget *webTabs;
    QWebView *c_webpage;        // current web tab

    void addNewTab(QWebView *);
public:
    explicit mainWindow();
    void addWindowActions();
    void addWindowMenu();
    void addCentralWindow();
private slots:
    void returnHome();
    void updateURL(QUrl);           // update url to search bar
    void applySearchText();         // this slot will take content in search bar and apply to web page
    void updateLoadProgress(int);   // update load progress on search bar
    void updateFinishProgress();    // update style search bar when load finish
    void updateTitlePage();         // update title of web page on tab
public slots:
    void setCurrentWebPage();       // update current tab and connection of actions
    void addPage(int index);        // add tab for searching
    void addPage();                 // add tab for searching using for action open tab in file menu
    void closeCurrentPage();        // close current tab
    void addHelpTab();              // add help tab
};

#endif // MAINWINDOW_H
