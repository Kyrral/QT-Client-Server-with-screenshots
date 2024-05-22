#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include <QStringList>
#include <QAtomicInt>
#include <QMutex>
#include <QImage>
#include <QPixmap>
#include <QDir>

class ClientSocket : public QTcpSocket
{
    Q_OBJECT
private:
    static QAtomicInt counter;
    QMutex mtx;

    int ID;
    QByteArray data;
    QString filename;

    QStringList fileList = {    };

    void checkFile();
    void saveScreenshot();

public:
    QPixmap* pixmap;

    explicit ClientSocket(QObject *parent = nullptr);
    ClientSocket(const ClientSocket &other);

    void processList();
    void processFile();

    QStringList getFileList() const;
    int getId () const;

    void setFileList(QStringList newList);

public slots:
    void receiveData();
    void sendData(const QString& filename);

signals:
    void sendAware(const QString& filename);

    void receivedFile();
    void receivedList();

    void fileListUpdated();
    void saved(QPixmap pixmap);
};

#endif // CLIENTSOCKET_H
