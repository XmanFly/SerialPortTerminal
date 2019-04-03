import QtQuick 2.4

AfpsAlgorithmForm {

    baselineWin {
        onEditingFinished : {
            AfpsAlgorithmViewModel.baselineWin = parseInt(baselineWin.text.toString())
        }
    }

    baselineThrold {
        onEditingFinished : {
            AfpsAlgorithmViewModel.baselineThrold = parseFloat(baselineThrold.text.toString())
        }
    }

    detectionTimeout {
        onEditingFinished : {
            AfpsAlgorithmViewModel.detectionTimeout = parseInt(detectionTimeout.text.toString())
        }
    }

    detectionThrold {
        onEditingFinished : {
            AfpsAlgorithmViewModel.detectionThrold = detectionThrold.text.toString()
        }
    }
}
