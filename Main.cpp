#include "Header.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "Niepoprawna liczba argumentow!" << endl;
        return -1;
    }

    string fileName = argv[1];
    ifstream configFile(fileName, ifstream::binary);

    if (!configFile) {
        cout << "Blad otwierania pliku!" << endl;
        return -1;
    }

    Json::Value config;
    configFile >> config;

    configFile.close();

    int canvasWidth = config["canvas"]["width"].asInt();
    int canvasHeight = config["canvas"]["height"].asInt();

    if (canvasWidth <= 0 || canvasHeight <= 0) {
        cout << "Bledne dane w pliku konfiguracyjnym!" << endl;
        return -1;
    }

    string emptyPixel = config["canvas"]["emptyPixel"].asString();

    ASCIICanvas canvas(canvasWidth, canvasHeight, emptyPixel[0]);

    Json::Value figures = config["figures"];

    for (int i = 0; i < figures.size(); i++) {
        int x = figures[i]["middle"]["x"].asInt();
        int y = figures[i]["middle"]["y"].asInt();
        string symbol = figures[i]["symbol"].asString();

        if (figures[i]["type"] == "Rectangle") {
            int width = figures[i]["dimensions"]["width"].asInt();
            int height = figures[i]["dimensions"]["height"].asInt();

            if (!checkGivenData(canvas, x, y, width, height)) {
                cout << "Bledne dane w pliku konfiguracyjnym dla " << figures[i]["customName"] << "!" << endl;
                cout << "Figura zostanie pominieta" << endl;
                continue;
            }

            Rectangle* prostokat = new Rectangle(x, y, width, height, symbol[0]);
            prostokat->draw(canvas);
            delete prostokat;
        }
        else if (figures[i]["type"] == "Square") {
            int sideLength = figures[i]["sideLength"].asInt();

            if (!checkGivenData(canvas, x, y, sideLength)) {
                cout << "Bledne dane w pliku konfiguracyjnym dla " << figures[i]["customName"] << "!" << endl;
                cout << "Figura zostanie pominieta" << endl;
                continue;
            }

            Square* kwadrat = new Square(x, y, sideLength, symbol[0]);
            kwadrat->draw(canvas);
            delete kwadrat;
        }
        else if (figures[i]["type"] == "Circle") {
            int radius = figures[i]["radius"].asInt();

            if (!checkGivenData(canvas, x, y, radius)) {
                cout << "Bledne dane w pliku konfiguracyjnym dla " << figures[i]["customName"] << "!" << endl;
                cout << "Figura zostanie pominieta" << endl;
                continue;
            }

            Circle* kolo = new Circle(x, y, radius, symbol[0]);
            kolo->draw(canvas);
            delete kolo;
        }
        else {
            cout << "Figura nie zostala rozpoznana!" << endl;
            continue;
        }
    }

    cout << "\nPodglad stworzonego obrazu" << endl;
    canvas.print();

    string resultFileName = config["outputFileName"].asString();
    cout << "\nTrwa zapis do pliku " << resultFileName << endl;

    fstream result;
    result.open(resultFileName, ios::out);

    if (!result) {
        cout << "Blad otwierania pliku!" << endl;
        return -1;
    }

    canvas.print(result);

    result.close();

    cout << "Plik stworzony pomyslnie" << endl;

    return 0;
}

