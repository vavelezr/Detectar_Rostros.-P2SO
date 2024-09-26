#include <opencv2/opencv.hpp>
#include <iostream>
#include <omp.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <ruta_imagen>" << endl;
        return 1;
    }

    Mat imagen = imread(argv[1], IMREAD_COLOR);
    if (imagen.empty()) {
        cerr << "No se pudo cargar la imagen." << endl;
        return 1;
    }

    CascadeClassifier detector_rostros;
    detector_rostros.load("haarcascade_frontalface_default.xml");
    // detector_rostros.load("haarcascade_profileface.xml");

    Mat gris;
    cvtColor(imagen, gris, COLOR_BGR2GRAY);

    vector<Rect> rostros;
    detector_rostros.detectMultiScale(gris, rostros);

    #pragma omp parallel for
    for (size_t i = 0; i < rostros.size(); i++) {
        rectangle(imagen, rostros[i], Scalar(57, 255, 51), 2);
    }

    imshow("Rostros detectados", imagen);
    waitKey(0);

    string nombre_archivo = "imagen_con_rostros_marcados.jpg";
    if (imwrite(nombre_archivo, imagen)) {
        cout << "Imagen guardada" << endl;
    } else {
        cerr << "Error al guardar la imagen." << endl;
    }

    string carpeta_individuales = "individuales";

    #pragma omp parallel for
    for (size_t i = 0; i < rostros.size(); i++  ) {
        double start_time = omp_get_wtime();
        Mat rostro = imagen(rostros[i]);

        string nombre_rostro = carpeta_individuales + "/rostro" + to_string(i) + ".jpg";

        if (imwrite(nombre_rostro, rostro)) {
            cout << "Rostro " << i << " guardado." << endl << "";
        } else {
            cerr << "Error al guardar el rostro " << i << endl;
        }

        double end_time = omp_get_wtime();
        double elapsed_time = end_time - start_time;


        #pragma omp critical 
        {
            cout << "Tiempo para guardar rostro " << i << ": " << elapsed_time << " segundos." << endl;
        }
    }
    
    return 0;
}
