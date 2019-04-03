#ifndef ALGORITHMVIEWMODEL_H
#define ALGORITHMVIEWMODEL_H

#include <QObject>
#include <QtTextToSpeech/QTextToSpeech>
#include "baseline.h"
#include "detection.h"
#include "algorithmrespository.h"

class AfpsAlgorithmViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString result READ getResult WRITE setResult NOTIFY sig_resultChanged)
    Q_PROPERTY(int baselineWin READ getBaselineWin WRITE setBaselineWin NOTIFY sig_baselineWin)
    Q_PROPERTY(double baselineThrold READ getBaselineThrold WRITE setBaselineThrold NOTIFY sig_baselineThrold)

public:
    explicit AfpsAlgorithmViewModel(QObject *parent = nullptr);

    void	setRespository(AlgorithmRespository *respository);
    QString	getResult();
    void	setResult(QString result);
    int	getBaselineWin();
    void	setBaselineWin(int baselineWin);
    double getBaselineThrold();
    void	setBaselineThrold(double baselineThrold);

private:
    QString result; //算法结果
    int baselineWin; //基线窗口
    double baselineThrold; //基线稳定阈值
    AlgorithmRespository *respository;

    void loadPara();

signals:
    void sig_resultChanged();
    void sig_baselineWin();
    void sig_baselineThrold();

public slots:
    void slot_updateResult(QString result);
    void slot_updateBaselineWin(int baselineWin);
    void slot_updateBaseThrold(int baselineThrold);
};

#endif // ALGORITHMVIEWMODEL_H
