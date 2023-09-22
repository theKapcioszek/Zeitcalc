#include <stdio.h>
#include <raylib.h>

#define WWINDOW 1280
#define HWINDOW 720

#define WWCENTER (WWINDOW / 2)
#define HWCENTER (HWINDOW / 2)

#define WROW ((WWINDOW / 100)*40)
#define HROW ((HWINDOW / 100)*6)

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
  row.centerw = posx + (WROW / 2);
  row.centerh = posy + (HROW / 2);
  row.text = text;

  return row;
}

void DrawRow(struct TextRow row){

  DrawRectangle(row.posx, row.posy, WROW, HROW, LIGHTGRAY);
  DrawText(row.text, row.centerw - (MeasureText(row.text,30) / 2), row.centerh - 15, 30, BLACK);

  return;
}

int main(int argc, char **argv){


  InitWindow(WWINDOW,HWINDOW,"Januszex");
  SetTargetFPS(60);

  while(!WindowShouldClose()){

    BeginDrawing();

    ClearBackground(GRAY);

    //struct TextRow trTest1 = NewTextRow("test",WWCENTER - (WROW / 2),(HWCENTER - (HROW / 2)) - (HROW + 10));
    //DrawRow(trTest1);
    //struct TextRow trTest2 = NewTextRow("test",WWCENTER - (WROW / 2),trTest1.posy + HROW + 10);
    //DrawRow(trTest2);
    //struct TextRow trTest3 = NewTextRow("test",WWCENTER - (WROW / 2),trTest2.posy + HROW + 10);
    //DrawRow(trTest3);
    int iPosyStart = (HWCENTER - (HROW / 2) - (HROW + 10)*6);
    int iPosyLast = iPosyStart;
    for (int i = 1; i <= 10; i++){

      struct TextRow trTestMulti = NewTextRow("test",WWCENTER - (WROW / 2),(iPosyLast + HROW + 10));
      DrawRow(trTestMulti);
      iPosyLast = trTestMulti.posy;

    }

    EndDrawing();

  }

  CloseWindow();

  return 0;
}
