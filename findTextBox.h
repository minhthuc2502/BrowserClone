#ifndef FINDTEXTBOX_H
#define FINDTEXTBOX_H

#include <QtWidgets>

class findTextBox : public QWidget {
    Q_OBJECT
private:
    QLineEdit *findTextLine;
    QPushButton *closeFindTextBox;
    QPushButton *nextTextButton;
    QPushButton *previousTextButton;
public:
    findTextBox();
    QPushButton* getNextTextButton();
    QPushButton* getPreviousTextButton();
    QPushButton* getCloseButton();
    bool isOpen();
signals:
    void textChanged(QString);
public slots:
    void generateSignalTextChanged(QString);
};

#endif // FINDTEXTBOX_H
