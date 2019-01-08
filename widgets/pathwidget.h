#ifndef PATHWIDGET_H
#define PATHWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QGuiApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QImageReader>

//TODO : доработать для сохранения
#ifndef DATA_PATH
    #define DATA_PATH "TestImages/Set1"
#endif //DATA_PATH

#ifndef LINEEDIT_PLACEHOLDER
#define LINEEDIT_PLACEHOLDER
    #define IMG_PLACEHOLDER "Выберите изображение..."
    #define CSV_PLACEHOLDER "Выберите файл данных..."
    #define OTHER_PLACEHOLDER "Выберите файл..."
    #define FOLDER_PLACEHOLDER "Выберите папку..."
#endif

#ifndef MSG_HEADERS
#define MSG_HEADERS
    #define IMG_MSG_HEADER "Выберите изображение"
    #define CSV_MSG_HEADER "Выберите CSV файл"
    #define FOLDER_MSG_HEADER "Выберите папку"
    #define OTHER_MSG_HEADER "Выберите файл"
#endif

#ifndef FILE_SUFFIX
#define FILE_SUFFIX
    #define IMG_SUFFIX "png"
    #define CSV_SUFFIX "csv"
#endif

#ifndef DIALOG_FILTER
#define DIALOG_FILTER
    #define FILTER_SEP QString(";;")
    #define CSV_MIME_CSV "text/csv"
    #define CSV_MIME_TXT "text/plain"
    #define IMG_FILTER_PNG "PNG image (*.png)"
    #define IMG_FILTER_BMP "Изображение Windows BMP (*.bmp *.dib)"
    #define CSV_FILTER "Документ CSV (*.csv)"
    #define OTHER_FILTER "All files (*)"
#endif

#ifndef STANDARD_LOCATIONS
#define STANDARD_LOCATIONS
    #define IMG_LOCATION QStandardPaths::PicturesLocation
    #define CSV_LOCATION QStandardPaths::DocumentsLocation
    #define FOLDER_LOCATION QStandardPaths::HomeLocation
    #define OTHER_LOCATION QStandardPaths::DesktopLocation
#endif

namespace Ui {
class PathWidget;
}

enum class PathType
{
    Image,
    CSV,
    Folder,
    Other
};

class PathWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PathWidget(QWidget *parent = nullptr);
    ~PathWidget();

    PathType dialogType() const;
    QString path() const;
    QString initFileDialog();
    QStringList localPathes() const;

    void setPlaceholder(const PathType &pt);
    void setDialogType(const PathType &dialogType);
    void setPath(const QString &path);
    void setLocalPathes(const QStringList &localPathes);

signals:
    void pathChanged(QString path);
    void localPathesChanged(QStringList localPathes);
    void imgCountChanged(int imgCount);

private slots:
    void on_chose_action_triggered();

private:
    //varibles
    Ui::PathWidget *ui;
    PathType dialogType_;
    QString path_;
    QStringList localPathes_;

    //methods
    //  static
    static QString dialogHeader(const PathType &pt);
    static QStandardPaths::StandardLocation initLocation(const PathType &pt);
    static QString filesFilterString(const PathType &pt);
    static QString defaultFileSuffix(const PathType &pt);
    static QString defaultFilter(const PathType &pt);
    static void messageDirNotExists( QString tryingDir,
                                     QString newDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) );

    //  non-static
    QString requiredPath(const QString &redirect = "",
                         const QStandardPaths::StandardLocation &loc = QStandardPaths::HomeLocation,
                         QDir currentDir = QDir::current());
    void createLocalPathesList(QString basePath);
};

#endif // PATHWIDGET_H
