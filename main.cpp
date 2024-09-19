#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    //----------------------CARGAR IMAGEN DESDE LA LINEA DE COMANDO---------------------
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <ruta_imagen>" << endl;
        return 1;
    }

    Mat imagen = imread(argv[1], IMREAD_COLOR);
    if (imagen.empty()) {
        cerr << "No se pudo cargar la imagen." << endl;
        return 1;
    }

    //--------------------DETECCIÓN DE ROSTROS-------------------------
    CascadeClassifier detector_rostros;
    detector_rostros.load("haarcascade_frontalface_default.xml"); //Cargar algoritmo

    Mat gris;
    cvtColor(imagen, gris, COLOR_BGR2GRAY); // Convertir a escala de grises para detección

    vector<Rect> rostros;
    detector_rostros.detectMultiScale(gris, rostros);

    for (size_t i = 0; i < rostros.size(); i++) {
        rectangle(imagen, rostros[i], Scalar(180, 105, 255), 2); // Dibujar un rectangulo rosado alrededor de los rostros
    }

    imshow("Rostros detectados", imagen);
    waitKey(0);

    // Guardar imagen con rostros marcados
    string nombre_archivo = "imagen_con_rostros_marcados.jpg";
    if (imwrite(nombre_archivo, imagen)) {
        cout << "Imagen guardada" << endl;
    } else {
        cerr << "Error al guardar la imagen." << endl;
    }

    return 0;
}
