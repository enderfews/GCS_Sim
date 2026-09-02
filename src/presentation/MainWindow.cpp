#include "MainWindow.h"
#include "Globals/WindowGlobals.h"

#include <QVBoxLayout>
#include <QNetworkDatagram>// Include the QNetworkDatagram header for handling incoming UDP datagrams
#include <QHBoxLayout> //Allow to desing better IU 
#include "presentation/Telemetry/Qt/QtTelemetryPanel.h"


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

    //Create a vertical Layout and add the label and button to it
    QVBoxLayout* Layout = new QVBoxLayout(this);

    //Generate the link to the title and subtitle, added BEFORE the status label
    Layout->addWidget(this->TitleLabel);
    Layout->addWidget(this->SubtitleLabel);

    //Telemetry cards row: the three labels side by side, equal width

    //Banners: full width, only one (or none) visible at a time
    TelemetryPanel = new QtUAVTelemetryPanel(this);
    Layout->addWidget(TelemetryPanel);
    Layout->addSpacing(16);
}

void GCSMainWindow::StartUAVTelemetry()
{
    if (!m_pUAVTelemetryService)
    {
        m_pUAVTelemetryService = make_unique<TelemetryService>();
        m_pUAVTelemetryService->InitializeTelemetryInput<QtUdpTelemetryInput>();
        m_pUAVTelemetryService->InitializeTelemetryDecoder<QtUtf8TelemetryDecoder>();
    }
    m_pUAVTelemetryService->SetTelemetryServiceCallback([this](UAVState& State)
        {
            OnTelemetryReceived(State);
        });

    m_pUAVTelemetryService->Start();
}

void GCSMainWindow::StopUAVTelemetry()
{
    if (!m_pUAVTelemetryService)
    {
        return;
    }
    m_pUAVTelemetryService->Stop();
}

void GCSMainWindow::closeEvent(QCloseEvent* CloseEvent)
{
    delete TitleLabel;
    delete SubtitleLabel;

    CloseEvent->accept();
}

void GCSMainWindow::OnTelemetryReceived(const UAVState& State)
{
    TelemetryPanel->SetUAVState(State);
}
