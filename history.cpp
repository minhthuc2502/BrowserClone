#include <history.h>
#include <QDebug>

history::history() : QWidget() {
    historyList = new QListWidget();
    clearHistory = new QPushButton(tr("Clear History"));
    connect(clearHistory, SIGNAL(clicked()), this, SLOT(removeHistory()));
}

void history::addHistory(const QWebView *current_webview) {
    QWebHistoryItem historyItem = current_webview->history()->currentItem();
    QString url = historyItem.url().toString();
    QString line;
    QFile file("/usr/share/qt-application/history.txt");
    file.open(QIODevice::ReadWrite);
    QTextStream out(&file);
    while (!out.atEnd()) {
        line = out.readLine();
        if (line == url)
            return;
    }
    file.close();
    file.open(QIODevice::Append);
    out << url + "\n";
    //out << historyItem.lastVisited().toString("h:m:s ap");
    //out << historyItem.title() + "\n";
    file.close();
    return;
}

void history::showHistory() {
    historyList->clear();
    QFile file("/usr/share/qt-application/history.txt");
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
    QFile file("/usr/share/qt-application/history.txt");
    file.open(QFile::WriteOnly|QFile::Truncate);
    file.close();
    // Show on web
    historyList->clear();
    historyList->show();
}

QListWidget* history::getHistoryList() {
    return historyList;
}

void history::refreshHistoryPage() {
    QFile file("/usr/share/qt-application/history.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    historyList->clear();
    while (!in.atEnd()) {
        QString line = in.readLine();
        historyList->addItem(line);
    }
    file.close();
}
