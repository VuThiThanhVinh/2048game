#ifndef BOARD_H
#define BOARD_H
#include<iostream>
#include<SDL2/SDL.h>
#include<ctime>
#include<cstdlib>
#include<SDL2/SDL_image.h>
#include<string>
#include <Windows.h>
#include<SDL2/SDL_mixer.h>
using namespace std;
const int StartWidth=39;
const int StartHeight=236;
const int WidthABox= 78;
const int HeightABox=80;
const int Space=16;
const int SCREEN_WIDTH= 437;
const int SCREEN_HEIGHT=700;
//danh sach cac anh
string path[]={
    "2_image.png","4_image.png","8_image.png",
    "16_image.png","32_image.png","64_image.png",
    "128_image.png","256_image.png","512_image.png",
    "1024_image.png","2048_image.png"
};

// anh tai cac o trong bang
SDL_Surface* Box[4][4]=
{NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL};

// toa do cac o trong bang
SDL_Rect Board[4][4];
void SetBoard()
{
    
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        { 
        Board[i][j].x=StartWidth+j*WidthABox+j*Space;
         Board[i][j].y=StartHeight+i*HeightABox+i*Space;
      
        }
    }
    
}

// khoi dong SDL va tao cua so
bool init();

// tai len phuong tien
bool loadMedia();

// giai phong phuong tien va tat SDL
void close();

//hien thi cua so
SDL_Window* window=NULL;

//lay ket qua cua viec doc tam anh image
    SDL_Surface* load_image =NULL;

//be mat cua cua so
SDL_Surface* screen_surface= NULL;

//anh background menu
SDL_Surface* BackgroundMenu=NULL;

//anh background main
SDL_Surface* BackgroundMain=NULL;

//anh background endgame
SDL_Surface* BackgroundEndgame=NULL;

//trinh xu ly su kien thoat de ket thuc ung dung
 SDL_Event e;

//luu anh cua cac hinh khoi can dung
SDL_Surface* imageX[11]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;

bool init()
{
//co khoi tao
bool success= true;

//SDL_Init(Uint 32 flags) tra ve 0 neu thanh cong hoac tra ve gia tri am neu that bai
if(SDL_Init(SDL_INIT_VIDEO| SDL_INIT_AUDIO)<0)
{
cout<<"SDL could not initialize! SDL_Error:"<<SDL_GetError()<<endl;
success= false;
}
else{
    // tao cua so
    window=SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if(window==NULL){
        cout<<"Window could not be created! SDL_Error: "<<SDL_GetError()<<endl;
        success=false;
    }
    else
    {
        //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
            //Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
            else
            {
                //Get window surface
                screen_surface = SDL_GetWindowSurface( window );
            }
        }
    }

    return success;
}

SDL_Surface* LoadImage(string file_path){
    
    //toi uu hoa dinh dang tam anh
    SDL_Surface* optimize_image= NULL;

    //load anh 
    load_image=IMG_Load(file_path.c_str());
    if(load_image==NULL)
    {
    cout<<"Unalbe to load image, SDL_image Error "<<SDL_GetError()<<endl;
    }
    else
    {
        // sao chep anh sang be mat duoc chi dinh
       optimize_image=SDL_ConvertSurface(load_image,screen_surface->format,0);
        if(optimize_image==NULL) cout<<"Unable to optimize image, SDL Error "<<SDL_GetError()<<endl;
        
        //giai phong load_image
        else SDL_FreeSurface(load_image);
    }
    return optimize_image;
}

bool loadMedia(){
    //co khoi tao
    bool success=true;

     //tai be mat mac dinh( man hinh menu)
    BackgroundMenu=LoadImage("BackgroundMenu_image.png");
    
    //tai be mat main
    BackgroundMain=LoadImage("main_image.png");

    //tai len anh endgame
    BackgroundEndgame=LoadImage("endgame.png");

  for(int i=0;i<11;i++) imageX[i]=LoadImage(path[i]);
  
    if(BackgroundMain==NULL) 
    {
     cout<<"Failed to load background menu image"<<endl;
    success=false;
    }
 //Load music
    gMusic = Mix_LoadMUS( "KokuhakuNoYoru-Ayasa-5922559.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    // //Load sound effects
    // gScratch = Mix_LoadWAV( "KokuhakuNoYoru-Ayasa-5922559.wav" );
    // if( gScratch == NULL )
    // {
    //     printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    //     success = false;
    // }
    
    gHigh = Mix_LoadWAV( "ringtonemakerwiz.com-2022-05-20.wav" );
    if( gHigh == NULL )
    {
        printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    
return success;

    

}
void close()
{
    

    //Free the sound effects
    Mix_FreeChunk( gScratch );
    Mix_FreeChunk( gHigh );
   
    gScratch = NULL;
    gHigh = NULL;
   
    
    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
//giai phong be mat
SDL_FreeSurface(load_image);
load_image = NULL;

//huy cua so
SDL_DestroyWindow(window);
window = NULL;

//thoat khoi SDL
Mix_Quit();
IMG_Quit();
SDL_Quit();
}

#endif