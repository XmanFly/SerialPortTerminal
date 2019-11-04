#ifndef ALGORITHMVIEWMODEL_H
#define ALGORITHMVIEWMODEL_H

#include <QObject>
#include <QtTextToSpeech/QTextToSpeech>
#include "baseline.h"
#include "detection.h"
#include "algorithmrespository.h"
#include "algorithm.h"

class AfpsAlgorithmViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString result READ getResult WRITE setResult NOTIFY sig_resultChanged)
    Q_PROPERTY(int baselineWin READ getBaselineWin WRITE setBaselineWin NOTIFY sig_baselineWin)
    Q_PROPERTY(double baselineThrold READ getBaselineThrold WRITE setBaselineThrold NOTIFY sig_baselineThrold)
    Q_PROPERTY(double baselineStandard READ getBaselineStandard WRITE setBaselineStandard NOTIFY sig_baselineStandard)
    Q_PROPERTY(int detectionTimeout READ getDetectionTimeout WRITE setDetectionTimeout NOTIFY sig_detectionTimeout)
    Q_PROPERTY(double detectionThrold READ getDetectionThrold WRITE setDetectionThrold NOTIFY sig_detectionThrold)
    Q_PROPERTY(double detectionDiff READ getDetectionDiff WRITE setDetectionDiff NOTIFY sig_detectionDiff)
    Q_PROPERTY(double detectionFallRate READ getDetectionFallRate WRITE setDetectionFallRate NOTIFY sig_detectionFallRate)
    Q_PROPERTY(QString state READ getState WRITE setState NOTIFY sig_state)
    Q_PROPERTY(Algorithm::STATE stateEnum READ getStateEnum WRITE setStateEnum NOTIFY sig_stateEnumChanged)

public:
    explicit AfpsAlgorithmViewModel(QObject *parent = nullptr);

    void	setRespository(AlgorithmRespository *respository);
    QString	getResult();
    void	setResult(QString result);
    int	getBaselineWin();
    void	setBaselineWin(int baselineWin);
    double getBaselineThrold();
    void	setBaselineThrold(double baselineThrold);
    double getBaselineStandard();
    void	setBaselineStandard(double baselineStandard);
    int	getDetectionTimeout();
    void	setDetectionTimeout(int detectionTimeout);
    double	getDetectionThrold();
    void	setDetectionThrold(double detectionThrold);
    double	getDetectionDiff();
    void	setDetectionDiff(double detectionDiff);
    double	getDetectionFallRate();
    void	setDetectionFallRate(double detectionFallRate);
    QString	getState();
    void	setState(QString state);
    Algorithm::STATE getStateEnum() const;
    void setStateEnum(const Algorithm::STATE &value);

private:
    int baselineWin; //基线窗口
    double baselineThrold; //基线稳定阈值
    int detectionTimeout; //检测期 超时点数
    double detectionThrold; //检测期 判定比例
    QString state; //状态
    Algorithm::STATE stateEnum; //状态 枚举型
    QString result; //算法结果
    double baselineStandard; //基线 基准值
    double detectionDiff; //下降差值
    double fallRate; //下降比例
    AlgorithmRespository *respository;

    void loadPara();

signals:
    void sig_resultChanged();
    void sig_baselineWin();
    void sig_baselineThrold();
    void sig_detectionTimeout();
    void sig_detectionThrold();
    void sig_baselineStandard();
    void sig_detectionDiff();
    void sig_detectionFallRate();
    void sig_state();
    void sig_stateEnumChanged(Algorithm::STATE state);

public slots:
    void slot_updateResult(QString result);
    void slot_updateBaselineWin(int baselineWin);
    void slot_updateBaseThrold(int baselineThrold);
    void slot_updateStandard();
    void slot_updateDetectionDiff();
    void slot_updateDetectionFallRate();
    void slot_updateState(QString state);
    void slot_updateStateEnum(Algorithm::STATE state);
};

#endif // ALGORITHMVIEWMODEL_H
