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
    Q_PROPERTY(int detectionTimeout READ getDetectionTimeout WRITE setDetectionTimeout NOTIFY sig_detectionTimeout)
    Q_PROPERTY(double detectionThrold READ getDetectionThrold WRITE setDetectionThrold NOTIFY sig_detectionThrold)

public:
    explicit AfpsAlgorithmViewModel(QObject *parent = nullptr);

    void	setRespository(AlgorithmRespository *respository);
    QString	getResult();
    void	setResult(QString result);
    int	getBaselineWin();
    void	setBaselineWin(int baselineWin);
    double getBaselineThrold();
    void	setBaselineThrold(double baselineThrold);
    int	getDetectionTimeout();
    void	setDetectionTimeout(int detectionTimeout);
    double	getDetectionThrold();
    void	setDetectionThrold(double detectionThrold);

private:
    int baselineWin; //基线窗口
    double baselineThrold; //基线稳定阈值
    int detectionTimeout; //检测期 超时点数
    double detectionThrold; //检测期 判定比例
//    QString state; //状态
    QString result; //算法结果
//    double baselineStandard; //基线 基准值
//    double diff; //下降差值
//    double fallRatio; //下降比例
    AlgorithmRespository *respository;

    void loadPara();

signals:
    void sig_resultChanged();
    void sig_baselineWin();
    void sig_baselineThrold();
    void sig_detectionTimeout();
    void sig_detectionThrold();

public slots:
    void slot_updateResult(QString result);
    void slot_updateBaselineWin(int baselineWin);
    void slot_updateBaseThrold(int baselineThrold);
};

#endif // ALGORITHMVIEWMODEL_H
