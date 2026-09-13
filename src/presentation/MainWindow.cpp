#include "MainWindow.h"
#include "Globals/WindowGlobals.h"

#include <QVBoxLayout>
#include <QNetworkDatagram>// Include the QNetworkDatagram header for handling incoming UDP datagrams
#include <QHBoxLayout> //Allow to desing better IU 

#include "presentation/Telemetry/Qt/QtTelemetryPanel.h"
#include "presentation/Telemetry/Qt/QtGraphicTelemetryPanel.h"

#include "Infraestructure/Qt/QtUdpTelemetryInput.h"
#include "Infraestructure/Qt/QtUtf8TelemetryDecoder.h"
#include "Infraestructure/Qt/QtTcpTelemetryInput.h"
#include "Infraestructure/Qt/QtTcpTelemetryDecoder.h"

//For debugging and testing purposes
#define USE_GRAPHIC_PANEL 1

GCSMainWindow::GCSMainWindow(QWidget* Parent)
	: QWidget(Parent)
    , m_pTitleLabel(nullptr)
    , m_pSubtitleLabel(nullptr)
    , m_pTelemetryPanel(nullptr)
    , m_pGraphicTelemetryPanel(nullptr)
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
    m_pTitleLabel = new QLabel(TITLE_LABEL_NAME, this);
    m_pTitleLabel->setAlignment(Qt::AlignCenter);
    m_pTitleLabel->setStyleSheet(TITLE_LABEL_STYLESHEET);

    m_pSubtitleLabel = new QLabel(SUBTITLE_LABEL_NAME, this);
    m_pSubtitleLabel->setAlignment(Qt::AlignCenter);
    m_pSubtitleLabel->setStyleSheet(SUBTITLE_LABEL_STYLESHEET);
    //Create a vertical Layout and add the label and button to it
    QVBoxLayout* Layout = new QVBoxLayout(this);

    //Generate the link to the title and subtitle, added BEFORE the status label
    Layout->addWidget(m_pTitleLabel);
    Layout->addWidget(m_pSubtitleLabel);

#if USE_GRAPHIC_PANEL
    m_pGraphicTelemetryPanel = new QtGraphicTelemetryPanel(this);
    Layout->addWidget(m_pGraphicTelemetryPanel);
    Layout->addSpacing(16);
#else
    m_pTelemetryPanel = new QtUAVTelemetryPanel(this);
    Layout->addWidget(m_pTelemetryPanel);
    Layout->addSpacing(16);
#endif
}

void GCSMainWindow::StartUAVTelemetry()
{
    if (!m_pUAVTelemetryService)
    {
        m_pUAVTelemetryService = make_unique<TelemetryService>();

#if defined(USE_TCP) && USE_TCP //For testing purposes
        m_pUAVTelemetryService->InitializeTelemetryInput<QtTcpTelemetryInput>();
        m_pUAVTelemetryService->InitializeTelemetryDecoder<QtTcpTelemetryDecoder>();
#else
        m_pUAVTelemetryService->InitializeTelemetryInput<QtUdpTelemetryInput>();
        m_pUAVTelemetryService->InitializeTelemetryDecoder<QtUtf8TelemetryDecoder>();
#endif
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
    m_pTitleLabel->deleteLater();
    m_pTitleLabel = nullptr;

    m_pSubtitleLabel->deleteLater();
    m_pSubtitleLabel = nullptr;

#if USE_GRAPHIC_PANEL
    m_pGraphicTelemetryPanel->deleteLater();
    m_pGraphicTelemetryPanel = nullptr;
#else
    m_pTelemetryPanel->deleteLater();
    m_pTelemetryPanel = nullptr;
#endif

    CloseEvent->accept();
}

void GCSMainWindow::OnTelemetryReceived(const UAVState& State)
{
#if USE_GRAPHIC_PANEL
    m_pGraphicTelemetryPanel->SetUAVState(State);
#else
    m_pTelemetryPanel->SetUAVState(State);
#endif
}
