#include "MainWindow.h"

MainWindow::MainWindow()
:   QWidget(0, Qt::Window)
{
    setWindowTitle(tr("Точки"));
    resize(600, 600);

    VBoxLayout1 = new QVBoxLayout;

    RadioButtonRed = new QRadioButton(tr("&Красная"));
    RadioButtonBlue = new QRadioButton(tr("&Синяя"));
    PushButtonClear = new QPushButton(tr("&Очистить"));
    PushButtonDrawLine = new QPushButton(tr("&Провести линию"));
    CheckBox1 = new QCheckBox(tr("&Показать опорные линии"));
    connect(RadioButtonRed, SIGNAL(clicked()), SLOT(RadioButtonClicked()));
    connect(RadioButtonBlue, SIGNAL(clicked()), SLOT(RadioButtonClicked()));
    connect(PushButtonClear, SIGNAL(clicked()), SLOT(PushButtonClearClicked()));
    connect(PushButtonDrawLine, SIGNAL(clicked()), SLOT(PushButtonDrawLineClicked()));
    connect(CheckBox1, SIGNAL(clicked()), SLOT(CheckBox1StateChanged()));

    VBoxLayout1->addWidget(RadioButtonRed);
    VBoxLayout1->addWidget(RadioButtonBlue);

    GroupBox1 = new QGroupBox;
    GroupBox1->setLayout(VBoxLayout1);
    
    TextEdit1 = new QTextEdit;

    GridLayout1 = new QGridLayout;

    PointsArea1 = new PointsArea;

    GridLayout1->addWidget(PointsArea1, 0, 0, 5, 1);
    GridLayout1->addWidget(GroupBox1, 0, 1);
    GridLayout1->addWidget(CheckBox1, 1, 1);
    GridLayout1->addWidget(PushButtonClear, 2, 1);
    GridLayout1->addWidget(PushButtonDrawLine, 3, 1);
    GridLayout1->addWidget(TextEdit1, 4, 1);
    GridLayout1->setColumnStretch(0, 1);
    GridLayout1->setColumnStretch(1, 0);
    GridLayout1->setRowStretch(0, 0);
    GridLayout1->setRowStretch(1, 0);
    GridLayout1->setRowStretch(2, 0);
    GridLayout1->setRowStretch(3, 0);
    GridLayout1->setRowStretch(4, 1);

    setLayout(GridLayout1);

    TextEdit1->resize(400, 100);
    RadioButtonRed->setChecked(true);
    CheckBox1->setChecked(false);
    PointsArea1->Lines1Visible = false;
}

void MainWindow::RadioButtonClicked()
{
    if(RadioButtonRed->isChecked())
    {
        PointsArea1->CurrentPoint = PointTypeRed;
    }
    else
    {
        PointsArea1->CurrentPoint = PointTypeBlue;
    }
}

void MainWindow::PushButtonClearClicked()
{
    PointsArea1->Clear();
}

void MainWindow::PushButtonDrawLineClicked()
{
	PointsArea1->DrawLine();
	TextEdit1->setPlainText(PointsArea1->log);
}

void MainWindow::CheckBox1StateChanged()
{
	PointsArea1->SetLines1Visible(CheckBox1->checkState() == Qt::Checked);
}
