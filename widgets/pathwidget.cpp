#include "pathwidget.h"
#include "ui_pathwidget.h"

PathWidget::PathWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PathWidget)
{
    ui->setupUi(this);
}

PathWidget::~PathWidget()
{
    delete ui;
}

void PathWidget::on_chose_action_triggered()
{
    setPath( initFileDialog() );
}

QStringList PathWidget::localPathes() const
{
    return localPathes_;
}

void PathWidget::setLocalPathes(const QStringList &localPathes)
{
    localPathes_ = localPathes;
}

QString PathWidget::path() const
{
    return path_;
}

void PathWidget::setPath(const QString &path)
{
    path_ = path;
    ui->path_le->setText(path);
    emit pathChanged(path);
    if(dialogType() == PathType::Folder)
        createLocalPathesList(path);
}

void PathWidget::setPlaceholder(const PathType &pt)
{
    QString ph = "";
    switch (pt)
    {
        case PathType::CSV:
        {
            ph = CSV_PLACEHOLDER;
        }
        break;
        case PathType::Image:
        {
            ph = IMG_PLACEHOLDER;
        }
        break;
        case PathType::Folder:
        {
            ph = FOLDER_PLACEHOLDER;
        }
            break;
        default:
        {
            ph = OTHER_PLACEHOLDER;
        }
            break;
    }
    ui->path_le->setPlaceholderText(ph);
}

PathType PathWidget::dialogType() const
{
    return dialogType_;
}

void PathWidget::setDialogType(const PathType &pathType)
{
    dialogType_ = pathType;
    setPlaceholder(pathType);
}

QString PathWidget::dialogHeader(const PathType &pt)
{
    QString header = "";
    switch (pt)
    {
        case PathType::CSV:
        {
            header = CSV_MSG_HEADER;
        }
        break;
        case PathType::Image:
        {
            header = IMG_MSG_HEADER;
        }
        break;
        case PathType::Folder:
        {
            header = FOLDER_MSG_HEADER;
        }
            break;
        default:
        {
            header = OTHER_MSG_HEADER;
        }
            break;
    }
    return header;
}

QStandardPaths::StandardLocation PathWidget::initLocation(const PathType &pt)
{
    QStandardPaths::StandardLocation loc = QStandardPaths::DesktopLocation;
    switch (pt)
    {
        case PathType::CSV:
        {
            loc = CSV_LOCATION;
        }
        break;
        case PathType::Image:
        {
            loc = IMG_LOCATION;
        }
        break;
        case PathType::Folder:
        {
            loc = FOLDER_LOCATION;
        }
        break;
        default:
        {
            loc = OTHER_LOCATION;
        }
        break;
    }
    return loc;
}

QString PathWidget::filesFilterString(const PathType &pt)
{
    QString filter = QString();
    switch (pt)
    {
        case PathType::CSV:
        {
            filter = "Текстовый документ (*.txt *.asc *,v)" + FILTER_SEP + "Документ CSV (*.csv)";
        }
        break;
        case PathType::Image:
        {
            filter = "Изображение Windows BMP (*.bmp *.dib)" + FILTER_SEP
                    + "Изображение GIF (*.gif)" + FILTER_SEP
                    + "Изображение JPEG (*.jpeg *.jpg *.jpe)" + FILTER_SEP
                    + "Изображение PNG (*.png)" + FILTER_SEP
                    + "Cжатое изображение SVG (*.svgz)" + FILTER_SEP
                    + "Изображение WebP (*.webp)";
        }
        break;
        default:
        {
            filter = OTHER_FILTER;
        }
        break;
    }
    return filter;
}

QString PathWidget::defaultFileSuffix(const PathType &pt)
{
    QString suf = "";
    switch (pt)
    {
    case PathType::CSV:
    {
        suf = CSV_SUFFIX;
    }
        break;
    case PathType::Image:
    {
        suf = IMG_SUFFIX;
    }
        break;
    default:
    {
        suf = "";
    }
        break;
    }
    return suf;
}

QString PathWidget::defaultFilter(const PathType &pt)
{
    QString filter = "";
    switch (pt)
    {
    case PathType::CSV:
    {
        filter = CSV_FILTER;
    }
        break;
    case PathType::Image:
    {
        filter = IMG_FILTER_BMP;
    }
        break;
    default:
    {
        filter = OTHER_FILTER;
    }
        break;
    }
    return filter;
}

QString PathWidget::initFileDialog()
{
    QString selectedPath = "";
    PathType dt = dialogType();
    QString openedPath = requiredPath(DATA_PATH, initLocation(dt));
    QString tittle = dialogHeader(dt);

    if(dt == PathType::Folder)
    {
        selectedPath = QFileDialog::getExistingDirectory(this, tittle, openedPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }
    else
    {
        QString filterStr =  filesFilterString(dt);
        QString selectedFilter = defaultFilter(dt);

        selectedPath = QFileDialog::getOpenFileName( this , tittle, openedPath, filterStr, &selectedFilter );
    }

    return selectedPath;
}

void PathWidget::createLocalPathesList(QString basePath)
{
    QStringList localPths = QStringList();
    QDir rootDir(basePath);
    if(rootDir.exists())
    {

    }
    else
    {

    }
}

QString PathWidget::requiredPath(const QString &redirect, const QStandardPaths::StandardLocation &loc, QDir currentDir)
{
    QString path = "";
    QString defaultPath = QStandardPaths::writableLocation(loc);
    if(currentDir.exists())
    {
    #ifdef Q_OS_MAC
        currentDir.cdUp();
        currentDir.cdUp();
        currentDir.cdUp();
    #endif

        currentDir.cdUp();
        QString newPath = QDir::toNativeSeparators(currentDir.absolutePath() + "/" + redirect);
        if(QDir(newPath).exists())
        {
           currentDir.cd(redirect);
        }
        else {
            messageDirNotExists(newPath, defaultPath);
            currentDir = QDir(defaultPath);
        }
    }
    else
    {
        messageDirNotExists(currentDir.path(), defaultPath);
        currentDir = QDir(defaultPath);
    }
    path = currentDir.absolutePath();
    return path;
}

void PathWidget::messageDirNotExists(QString tryingDir, QString newDir)
{
    QMessageBox::information(nullptr, QGuiApplication::applicationDisplayName(),
                             tr("Cannot open %1, the directory doesn't exist. Opened %2.")
                             .arg( tryingDir, newDir ));
}
