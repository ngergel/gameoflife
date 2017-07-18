#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <TouchScreen.h>

//using namespace std;

const int R =24;
const int C =32;
const int CELL_LENGTH = 10;
const int WIDTH = 240;
const int LENGTH = 320;
#define forLoop(var, L) \
  for (int var=0;var<L;var++)

// These are the four touchscreen analog pins
#define YP A2  // must be an analog pin
#define XM A3  // must be an analog pin
#define YM 8   // can be a digital pin
#define XP 7   // can be a digital pin

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

// For the Adafruit shield, these are the default throughout all the labs.
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 6
#define TFT_MOSI 51
#define TFT_MISO 50
#define TFT_CLK 52

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

//const int lws[][]={{},
{},{},};
int life[R][C+2]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0},
                {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
int temp[R][C];

void transfer() {
  //send the information about its first two columns it processes
  for (int row = 0; row<R;row++){
    for (size_t col = 2; col < 4; col++) {
      Serial.print(life[row][col]);
    }
  }

  //receive the state of the first two columns it inspects
  if (Serial1.avalible()) {
      for (size_t row = 0; row < R; row++) {
        for (size_t col = 0; col < 2; col++) {
          life[row][col]=Serial1.read();
        }
      }
  }
}
void setup() {
  // put your setup code here, to run once:
  tft.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Starting ...");
  tft.fillScreen(ILI9341_BLACK);

  for (int row = 0; row < R; row++) {
    for (int col = 0; col < C; col++) {
      if (life[row][col]==1) tft.fillRect(row*10, col *10, CELL_LENGTH, CELL_LENGTH,ILI9341_WHITE);
      else tft.fillRect(row*10, col *10,CELL_LENGTH, CELL_LENGTH, ILI9341_BLUE);
    }
  }

}

//displays the contents of the next gen onto the screen and updates old generation's states to the new generation
void displayCells() {
  for (int row = 0; row < R; row++) {
    for (int col = 2; col < C+2; col++) {
      int state = life[row][col];
      life[row][col]=temp[row][col];
      if (life[row][col]==state) continue;
      if (temp[row][col]==1) tft.fillRect(row*10, col *10, CELL_LENGTH, CELL_LENGTH,ILI9341_WHITE);
      else tft.fillRect(row*10, col *10,CELL_LENGTH, CELL_LENGTH, ILI9341_BLUE);
    }
  }
}

//checks if coordinates are within the arrays dimensions
bool checkBounds(int r, int c) {
  if (r<R&&r>=0&&c<C+2&&c>=0) return true;
  return false;
}

void processCell(int r, int c) {
  //count the number of adjacent cells that are occupied
  int count=0;
  if (checkBounds(r+1,c)&&life[r+1][c]==1) count++;
  if (checkBounds(r-1,c)&&life[r-1][c]==1) count++;
  if (checkBounds(r+1,c-1)&&life[r+1][c-1]==1) count++;
  if (checkBounds(r+1,c+1)&&life[r+1][c+1]==1) count++;
  if (checkBounds(r,c+1)&&life[r][c+1]==1) count++;
  if (checkBounds(r,c-1)&&life[r][c-1]==1) count++;
  if (checkBounds(r-1,c+1)&&life[r-1][c+1]==1) count++;
  if (checkBounds(r-1,c-1)&&life[r-1][c-1]==1) count++;



  //determine the state of the cell for next generation
  switch(count){
    case 0:
    case 1: temp[r][c]=0; break;    //lonely
    case 2:
      if (life[r][c]==1) {
        temp[r][c]=1;
      } else {
        temp[r][c]=0;
      }
     break;                         //remains the same state
    case 3: temp[r][c]=1; break;    //is always guaranteed to be alive next gen
    case 4:
    case 5:
    case 6:
    case 7:
    case 8: temp[r][c]=0; break;    //overpopulated
  }
}

void loop() {
  while(true){
    forLoop(row, R) {forLoop(col, C) {processCell(row, col);/** temp[row][col]=life[row][col];**/}}
    //forLoop(row, R) {forLoop(col, C) {cout<<temp[row][col]<<" "; life[row][col]=temp[row][col];} cout<<endl;}
    //cout<<endl;
    /*transfer information of each half of the new generation*/
    displayCells();
    transfer();
  }
}
