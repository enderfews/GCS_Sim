#include "MainWindow.h"
//#include <spdlog/spdlog.h>

GCSMainWindow::GCSMainWindow(QWidget* Parent)
	: QWidget(Parent)
{
	setWindowTitle("Ground Control Station Window");

    //Window background. "QWidget" targets this window itself; "QLabel"
//sets a default text color for any label that does NOT have its own
//setStyleSheet (titleLabel, badges, cards and buttons already have
//their own, so they keep their colors - this only rescues "label",
//which never had one and would turn invisible (black-on-dark) otherwise.
    setStyleSheet(
        "QWidget { background-color: #1b1f27; border: 1px solid #2a2f3a; }"
        "QLabel { color: #e8eaed; }");

    //Title and subtitle, centered above everything else
    TitleLabel = new QLabel("GCS simulator", this);
    TitleLabel->setAlignment(Qt::AlignCenter);
    TitleLabel->setStyleSheet("font-size: 20px; font-weight: 600; color: #f5f5f5;");

    SubtitleLabel = new QLabel("Telemetry & command interface", this);
    SubtitleLabel->setAlignment(Qt::AlignCenter);
    SubtitleLabel->setStyleSheet("font-size: 13px; color: #9aa0a6;");

    resize(1200, 800);
}

void GCSMainWindow::closeEvent(QCloseEvent* CloseEvent)
{
    delete TitleLabel;
    delete SubtitleLabel;

    CloseEvent->accept();
}
