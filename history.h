/*
 * Todo:
 * - change method to add history to file
 * - custom tab widget history
 * - delete page have to open the tab of this page before (need to be changed)
 * - handle datetime and title in history (function datetime() not work and title() is set in depend on which page)
*/
#ifndef HISTORY_H
#define HISTORY_H

#include <QtWebKitWidgets>

class history : public QWidget {
    Q_OBJECT
private:
    QPushButton *clearHistory;
    QListWidget *historyList;
signals:
    void itemHistoryDoubleClicked(QListWidgetItem *);
public:
    history();
    static void addHistory(const QWebView *);
    QListWidget *getHistoryList();
    void showHistory();
public slots:
    void removeHistory();
    void refreshHistoryPage();
};

#endif // HISTORY_H
