#include "fileIO.hpp"

QString FileIO::open(MainWindow *mainWindow) {
    // Taken from QFileDialog Qt Class Reference Page:
    // https://doc.qt.io/archives/3.3/qfiledialog.html
    QString fileName = QFileDialog::getOpenFileName(
                    "/home",
                    "Images (*.png *.jpg)",
                    mainWindow,
                    "open file dialog",
                    "Choose a file" );

    // If a file was chosen, then load that file into the imageStorage array
    // and display it to the user through a Pixmap.
    if (fileName != "") {
        if(mainWindow->imageStorage.load(fileName)) {
            QPixmap pm(mainWindow->imageStorage);
            mainWindow->imageDisplay->setPixmap(pm);
            mainWindow->imageDisplay->show();
            mainWindow->setCentralWidget(mainWindow->imageDisplay);
            mainWindow->imageWidth = mainWindow->imageStorage.width();
            mainWindow->imageHeight = mainWindow->imageStorage.height();
            // Update status bar with width/height of new image.
            StatusBar::setStatusBar(mainWindow);
        }
    }
    return fileName;
}

void FileIO::saveAs(MainWindow *mainWindow) {
    // Get current working directory to use as default directory for file export dialog.
    QDir dir;
    // Used this post to figure how to save a QImage file
    // Using a dialog box to select output format:
    // https://stackoverflow.com/questions/47469200/form-of-saving-an-image-in-qt
    QString outputName = QFileDialog::getSaveFileName(
        dir.absPath(),
        "Images (*.png *.jpeg *.jpg *.bmp)",
        mainWindow,
        "Export File Dialog"
        "Choose a file name (append the appropriate extension at the end of the file name)"
    );
    if(outputName == "") {
        return;
    }
    // Verifying if a valid extension was provided.
    QFileInfo fileInfo(outputName);
    QString extension = fileInfo.extension().lower();
    if(extension == "jpg") {
        extension = "jpeg";
    }
    if(extension != "png" || extension != "jpeg" || extension != "bmp" || extension != "ppm") {
        QMessageBox::warning(mainWindow, "Raster Editor",
        "Please choose a valid image format. Supported image formats are .png, .jpg, .jpeg, .bmp, and .ppm.");
        return;
    }

    // Saving file to the location specified if extension is valid.
    if (outputName != "") {
        bool imageSaved = mainWindow->imageStorage.save(outputName, extension.upper());
        // Display status messages depending on if file was saved successfully.
        if(imageSaved) {
            QMessageBox::information(mainWindow, "Raster Editor", "Image saved successfully to: " + outputName);
        } else {
            QMessageBox::warning(mainWindow, "Raster Editor",
             "There was an error saving the image.Perhaps the directory is not writable");
             return;
        }
    }
}