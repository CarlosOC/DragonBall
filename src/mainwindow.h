#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "apirequest.h"
#include <QMainWindow>
#include <QBuffer>
#include "QFile"
#include <QDir>
#include <QIcon>
#include "QLabel"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
     QNetworkAccessManager *networkManager;
signals:
     void imagenDescargada(const QPixmap &imagen);
private slots:
    void initStylesheet();
    void inicializacion (QUrl URLPersonajes, QUrl URLPlanetas);
    void on_pushButton_clicked();
    void BuscarPersonaje (QUrl URL);
    void BuscarPlaneta (QUrl URL);
    void GenerarCardPersonaje(QJsonObject Personaje);
    void GenerarCardPlaneta (QJsonObject Planeta);


    void on_pushButton_planeta_clicked();

    void on_tabWidget_tabBarClicked(int index);
    void TransformacionesCard(QJsonArray Transformaciones);
    void TransformacionPersonajeCard(QString nombre, QString Ki, QUrl imageUrl);
    void clearTrasnformacionPersonajeCard();
    void clearPersonajesPlaneta();
    void setImageForTitleLabel(QPixmap image);
    void BuscarImagen(QUrl imageUrl, QLabel* label);
    void PersonajesenPlanetaCard(QJsonArray Transformaciones);
    void PlanetaPersonajeCard(QString nombre, QString Ki, QUrl imageUrl);
private:
    struct Transformacion {
        QString nombre;
        QString imagen;
        QString ki;

        Transformacion(const QString& n, const QString& img, const QString& desc)
            : nombre(n), imagen(img), ki(desc) {}
    };

    Ui::MainWindow *ui;
    APIRequest API;
    QList<QPair<int, QString>> ListaPersonajes;
    QList<QPair<int, QString>> ListaPlanetas;
    QList<Transformacion> listaTransformaciones;
    QLabel * Imagen;
};
#endif // MAINWINDOW_H
