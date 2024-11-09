#include "mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "ui_mainwindow.h"
#include "QImageReader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initStylesheet();
    //
    // Crear una sola instancia de QNetworkAccessManager en el constructor
    networkManager = new QNetworkAccessManager(this);

    QUrl ApiUrlPersonajes("https://dragonball-api.com/api/characters?page=1&limit=100");
    QUrl ApiUrlPlanetas("https://dragonball-api.com/api/planets?limit=100");
    inicializacion(ApiUrlPersonajes,ApiUrlPlanetas);

    ui->textEdit_setdescripcion->setReadOnly(true);
    ui->textEdit_planeta_descripcion->setReadOnly(true);
    ui->textEdit_setdescripcion->setAlignment(Qt::AlignJustify);
    ui->textEdit_planeta_descripcion->setAlignment(Qt::AlignJustify);
    setWindowIcon(QIcon(":/resource/icono/icon.png"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initStylesheet() {

    // You have to create the css file first in the main project directory
    // Get the css file
    QFile style(":/resource/style/style.css");
    bool ok = style.open(QFile::ReadOnly);
    qDebug()<<ok;
    if(ok)
    {
        QString s = QString::fromLatin1(style.readAll());
        setStyleSheet(s);
    }
}


void MainWindow::inicializacion(QUrl URLPersonajes, QUrl URLPlanetas)
{
    QJsonObject ObjectPersonajes = API.getJsonObject(URLPersonajes);
    QJsonObject ObjectPlanetas = API.getJsonObject(URLPlanetas);
    QJsonArray itemsArray;
    QJsonObject personaje;
    QJsonObject planeta;
    if (ObjectPersonajes.contains("items")) {
        itemsArray = ObjectPersonajes["items"].toArray();
        // Iterar sobre cada personaje en el array
        for (const QJsonValue &characterValue : itemsArray) {
            personaje = characterValue.toObject();
            int id = personaje["id"].toInt();
            QString name = personaje["name"].toString();
            // Agregar el id y el nombre a la lista
            ListaPersonajes.append(qMakePair(id, name));
        }
    } else {
        ui->statusbar->clearMessage();
        ui->statusbar->showMessage("No se encontraron personajes en la respuesta.");
        qWarning() << "No se encontraron personajes en la respuesta.";
    }
    for (const QPair<int, QString> &Personaje : ListaPersonajes) {
        ui->comboBox_personajes->addItem(Personaje.second, Personaje.first);
    }

    if (ObjectPlanetas.contains("items")) {
        itemsArray = ObjectPlanetas["items"].toArray();
        // Iterar sobre cada personaje en el array
        for (const QJsonValue &characterValue : itemsArray)
        {
            planeta = characterValue.toObject();
            int id = planeta["id"].toInt();
            QString name = planeta["name"].toString();
            // Agregar el id y el nombre a la lista
            ListaPlanetas.append(qMakePair(id, name));
        }
    } else {
        ui->statusbar->clearMessage();
        ui->statusbar->showMessage("No se encontraron personajes en la respuesta.");
        qWarning() << "No se encontraron personajes en la respuesta.";
    }
    for (const QPair<int, QString> &Planeta : ListaPlanetas) {
        ui->comboBox_planeta->addItem(Planeta.second, Planeta.first);
    }

}


void MainWindow::on_pushButton_clicked()
{
    int id;
    QString URL;
    for (const QPair<int, QString>& par : ListaPersonajes)   if (par.second == ui->comboBox_personajes->currentText()) id= par.first;

    URL="https://dragonball-api.com/api/characters/"+QString::number(id);

    qDebug() << "URL: "<< URL;
    BuscarPersonaje (QUrl (URL));
}

void MainWindow::on_pushButton_planeta_clicked()
{
    int id;
    QString URL;
    for (const QPair<int, QString>& par : ListaPlanetas)  if (par.second == ui->comboBox_planeta->currentText()) id= par.first;
    URL="https://dragonball-api.com/api/planets/"+QString::number(id);
    clearPersonajesPlaneta();
    BuscarPlaneta (QUrl (URL));
}
void MainWindow::BuscarPersonaje(QUrl URL)
{
    // Realizar la solicitud GET y obtener la respuesta como un objeto JSON
    QJsonObject Personaje = API.getJsonObject(URL);
    // Realizar la solicitud GET y obtener la respuesta como un objeto JSON
    ui->label_image->clear();
    clearTrasnformacionPersonajeCard();
    if (!Personaje.isEmpty()) GenerarCardPersonaje( Personaje);
    else
        {
         qWarning() << "No se pudo obtener la información del personaje.";
         ui->statusbar->clearMessage();
         ui->statusbar->showMessage("No se pudo obtener la información del personaje.");
        }
}
void MainWindow::BuscarPlaneta(QUrl URL)
{
    // Realizar la solicitud GET y obtener la respuesta como un objeto JSON
    QJsonObject Planeta = API.getJsonObject(URL);

    // Realizar la solicitud GET y obtener la respuesta como un objeto JSON
    ui->label_planeta_imagen->clear();
    if (!Planeta.isEmpty()) GenerarCardPlaneta( Planeta);
    else {
           ui->statusbar->clearMessage();
           ui->statusbar->showMessage("No se pudo obtener la información del personaje.");
           qWarning() << "No se pudo obtener la información del personaje.";
          }
}

void MainWindow::GenerarCardPersonaje(QJsonObject Personaje)
{
   QPixmap PersonaImage;
   QJsonArray Transformaciones;
   QJsonObject TransformacionesAux;
   QJsonObject PlanetaOrigen;
   QString PersonajeimageUrl = Personaje["image"].toString();
   PlanetaOrigen= Personaje["originPlanet"].toObject();
   Transformaciones = Personaje["transformations"].toArray();
   ui->label_setgenero->setText(Personaje["gender"].toString());
   ui->label_setraza->setText(Personaje["race"].toString());
   ui->label_setki->setText(Personaje["ki"].toString());
   ui->label_setkimax->setText(Personaje["maxKi"].toString());
   ui->label_setplanetaorigen->setText(PlanetaOrigen["name"].toString());
   ui->textEdit_setdescripcion->setPlainText(Personaje["description"].toString());
   ui->textEdit_setdescripcion->setAlignment(Qt::AlignJustify);
   if (!Transformaciones.isEmpty())  TransformacionesCard(Transformaciones);
    else ui->label_Ntransformaciones->setText("No posee");

   BuscarImagen(QUrl(PersonajeimageUrl),ui->label_image);


}
void MainWindow::GenerarCardPlaneta(QJsonObject Planeta)
{
   QString PlanetaimageUrl = Planeta["image"].toString();
   QJsonArray PersonajesdelPlaneta;
   PersonajesdelPlaneta=Planeta["characters"].toArray();
   if(Planeta["isDestroyed"]==true) ui->label_planeta_setestado->setText("Destruido");
   else ui->label_planeta_setestado->setText("Existe");
   ui->textEdit_planeta_descripcion->setPlainText(Planeta["description"].toString());
   ui->textEdit_planeta_descripcion->setAlignment(Qt::AlignJustify);
   BuscarImagen(QUrl(PlanetaimageUrl),ui->label_planeta_imagen);
   PersonajesenPlanetaCard(PersonajesdelPlaneta);

}

void MainWindow::TransformacionesCard(QJsonArray Transformaciones)
{
   listaTransformaciones.clear();

   if (!Transformaciones.isEmpty())
   {
    qDebug() << "\nTransformaciones:";
    for (const QJsonValue &Trasnformacion : Transformaciones)
        {
        QJsonObject Personaje = Trasnformacion.toObject();
        listaTransformaciones.append(Transformacion(Personaje["name"].toString(), Personaje["image"].toString(), Personaje["ki"].toString()));
        TransformacionPersonajeCard(Personaje["name"].toString(),Personaje["ki"].toString(),QUrl(Personaje["image"].toString()));
    }
    ui->label_Ntransformaciones->setText(QString::number(listaTransformaciones.length()));
    qDebug()<<"listaTransformaciones: "<<listaTransformaciones.length();

   }

}
void MainWindow::clearTrasnformacionPersonajeCard()
{
   // Obtener el layout de scrollAreaWidgetContents_personajes
   QLayout* layout = ui->scrollAreaWidgetContents_personajes->layout();

   if (layout) {
    // Remover y eliminar cada widget del layout
    while (QLayoutItem* item = layout->takeAt(0)) {
        // Si el item contiene un widget, eliminar el widget
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        // Eliminar el item del layout
        delete item;
    }
   }
}
void MainWindow::TransformacionPersonajeCard(QString nombre, QString Ki, QUrl imageUrl)
{
   QGridLayout* gridLayout = qobject_cast<QGridLayout*>(ui->scrollAreaWidgetContents_personajes->layout());
   int totalCards = gridLayout->count();
   int row = totalCards / 3;
   int column = totalCards % 3;

   if (!gridLayout) {
    gridLayout = new QGridLayout(ui->scrollAreaWidgetContents_personajes);
    ui->scrollAreaWidgetContents_personajes->setLayout(gridLayout);
   }

   // Crea el marco principal para la tarjeta del personaje con estilo
   QFrame* Hframe = new QFrame();
   Hframe->setFrameStyle(QFrame::StyledPanel);
   Hframe->setStyleSheet("background-color: #b0bac4; border-radius: 5px;");

   QHBoxLayout* newTask = new QHBoxLayout(Hframe);

   QFrame* Vframe = new QFrame();
   QVBoxLayout* taskDetails = new QVBoxLayout(Vframe);
   taskDetails->setAlignment(Qt::AlignCenter);
   taskDetails->setSpacing(5);
   taskDetails->setContentsMargins(0, 0, 0, 0);

   // Crear QLabel para la imagen con estilo y tamaño fijo
   QLabel* ImagenTransformacion = new QLabel();
   ImagenTransformacion->setFixedSize(300, 300);
   ImagenTransformacion->setAlignment(Qt::AlignCenter);
   taskDetails->addWidget(ImagenTransformacion);

   // Crear QLabel para el nombre con estilo de texto
   QLabel* tasklabel = new QLabel(nombre);
   tasklabel->setAlignment(Qt::AlignCenter);
   tasklabel->setStyleSheet("color: #5f2e37; font-size: 14px;");
   taskDetails->addWidget(tasklabel);

   // Crear un layout horizontal para "Ki: " y el valor de Ki, aplicando estilo de texto
   QHBoxLayout* kiLayout = new QHBoxLayout();
   QLabel* kiLabel = new QLabel("Ki: ");
   QLabel* kiValueLabel = new QLabel(Ki);

   kiLabel->setStyleSheet("color: #5f2e37; font-size: 14px;");
   kiValueLabel->setStyleSheet("color: #5f2e37; font-size: 14px;");
   kiLayout->addWidget(kiLabel);
   kiLayout->addWidget(kiValueLabel);
   kiLayout->setAlignment(Qt::AlignCenter);

   taskDetails->addLayout(kiLayout);
   newTask->insertWidget(0, Vframe);

   QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
   newTask->insertSpacerItem(1, spacer);

   gridLayout->addWidget(Hframe, row, column);

   // Llama a BuscarImagen para descargar y establecer la imagen en el QLabel específico de esta tarjeta
   BuscarImagen(imageUrl, ImagenTransformacion);
}
void MainWindow::setImageForTitleLabel(QPixmap image)
{
   if (Imagen) {
    Imagen->setPixmap(image.scaled(Imagen->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
   }
}
void MainWindow::on_tabWidget_tabBarClicked(int index)
{
   clearTrasnformacionPersonajeCard();
   ui->label_planeta_imagen->clear();
   ui->label_image->clear();
   ui->label_setgenero->clear();
   ui->label_setraza->clear();
   ui->label_setki->clear();
   ui->label_setkimax->clear();
   ui->label_setplanetaorigen->clear();
   ui->textEdit_setdescripcion->clear();
   ui->textEdit_planeta_descripcion->clear();
   ui->label_planeta_setestado->clear();
}

void MainWindow::BuscarImagen(QUrl imageUrl, QLabel* label)
{
   QNetworkRequest request(imageUrl);
   QNetworkReply* reply = networkManager->get(request);

   // Conecta la respuesta con un lambda que actualiza solo el QLabel correspondiente
   connect(reply, &QNetworkReply::finished, this, [this, reply, label]()
           {
               if (reply->error() == QNetworkReply::NoError) {
                   QByteArray imageData = reply->readAll();
                   QBuffer imageBuffer(&imageData);
                   imageBuffer.open(QIODevice::ReadOnly);

                   QImageReader reader(&imageBuffer);
                   reader.setDecideFormatFromContent(true);
                   QImage image;

                   if (reader.read(&image) && !image.isNull()) {
                       QPixmap ImagenDescargada = QPixmap::fromImage(image);
                       label->setPixmap(ImagenDescargada.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                   } else {
                       qDebug() << "Error: La imagen está vacía o no pudo ser cargada.";
                       label->setText("Imagen no disponible");  // Mensaje de error en el QLabel si falla la carga
                   }
               } else {
                   qDebug() << "Error de red:" << reply->errorString();
                   label->setText("Error de red");  // Mensaje de error en el QLabel si falla la red
               }
               reply->deleteLater();
           });
}

void MainWindow::clearPersonajesPlaneta()
{
   // Obtener el layout de scrollAreaWidgetContents_personajes
   QLayout* layout = ui->scrollAreaWidgetContents_planetas->layout();

   if (layout) {
    // Remover y eliminar cada widget del layout
    while (QLayoutItem* item = layout->takeAt(0)) {
        // Si el item contiene un widget, eliminar el widget
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        // Eliminar el item del layout
        delete item;
    }
   }
}
void MainWindow::PersonajesenPlanetaCard(QJsonArray PersonajesdelPlaneta)
{
   if (!PersonajesdelPlaneta.isEmpty())
   {
    qDebug() << "\nTransformaciones:";
    for (const QJsonValue &personaje : PersonajesdelPlaneta)
    {
        QJsonObject Personaje = personaje.toObject();

        PlanetaPersonajeCard(Personaje["name"].toString(), Personaje["ki"].toString(), QUrl(Personaje["image"].toString()));
        //TransformacionPersonajeCard(Personaje["name"].toString(),Personaje["ki"].toString(),QUrl(Personaje["image"].toString()));
    }
    ui->label_Ntransformaciones->setText(QString::number(listaTransformaciones.length()));
    qDebug()<<"listaTransformaciones: "<<listaTransformaciones.length();

   }

}
void MainWindow::PlanetaPersonajeCard(QString nombre, QString Ki, QUrl imageUrl)
{
   QGridLayout* gridLayout = qobject_cast<QGridLayout*>(ui->scrollAreaWidgetContents_planetas->layout());
   int totalCards = gridLayout->count();
   int row = totalCards / 3;
   int column = totalCards % 3;

   if (!gridLayout) {
    gridLayout = new QGridLayout(ui->scrollAreaWidgetContents_personajes);
    ui->scrollAreaWidgetContents_personajes->setLayout(gridLayout);
   }

   // Crea el marco principal para la tarjeta del personaje con estilo
   QFrame* Hframe = new QFrame();
   Hframe->setFrameStyle(QFrame::StyledPanel);
   Hframe->setStyleSheet("background-color: #b0bac4; border-radius: 5px;");

   QHBoxLayout* newTask = new QHBoxLayout(Hframe);

   QFrame* Vframe = new QFrame();
   QVBoxLayout* taskDetails = new QVBoxLayout(Vframe);
   taskDetails->setAlignment(Qt::AlignCenter);
   taskDetails->setSpacing(5);
   taskDetails->setContentsMargins(0, 0, 0, 0);

   // Crear QLabel para la imagen con estilo y tamaño fijo
   QLabel* ImagenTransformacion = new QLabel();
   ImagenTransformacion->setFixedSize(300, 300);
   ImagenTransformacion->setAlignment(Qt::AlignCenter);
   taskDetails->addWidget(ImagenTransformacion);

   // Crear QLabel para el nombre con estilo de texto
   QLabel* tasklabel = new QLabel(nombre);
   tasklabel->setAlignment(Qt::AlignCenter);
   tasklabel->setStyleSheet("color: #5f2e37; font-size: 14px;");
   taskDetails->addWidget(tasklabel);

   // Crear un layout horizontal para "Ki: " y el valor de Ki, aplicando estilo de texto
   QHBoxLayout* kiLayout = new QHBoxLayout();
   QLabel* kiLabel = new QLabel("Ki: ");
   QLabel* kiValueLabel = new QLabel(Ki);

   kiLabel->setStyleSheet("color: #5f2e37; font-size: 14px;");
   kiValueLabel->setStyleSheet("color: #5f2e37; font-size: 14px;");
   kiLayout->addWidget(kiLabel);
   kiLayout->addWidget(kiValueLabel);
   kiLayout->setAlignment(Qt::AlignCenter);

   taskDetails->addLayout(kiLayout);
   newTask->insertWidget(0, Vframe);

   QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
   newTask->insertSpacerItem(1, spacer);

   gridLayout->addWidget(Hframe, row, column);

   // Llama a BuscarImagen para descargar y establecer la imagen en el QLabel específico de esta tarjeta
   BuscarImagen(imageUrl, ImagenTransformacion);
}
