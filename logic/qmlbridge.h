#ifndef QMLBRIDGE_H
#define QMLBRIDGE_H

#include <QObject>
#include <QImage>
#include <QTemporaryDir>
#include <QVariant>

#include "block.h"

namespace Tanks {

class Game;
class Tank;

class QMLBridge : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mapImageFilename MEMBER _lowerFilename NOTIFY mapRendered)
    Q_PROPERTY(QString bushImageFilename MEMBER _bushFilename NOTIFY mapRendered)
    Q_PROPERTY(QSize boardImageSize READ boardImageSize NOTIFY mapRendered)
    //Q_PROPERTY(QString boardHeight READ boardHeight)
public:
    explicit QMLBridge(QObject *parent = 0);
    QSize boardImageSize() const;

private:
    QVariant tank2variant(Tank *tank);

signals:
    void mapRendered();
    void newTank(QVariant tank);
    void newBullet(QVariant bullet);
    void tankUpdated(QVariant tank);
    void blockRemoved(QRect block);
    void bulletMoved(QString id, QPoint pos);
    void bulletRemoved(QString id);

    void qmlTankAction(int player, int key);
    void qmlTankActionStop(int player, int key);

public slots:

private slots:
    void humanTankAction(int player, int key);
    void humanTankActionStop(int player, int key);

    void mapLoaded();

    void newTankAvailable(QObject *obj);
    void newBulletAvailable(QObject *obj);
    void moveTank(QObject *obj);
    void removeBlock(const QRect &r);
    void moveBullet(QObject *obj);
    void removeBullet(QObject *obj);
private:
    QTemporaryDir _tmpDir;
    Game *_game;
    QString _lowerFilename;
    QString _bushFilename;
    int _qmlId;
    //QHash<QString, QWeakPointer<Block>> _activeBlocks;
};

} // namespace Tanks

#endif // QMLBRIDGE_H