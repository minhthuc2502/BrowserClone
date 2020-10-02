#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtWebKitWidgets>
#include <QTextBrowser>
#include <history.h>
#include <findTextBox.h>

class mainWindow : public QMainWindow {
    Q_OBJECT
private:
    QString textToFind;
    QAction *w_previous;
    QAction *w_next;
    QAction *w_stop;
    QAction *w_refresh;
    QAction *w_home;
    QAction *w_changeTab;
    QAction *openFindText;
    findTextBox* w_findBox;
    QLineEdit *searchBar;

    QMenu *fileMenu;
    QMenu *ActionsMenu;
    QMenu *helpMenu;
    QAction *helpAction;

    QTabWidget *webTabs;
    QWebView *c_webpage;        // current web tab

    void addWindowActions();
    void addWindowMenu();
    void addCentralWindow();
    void addNewTab(QWebView *, QString);
public:
    explicit mainWindow();
private slots:
    void returnHome();
    void updateURL(QUrl);           // update url to search bar
    void applySearchText();         // this slot will take content in search bar and apply to web page
    void updateLoadProgress(int);   // update load progress on search bar
    void updateFinishProgress();    // update style search bar when load finish
    void updateTitlePage();         // update title of web page on tab
    void findText(QString);         // call webView to find text
    void findNextText();            // find next text in web page
    void findPreviousText();        // find previous text in web page
    void clearTextFound();          // clear text found when find box closed
public slots:
    void setCurrentWebPage();       // update current tab and connection of actions
    void addPage(int index);        // add tab for searching
    void addPage();                 // add tab for searching using for action open tab in file menu
    void closeCurrentPage();        // close current tab
    void addHelpTab();              // add help tab
    void showHistoryTab();          // show history
    void callHistoryUrl(QListWidgetItem *);          // load old url
    void addFindBox();                // find text on page
};

#endif // MAINWINDOW_H
