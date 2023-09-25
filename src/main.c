#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

#define MAX_STRING_LENGTH 10

struct TextRow{

  int posx;
  int posy;
  int width;
  int height;
  int centerw;
  int centerh;
  char *text;
  char *date;

};

struct TextRow NewTextRow(char *date,char *text, int posx, int posy){
  struct TextRow row;
  row.posx = posx;
  row.posy = posy;
  row.width = WROW;
  row.height = HROW;
  row.centerw = posx + (WROW / 2);
  row.centerh = posy + (HROW / 2);
  row.text = text;
  row.date = date;

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
  button.date = NULL;

  return button;
}

void DrawRow(struct TextRow row, char* text,int fontSize){

  DrawRectangle(row.posx, row.posy, row.width, row.height, LIGHTGRAY);
  if(row.width != WROW){
    DrawText(row.text, row.centerw - (MeasureText(row.text,fontSize) / 2), row.centerh - (fontSize / 2), fontSize, BLACK);
  }
  else{
    DrawText(text, row.centerw - (MeasureText(text,fontSize) / 2), row.centerh - (fontSize / 2), fontSize, BLACK);
  }

  return;
}

int main(int argc, char **argv){


  InitWindow(WWINDOW,HWINDOW,"Januszex");
  SetTargetFPS(60);
  char chpTextBuffer[MAX_STRING_LENGTH + 1] = "\0";
  int iLetterCount = 0;


  while(!WindowShouldClose()){

    BeginDrawing();

    ClearBackground(DARKBLUE);

    int iPosyStart = (HWCENTER - (HROW / 2) - (HROW + 10)*6);
    int iPosyLast = iPosyStart;
    for (int i = 1; i <= 10; i++){

      struct TextRow trTestMulti = NewTextRow("25.09.2023","test",WWCENTER - (WROW / 2),(iPosyLast + HROW + 10));

      char *chpCombinedText;
      chpCombinedText = malloc(strlen(trTestMulti.date)+2+strlen(trTestMulti.text)+1);
      strcpy(chpCombinedText,trTestMulti.date);
      strcat(chpCombinedText,": ");
      strcat(chpCombinedText,trTestMulti.text);

      DrawRow(trTestMulti,chpCombinedText,30);
      iPosyLast = trTestMulti.posy;

      free(chpCombinedText);

    }

    struct TextRow trBackButton = NewButton("<",WWCENTER - (WROW / 2) - (WBUT + 10),(iPosyLast + HROW + 20),WBUT,HBUT);
    DrawRow(trBackButton,NULL,40);
    struct TextRow trForwardButton = NewButton(">",WWCENTER - (WROW / 2),(iPosyLast + HROW + 20),WBUT,HBUT);
    DrawRow(trForwardButton,NULL,40);
    struct TextRow trPageResult = NewButton("Suma: ",WWCENTER - (WROW / 2) + (WBUT + 25),(iPosyLast + HROW + 20),WBUT,HBUT);
    DrawRow(trPageResult,NULL,20);
    struct TextRow trAllResult = NewButton("Cala Suma: ",WWCENTER - (WROW / 2) + ((WBUT * 2)+35),(iPosyLast + HROW + 20),WBUT,HBUT);
    DrawRow(trAllResult,NULL,20);
    DrawText("0/0", WWCENTER - (MeasureText("0/0",20) / 2), iPosyLast + HROW + 20 + HBUT + 10, 20, BLACK);

    int iPressedKey = GetCharPressed();

    while(iPressedKey > 0){
      if((iPressedKey >=32) && (iPressedKey <= 125) && (iLetterCount <= MAX_STRING_LENGTH)){

        chpTextBuffer[iLetterCount] = (char)iPressedKey;
        chpTextBuffer[iLetterCount+1] = '\0';
        iLetterCount++;

      }
      iPressedKey = GetCharPressed();
    }

    DrawText(chpTextBuffer, WWCENTER - (MeasureText(chpTextBuffer,30) / 2), iPosyStart,30,BLACK);

    EndDrawing();

  }

  CloseWindow();

  return 0;
}
