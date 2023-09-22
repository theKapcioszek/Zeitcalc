#include <stdio.h>
#include <raylib.h>

#define WWINDOW 1280
#define HWINDOW 720

#define WWCENTER (WWINDOW / 2)
#define HWCENTER (HWINDOW / 2)

#define WROW ((WWINDOW / 100)*37)
#define HROW ((HWINDOW / 100)*8)

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
  row.centerw = posx + (row.width / 2);
  row.centerh = posy + (row.height / 2);
  row.text = text;

  return row;
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

    struct TextRow trTest = NewTextRow("test",WWCENTER - (WROW / 2),HWCENTER - (HROW / 2));
    DrawRow(trTest);

    EndDrawing();

  }

  CloseWindow();

  return 0;
}
