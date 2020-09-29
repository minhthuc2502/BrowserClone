#include <history.h>
#include <QDebug>

history::history() : QWidget() {
    historyList = new QListWidget();
    clearHistory = new QPushButton(tr("Clear History"));
    connect(clearHistory, SIGNAL(clicked()), this, SLOT(removeHistory()));
}

void history::addHistory(const QWebView *current_webview) {
    QList<QWebHistoryItem> historyItem = current_webview->history()->items();
    QFile file(QApplication::applicationDirPath() + "/../BrowserClone/history.txt");
    file.open(QIODevice::Append);
    QTextStream out(&file);
    for (QList<QWebHistoryItem>::iterator it = historyItem.begin(); it != historyItem.end(); it++)
    {
        out << it->url().toString() + "\n";
        //out << it->lastVisited().toString("h:m:s ap");
        //out << it->title() + "\n";
    }
    file.close();
    return;
}

void history::showHistory() {
    historyList->clear();
    QFile file(QApplication::applicationDirPath() + "/../BrowserClone/history.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        historyList->addItem(line);
    }
    file.close();
    QVBoxLayout *historyLayout = new QVBoxLayout();
    historyLayout->addWidget(clearHistory);
    historyLayout->addWidget(historyList);
    setLayout(historyLayout);
    clearHistory->setFixedSize(100, 25);
}

void history::removeHistory() {
    QFile file(QApplication::applicationDirPath() + "/../BrowserClone/history.txt");
    file.open(QFile::WriteOnly|QFile::Truncate);
    file.close();
    historyList->clear();
    historyList->show();
}

QListWidget* history::getHistoryList() {
    return historyList;
}
