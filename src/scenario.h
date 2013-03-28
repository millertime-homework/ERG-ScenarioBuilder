#ifndef SCENARIO_H
#define SCENARIO_H

#include <QObject>
#include <QStringList>
class QLabel;

struct IntUndefInf
{
    IntUndefInf() : i(0), u(true), inf(false) {}
    int i;
    bool u;
    bool inf;
};

struct Prop
{
    QString identifier;
    QString name;
    QString imagePath;
    QString hoverImagePath;
    QString openImagePath;
    int width;
    int height;
    int top;
    int left;
    QString action;
    QStringList actionVariables;
};

struct Destination
{
    IntUndefInf x;
    IntUndefInf y;
    IntUndefInf z;
    QString f;
};

struct WallThumbnail
{
    QString identifier;
    QString name;
    QString imagePath;
    QStringList triggers;
    QList<Prop*> props;
    Destination *destination;
};

struct Room
{
    Room(const QString &n) : name(n), x(0), y(0) {}
    QString name;
    QString roomId;
    int x;
    int y;
    QString annotation;
    QStringList triggers;
    QList<WallThumbnail*> walls;
};

struct Floor
{
    Floor(const QString &n) : name(n), z(0) {}
    QString name;
    int z;
    QList<Room*> rooms;
};

struct ConversationReply
{
    QString message;
    int goToKey;
};

struct ConversationCheck
{
    QString key;
    QStringList keyArgs;
    int goToKey;
};

struct ConversationOption
{
    QString name;
    QString message;
    QList<ConversationReply*> replies;
    QStringList triggers;
    QList<ConversationCheck*> checks;
    ConversationCheck *requires;
};

struct Conversation
{
    Conversation(const QString &n) : name(n) {}
    QString name;
    QList<ConversationOption*> options;
};

struct Event
{
    QString name;
    QStringList arguments;
};

struct Trigger
{
    Trigger(const QString &n) : name(n), showCountdown(false), disabled(false) {}
    QString name;
    QList<Event*> events;
    IntUndefInf lives;
    QStringList startTriggers;
    QStringList enableTriggers;
    QStringList disableTriggers;
    QStringList deleteTriggers;
    IntUndefInf addPoints;
    IntUndefInf moveDelay;
    IntUndefInf timeDelay;
    bool showCountdown;
    bool disabled;
};

struct Annotation
{
    QString xyz;
    QString imagePath;
};

struct Scenario
{
    Scenario(const QString &n) : name(n), playerX(0), playerY(0), playerZ(0) {}
    QString name;
    QList<Floor*> floors;
    QList<Conversation*> conversations;
    QList<Trigger*> triggers;
    QStringList inactiveProps;
    int playerX;
    int playerY;
    int playerZ;
    QString playerFacing;
    QStringList playerInventory;
    QList<Annotation*> annotations;
};

#endif // SCENARIO_H
