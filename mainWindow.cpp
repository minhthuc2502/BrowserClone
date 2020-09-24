#include <mainWindow.h>

mainWindow::mainWindow() : QMainWindow() {
    addWindowActions();
    addWindowMenu();
    addCentralWindow();
    // set connnect for actions
    connect(w_previous, SIGNAL(triggered()), w_webpage, SLOT(back()));
    connect(w_next, SIGNAL(triggered(bool)), w_webpage, SLOT(forward()));
    connect(w_stop, SIGNAL(triggered(bool)), w_webpage, SLOT(stop()));
    connect(w_refresh, SIGNAL(triggered(bool)), w_webpage, SLOT(reload()));
    connect(w_home, SIGNAL(triggered(bool)), this, SLOT(returnHome()));
    connect(w_webpage, SIGNAL(urlChanged(QUrl)), this, SLOT(updateURL(QUrl)));
    connect(searchBar, SIGNAL(returnPressed()), this, SLOT(applySearchText()));
    connect(w_webpage,SIGNAL(loadProgress(int)), this, SLOT(updateLoadProgress(int)));
}

void mainWindow::addWindowActions() {
    w_previous = new QAction(tr("Previous"));
    w_previous->setToolTip(tr("click to go back"));
    w_previous->setIcon(QIcon(QApplication::applicationDirPath() + "/../BrowserClone/img/left-arrow.png"));
    w_next = new QAction(tr("Next"));
    w_next->setToolTip(tr("click to go foward"));
    w_next->setIcon(QIcon(QApplication::applicationDirPath() + "/../BrowserClone/img/right-arrow.png"));
    w_stop = new QAction(tr("Stop"));
    w_stop->setToolTip(tr("click to stop loading page"));
    w_stop->setIcon(QIcon(QApplication::applicationDirPath() + "/../BrowserClone/img/stop.png"));
    w_refresh = new QAction(tr("Refresh"));
    w_refresh->setToolTip(tr("click to refresh page"));
    w_refresh->setIcon(QIcon(QApplication::applicationDirPath() + "/../BrowserClone/img/refresh.png"));
    w_home = new QAction(tr("Home"));
    w_home->setToolTip(tr("click to return home page"));
    w_home->setIcon(QIcon(QApplication::applicationDirPath() + "/../BrowserClone/img/home.png"));
    w_changeTab = new QAction(tr("Change tab"));
    w_changeTab->setToolTip(tr("click to change tab"));
    w_changeTab->setIcon(QIcon(QApplication::applicationDirPath() + "/../BrowserClone/img/next.png"));
    searchBar = new QLineEdit();
    searchBar->addAction(QIcon(QApplication::applicationDirPath() + "/../BrowserClone/img/google.png"), QLineEdit::LeadingPosition);
    searchBar->setLayoutDirection(Qt::LeftToRight);

    QToolBar *w_toolBar = new QToolBar("tool bar of browser", this);
    w_toolBar->addAction(w_previous);
    w_toolBar->addAction(w_next);
    w_toolBar->addAction(w_stop);
    w_toolBar->addAction(w_refresh);
    w_toolBar->addAction(w_home);
    w_toolBar->addWidget(searchBar);
    w_toolBar->addAction(w_changeTab);

    addToolBar(w_toolBar);
}

void mainWindow::addWindowMenu() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    ActionsMenu = menuBar()->addMenu(tr("&Actions"));
    helpMenu = menuBar()->addMenu(tr("&Help"));
    // add Action in menu
    fileMenu->addAction(tr("Open tab"));
    fileMenu->addAction(tr("Close Tab"));
    fileMenu->addAction(tr("Exit"));

    ActionsMenu->addAction(w_previous);
    ActionsMenu->addAction(w_next);
    ActionsMenu->addAction(w_stop);
    ActionsMenu->addAction(w_refresh);
    ActionsMenu->addAction(w_home);
    ActionsMenu->addAction(w_changeTab);

    helpAction = new QAction(QIcon(QApplication::applicationDirPath() + "/../BrowserClone/img/questionMark.png"), tr("About Browser Clone..."));
    helpMenu->addAction(helpAction);
}

void mainWindow::addCentralWindow() {
    w_webpage = new QWebView();
    w_webpage->load(QUrl("https://www.google.com/"));
    QWidget* centralWindow = new QWidget();
    QVBoxLayout* centralLayout = new QVBoxLayout();
    centralLayout->addWidget(w_webpage);
    centralWindow->setLayout(centralLayout);
    setCentralWidget(centralWindow);

    connect(w_webpage, SIGNAL(urlChanged(QUrl)), w_webpage, SLOT(update()));
}


void mainWindow::returnHome() {
    w_webpage->load(QUrl("https://www.google.com/"));
}

void mainWindow::updateURL(QUrl currentUrl) {
    searchBar->setText(currentUrl.toString());
}

void mainWindow::applySearchText() {
    w_webpage->load(QUrl("https://www.google.com/search?q=" + searchBar->text()));
}

void mainWindow::updateLoadProgress(int pr) {
    float progress = pr;
    if (progress < 0.1)
        progress = 1;
    else
        progress -= 0.1;
    QPalette* searchPalette = new QPalette();   // contain color defined in gradient
    QRect rs = searchBar->rect();
    // gradient using to set color for search bar
    QLinearGradient *gradient = new QLinearGradient(rs.topLeft(), rs.topRight());
    gradient->setColorAt(progress/100 + 0.001, QColor("#ffffff"));
    gradient->setColorAt(progress/100, QColor("#00FF40"));
    gradient->setColorAt(progress/100 - 0.001, QColor("#82FA58"));
    searchPalette->setBrush(QPalette::Base, QBrush(*gradient));
    searchBar->setPalette(*searchPalette);
}
