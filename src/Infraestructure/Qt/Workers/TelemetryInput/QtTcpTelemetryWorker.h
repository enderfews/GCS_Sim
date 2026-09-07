
#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>

#include <cstdint>

/*
    @brief Worker that handles TCP telemetry reception inside a dedicated thread.
*/
class QtTcpTelemetryWorker
    : public QObject
{
    Q_OBJECT

public:
    QtTcpTelemetryWorker(QHostAddress::SpecialAddress InAddress, uint16_t InPort);

public slots:
    //Slots called by thread signal when we start/stop the thread
    void Start();
    void Stop();

signals:
    
    void TelemetryReceived(const QByteArray& Data);
    //Signal called inside Start()
    void Started();
    //Signal called inside Stop()
    void Stopped();
    //Send error messages from the thread to the main thread to print it to the GCSLog
    void Error(const QString& Message);

private slots:
    // Slot function to handle TCP server signal.
    void OnNewConnection();

    // Slot functions to handle TCP socket signals.
    void OnReadyRead();
    void OnDisconnected();
    void OnTcpError(QAbstractSocket::SocketError SocketError);

private:
    void ProcessBuffer();
private:


    QTcpServer* m_pServer = nullptr;
    QTcpSocket* m_pClientTcpSocket = nullptr;

    QByteArray m_CachedBuffer;

    uint16_t m_uPort;
    QHostAddress::SpecialAddress m_eAddress;

    static constexpr int HeaderSize = 4;
};
