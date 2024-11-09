# Dragon Ball API Application
Esta aplicación, desarrollada en *Qt* con *C++*, permite interactuar con la API de Dragon Ball para obtener y visualizar información sobre personajes de la serie. Incluye datos como el nombre, género, raza, nivel de poder (ki), y muestra una imagen del personaje en un QLabel. 

## Funcionalidades

- Conexión con la [Dragon Ball API](https://dragonball-api.com) para obtener información de los personajes.
- Despliegue de datos detallados del personaje y de los planetas de la saga Dragon Ball en una interfaz gráfica.
- Visualización de la imagen del personaje en un QLabel mediante QNetworkAccessManager.
- Selección de personajes desde un QComboBox para facilitar la navegación.

## Requisitos

- *Qt 6.5.2* o superior
- *Compilador MSVC2019* en un entorno de Windows de 64 bits (ajustar según la configuración del sistema).
- Conexión a internet para cargar imágenes desde la API.

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

| **About** | **Personajes** | **Planetas** |
|---|---|---|
| ![About](https://github.com/CarlosOC/DragonBall/blob/main/imagenes/About.png) | ![Personajes](https://github.com/CarlosOC/DragonBall/blob/main/imagenes/Personajes.png) | ![Planetas](https://github.com/CarlosOC/DragonBall/blob/main/imagenes/Planetas.png) |
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
