#ifndef ALGORITHMVIEWMODEL_H
#define ALGORITHMVIEWMODEL_H

#include <QObject>
#include <QtTextToSpeech/QTextToSpeech>

class AfpsAlgorithmViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString result READ getResult WRITE setResult NOTIFY sig_resultChanged)

public:
    explicit AfpsAlgorithmViewModel(QObject *parent = nullptr);

    QString	getResult();
    void	setResult(QString result);

private:
    QString result; //算法结果

signals:
    void sig_resultChanged();

public slots:
    void slot_updateResult(QString result);
};

#endif // ALGORITHMVIEWMODEL_H
