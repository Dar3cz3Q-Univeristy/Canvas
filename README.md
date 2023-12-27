# Canvas

## Used libraries
1. [jsoncpp](https://github.com/open-source-parsers/jsoncpp)

## Running program
1. Clone the repository,
2. Fill up the configuration file (schema shown below),
3. Run ```g++ Main.cpp Source.cpp Header.h dist/jsoncpp.cpp dist/json/json.h dist/json/json-forwards.h -o main``` command to compile,
4. Run ```./main``` command, use the name of the configuration file as an argument,

## Config file

### At the moment there are 3 figures that you can draw.
1. Rectangle,
2. Square,
3. Circle

### In config file every figure needs to have properties shown below:
1. customName,
2. type,
3. middle {x, y},
4. symbol

### Depending on what figure you want to draw u need to specify size of the figure differently.
For rectangle
```
"dimensions": {
    "width": 3,
    "height": 6
},
```
For square
```
"sideLength": 3,
```
For circle
```
"radius": 10,
```

### Sample file
```
{
  "outputFileName": "file.ascii",    // Name of output file
  "canvas": {
    "width": 50,             // Width of the canvas
    "height": 50,            // Height of the canvas
    "emptyPixel": " "      // Char that will be used as empty pixel on image
  },
  "figures": [             // List of figures to draw
    {
      "customName": "myFigure1",
      "type": "Rectangle",
      "middle": {
        "x": 3,
        "y": 3
      },
      "dimensions": {
        "width": 3,
        "height": 6
      },
      "symbol": "."
    },
    {
      "customName": "myFigure2",
      "type": "Square",
      "middle": {
        "x": 5,
        "y": 10
      },
      "sideLength": 3,
      "symbol": "#"
    },
    {
      "customName": "myFigure3",
      "type": "Circle",
      "middle": {
        "x": 25,
        "y": 25
      },
      "radius": 10,
      "symbol": "*"
    }
  ]
}
```
