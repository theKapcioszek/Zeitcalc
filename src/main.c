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

#define COLS 10
#define ROWS 365

typedef struct {

  int posx;
  int posy;
  int width;
  int height;
  int centerw;
  int centerh;
  char *text;
  //char *date;

} TextRow;

TextRow NewTextRow(char *text, int posx, int posy){
  TextRow row;
  row.posx = posx;
  row.posy = posy;
  row.width = WROW;
  row.height = HROW;
  row.centerw = posx + (WROW / 2);
  row.centerh = posy + (HROW / 2);
  row.text = text;
  //row.date = date;

  return row;
}

TextRow NewButton(char *text, int posx, int posy, int width, int height){
  TextRow button;
  button.posx = posx;
  button.posy = posy;
  button.width = width;
  button.height = height;
  button.centerw = posx + (width / 2);
  button.centerh = posy + (height / 2);
  button.text = text;
  //button.date = NULL;

  return button;
}

void DrawRow(TextRow row, char* text,int fontSize){

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

  char* (*array)[COLS];
  array = malloc(sizeof(*array) * ROWS);
  array = malloc(sizeof(char*[ROWS][COLS]));


    array[0][0]="test 1";
    array[0][1]="test 2";
    array[0][2]="test 3";
    array[0][3]="test 4";
    array[0][4]="test 5";
    array[0][5]="test 6";
    array[0][6]="test 7";
    array[0][7]="test 8";
    array[0][8]="test 9";
    array[0][9]="test 10";

    int iPosyStart = (HWCENTER - (HROW / 2) - (HROW + 10)*6);

  while(!WindowShouldClose()){

//INPUT SECTION

    int iPressedKey = GetCharPressed();

    while(iPressedKey > 0){
      if((iPressedKey >=32) && (iPressedKey <= 125) && (iLetterCount <= MAX_STRING_LENGTH)){

        chpTextBuffer[iLetterCount] = (char)iPressedKey;
        chpTextBuffer[iLetterCount+1] = '\0';
        iLetterCount++;

      }
      iPressedKey = GetCharPressed();
    }

    array[0][0] = chpTextBuffer;


//INPUT SECTION

    BeginDrawing();

    ClearBackground(DARKBLUE);

    int iPosyLast = iPosyStart;

    for (int i = 1; i <= 10; i++){

      TextRow trTestMulti = NewTextRow(array[0][i-1],WWCENTER - (WROW / 2),(iPosyLast + HROW + 10));

      //char *chpCombinedText;
      //chpCombinedText = malloc(strlen(trTestMulti.date)+2+strlen(trTestMulti.text)+1);
      //strcpy(chpCombinedText,trTestMulti.date);
      //strcat(chpCombinedText,": ");
      //strcat(chpCombinedText,trTestMulti.text);

      DrawRow(trTestMulti,trTestMulti.text,30);
      iPosyLast = trTestMulti.posy;

      //free(chpCombinedText);

    }

    TextRow trBackButton = NewButton("<",WWCENTER - (WROW / 2) - (WBUT + 10),(iPosyLast + HROW + 20),WBUT,HBUT);
    DrawRow(trBackButton,NULL,40);
    TextRow trForwardButton = NewButton(">",WWCENTER - (WROW / 2),(iPosyLast + HROW + 20),WBUT,HBUT);
    DrawRow(trForwardButton,NULL,40);
    TextRow trPageResult = NewButton("Suma: ",WWCENTER - (WROW / 2) + (WBUT + 25),(iPosyLast + HROW + 20),WBUT,HBUT);
    DrawRow(trPageResult,NULL,20);
    TextRow trAllResult = NewButton("Cala Suma: ",WWCENTER - (WROW / 2) + ((WBUT * 2)+35),(iPosyLast + HROW + 20),WBUT,HBUT);
    DrawRow(trAllResult,NULL,20);

    char chpMaxPages[3];
    char chpCurPage[2];
    sprintf(chpMaxPages,"%d",ROWS);
    sprintf(chpCurPage,"%d",1);


    char *chpCombinedText;
    chpCombinedText = malloc(strlen(chpMaxPages)+2+strlen(chpCurPage)+1);
    strcpy(chpCombinedText,chpCurPage);
    strcat(chpCombinedText,"/");
    strcat(chpCombinedText,chpMaxPages);

    DrawText(chpCombinedText, WWCENTER - (MeasureText(chpCombinedText,20) / 2), iPosyLast + HROW + 20 + HBUT + 10, 20, BLACK);
    free(chpCombinedText);

    DrawText(chpTextBuffer, WWCENTER - (MeasureText(chpTextBuffer,30) / 2), iPosyStart,30,BLACK);

    EndDrawing();

  }
  free(array);
  CloseWindow();

  return 0;
}
