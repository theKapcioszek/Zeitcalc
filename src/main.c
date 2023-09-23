#include <stdio.h>
#include <raylib.h>

#define WWINDOW 1280
#define HWINDOW 720
//#define WWINDOW 1920
//#define HWINDOW 1080

#define WWCENTER (WWINDOW / 2)
#define HWCENTER (HWINDOW / 2)

#define WROW ((WWINDOW / 100)*40)
#define HROW ((HWINDOW / 100)*6)

#define WBUT ((WWINDOW / 100)*19)
#define HBUT ((HWINDOW / 100)*6)

struct TextRow{

  int posx;
  int posy;
  int width;
  int height;
  int centerw;
  int centerh;
  char *text;

};

struct TextRow NewTextRow(char *text, int posx, int posy){
  struct TextRow row;
  row.posx = posx;
  row.posy = posy;
  row.width = WROW;
  row.height = HROW;
  row.centerw = posx + (WROW / 2);
  row.centerh = posy + (HROW / 2);
  row.text = text;

  return row;
}

struct TextRow NewButton(char *text, int posx, int posy, int width, int height){
  struct TextRow button;
  button.posx = posx;
  button.posy = posy;
  button.width = width;
  button.height = height;
  button.centerw = posx + (width / 2);
  button.centerh = posy + (height / 2);
  button.text = text;

  return button;
}

void DrawRow(struct TextRow row){

  DrawRectangle(row.posx, row.posy, row.width, row.height, LIGHTGRAY);
  DrawText(row.text, row.centerw - (MeasureText(row.text,30) / 2), row.centerh - 15, 30, BLACK);

  return;
}

int main(int argc, char **argv){


  InitWindow(WWINDOW,HWINDOW,"Januszex");
  SetTargetFPS(60);

  while(!WindowShouldClose()){

    BeginDrawing();

    ClearBackground(GRAY);

    int iPosyStart = (HWCENTER - (HROW / 2) - (HROW + 10)*6);
    int iPosyLast = iPosyStart;
    for (int i = 1; i <= 10; i++){

      struct TextRow trTestMulti = NewTextRow("test",WWCENTER - (WROW / 2),(iPosyLast + HROW + 10));
      DrawRow(trTestMulti);
      iPosyLast = trTestMulti.posy;

    }

    struct TextRow trBackButton = NewButton("<",WWCENTER - (WROW / 2) - (WBUT + 10),(iPosyLast + HROW + 20),WBUT,HBUT);
    DrawRow(trBackButton);
    struct TextRow trForwardButton = NewButton(">",WWCENTER - (WROW / 2),(iPosyLast + HROW + 20),WBUT,HBUT);
    DrawRow(trForwardButton);
    struct TextRow trPageResult = NewButton("Suma: ",WWCENTER - (WROW / 2) + (WBUT + 25),(iPosyLast + HROW + 20),WBUT,HBUT);
    DrawRow(trPageResult);
    struct TextRow trAllResult = NewButton("Cala Suma: ",WWCENTER - (WROW / 2) + ((WBUT * 2)+35),(iPosyLast + HROW + 20),WBUT,HBUT);
    DrawRow(trAllResult);
    DrawText("0/0", WWCENTER - (MeasureText("0/0",20) / 2), iPosyLast + HROW + 20 + HBUT + 10, 20, BLACK);

    EndDrawing();

  }

  CloseWindow();

  return 0;
}
