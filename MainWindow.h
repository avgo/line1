
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   line1 - разделение классов точек на плоскости.
 *   4-й курс, 2-й семестр.
 *   Лабораторная работа по курсу "Искусственный интеллект".
 *   01.02.2008 - 31.03.2008.
 *   Автор: Антон Гончаров
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

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
