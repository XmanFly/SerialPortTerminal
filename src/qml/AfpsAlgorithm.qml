import QtQuick 2.4

AfpsAlgorithmForm {

    baselineWin {
        onEditingFinished : {
            AfpsAlgorithmViewModel.baselineWin = parseFloat(baselineWin.text.toString())
        }
    }

    baselineThrold {
        onEditingFinished : {
            AfpsAlgorithmViewModel.baselineThrold = parseFloat(baselineThrold.text.toString())
        }
    }
}
