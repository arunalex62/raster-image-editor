#include "fileIO.hpp"
#include "statusBar.hpp"
#include <qfiledialog.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <qmessagebox.h>
#include <qimage.h>

QString FileIO::open(MainWindow *mainWindow) {
    // Gets the current directory information.
    QDir dir;
    // Taken from QFileDialog Qt Class Reference Page:
    // https://doc.qt.io/archives/3.3/qfiledialog.html
    QString fileName = QFileDialog::getOpenFileName(
                    dir.absPath(),
                    "Images (*.png *.jpg *.jpeg *.bmp *.ppm)",
                    mainWindow,
                    "open file dialog",
                    "Choose a file" );

    if (fileName != "") {
        // If a file was chosen, store it into QImage to 
        // find its dimensions.
        QImage image(fileName);

        // Case where the file could not be read properly, or is null.
        if(image.isNull()) {
            QMessageBox::warning(mainWindow, "Raster Editor",
             "There was an error opening the image. Perhaps the file is corrupted.");
             return "";
        }
        // Handle the dimension sizes of the loaded image files.
        // The limit on the images dimensions for this program is 2000 pixels
        // in each dimension for the sake of performance.
        if(image.width() > 2000 || image.width() < 1) {
            QMessageBox::warning(mainWindow, "Raster Editor",
             "Please ensure the image width is between 1 and 2000 pixels.");
             return "";
        }
        if(image.height() > 2000 || image.height() < 1) {
            QMessageBox::warning(mainWindow, "Raster Editor",
             "Please ensure the image height is between 1 and 2000 pixels.");
             return "";
        }
        // At this point, the image is "safe" to load into the viewer.
        if(mainWindow->imageView->buffer.load(fileName)) {
            // Getting the file name to display in the status bar.
            QFileInfo fileInfo(fileName);
            fileName = fileInfo.fileName();
            // Setting the central display of the main window
            // as the image just loaded in.
            mainWindow->setCentralWidget(mainWindow->imageView);
            mainWindow->imageView->repaint();
            // Update status bar with width/height of new image.
            StatusBar::setStatusBarDimensions(mainWindow);
            // Redraw grid-lines (if setting is enabled).
            mainWindow->imageView->gridDrawHelper();
            QMessageBox::information(mainWindow, "Raster Editor", "Image successfully opened.");
        } else {
            QMessageBox::warning(mainWindow, "Raster Editor",
             "There was an error opening the image. Perhaps the file is corrupted.");
             return "";
        }
    }
    return fileName;
}

QString FileIO::saveAs(MainWindow *mainWindow) {
    // Get current working directory to use as default directory for file export dialog.
    QDir dir;
    // Used this post to figure how to save a QImage file
    // Using a dialog box to select output format:
    // https://stackoverflow.com/questions/47469200/form-of-saving-an-image-in-qt
    QString outputName = QFileDialog::getSaveFileName(
        dir.absPath(),
        "Images (*.png *.jpeg *.jpg *.bmp *.ppm)",
        mainWindow,
        "Export File Dialog"
        "Choose a file name (append the appropriate extension at the end of the file name)"
    );
    // Handles if the user exits/cancels out of the dialog.
    if(outputName == "") {
        return "";
    }
    // Verifying if a valid extension was provided.
    QFileInfo fileInfo(outputName);
    QString extension = fileInfo.extension().lower();
    if(extension == "jpg") {
        extension = "jpeg";
    }
    if(extension != "png" && extension != "jpeg" && extension != "bmp" && extension != "ppm") {
        QMessageBox::warning(mainWindow, "Raster Editor",
        "Please specify a valid image format. Supported image formats are .png, .jpg, .jpeg, .bmp, and .ppm.");
        return "";
    }

    // Saving file to the location specified if extension is valid.
    bool imageSaved = mainWindow->imageView->buffer.save(outputName, extension.upper());
    // Display status messages depending on if file was saved successfully.
    if(imageSaved) {
        QMessageBox::information(mainWindow, "Raster Editor", "Image saved successfully to: " + outputName);
        return fileInfo.fileName();
    } else {
        QMessageBox::warning(mainWindow, "Raster Editor",
            "There was an error saving the image. Perhaps the directory is not writable.");
            return "";
    }
}