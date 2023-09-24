import QtQuick

QtObject {
    enum DeviceType {
        BarcodeScanner,
        RoboticArm,
        PLC,
        IOTransfer
    }

    enum LineNo {
        Unknow,
        W1,
        W2,
        W3,
        N3,
        N2,
        N1
    }
}
