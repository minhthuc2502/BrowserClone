#include <findTextBox.h>

findTextBox::findTextBox() : QWidget() {
    setWindowTitle("Find Text");
    QString styleFindButton = "QPushButton {"
                              " border-color: #424242;"
                              "}"
                              "QPushButton:hover {"
                              " background-color: #E6E6E6"
                              "}";
    findTextLine = new QLineEdit();
    previousTextButton = new QPushButton();
    previousTextButton->setIcon(QIcon(QApplication::applicationDirPath() + "/../git/img/up-arrow.png"));
    previousTextButton->setDisabled(true);
    previousTextButton->setStyleSheet(styleFindButton);
    nextTextButton = new QPushButton();
    nextTextButton->setIcon(QIcon(QApplication::applicationDirPath() + "/../git/img/down-arrow.png"));
    nextTextButton->setDisabled(true);
    nextTextButton->setStyleSheet(styleFindButton);
    closeFindTextBox = new QPushButton();
    closeFindTextBox->setIcon(QIcon(QApplication::applicationDirPath() + "/../git/img/cancel.png"));
    closeFindTextBox->setStyleSheet(styleFindButton);

    QHBoxLayout *findTextLayout = new QHBoxLayout();

    findTextLayout->addWidget(findTextLine);
    findTextLayout->addWidget(previousTextButton);
    findTextLayout->addWidget(nextTextButton);
    findTextLayout->addWidget(closeFindTextBox);

    this->setLayout(findTextLayout);

    connect(findTextLine, SIGNAL(textChanged(QString)), this, SLOT(generateSignalTextChanged(QString)));
    connect(closeFindTextBox, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void findTextBox::generateSignalTextChanged(QString text) {
    emit textChanged(text);
}

QPushButton* findTextBox::getNextTextButton() {
    return nextTextButton;
}

QPushButton* findTextBox::getPreviousTextButton() {
    return previousTextButton;
}

QPushButton* findTextBox::getCloseButton() {
    return closeFindTextBox;
}
