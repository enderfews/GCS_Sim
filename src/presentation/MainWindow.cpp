#include "MainWindow.h"
#include "Globals/WindowGlobals.h"
//#include <spdlog/spdlog.h>
#include <QNetworkDatagram>


GCSMainWindow::GCSMainWindow(QWidget* Parent)
	: QWidget(Parent)
{
	setWindowTitle(APP_WINDOW_TITLE);

    //Window background. "QWidget" targets this window itself; "QLabel"
//sets a default text color for any label that does NOT have its own
//setStyleSheet (titleLabel, badges, cards and buttons already have
//their own, so they keep their colors - this only rescues "label",
//which never had one and would turn invisible (black-on-dark) otherwise.
    setStyleSheet(APP_WINDOW_STYLESHEET);
    resize(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT);

    //Title and subtitle, centered above everything else
    TitleLabel = new QLabel(TITLE_LABEL_NAME, this);
    TitleLabel->setAlignment(Qt::AlignCenter);
    TitleLabel->setStyleSheet(TITLE_LABEL_STYLESHEET);

    SubtitleLabel = new QLabel(SUBTITLE_LABEL_NAME, this);
    SubtitleLabel->setAlignment(Qt::AlignCenter);
    SubtitleLabel->setStyleSheet(SUBTITLE_LABEL_STYLESHEET);
}

void GCSMainWindow::closeEvent(QCloseEvent* CloseEvent)
{
    delete TitleLabel;
    delete SubtitleLabel;

    CloseEvent->accept();
}
