#ifndef IMAGE_H
#define IMAGE_H

#include <QLabel>
#include <QProgressBar>
#include <QPixmap>
#include <QImage>
#include <QRgb>
#include <QFile>
#include <QFileDialog>
#include <QScrollArea>
#include <QScrollBar>
#include <string>
#include <iostream>
#include <QMessageBox>
//---
#include "Types.h"
#include "SignalProcessor.h"

using namespace std;

class Image {
public:
    /* --- constructors / destructors --- */
    Image() {};
    Image(QLabel* label_, QProgressBar* progressBar_)
        : label(label_), progressBar(progressBar_) { };

    /* --- getter / setter --- */
    void setPath(const string& path_ ) {path = path_;};
    const string& getPath() {return path;};

    /* --- load / save --- */
    QSize loadImage(QWidget &widget_, const string& path_); // without file-open-dialog
    QSize loadImage(QWidget& widget_);    // with    file-open-dialog
    QSize loadImage(const Image& image_);    // copy from image
    bool saveImage(const string& path_);  // without file-save-dialog
    bool saveImage();                     // with    file-save-dialog

    /* --- converting / grayScale / Formats --- */
    QImage convertToGrayScale(const QImage& image_);

    /* --- scaling / zooming / stretching --- */
    void stretchImageToLabel(bool stretchImageToLabel_);
    void scaleImage(double factor_);
    void swap(Image& image_);

    /* --- modify image --- */
    void modifyRGB(signedRGBDelta delta_);
    void setAndReScalePixMapAfterModification(const QImage& image_);
    void smooth();

    /* --- analyze image --- */
    QColor getMinMax(bool min_);
    QColor getAverage();
    QColor getStandardDeviation();
    QColor getMaxRGB();
    void todo();

private:
    QImage image;
    string path;
    QLabel* label;
    QProgressBar* progressBar;
    void setProgressBar(unsigned int percentage_);
    // Converting QImage <---> SignalProcessor
    void qImageToSignalProcessors(QImage imageToLoadFrom_);
    void signalProcessorsToQImage(QImage& imageToWriteTo_);
    // SignalProcessors
    SignalProcessor grayScaleSignal;
};

#endif // IMAGE_H
