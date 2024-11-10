# Dragon Ball API Application
Esta aplicación, desarrollada en *Qt* con *C++*, permite interactuar con la API de Dragon Ball para obtener y visualizar información sobre personajes de la serie. Incluye datos como el nombre, género, raza, nivel de poder (ki), y muestra una imagen del personaje en un QLabel. 

## Características

- **Conexión a la API de Dragon Ball**: Obtén información detallada de personajes y planetas de la saga.
- **Interfaz gráfica amigable**: Usa una interfaz intuitiva con QComboBox para la selección de personajes y planetas.
- **Visualización de imágenes**: Muestra imágenes de los personajes usando QNetworkAccessManager.
- **Manejo de errores**: Proporciona mensajes de depuración para la resolución de problemas.

## Estructura del Proyecto
```
dragonball-api-app/
├── apirequest.cpp       # Implementación de las funciones para conectarse a la API de Dragon Ball
├── apirequest.h         # Declaración de la clase para gestionar la conexión a la API
├── DragonBallApiRequest.pro # Archivo de configuración del proyecto para Qt
├── main.cpp             # Punto de entrada de la aplicación
├── mainwindow.cpp       # Implementación de la interfaz gráfica principal
├── mainwindow.h         # Declaración de la clase MainWindow
├── mainwindow.ui        # Diseño de la interfaz de usuario en formato .ui de Qt
├── resources.qrc        # Archivo de recursos que incluye imágenes y otros recursos necesarios
└── README.md            # Documentación del proyecto
```
Cada archivo cumple un rol específico:
- **apirequest.cpp y apirequest.h**: Gestión de las solicitudes HTTP para obtener datos de la API.
- **DragonBallApiRequest.pro**: Configuración del proyecto en Qt Creator.
- **main.cpp**: Inicia la aplicación y muestra la ventana principal.
- **mainwindow.cpp y mainwindow.h**: Controlan la lógica y los eventos de la interfaz principal.
- **mainwindow.ui**: Define el diseño visual de la ventana principal.
- **resources.qrc**: Incluye las rutas de las imágenes y otros archivos usados en la aplicación.
- **README.md**: Documentación para los desarrolladores y usuarios.
## Requisitos

- *Qt 6.5.2* o superior
- *Compilador MSVC2019* en un entorno de Windows de 64 bits (ajustar según la configuración del sistema).
- Conexión a internet para cargar imágenes y datos desde la API.

## Instalación y Ejecución

1. Clona este repositorio:
   ```bash
   git clone https://github.com/tu-usuario/dragonball-api-app.git
   cd dragonball-api-app
2. Abre el proyecto en Qt Creator y asegúrate de seleccionar el kit correcto (Qt 6.5.2 y MSVC2019).
3. Ejecuta el proyecto. La aplicación debería compilar y ejecutar en Qt Creator sin problemas.

## Uso
1. Selecciona un personaje o un planeta desde los QComboBox.
2. La aplicación mostrará detalles del personaje y su imagen en la interfaz.
3. Si no se puede cargar la imagen, el terminal mostrará mensajes de depuración que ayudan a identificar posibles errores.

### Capturas de pantalla

| **About** | **Personajes & Transformaciones** | **Planetas & Habitantes** |
|---|---|---|
| ![About](https://github.com/CarlosOC/DragonBall/blob/main/imagenes/About.png) | ![Personajes_&_Transformaciones](https://github.com/CarlosOC/DragonBall/blob/main/imagenes/Personajes.png) | ![Planetas_&_Habitantes](https://github.com/CarlosOC/DragonBall/blob/main/imagenes/Planetas.png) |

## Contribuciones
Las contribuciones son bienvenidas. Si encuentras algún problema o tienes alguna mejora, crea un issue o un pull request en este repositorio.

## Licencia
Este proyecto está bajo la licencia MIT.

## Contacto

Si tienes alguna pregunta o sugerencia, no dudes en ponerte en contacto conmigo:

- Correo electrónico: carlosoviedolr@gmail.com
- Linkedin: [https://www.linkedin.com/in/carlosnicolasoviedocodigoni/]

¡Espero que disfrutes trabajando en estos ejercicios tanto como yo disfruto enseñándolos!

Happy coding! 🚀
