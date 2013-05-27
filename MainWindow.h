#ifndef main_window_h
#define main_window_h

#include <QtGui>
#include "PointsArea.h"

class MainWindow: public QWidget {

    Q_OBJECT

public:
    QRadioButton *RadioButtonBlue;
    QRadioButton *RadioButtonRed;
    QGridLayout *GridLayout1;
    QVBoxLayout *VBoxLayout1;
    PointsArea *PointsArea1;
    QGroupBox *GroupBox1;
    QPushButton *PushButtonClear;
    QPushButton *PushButtonDrawLine;
    QTextEdit *TextEdit1;
    QCheckBox *CheckBox1;

public slots:
    void RadioButtonClicked();
    void PushButtonClearClicked();
    void PushButtonDrawLineClicked();
    void CheckBox1StateChanged();
public:
    MainWindow();
};

#endif
