#include <mainWindow.h>

mainWindow::mainWindow() : QMainWindow() {
    addWindowActions();
    addWindowMenu();
    addCentralWindow();
}

void mainWindow::addWindowActions() {
    // set button on tool bar
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
    // set search bar on tool bar
    searchBar = new QLineEdit();
    searchBar->addAction(QIcon(QApplication::applicationDirPath() + "/../BrowserClone/img/google.png"), QLineEdit::LeadingPosition);
    searchBar->setLayoutDirection(Qt::LeftToRight);

    // set up tool bar
    QToolBar *w_toolBar = new QToolBar("tool bar of browser", this);
    w_toolBar->addAction(w_previous);
    w_toolBar->addAction(w_next);
    w_toolBar->addAction(w_stop);
    w_toolBar->addAction(w_refresh);
    w_toolBar->addAction(w_home);
    w_toolBar->addWidget(searchBar);
    w_toolBar->addAction(w_changeTab);

    // add tool bar to window
    addToolBar(w_toolBar);
}

void mainWindow::addWindowMenu() {
    // set up menu bar with menus
    fileMenu = menuBar()->addMenu(tr("&File"));
    ActionsMenu = menuBar()->addMenu(tr("&Actions"));
    helpMenu = menuBar()->addMenu(tr("&Help"));
    // add Actions in menu
    // file menu
    QAction *openTabAction = fileMenu->addAction(tr("Open tab"));
    QAction *closeTabAction = fileMenu->addAction(tr("Close Tab"));
    QAction* exitAction = fileMenu->addAction(tr("Exit"));
    exitAction->setShortcut(QKeySequence("Alt+F4"));
    // actions menu
    ActionsMenu->addAction(w_previous);
    ActionsMenu->addAction(w_next);
    ActionsMenu->addAction(w_stop);
    ActionsMenu->addAction(w_refresh);
    ActionsMenu->addAction(w_home);
    ActionsMenu->addAction(w_changeTab);
    // help menu
    helpAction = new QAction(QIcon(QApplication::applicationDirPath() + "/../BrowserClone/img/questionMark.png"), tr("About Browser Clone..."));
    helpMenu->addAction(helpAction);
    // add connection for menu bar
    connect(exitAction, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    connect(openTabAction, SIGNAL(triggered(bool)), this, SLOT(addPage()));
    connect(closeTabAction, SIGNAL(triggered(bool)), this, SLOT(closeCurrentPage()));
}

void mainWindow::addCentralWindow() {
    // create first central window for browser when open it
    webTabs = new QTabWidget();
    // add first tab
    c_webpage = new QWebView();
    addNewTab(c_webpage);
    // tab + to add more tab by users
    QWidget* plusPage = new QWidget();
    webTabs->addTab(plusPage, "+");

    // add tab widget to central window
    setCentralWidget(webTabs);

    setCurrentWebPage();
    // add connection for behaviors of tabs
    connect(webTabs, SIGNAL(currentChanged(int)), this, SLOT(setCurrentWebPage()));
    connect(webTabs, SIGNAL(tabBarClicked(int)), this, SLOT(addPage(int)));
}

void mainWindow::setCurrentWebPage() {
    c_webpage = webTabs->currentWidget()->findChild<QWebView *>();
    // set connnect for actions
    connect(w_previous, SIGNAL(triggered(bool)), c_webpage, SLOT(back()));
    connect(w_next, SIGNAL(triggered(bool)), c_webpage, SLOT(forward()));
    connect(w_stop, SIGNAL(triggered(bool)), c_webpage, SLOT(stop()));
    connect(w_refresh, SIGNAL(triggered(bool)), c_webpage, SLOT(reload()));
    connect(w_home, SIGNAL(triggered(bool)), this, SLOT(returnHome()));
    connect(c_webpage, SIGNAL(urlChanged(QUrl)), this, SLOT(updateURL(QUrl)));
    connect(searchBar, SIGNAL(returnPressed()), this, SLOT(applySearchText()));
    connect(c_webpage,SIGNAL(loadProgress(int)), this, SLOT(updateLoadProgress(int)));
    connect(c_webpage, SIGNAL(loadFinished(bool)), this, SLOT(updateFinishProgress()));
    connect(c_webpage, SIGNAL(loadProgress(int)), this, SLOT(updateTitlePage()));
}

void mainWindow::addNewTab(QWebView *tab) {
    tab->load(QUrl("https://www.google.com/"));
    QWidget* TabWidget = new QWidget();
    QVBoxLayout* tabLayout = new QVBoxLayout();
    tabLayout->addWidget(tab);
    TabWidget->setLayout(tabLayout);

    QTabBar *tabBarStyle = webTabs->tabBar();
    QPushButton *closeTabButton = new QPushButton("X");
    QString styleCloseButton = "QPushButton {"
                                   "border-width: 0.1px;"
                                   "border-style: solid;"
                                   "border-radius: 7px;"
                                   "background-color: rgba( 255, 255, 255, 0% );"
                                   "max-width: 14px;"
                                   "max-height: 14px;"
                                   "min-width: 14px;"
                                   "min-height: 14px;"
                                   "background-position: center"
                               "}"
                               "QPushButton:hover {"
                                   "background-color: #D8D8D8;"
                               "}";
    closeTabButton->setStyleSheet(styleCloseButton);

    if (webTabs->count() >= 1) {
        webTabs->insertTab(webTabs->count() - 1, TabWidget, "New Tab");
        tabBarStyle->setTabButton(webTabs->count() - 2, QTabBar::RightSide, closeTabButton);
    }
    else if (webTabs->count() == 0) {
        webTabs->addTab(TabWidget, "New Tab");
        tabBarStyle->setTabButton(webTabs->count() - 1, QTabBar::RightSide, closeTabButton);
    }

    connect(closeTabButton, SIGNAL(clicked(bool)), this, SLOT(closeCurrentPage()));
}

void mainWindow::returnHome() {
    c_webpage->load(QUrl("https://www.google.com/"));
}

void mainWindow::updateURL(QUrl currentUrl) {
    searchBar->setText(currentUrl.toString());
}

void mainWindow::applySearchText() {
    QUrl url = QUrl::fromUserInput(searchBar->text());
    if (url.topLevelDomain().isEmpty())
        c_webpage->load(QUrl("https://www.google.com/search?q=" + searchBar->text()));
    else {
        c_webpage->load(url);
    }
}

void mainWindow::updateLoadProgress(int pr) {
    float progress = pr;
    if (progress < 0.1)
        progress = 1;
    else
        progress -= 0.15;
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

void mainWindow::updateFinishProgress() {
    QPalette* searchPalette = new QPalette();   // contain color defined in gradient
    QRect rs = searchBar->rect();
    // gradient using to set color for search bar
    QLinearGradient *gradient = new QLinearGradient(rs.topLeft(), rs.topRight());
    gradient->setColorAt(0, QColor("#FFFFFF"));
    gradient->setColorAt(1, QColor("#FFFFFF"));
    searchPalette->setBrush(QPalette::Base, QBrush(*gradient));
    searchBar->setPalette(*searchPalette);
}

void mainWindow::addPage(int index) {
    if (index == (webTabs->count() - 1)) {
        QWebView *newWebpage = new QWebView();
        addNewTab(newWebpage);
    }
    else return;
}

void mainWindow::addPage() {
    QWebView *newWebpage = new QWebView();
    addNewTab(newWebpage);
}

void mainWindow::closeCurrentPage() {
    if (webTabs->currentIndex() == 0) {
        if (webTabs->count() == 2) {
            qApp->quit();
            return;
        }
        else {
            webTabs->setCurrentIndex(webTabs->currentIndex() + 1);
            webTabs->removeTab(webTabs->currentIndex() - 1);
        }
    } else {
        webTabs->setCurrentIndex(webTabs->currentIndex() - 1);
        webTabs->removeTab(webTabs->currentIndex() + 1);
    }
}

void mainWindow::updateTitlePage() {
    webTabs->setTabText(webTabs->currentIndex(), webTabs->currentWidget()->findChild<QWebView *>()->title());
}
